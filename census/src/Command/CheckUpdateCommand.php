<?php
/**
 * @file CheckUpdateCommand.php
 */

namespace NYS_Census\Command;

use NYS_Census\Config;
use NYS_Census\Helper\DatabaseHelper;
use NYS_Census\Logger;
use NYS_Census\Service\CensusApi;

/**
 * Class CheckUpdateCommand
 *
 * @package NYS_Census\Command
 */
class CheckUpdateCommand extends CommandBase {

  /**
   * @return int
   * @throws \Symfony\Contracts\HttpClient\Exception\ClientExceptionInterface
   * @throws \Symfony\Contracts\HttpClient\Exception\RedirectionExceptionInterface
   * @throws \Symfony\Contracts\HttpClient\Exception\ServerExceptionInterface
   * @throws \Symfony\Contracts\HttpClient\Exception\TransportExceptionInterface
   */
  public function handle() {
    // Get a reference to
    $cfg = Config::getInstance();

    // Get the date of the last update from the database.
    $last_update = (int) DatabaseHelper::fetchParam('last_update');

    // Get the current timestamp from census API.
    $api = new CensusApi\CurrentDate();
    $result = $api->run();
    $content = CensusApi::associateArray($result->getContent(FALSE));
    $current = strtotime($content[0]['RESP_DATE'] ?? 0);

    // If current date could not be retrieved, post a warning.
    if (!$current) {
      $cfg->log("Could not retrieve current date from API", Logger::NYSS_LOG_LEVEL_WARN);
      $ret = 2;
    }
    // Otherwise, indicate 0 for no update, or 1 for update available
    else {
      $msg = "Current:" . date("Y-m-d", $current) . ', ' .
        "last:" . date("Y-m-d", $last_update);
      $cfg->log($msg, Logger::NYSS_LOG_LEVEL_INFO);
      $ret = ($current <= $last_update) ? 0 : 1;
    }

    return $ret;
  }
}
