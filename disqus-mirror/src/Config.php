<?php

namespace DisqusImporter;

use GetOpt\GetOpt;
use DisqusImporter\Commands;

/**
 * Class Config
 * Acts as a centralized repository of all application configuration and
 * parameters passed from the command line.
 *
 * Application configuration is (by default) found in app_config.json.
 * See app_config.json.example for more instruction on the parameters.
 * It is mostly used to configure the GetOpt package, which handles
 * parsing command line parameters.
 *
 * Config will also attempt to discover parameter values in config.ini
 * (default file).  Any values found in the INI will be considered as a
 * "default state" for the application.  Parameters passed on command
 * line will override them.
 *
 * @package DisqusImporter
 */
class Config {

  /**
   * @var \DisqusImporter\Config null
   */
  protected static $instance = NULL;

  /**
   * @var \DisqusImporter\Logger
   */
  protected $logger = NULL;

  /**
   * @var \GetOpt\GetOpt
   */
  protected $getopt;

  /**
   * @var array
   * Used to hold custom-defined/runtime configuration points (i.e.,
   * those not populated through INI or command-line parameters).
   */
  protected $settings = [];

  /**
   * Config constructor.
   *
   * @param array $args @deprecated unused for now
   * TODO: do we really need args here?
   */
  protected function __construct($args = NULL) {
    // Read the app config file
    $this->configGetOpt();

    // Instantiate GetOpt
    // Add all config.ini values to GetOpt options
    // Process passed arguments
    // Process command line
    $this->getopt->process();
    // Get config resolved.
    $this->readAppConfig();

    // TODO: last two params should be in app_config/ini
    $this->logger = Logger::getInstance($this->error_log_level, $this->error_log, '.', NYSS_LOG_MODE_TEE);
  }

  /**
   * Configure the getopt object.  This will instantiate the object
   * and populate the commands, options, and operands from the JSON
   * config file.
   *
   * @param bool $create
   * Indicates if a new GetOpt object should be created.
   *
   * @param string $app_cfg
   * The path/name of the config file to be read.
   */
  public function configGetOpt($create = TRUE, $app_cfg = 'app_config.json') {
    if ($create || !$this->getopt) {
      $this->getopt = $this->createGetOpt();
    }
    $app_config = $this->readAppConfig($app_cfg);
    foreach (['Commands', 'Options', 'Operands'] as $val) {
      $this->{"populate$val"}($app_config->{strtolower($val)});
    }
    $this->getopt->process();
  }

  /**
   * Helper method to instantiate a new GetOpt object.
   *
   * @param null $options
   * @param array $settings
   *
   * @return \GetOpt\GetOpt
   */
  public function createGetOpt($options = NULL, $settings = []) {
    return new GetOpt($options, $settings);
  }

  /**
   * Reads the application's config file, which must be a well-formatted
   * JSON object.
   *
   * @param string $filename
   *
   * @return object
   */
  public function readAppConfig($filename = 'app_config.json') {
    $cfg = json_decode(file_get_contents($filename));
    if (!$cfg) {
      $cfg = (object) [];
    }
    foreach (['commands', 'options', 'operands'] as $val) {
      $cfg->{$val} = isset($cfg->{$val}) ? $cfg->{$val} : (object) [];
    }
    return $cfg;
  }

  /**
   * Singleton pattern.
   *
   * @param array $args
   *
   * @return \DisqusImporter\Config
   */
  public static function getInstance($args = NULL) {
    if (!static::$instance) {
      static::$instance = new static($args);
    }
    return static::$instance;
  }

  /**
   * Magic method for retrieving values by direct reference.
   *
   * @param $name
   *
   * @return mixed|null
   */
  public function __get($name) {
    return $this->settings[$name] ?? NULL;
  }

  /**
   * Magic method for setting values by direct reference.
   *
   * @param $name
   * @param $value
   */
  public function __set($name, $value) {
    $this->settings[$name] = $value;
  }

  /**
   * Populates the GetOpt object with commands read from the application's
   * config file.
   *
   * @param Object $object
   * The JSON-decoded object representing the commands for this application.
   * (i.e., $json->commands)
   */
  public function populateCommands($object = NULL) {
    if (is_object($object)) {
      foreach ($object as $key => $val) {
        $cmd = Commands\CommandTemplate::createFromTemplate($key, $val);
        $this->getopt->addCommand($cmd);
      }
    }
  }

  /**
   * Populates the GetOpt object with options read from the application's
   * config file.
   *
   * @param Object $object
   * The JSON-decoded object representing the options for this application.
   * (i.e., $json->options)
   */
  public function populateOptions($object) {

  }

  /**
   * Populates the GetOpt object with operands read from the application's
   * config file.
   *
   * @param Object $object
   * The JSON-decoded object representing the operands for this application.
   * (i.e., $json->operands)
   */
  public function populateOperands($object) {

  }

  /**
   * Wrapper/helper function to expose logging facilities through Config.
   * @param $msg
   * @param int $lvl
   */
  public function log($msg, $lvl = NYSS_LOG_LEVEL_INFO) {
    $this->logger->log($msg, $lvl);
  }
}