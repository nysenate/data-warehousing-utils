<?php
/**
 * @file CurrentDate.php
 */

namespace NYS_Census\Service\CensusApi;

use NYS_Census\Service\CensusApi;

class CurrentDate extends CensusApi {
  protected $api_get = ['RESP_DATE'];
  protected $api_for = ['STATE:36'];
  protected $api_in = [];
}