<?php
/**
 * @file CensusApi.php
 */

namespace NYS_Census\Service;

use NYS_Census\Config;
use NYS_Census\Logger;
use Symfony\Component\HttpClient\HttpClient;

/**
 * Class CensusApi
 *
 * @package NYS_Census\Service
 */
abstract class CensusApi {

  /**
   * @var HttpClient
   */
  protected static $client = NULL;

  /**
   * @var string
   */
  private static $default_url = 'https://api.census.gov/data/2020/dec/responserate';

  /**
   * The next three properties should be set by child classes to configure
   * the parameters of its particular call.
   */

  /**
   * An array of field names to include in the request.  E.g.,
   * ['RESP_DATE', 'COUNTY', 'COUSUB', 'CRRALL']
   *
   * @var string[]
   */
  protected $api_get = [];

  /**
   * An array of 'for' terms, e.g., ['TRACT:*']
   *
   * @var string[]
   */
  protected $api_for = [];

  /**
   * An array of 'in' terms, e.g., ['STATE:36']
   * @var string[]
   */
  protected $api_in = [];

  /**
   * @var string
   */
  private $api_key = '';

  /**
   * @var string
   */
  private $api_url = '';

  /**
   * CensusApi constructor.
   *
   * @param null $api_key
   */
  public function __construct($api_key = NULL, $api_url = NULL) {
    if (!$api_key) {
      $api_key = Config::getInstance()->api_key;
    }
    $this->api_key = $api_key;

    if (!$api_url) {
      $api_url = Config::getInstance()->api_url ?? self::$default_url;
    }
    $this->api_url = $api_url;
  }

  /**
   * Given a JSON source array, in which the first element is an
   * array of header labels, returns an associative array with
   * the header row as keys.
   *
   * @param string $source JSON source
   *
   * @return array[]
   */
  public static function associateArray($source = '') {
    $ret = [];
    if ($array = json_decode($source)) {
      $headers = array_shift($array);
      $ret = array_map(
        function ($v) use ($headers) {
          return array_combine($headers, $v);
        },
        $array
      );
    }
    return $ret;
  }

  /**
   * Runs the API call.
   *
   * @return \Symfony\Contracts\HttpClient\ResponseInterface
   *
   * @throws \Symfony\Contracts\HttpClient\Exception\ClientExceptionInterface
   * @throws \Symfony\Contracts\HttpClient\Exception\RedirectionExceptionInterface
   * @throws \Symfony\Contracts\HttpClient\Exception\ServerExceptionInterface
   * @throws \Symfony\Contracts\HttpClient\Exception\TransportExceptionInterface
   */
  public function run() {
    // Instantiate HTTP client
    $client = $this->getClient();

    // Get query parameters
    $query = $this->getQuery();
    Config::getInstance()->log("Calling API with query:\n" . var_export($query,1), Logger::NYSS_LOG_LEVEL_DEBUG);

    // Make the call
    $result = $client->request('GET', $this->api_url, ['query' => $query]);

    // Report, if not a 200 response.
    Config::getInstance()
      ->log("API call status code: " . $result->getStatusCode(), Logger::NYSS_LOG_LEVEL_DEBUG);
    if ($result->getStatusCode() !== 200) {
      Config::getInstance()
        ->log("API: " . $result->getContent(FALSE), Logger::NYSS_LOG_LEVEL_ERROR);
    }

    // Return the response.
    return $result;
  }

  /**
   * Instantiates an HTTPClient object.
   *
   * @param bool $refresh Force creation of a new object.
   *
   * @return \Symfony\Component\HttpClient\HttpClient
   */
  protected function getClient($refresh = FALSE) {
    if (!static::$client || $refresh) {
      static::$client = HttpClient::create();
    }
    return static::$client;
  }

  /**
   * Builds the query parameter array for a call to the API.
   * Additional $params can be passed in to override class-level
   * instructions.  The API key, if present, is always written last.
   *
   * @param array $params
   *
   * @return array
   */
  protected function getQuery($params = []) {
    // Initialize the return.
    $ret = [];

    // Add the known class-level parameters.
    foreach (['get', 'for', 'in'] as $val) {
      $ret[$val] = implode(',', $this->{"api_$val"});
    }

    // Add any custom parameters passed in.
    foreach ($params as $key => $val) {
      $ret[$key] = $val;
    }

    // Force the API key to the config value.  If one doesn't exist,
    // post a warning.
    if ($this->api_key) {
      $ret['key'] = $this->api_key;
    }
    else {
      Config::getInstance()->log("No API key is configured.  See config.ini.", Logger::NYSS_LOG_LEVEL_WARN);
    }

    // Return a *filtered* array.  The API really really dislikes
    // empty parameter fields.
    return array_filter($ret);
  }

}