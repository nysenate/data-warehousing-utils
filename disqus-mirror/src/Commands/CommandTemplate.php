<?php

namespace DisqusImporter\Commands;

use DisqusImporter\OldConfig;
use GetOpt\Command;
use GetOpt\Operand;
use RuntimeException;

abstract class CommandTemplate extends Command {
	/** @var \DisqusImporter\OldConfig */
	protected $config;

	/** @var callable */
	protected $log;

  public function __construct($name, $options = NULL) {
    parent::__construct($name, static::class . '::handle', $options);
    //$this->config = NewConfig::getInstance();
	  //$this->log = $this->config->log->log;
    $this->initialize();
  }

  public static function createFromTemplate($name, $source) {
    $command_name = str_replace(' ', '', ucwords(str_replace('-', ' ', $name)));
    $command_class = __NAMESPACE__ . "\\{$command_name}Command";
    if (!class_exists($command_class)) {
      throw new RuntimeException("Could not find command class for config entry '$name' (class '$command_class').");
    }
    if (!isset($source->operands)) {
      $source->operands = (object) [];
    }
    $operands = [];
    foreach ($source->operands as $one_operand) {
      $mode_name = strtoupper($one_operand->mode);
      $mode = defined("\GetOpt\Operand::$mode_name")
        ? constant("\GetOpt\Operand::{$mode_name}")
        : Operand::OPTIONAL;
      $operands[] = Operand::create($one_operand->name, $mode);
    }
    /** @var CommandTemplate $cmd */
    $cmd = new $command_class($name);
    $cmd->setDescription($source->description ?? '')
      ->setShortDescription($source->short_description ?? '')
      ->addOperands($operands);
    return $cmd;
  }

  protected function initialize() {
  }

  public abstract function handle();

}
