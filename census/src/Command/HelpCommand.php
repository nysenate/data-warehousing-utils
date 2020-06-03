<?php

namespace NYS_Census\Command;

use NYS_Census\Config;
use NYS_Census\Logger;

/**
 * Class HelpCommand
 *
 * @package NYS_Census\Command
 */
class HelpCommand extends CommandBase {

  /**
   * Shows the application's compiled help.
   *
   * @return string
   */
  public function handle() {
		$cfg = Config::getInstance();
		$cfg->log("Rendering help text and exiting", Logger::NYSS_LOG_LEVEL_INFO);
		return $cfg->renderHelp();
	}
}