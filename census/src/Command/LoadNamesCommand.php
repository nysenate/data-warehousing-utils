<?php
/**
 * @file LoadNamesCommand.php
 */

namespace NYS_Census\Command;

use NYS_Census\Config;
use NYS_Census\Helper\DatabaseHelper;
use NYS_Census\Logger;
use NYS_Census\Service\CensusApi;
use NYS_Census\Service\CensusApi\GetNameData;

/**
 * Class LoadNamesCommand
 *
 * @package NYS_Census\Command
 */
class LoadNamesCommand extends CommandBase {

  /**
   * Loads the mostly-static name data from the Census.  Returns
   * the number of rows uploaded.
   *
   * @return int
   * @throws \Symfony\Contracts\HttpClient\Exception\ClientExceptionInterface
   * @throws \Symfony\Contracts\HttpClient\Exception\RedirectionExceptionInterface
   * @throws \Symfony\Contracts\HttpClient\Exception\ServerExceptionInterface
   * @throws \Symfony\Contracts\HttpClient\Exception\TransportExceptionInterface
   */
  public function handle() {
    // Get and run the census API call.
    $api = new GetNameData();
    $response = $api->run();

    // Transform the return into an associative array
    $array = CensusApi::associateArray($response->getContent(FALSE));

    // Upload the data and report.
    $ret = DatabaseHelper::uploadData('name_data', $array);
    Config::getInstance()->log("$ret rows uploaded for name_data", Logger::NYSS_LOG_LEVEL_INFO);

    return $ret;
  }
}