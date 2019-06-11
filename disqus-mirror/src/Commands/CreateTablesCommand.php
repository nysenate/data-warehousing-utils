<?php

namespace DisqusImporter\Commands;

use DisqusImporter\Config;
use DisqusImporter\Logger;

class CreateTablesCommand extends CommandTemplate {

	public function handle() {
		$config = Config::getInstance();

		$filename = $this->getOperand('sqlfile');

		$config->log("Running SQL file '$filename'", Logger::NYSS_LOG_LEVEL_INFO);

		// Should not run multi-statement queries, so explode the contents and run
		// them one by one.
		$sql     = array_filter(explode(';', @file_get_contents($filename)));
		$total   = 0;
		$success = 0;
		try {
			foreach ($sql as $statement) {
				$q = trim($statement);
				if ($q) {
					$total++;
					if (db_query($statement)) {
						$success++;
					}
				}
			}
		}
		catch (\Exception $e) {
			$config->log("Create tables task failed: " . $e->getMessage(), Logger::NYSS_LOG_LEVEL_FATAL);
		} finally {
			$msg = "SQL run " . ($success === $total ? 'complete' : 'failed') .
				", $success of $total queries processed.";
			$config->log($msg, Logger::NYSS_LOG_LEVEL_INFO);
		}

		return $msg . "\n";
	}
}