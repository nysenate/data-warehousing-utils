<?php
/**
 * @file GetNameData.php
 */

namespace NYS_Census\Service\CensusApi;

class GetNameData extends \NYS_Census\Service\CensusApi {

  protected $api_get = [
    'REGION',
    'STATE',
    'COUNTY',
    'COUSUB',
    'TRACT',
    'PLACE',
    'AIANHH',
    'TTRACT',
    'CD',
    'NAME',
    'GEO_ID',
  ];

  protected $api_for = [];

  protected $api_in = [];


}