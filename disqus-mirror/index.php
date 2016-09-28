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
$logger->log("Runtime Config:\n".var_export($config,1), NYSS_LOG_LEVEL_DEBUG);

// necessary setup for Drupal's DAL
$databases['default']['default'] = array(
  'driver' => 'mysql',
  'database' => $config->db_name,
  'username' => $config->db_user,
  'password' => $config->db_pass,
  'host'     => 'localhost',
);
db_query("set names utf8mb4;");

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

