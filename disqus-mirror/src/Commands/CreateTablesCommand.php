<?php

namespace DisqusImporter\Commands;

use DisqusImporter\OldConfig;
use GetOpt\GetOpt;
use GetOpt\Command;
use GetOpt\Operand;

class CreateTablesCommand extends CommandTemplate {
	public function handle() {
		$filename = $this->getOperand('sqlfile');

	  $this->log("Creating tables based on SQL in file: {$filename}", NYSS_LOG_LEVEL_INFO);

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
		  $this->log("Create tables task failed: " . $e->getMessage(), NYSS_LOG_LEVEL_FATAL);
		  $result = FALSE;
	  } finally {
		  if ($result) {
			  $msg = "Tables successfully created from file {$filename}.";
			  $this->log($msg, NYSS_LOG_LEVEL_INFO);
			  echo $msg."\n";
		  }
	  }
	  exit(!$result);
  }
}