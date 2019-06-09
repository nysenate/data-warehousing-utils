<?php

namespace DisqusImporter\Commands;

use DisqusImporter\Config;
use DisqusImporter\Logger;

class CreateTablesCommand extends CommandTemplate {
	public function handle() {
		$config = Config::getInstance();

		$filename = $this->getOperand('sqlfile');

	  $config->log("Creating tables based on SQL in file: {$filename}", Logger::NYSS_LOG_LEVEL_INFO);

	  // Should not run multi-statement queries, so explode the contents and run
	  // them one by one.
	  $sql = explode(';', @file_get_contents($filename));
	  $result = TRUE;
	  try {
		  foreach ($sql as $statement) {
			  $q = trim($statement);
			  if ($q) {
				  $result &= db_query($statement);
			  }
		  }
	  } catch (\Exception $e) {
		  $config->log("Create tables task failed: " . $e->getMessage(), Logger::NYSS_LOG_LEVEL_FATAL);
		  $result = FALSE;
	  } finally {
		  if ($result) {
			  $msg = "Tables successfully created from file {$filename}.";
			  $config->log($msg, Logger::NYSS_LOG_LEVEL_INFO);
			  $result =  $msg."\n";
		  }
	  }
	  return $result;
  }
}