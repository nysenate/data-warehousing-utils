<?php
/**
 * @file GetStatData.php
 */

namespace NYS_Census\Service\CensusApi;

class GetStatData extends \NYS_Census\Service\CensusApi {

  protected $api_get = [
    'GEO_ID',
    'RESP_DATE',
    'CINTMIN',
    'CINTAVG',
    'CINTMED',
    'DMED',
    'DRRALL',
    'DMIN',
    'CMIN',
    'CAVG',
    'CRRINT',
    'CMED',
    'CINTMAX',
    'DMAX',
    'CRRALL',
    'DINTMIN',
    'DINTAVG',
    'DINTMED',
    'SUMLEVEL',
    'DAVG',
    'DINTMAX',
    'DRRINT',
    'CMAX',
  ];

  protected $api_for = [];

  protected $api_in = [];


}