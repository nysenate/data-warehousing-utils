<?php
/**
 * Test app to hit disqus API and query comments/threads
 *
 */

// all required files go here
require_once 'lib.require.inc';

// instantiate the configuration and the logger
try {
  $config = Config::getInstance();
} catch (Exception $e) {
  die("FATAL: " . $e->getMessage() . "\n");
}
$logger = Logger::getInstance($config->error_log_level, $config->error_log, '.', NYSS_LOG_MODE_TEE);

// debug log for runtime config
$logger->log("Runtime Config:\n".var_export($config->getOptions(),1), NYSS_LOG_LEVEL_DEBUG);

// necessary setup for Drupal's DAL
$databases['default']['default'] = array(
  'driver' => 'mysql',
  'database' => $config->db_name,
  'username' => $config->db_user,
  'password' => $config->db_pass,
  'host'     => $config->db_host,
  'port'     => $config->db_port
);

// This will a) ensure the connection can be made, and b) ensure proper encoding
// is maintained.
try {
  $set_names_query = db_query("set names utf8mb4;");
} catch (Exception $e) {
  $logger->log("Could not run 'SET NAMES' on connection! (".$e->getMessage().")", NYSS_LOG_LEVEL_FATAL);
  exit(1);
}

// If the create tables is detected, run the SQL file and leave.
if ($config->create_tables) {
  $logger->log("Creating tables based on SQL in file: {$config->create_tables}", NYSS_LOG_LEVEL_DEBUG);

  // Should not run multi-statement queries, so explode the contents and run
  // them one by one.
  $sql = explode(';', @file_get_contents($config->create_tables));
  $result = TRUE;
  try {
    foreach ($sql as $statement) {
      $q = trim($statement);
      if ($q) {
        $result &= db_query($statement);
      }
    }
  } catch (Exception $e) {
    $logger->log("Create tables task failed: " . $e->getMessage(), NYSS_LOG_LEVEL_FATAL);
    $result = FALSE;
  } finally {
    if ($result) {
      $msg = "Tables successfully created from file {$config->create_tables}.";
      $logger->log($msg, NYSS_LOG_LEVEL_INFO);
      echo $msg."\n";
    }
  }
  exit(!$result);
}

// instantiate Disqus API
$disqus = new DisqusAPI($config->api_secret);

// run categories
$a = new API_Object_Categories($disqus);
$a->executeSearch();

// run threads
$b = new API_Object_Threads($disqus);
$b->executeSearch();

// run posts
$c = new API_Object_Posts($disqus);
$c->executeSearch();

