<?php
/**
 * @file UpdateCommand.php
 */

namespace NYS_Census\Command;

use NYS_Census\Config;
use NYS_Census\Helper\DatabaseHelper;
use NYS_Census\Logger;
use NYS_Census\Service\CensusApi;
use NYS_Census\Service\CensusApi\GetStatData;

/**
 * Class UpdateCommand
 *
 * @package NYS_Census\Command
 */
class UpdateCommand extends CommandBase {

  /**
   * Downloads and insert a new update from the census API.  Calls
   * the check-update command first to verify work needs to be done.
   * Returns 0 if no update was found, otherwise returns the number
   * of update rows found.
   *
   * @return int
   * @throws \Symfony\Contracts\HttpClient\Exception\ClientExceptionInterface
   * @throws \Symfony\Contracts\HttpClient\Exception\RedirectionExceptionInterface
   * @throws \Symfony\Contracts\HttpClient\Exception\ServerExceptionInterface
   * @throws \Symfony\Contracts\HttpClient\Exception\TransportExceptionInterface
   */
  public function handle() {
    $cfg = Config::getInstance();

    // Work only needs to be done if check-update returns 1.
    $need_update = $cfg->getCommand('check-update')->handle();
    if ($need_update === 1) {
      $cfg->log("UPDATE AVAILABLE, beginning import", Logger::NYSS_LOG_LEVEL_INFO);
      // Call the Census API for the current data
      $api = new GetStatData();
      $response = $api->run();

      // Reform the response into an associative array.
      $array = CensusApi::associateArray($response->getContent(FALSE));

      // Get the current data's submission date for reference.
      $last_update = $array[0]['RESP_DATE'] ?? 0;

      // Upload data and report.
      $ret = DatabaseHelper::uploadData('stat_data', $array);
      $cfg->log("$ret rows uploaded for stat_data", Logger::NYSS_LOG_LEVEL_INFO);

      // If work was done, set the last_update application parameter.
      if ($last_update && $ret) {
        DatabaseHelper::setParam('last_update', strtotime($last_update));
      }

      // Return number of rows uploaded
      return $ret;
    }
    // No update.  Report and exit.
    else {
      $cfg->log("NO UPDATE AVAILABLE", Logger::NYSS_LOG_LEVEL_INFO);
      return 0;
    }

  }

}