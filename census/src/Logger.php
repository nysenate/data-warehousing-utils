<?php

namespace NYS_Census;

/*
  Logger class
  Provides a logging interface, including tee to file/stdout and severity gradiations
*/


class Logger {

	/* log level constants */
	const NYSS_LOG_LEVEL_FATAL = 0;
	const NYSS_LOG_LEVEL_ERROR = 1;
	const NYSS_LOG_LEVEL_WARN  = 2;
	const NYSS_LOG_LEVEL_INFO  = 3;
	const NYSS_LOG_LEVEL_DEBUG = 4;

	/* log mode constants */
	const NYSS_LOG_MODE_FILE   = 0;
	const NYSS_LOG_MODE_STDOUT = 1;
	const NYSS_LOG_MODE_TEE    = 2;

	public static $LOG_LEVELS = [
		'FATAL' => self::NYSS_LOG_LEVEL_FATAL,
		'ERROR' => self::NYSS_LOG_LEVEL_ERROR,
		'WARN'  => self::NYSS_LOG_LEVEL_WARN,
		'INFO'  => self::NYSS_LOG_LEVEL_INFO,
		'DEBUG' => self::NYSS_LOG_LEVEL_DEBUG,
	];

	public static $LOG_LEVEL_LABELS = [
		self::NYSS_LOG_LEVEL_FATAL => 'FATAL',
		self::NYSS_LOG_LEVEL_ERROR => 'ERROR',
		self::NYSS_LOG_LEVEL_WARN  => 'WARN',
		self::NYSS_LOG_LEVEL_INFO  => 'INFO',
		self::NYSS_LOG_LEVEL_DEBUG => 'DEBUG',
	];

	private static $instance = NULL;

	private $_logfile = NULL;

	protected $logfile = '';

	// TODO: why split file name and location?
	protected $log_location = '';

	protected $log_level = self::NYSS_LOG_LEVEL_ERROR;

	protected $log_mode = self::NYSS_LOG_MODE_FILE;

	private function __construct($lvl = self::NYSS_LOG_LEVEL_ERROR, $fn = '', $loc = NULL, $mode = self::NYSS_LOG_MODE_FILE) {
		$lvl = static::$LOG_LEVELS[$lvl] ?? $lvl;
		$this->setLevel($lvl);
		$this->setMode($mode);
		$this->setLogLocation($loc, $fn);
	}

	public static function getBackTrace($most_recent = FALSE) {
		$backTrace = debug_backtrace();
		array_shift($backTrace);
		if ($most_recent) {
			return array_shift($backTrace);
		}
		$showArgs = FALSE;
		$message  = '';
		$idx      = 0;
		foreach ($backTrace as $idx => $trace) {
			$args      = [];
			$fnName    = $trace['function'] ?? NULL;
			$className = array_key_exists('class', $trace) ? ($trace['class'] . $trace['type']) : '';

			// do now show args for a few password related functions
			$skipArgs = ($className == 'DB::' && $fnName == 'connect');

			foreach ($trace['args'] as $arg) {
				if (!$showArgs || $skipArgs) {
					$args[] = '(' . gettype($arg) . ')';
					continue;
				}
				switch ($type = gettype($arg)) {
					case 'boolean':
						$args[] = $arg ? 'TRUE' : 'FALSE';
						break;
					case 'integer':
					case 'double':
						$args[] = $arg;
						break;
					case 'string':
						$args[] = '"' . (string) $arg . '"';
						break;
					case 'array':
						$args[] = '(Array:' . count($arg) . ')';
						break;
					case 'object':
						$args[] = 'Object(' . get_class($arg) . ')';
						break;
					case 'resource':
						$args[] = 'Resource';
						break;
					case 'NULL':
						$args[] = 'NULL';
						break;
					default:
						$args[] = "($type)";
						break;
				}
			}

			$message .= sprintf(
				"#%s %s(%s): %s%s(%s)\n",
				$idx,
				$trace['file'] ?? '[internal function]',
				$trace['line'] ?? '',
				$className,
				$fnName,
				implode(", ", $args)
			);
		}
		$message .= sprintf("#%s {main}\n", 1 + $idx);

		return $message;
	}

	/**
	 * @param int    $lvl
	 * @param string $fn
	 * @param null   $loc
	 * @param int    $mode
	 *
	 * @return Logger
	 */
	public static function getInstance($lvl = self::NYSS_LOG_LEVEL_ERROR, $fn = '', $loc = NULL, $mode = self::NYSS_LOG_MODE_FILE) {
		if (!static::$instance) {
			static::$instance = new static($lvl, $fn, $loc, $mode);
		}

		return static::$instance;
	}

	protected function _closeFile() {
		if ($this->_logfile) {
			@fclose($this->_logfile);
		}
		$this->_logfile = NULL;
	}

	protected function _fullLogName() {
		$fn = '';
		if ($this->logfile) {
			$fn = $this->log_location .
				(in_array(substr($this->log_location, -1), ['/', '\\']) ? '' : '/') .
				$this->logfile;
		}

		return $fn;
	}

	protected function _isUsingFile() {
		return in_array($this->log_mode, [self::NYSS_LOG_MODE_FILE, self::NYSS_LOG_MODE_TEE]);
	}

	protected function _isUsingStdout() {
		return in_array($this->log_mode, [self::NYSS_LOG_MODE_STDOUT, self::NYSS_LOG_MODE_TEE]);
	}

	protected function _openFile() {
		if ($this->_isUsingFile() && $this->logfile) {
			$fn = $this->_fullLogName();
			$this->_logfile = fopen($fn, 'a');
			if (!$this->_logfile) {
				$this->_closeFile();
				$this->logfile = '';
				$this->log("Could not open file '$fn' for writing, reverting to error_log()");
			}
		}
	}

	protected function _resolveDefaultLocation() {
    return $_SERVER['DOCUMENT_ROOT'] ?? '.';
	}

	protected function _setFile($fn) {
		$fn = (string) $fn;
		$this->logfile = $fn;
	}

	protected function _setLocation($loc) {
		$loc = (string) $loc;
		if (!$loc) {
			$loc = $this->_resolveDefaultLocation();
		}
		$this->log_location = is_dir($loc) ? $loc : '';
	}

	protected function initLog() {
		if ($this->_isUsingFile() && $this->logfile) {
			$this->_openFile();
		}
	}

	public function log($msg, $lvl = self::NYSS_LOG_LEVEL_INFO) {
		$lvl = (int) $lvl;
		if ($lvl < 0) {
			$lvl = 0;
		}
		if ($lvl <= $this->log_level) {
			$datestr  = date('Y-m-d H:i:s');
			$lvllabel = static::$LOG_LEVEL_LABELS[$lvl] ?? 'CUSTOM';
			$msg      = (string) $msg;
			$logmsg   = "[$lvllabel] $msg";
			if ($this->_isUsingStdout()) {
				echo "{$datestr} {$logmsg}\n";
			}
			if ($this->_isUsingFile()) {
				if ($this->_logfile) {
					$res = fwrite($this->_logfile, "{$datestr} {$logmsg}\n");
					if ($res === FALSE) {
						error_log("COULD NOT WRITE TO LOG FILE '" . $this->_fullLogName() . "'!");
						error_log($logmsg);
					}
				}
				else {
					error_log($logmsg);
				}
			}
		}
	}

	public function setLevel($lvl = self::NYSS_LOG_LEVEL_ERROR) {
		$lvl = (int) (static::$LOG_LEVELS[$lvl] ?? $lvl);
		if ($lvl < 1) {
			$lvl = 0;
		}
		$this->log_level = $lvl;
	}

	public function setLogFile($fn) {
		if ($fn) {
			$this->_closeFile();
			$this->logfile = $fn;
		}
		$this->initLog();
	}

	public function setLogLocation($loc, $fn) {
		$this->_setLocation($loc);
		$this->_setFile($fn);
		$this->initLog();
	}

	public function setMode($mode = self::NYSS_LOG_MODE_FILE) {
		$mode = (int) $mode;
		if (!in_array($mode, [0, 1, 2])) {
			$mode = self::NYSS_LOG_MODE_FILE;
		}
		$this->log_mode = $mode;
	}
}
