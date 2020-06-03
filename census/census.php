#!/usr/bin/env php
<?php

namespace NYS_Census;

define('ROOTDIR', __DIR__);

require_once ROOTDIR . '/vendor/autoload.php';

// Get the config instance.
$config = Config::getInstance();
$config->log("Runtime Config:\n" . var_export($config->getSettings(), 1), Logger::NYSS_LOG_LEVEL_DEBUG);

// Get the detected command.  Default to 'help'.
$command = $config->getCommand();
if (!$command) {
  $command = $config->getCommand('help');
}
$cmd_name = $command->getName();

/*if (!$cmd_name == 'help') {
  // Set encoding/
  try {
    db_query("set names utf8mb4;");
  }
  catch (\Exception $e) {
    $config->log("Could not run 'SET NAMES' on connection! (" . $e->getMessage() . ")", Logger::NYSS_LOG_LEVEL_FATAL);
    return 999;
  }
}*/

$config->log("Executing command '$cmd_name' . . .", Logger::NYSS_LOG_LEVEL_INFO);

// Run the command.
$result = $command->handle();
$config->log("Command $cmd_name returned exit code " . (string) $result);

// Return
return $result;
