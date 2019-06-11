<?php

namespace DisqusImporter\Commands;

use GetOpt\Command;
use GetOpt\GetOpt;
use GetOpt\Operand;
use GetOpt\Option;
use RuntimeException;

abstract class CommandTemplate extends Command {
	/** @var callable */
	protected $log;

  public function __construct($name, $options = NULL) {
    parent::__construct($name, static::class . '::handle', $options);
    $this->initialize();
  }

  public static function executeHandler(CommandTemplate $cmd) {
  	return $cmd->handle();
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
    if (!isset($source->options)) {
    	$source->options = (object) [];
    }
    $operands = [];
    $options = [];
	  foreach ($source->operands as $one_operand) {
		  $mode_name = strtoupper($one_operand->mode);
		  $mode = defined("\\GetOpt\\Operand::$mode_name")
			  ? constant("\\GetOpt\\Operand::{$mode_name}")
			  : Operand::OPTIONAL;
		  $new_operand = Operand::create($one_operand->name, $mode)
			  ->setDescription($one_operand->description ?? '');
		  if (isset($one_operand->default)) {
			  $new_operand->setDefaultValue($one_operand->default);
		  }
		  $operands[] = $new_operand;
	  }
	  foreach ($source->options as $one_option) {
		  $mode_name = strtoupper($one_option->mode) . '_ARGUMENT';
		  $mode = defined("\\GetOpt\\GetOpt::$mode_name")
			  ? constant("\\GetOpt\\GetOpt::{$mode_name}")
			  : GetOpt::NO_ARGUMENT;
		  $short = $one_option->short ?? NULL;
		  $long = $one_option->long ?? NULL;
		  $new_option = Option::create($short, $long, $mode)
			  ->setDescription($one_option->description ?? '');
		  $options[] = $new_option;
	  }
    /** @var CommandTemplate $cmd */
    $cmd = new $command_class($name);
    $cmd->setDescription($source->description ?? '')
      ->setShortDescription($source->short_description ?? '')
      ->addOperands($operands)
	    ->addOptions($options);
    return $cmd;
  }

  protected function initialize() {
  }

  public abstract function handle();

}
