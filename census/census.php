#!/usr/bin/env php
<?php

namespace NYS_Census;

chdir(__DIR__);

require_once 'vendor/autoload.php';

// Get the config instance.
$config = Config::getInstance();
$config->log("Runtime Config:\n" . var_export($config->getSettings(), 1), Logger::NYSS_LOG_LEVEL_DEBUG);

// Get the detected command.  Default to 'help'.
$command = $config->getCommand();
if (!$command) {
  $command = $config->getCommand('help');
}
$cmd_name = $command->getName();

$config->log("Executing command '$cmd_name' . . .", Logger::NYSS_LOG_LEVEL_INFO);

// Run the command.
$result = $command->handle();
$config->log("Command $cmd_name returned exit code " . (string) $result);

// Return
return $result;
