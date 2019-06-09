<?php
namespace DisqusImporter;

define('ROOTDIR', __DIR__);

require_once ROOTDIR . '/vendor/autoload.php';

$config = Config::getInstance();

// debug log for runtime config
$config->log("Runtime Config:\n".var_export($config->getSettings(),1), Logger::NYSS_LOG_LEVEL_DEBUG);

// This will a) ensure the connection can be made, and b) ensure proper encoding
// is maintained.
try {
	$set_names_query = db_query("set names utf8mb4;");
} catch (\Exception $e) {
	$config->log("Could not run 'SET NAMES' on connection! (".$e->getMessage().")", Logger::NYSS_LOG_LEVEL_FATAL);
	//exit(1);
}

$command = $config->getCommand() ? $config->getCommand()->getName() : '';

if ($command == 'help' || $config->help || !$command) {
	$config->log("Rendering help text and exiting", Logger::NYSS_LOG_LEVEL_INFO);
	echo "\n" . $config->renderHelp() . "\n";
	exit();
}

$config->log("Config loaded, running command $command . . .", Logger::NYSS_LOG_LEVEL_INFO);
die("w0oT!\n" . var_export($config->getSettings(),1));






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

