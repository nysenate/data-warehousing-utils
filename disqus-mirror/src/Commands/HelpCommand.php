<?php

namespace DisqusImporter\Commands;

use DisqusImporter\Config;
use DisqusImporter\Logger;

class HelpCommand extends CommandTemplate {
	public function handle() {
		$config = Config::getInstance();
		$config->log("Rendering help text and exiting", Logger::NYSS_LOG_LEVEL_INFO);
		return $config->renderHelp();
	}
}