<?php

namespace NYS_Census\Command;

use GetOpt\Command;
use GetOpt\GetOpt;
use GetOpt\Operand;
use GetOpt\Option;
use RuntimeException;

/**
 * Class CommandBase
 *
 * @package NYS_Census\Command
 */
abstract class CommandBase extends Command {
	/** @var callable */
	protected $log;

  /**
   * CommandBase constructor, extending GetOpt\Command.
   * This standardizes static::handle as the command's handler
   * and provides for command-specific init routines.
   *
   * @param $name
   * @param string|array|Option[]|null $options
   */
  public function __construct($name, $options = NULL) {
    parent::__construct($name, static::class . '::handle', $options);
    $this->initialize();
  }

  /**
   * A static equivalent to Command->handle()
   *
   * @param \NYS_Census\Command\CommandBase $cmd
   *
   * @return mixed
   */
  public static function executeHandler(CommandBase $cmd) {
  	return $cmd->handle();
  }

  /**
   * @param $name
   * @param $source
   *
   * @return \NYS_Census\Command\CommandBase
   */
  public static function createFromTemplate($name, $source) {
    // Make the command name conform to our naming standard
    $command_name = str_replace(' ', '', ucwords(str_replace('-', ' ', $name)));

    // Check for existence of the target class
    $command_class = __NAMESPACE__ . "\\{$command_name}Command";
    if (!class_exists($command_class)) {
      throw new RuntimeException("Could not find command class for config entry '$name' (class '$command_class').");
    }

    // Ensure operands and options are minimally populated.
    if (!isset($source->operands)) {
      $source->operands = (object) [];
    }
    if (!isset($source->options)) {
    	$source->options = (object) [];
    }

    // Initialize operand and option inventory.
    $operands = [];
    $options = [];

    // Populate the command operands from the source.
	  foreach ($source->operands as $one_operand) {
	    // Find the operand's mode, defaulting to OPTIONAL.
		  $mode_name = strtoupper($one_operand->mode);
		  $mode = defined("\\GetOpt\\Operand::$mode_name")
			  ? constant("\\GetOpt\\Operand::{$mode_name}")
			  : Operand::OPTIONAL;

		  // Create the operand object.  Apply the description, and
      // the default value, if it exists.
		  $new_operand = Operand::create($one_operand->name, $mode)
			  ->setDescription($one_operand->description ?? '');
		  if (isset($one_operand->default)) {
			  $new_operand->setDefaultValue($one_operand->default);
		  }

		  // Add the operand to the inventory.
		  $operands[] = $new_operand;
	  }

	  // Populate the command options from the source.
	  foreach ($source->options as $one_option) {
	    // Find the option's mode, defaulting to NO_ARGUMENT
		  $mode_name = strtoupper($one_option->mode) . '_ARGUMENT';
		  $mode = defined("\\GetOpt\\GetOpt::$mode_name")
			  ? constant("\\GetOpt\\GetOpt::{$mode_name}")
			  : GetOpt::NO_ARGUMENT;
		  $short = $one_option->short ?? NULL;
		  $long = $one_option->long ?? NULL;

		  // Create the option object and apply the description.
		  $new_option = Option::create($short, $long, $mode)
			  ->setDescription($one_option->description ?? '');

		  // Add the option to the inventory.
		  $options[] = $new_option;
	  }

	  // Create the command object and return.
    /** @var CommandBase $cmd */
    $cmd = new $command_class($name);
    $cmd->setDescription($source->description ?? '')
      ->setShortDescription($source->short_description ?? '')
      ->addOperands($operands)
	    ->addOptions($options);
    return $cmd;
  }

  /**
   * To be extended by child classes, if custom initialization is
   * required after parent construction.
   */
  protected function initialize() {
  }

  /**
   * Must be implemented by child classes.  The actual handler for
   * the command.
   *
   * @return mixed
   */
  public abstract function handle();

}
