<?php

namespace DisqusImporter\APIObjects;

use DisqusImporter\Logger;
use DisqusImporter\Config;

abstract class APIObjectTemplate {

	// special log level for logging API returns
	const NYSS_LOG_LEVEL_DEBUGAPI = 5;

	protected static $table_name;

	protected static $object_name;

	protected static $object_action;

	protected static $field_map;

	protected static $mangle_map;

	protected $config;

	protected $disqus;

	public static function createFromTemplate($name, $disqus) {
		$class = __NAMESPACE__ . "\\{$name}APIObject";
		if (!class_exists($class)) {
			throw new RuntimeException("Could not find APIObject class for '$name' (class '$class').");
		}
		/** @var APIObjectTemplate $obj */
		$obj = new $class($disqus);
		return $obj;
	}

	public function __construct($disqus) {
		$this->config = Config::getInstance();
		$this->disqus = $disqus;
		$this->log = Logger::getInstance();
	}

	public static function insertFromData($data) {
		// Get a Logger instance
		$log = Logger::getInstance();

		$log->log("insertFromData() called in " . get_called_class(), Logger::NYSS_LOG_LEVEL_DEBUG);
		$log->log("passed data = \n" . var_export($data, 1), self::NYSS_LOG_LEVEL_DEBUGAPI);

		$fields = [];

		// Build the array used for the db_insert() call.  Note that certain fields
		// may need special handling due to how they get translated by the DAL.  The
		// $mangle_map array references these requirements.
		foreach (static::$field_map as $orig => $dest) {
			$data_point = property_exists($data, $orig) ? $data->{$orig} : NULL;
			switch (static::$mangle_map[$orig] ?? $orig) {
				case 'boolean':
					$fields[$dest] = (int) ((boolean) $data_point);
					break;
				case 'string':
					$fields[$dest] = (string) $data_point;
					break;
				case 'integer':
					$fields[$dest] = intval($data_point);
					break;
				case 'float':
					$fields[$dest] = floatval($data_point);
					break;
				default:
					$fields[$dest] = $data_point;
					break;
			}
		}
		$log->log("Final fields for INSERT:\n" . var_export($fields, 1), Logger::NYSS_LOG_LEVEL_DEBUG);

		// Insert the new record.
		try {
			$insert_id = db_insert(static::$table_name)
				->fields($fields)
				->execute();
		}
		catch (\Exception $e) {
			$log->log("Exception generated during INSERT in " . get_called_class() .
				":\nCode: " . var_export($e->getCode(), 1) . "\nMessage: " . var_export($e->getMessage(), 1),
				Logger::NYSS_LOG_LEVEL_ERROR);

			return NULL;
		}
		$log->log("Inserted " . static::$object_name . " as id={$insert_id}", Logger::NYSS_LOG_LEVEL_INFO);

		return $insert_id;
	}

	protected function preInsert(&$data) {
	}

	protected function postInsert($insert_id, $data) {
	}

	protected function getCursorName() {
		return static::$object_name . '_' . static::$object_action . '_cursor';
	}

	protected function setCursor($cursor) {
		if ($cursor) {
			try {
				$ret = db_merge('settings')
					->key(['name' => static::getCursorName()])
					->fields(['value' => serialize($cursor)])
					->execute();
			}
			catch (\Exception $e) {
				$this->config->log("Exception generated during cursor MERGE:\nCode: " . var_export($e->getCode(), 1) . "\nMessage: " . var_export($e->getMessage(), 1), Logger::NYSS_LOG_LEVEL_ERROR);

				return NULL;
			}
			$this->config->log("setCursor set value.  ret=" . var_export($ret, 1), Logger::NYSS_LOG_LEVEL_DEBUG);
		}
	}

	protected function fetchCursor() {
		// Try to read cursor information from the db.
		try {
			$cursor_value = db_select('settings', 's')
				->fields('s', ['value'])
				->condition('name', static::getCursorName())
				->execute()
				->fetchField();
		}
		catch (\Exception $e) {
			$this->config->log("Exception generated during cursor SELECT:\nCode: " . var_export($e->getCode(), 1) . "\nMessage: " . var_export($e->getMessage(), 1), Logger::NYSS_LOG_LEVEL_ERROR);

			return NULL;
		}
		$this->config->log("fetchCursor found " . var_export($cursor_value, 1), Logger::NYSS_LOG_LEVEL_DEBUG);

		// Set the return.
		$ret = $cursor_value
			? unserialize($cursor_value)
			: (object) ['hasNext' => FALSE, 'next' => NULL];

		return $ret;
	}

	public function executeSearch() {
		$this->config->log("Executing API search for: " . get_called_class(), Logger::NYSS_LOG_LEVEL_INFO);

		// Initialize the cursor.
		$cursor = $this->fetchCursor();
		if (!is_object($cursor)) {
			$this->config->log("Aborting - failed to find cursor for: " . get_called_class(), Logger::NYSS_LOG_LEVEL_ERROR);

			return NULL;
		}

		// Repeat this loop until the cursor comes back empty.
		$count = 0;
		do {
			// Generate options for this API call.
			$req_opts = [
				'forum' => $this->config->forum,
				'order' => 'asc',
				'limit' => 100,
			];
			if ($cursor->next) {
				$req_opts['cursor'] = $cursor->next;
			}
			$this->config->log("Final request options:\n" . var_export($req_opts, 1), Logger::NYSS_LOG_LEVEL_DEBUG);

			// Execute the call using the established Disqus object.
			$retry = 0;
			$ret   = NULL;
			do {
				try {
					$this->config->log("Attempting call to Disqus API " . static::$object_name . ":" . static::$object_action, Logger::NYSS_LOG_LEVEL_DEBUG);
					$ret = $this->disqus->{static::$object_name}->{static::$object_action}($req_opts);
				}
				catch (\Exception $e) {
					$this->config->log("Exception generated during API call:\nCode: " . var_export($e->getCode(), 1) . "\nMessage: " . var_export($e->getMessage(), 1), Logger::NYSS_LOG_LEVEL_ERROR);
				}
				$retry++;
				$this->config->log("Full API return:\n" . var_export($ret, 1), self::NYSS_LOG_LEVEL_DEBUGAPI);
			} while ($retry < 5 && is_null($ret));
			if (is_null($ret)) {
				$this->config->log("Aborting - API call to Disqus did not return.", Logger::NYSS_LOG_LEVEL_ERROR);

				return NULL;
			}

			$this->config->log("Found " . count($ret) . " returns", Logger::NYSS_LOG_LEVEL_INFO);

			// Get the most recent cursor returned.
			$cursor = \DisqusAPICursor::getCursor();
			$this->config->log("Request cursor object:\n" . var_export($cursor, 1), Logger::NYSS_LOG_LEVEL_DEBUG);

			// Process the records from the API call.
			foreach ($ret as $index => &$data) {
				$this->config->log("Processing " . static::$object_name . " id={$data->id}", Logger::NYSS_LOG_LEVEL_INFO);
				// For each record, check to make sure this object has not already been inserted.
				// Every object has an ID generated by Disqus.
				try {
					$exists = db_select(static::$table_name)
						->condition(static::$field_map['id'], $data->id)
						->countQuery()
						->execute()
						->fetchField();
					$this->config->log(" .. (check for existing found $exists)", Logger::NYSS_LOG_LEVEL_INFO);
				}
				catch (\Exception $e) {
					$this->config->log("Exception generated during record search:\nCode: " . var_export($e->getCode(), 1) . "\nMessage: " . var_export($e->getMessage(), 1), Logger::NYSS_LOG_LEVEL_ERROR);
					continue;
				}

				// If the object does not exist, insert it.
				if (!$exists) {
					$this->config->log("Generating INSERT", Logger::NYSS_LOG_LEVEL_DEBUG);

					// Call the preInsert() method so children can do special stuff.
					$this->preInsert($data);

					try {
						$insert_id = static::insertFromData($data);
					}
					catch (\Exception $e) {
						$this->config->log("Exception generated during record INSERT:\nCode: " . var_export($e->getCode(), 1) . "\nMessage: " . var_export($e->getMessage(), 1), Logger::NYSS_LOG_LEVEL_ERROR);
						$insert_id = 0;
					}

					// Call the postInsert() method so children can do special stuff.
					$this->postInsert($insert_id, $data);
				}
				$this->config->log("Done processing " . static::$object_name . " {$data->id}", Logger::NYSS_LOG_LEVEL_DEBUG);
			}
			$this->config->log("Done processing request, cursor->hasNext = " . var_export($cursor->hasNext, 1), Logger::NYSS_LOG_LEVEL_DEBUG);

			// Save the current cursor to retain "last read" status
			$this->setCursor($cursor);
			$count++;
		} while ($cursor->hasNext);
		$this->config->log("Finished executing API search for: " . get_called_class(), Logger::NYSS_LOG_LEVEL_INFO);
	}
}
