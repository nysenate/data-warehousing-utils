<?php

namespace DisqusImporter;

use GetOpt\GetOpt;
use DisqusImporter\Commands;
use GetOpt\Option;

// TODO: need to move this into PSR-4, maybe a different package?
// Drupal's MySQL DAL
require_once ROOTDIR . '/database/database.inc';

/**
 * Class Config
 * Acts as a centralized repository of all application configuration and
 * parameters passed from the command line.
 *
 * Application configuration is (by default) found in app_config.json.
 * See app_config.json.example for more instruction on the parameters.
 * It is mostly used to configure the GetOpt package, which handles
 * parsing command line parameters.
 *
 * Config will also attempt to discover parameter values in config.ini
 * (default file).  Any values found in the INI will be considered as a
 * "default state" for the application.  Parameters passed on command
 * line will override them.
 *
 * @package DisqusImporter
 */
class Config {

	/**
	 * @var \DisqusImporter\Config null
	 */
	protected static $instance = NULL;

	/**
	 * @var \DisqusImporter\Logger
	 */
	protected $logger = NULL;

	/**
	 * @var \GetOpt\GetOpt
	 */
	protected $getopt;

	/**
	 * @var array
	 * Used to hold custom-defined/runtime configuration points (i.e.,
	 * those not populated through INI or command-line parameters).
	 */
	protected $settings = [];

	/**
	 * Config constructor.
	 *
	 * @param array $args @deprecated unused for now
	 *                    TODO: do we really need args here?
	 */
	protected function __construct($args = NULL) {
		// Do the needfuls to configure the GetOpt object.
		$this->configGetOpt();

		// TODO: last two params should be in app_config/ini
		$this->logger = Logger::getInstance($this->{'error-log-level'}, $this->{'error-log'}, '.', Logger::NYSS_LOG_MODE_TEE);

		// TODO: need a PSR-4 DAL package.  Until then, this is da way.
		global $databases;
		$databases['default']['default'] = [
			'driver'   => 'mysql',
			'database' => $this->db_name,
			'username' => $this->db_user,
			'password' => $this->db_pass,
			'host'     => $this->db_host,
			'port'     => $this->db_port,
		];
	}

	/**
	 * Configure the getopt object.  This will instantiate the object
	 * and populate the commands, options, and operands from the JSON
	 * config file.
	 *
	 * @param bool   $create
	 * Indicates if a new GetOpt object should be created.
	 *
	 * @param string $app_cfg
	 * The path/name of the config file to be read.
	 */
	public function configGetOpt($create = TRUE, $app_cfg = 'app_config.json') {
		// Create the GetOpt object
		if ($create || !$this->getopt) {
			$this->getopt = $this->createGetOpt();
		}

		// Read the configuration file.
		$app_config = $this->readAppConfig($app_cfg);

		// Populate GetOpt with the config metadata.
		foreach (['Commands', 'Options', 'Operands'] as $val) {
			$this->{"populate$val"}($app_config->{strtolower($val)});
		}

		// The "config-file" option could appear on the command line, so we
		// need to do a preliminary process to make sure we get it.
		$this->getopt->process();

		// Set any app config items found in the file.
		if ($cfg_file = $this->getopt->getOption('config-file')) {
			$this->populateINI($cfg_file);
		}

		// Populate the easy-access property.
		$this->settings = $this->getopt->getOptions();
	}

	/**
	 * Helper method to instantiate a new GetOpt object.
	 *
	 * @param null  $options
	 * @param array $settings
	 *
	 * @return \GetOpt\GetOpt
	 */
	public function createGetOpt($options = NULL, $settings = []) {
		return new GetOpt($options, $settings);
	}

	/**
	 * Reads the application's config file, which must be a well-formatted
	 * JSON object.
	 *
	 * @param string $filename
	 *
	 * @return \stdClass
	 */
	public function readAppConfig($filename = 'app_config.json') {
		$cfg = json_decode(file_get_contents($filename));
		if (!$cfg) {
			$cfg = (object) [];
		}
		foreach (['commands', 'options', 'operands', 'config'] as $val) {
			$cfg->{$val} = isset($cfg->{$val}) ? $cfg->{$val} : (object) [];
		}

		return $cfg;
	}

	/**
	 * Singleton pattern.
	 *
	 * @param array $args
	 *
	 * @return \DisqusImporter\Config
	 */
	public static function getInstance($args = NULL) {
		if (!static::$instance) {
			static::$instance = new static($args);
		}

		return static::$instance;
	}

	/**
	 * Magic method for retrieving values by direct reference.
	 *
	 * @param $name
	 *
	 * @return mixed|null
	 */
	public function __get($name) {
		$name = str_replace('_', '-', $name);

		return $this->settings[$name] ?? NULL;
	}

	/**
	 * Magic method for setting values by direct reference.
	 *
	 * @param $name
	 * @param $value
	 */
	public function __set($name, $value) {
		$name = str_replace('_', '-', $name);
		$this->settings[$name] = $value;
	}

	/**
	 * Populates the GetOpt object with commands read from the application's
	 * config file.
	 *
	 * @param \stdClass $object
	 * The JSON-decoded object representing the commands for this application.
	 * (i.e., $json->commands)
	 */
	public function populateCommands($object = NULL) {
		$help_cmd = (object) [
			'description'       => "Print help text and exit",
			'short_description' => "Print help text",
		];
		$cmd      = Commands\CommandTemplate::createFromTemplate('help', $help_cmd);
		$this->getopt->addCommand($cmd);
		if (is_object($object)) {
			foreach ($object as $key => $val) {
				$cmd = Commands\CommandTemplate::createFromTemplate($key, $val);
				$this->getopt->addCommand($cmd);
			}
		}
	}

	/**
	 * Populates the GetOpt object with options read from the application's
	 * config file.
	 *
	 * @param \stdClass $object
	 * The JSON-decoded object representing the options for this application.
	 * (i.e., $json->options)
	 */
	public function populateOptions($object) {
		if (is_object($object)) {
			foreach ($object as $key => $val) {
				$short     = $val->short ?? NULL;
				$mode_name = strtoupper($val->mode) . "_ARGUMENT";
				$mode      = defined("\GetOpt\GetOpt::$mode_name")
					? constant("\GetOpt\GetOpt::{$mode_name}")
					: GetOpt::NO_ARGUMENT;
				$opt       = Option::create($short, $key, $mode);
				if (isset($val->default)) {
					$opt->setDefaultValue($val->default ?? NULL);
				}
				if (isset($val->description)) {
					$opt->setDescription($val->description ?? '');
				}
				$this->getopt->addOption($opt);
			}
		}
	}

	/**
	 * Populates the GetOpt object with operands read from the application's
	 * config file.
	 *
	 * @param \stdClass $object
	 * The JSON-decoded object representing the operands for this application.
	 * (i.e., $json->operands)
	 */
	public function populateOperands($object) {

	}

	public function populateINI($cfg_file) {
		$ini = @parse_ini_file($cfg_file);
		if ($ini) {
			foreach ($ini as $key => $val) {
				$key = str_replace('_', '-', $key);
				// Don't allow the config file to reset the config_file option.
				if ($key !== 'config-file' && $key !== 'c') {
				  // Set the default value so command line can override it.
					$this->getopt->getOption($key, TRUE)->setDefaultValue($val);
				}
			}
		}
		else {
			echo "WARN: Config file '{$cfg_file}' is missing or blank!  Current config may be incorrect.\n";
		}
	}

	/**
	 * Wrapper/helper function to expose logging facilities through Config.
	 *
	 * @param     $msg
	 * @param int $lvl
	 */
	public function log($msg, $lvl = Logger::NYSS_LOG_LEVEL_INFO) {
		$this->logger->log($msg, $lvl);
	}

	public function getSettings() {
		return $this->settings;
	}

	public function getCommand($name = NULL) {
		return $this->getopt->getCommand($name);
	}

	public function renderHelp() {
		return $this->getopt->getHelpText();
	}
}