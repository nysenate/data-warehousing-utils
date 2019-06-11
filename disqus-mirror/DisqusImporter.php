#!/usr/bin/php
<?php
namespace DisqusImporter;

use DisqusImporter\APIObjects\CategoriesAPIObject;

define('ROOTDIR', __DIR__);

require_once ROOTDIR . '/vendor/autoload.php';

$config = Config::getInstance();

// debug log for runtime config
$config->log("Runtime Config:\n".var_export($config->getSettings(),1), Logger::NYSS_LOG_LEVEL_DEBUG);

$command = $config->getCommand();
if (!$command) {
	$command = $config->getCommand('help');
}

$cmd_name = $command->getName();

if (!$cmd_name == 'help') {
	// Set encoding/
	try {
		db_query("set names utf8mb4;");
	} catch (\Exception $e) {
		$config->log("Could not run 'SET NAMES' on connection! (".$e->getMessage().")", Logger::NYSS_LOG_LEVEL_FATAL);
	}
}

$config->log("Executing command '$cmd_name' . . .", Logger::NYSS_LOG_LEVEL_INFO);

if (!$result = $command->handle()) {
	$result = "Command " . $command->getName() . " complete but returned no output.";
}

echo "\n$result\n";
