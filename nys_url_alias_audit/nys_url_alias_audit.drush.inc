<?php

/**
 * @file
 * File nys_school_delete.drush.inc.
 */

/**
 * Implements hook_drush_help().
 */
function nys_url_alias_audit_drush_help($command) {
  switch ($command) {
    case 'drush:clear-all-statutes':
      return dt('Run clear-all-schools');

  }
}

/**
 * Implements hook_drush_command().
 */
function nys_url_alias_audit_drush_command() {
  $items = array();

  $items['survey-bill-alias'] = array(
    'description' => dt('Run Survey of Bill Url Aliases.'),
    'arguments'   => array(
      'arg1'    => dt('An optional node/12345 OR node/12345,node/12345,node/12345'),
    ),
    'examples' => array(
      'Standard example' => 'drush survey-bill-alias',
      'Argument example' => 'drush survey-bill-alias alias source',
    ),
    'aliases' => array('sba'),
  );

  $items['alias-duplicates'] = array(
    'description' => dt('Finds Duplicate URL Aliases.'),
    'arguments'   => array(
      'arg1'    => dt('An optional node type argument'),
    ),
    'examples' => array(
      'Standard example' => 'drush alias-duplicates',
      'Argument example' => 'drush alias-duplicates',
    ),
    'aliases' => array('adu'),
  );

  $items['remove-duplicates'] = array(
    'description' => dt('Takes site off line and rebuilds the url_alias table without duplicates.'),
    'arguments'   => array(
      'arg1'    => dt('An optional argument'),
    ),
    'examples' => array(
      'Standard example' => 'drush remove-duplicates',
      'Argument example' => 'drush remove-duplicates 5',
    ),
    'aliases' => array('rdu'),
  );

  $items['alias-short-amendments'] = array(
    'description' => dt('Find short URL aliases for ammendments.'),
    'arguments'   => array(
      'arg1'    => dt('An optional node type argument'),
    ),
    'examples' => array(
      'Standard example' => 'drush alias-short-amendments',
      'Argument example' => 'drush alias-short-amendments',
    ),
    'aliases' => array('asa'),
  );


  $items['remove-alias-short-amendments'] = array(
    'description' => dt('Removeshort URL aliases for ammendments.'),
    'arguments'   => array(
      'arg1'    => dt('An optional node type argument'),
    ),
    'examples' => array(
      'Standard example' => 'drush remove-alias-short-amendments',
      'Argument example' => 'drush remove-alias-short-amendments',
    ),
    'aliases' => array('rasa'),
  );

  $items['alias-not-original'] = array(
    'description' => dt('Run Alias Not Original.'),
    'arguments'   => array(
      'arg1'    => dt('Find the original outdated url aliass.'),
    ),
    'examples' => array(
      'Standard example' => 'drush alias-not-original',
      'Argument example' => 'drush alias-not-original',
    ),
    'aliases' => array('ano'),
  );

  $items['remove-not-original'] = array(
    'description' => dt('Remove the original outdated url aliass.'),
    'arguments'   => array(
      'arg1'    => dt('An optional node type argument'),
    ),
    'examples' => array(
      'Standard example' => 'remove-not-original',
      'Argument example' => 'remove-not-original',
    ),
    'aliases' => array('rno'),
  );

  $items['alias-empty'] = array(
    'description' => dt('Remove short URL aliases for ammendments.'),
    'arguments'   => array(
      'arg1'    => dt('An optional node type argument'),
    ),
    'examples' => array(
      'Standard example' => 'drush alias-empty',
      'Argument example' => 'drush alias-empty',
    ),
    'aliases' => array('amt'),
  );

  $items['survey-laws'] = array(
    'description' => dt('Run Survey of Law Url Aliases.'),
    'arguments'   => array(
      'arg1'    => dt('An optional argument'),
    ),
    'examples' => array(
      'Standard example' => 'drush survey-laws',
      'Argument example' => 'drush survey-laws',
    ),
    'aliases' => array('sla'),
  );

  $items['survey-laws-report'] = array(
    'description' => dt('Report on Law Url Aliases.'),
    'arguments'   => array(
      'arg1'    => dt('An optional argument'),
    ),
    'examples' => array(
      'Standard example' => 'drush survey-laws-report',
      'Argument example' => 'drush survey-laws-report',
    ),
    'aliases' => array('slr'),
  );

  $items['audit-url-alias'] = array(
    'description' => dt('General Audit of URL Aliases for Bills, Resolutions and Laws.'),
    'arguments'   => array(
      'arg1'    => dt('An optional argument'),
    ),
    'examples' => array(
      'Standard example' => 'drush audit-url-alias',
      'Argument example' => 'drush audit-url-alias',
    ),
    'aliases' => array('aua'),
  );

  return $items;
}


/**
 * Callback function for drush survey-bill-alias.
 *
 * Callback is called by using drush_hook_command() where
 * hook is the name of the module (MYMODULE) and command is the name of
 * the Drush command with all "-" characters
 * converted to "_" characters (my_command).
 *
 * $arg1
 *   An optional argument
 */
function drush_nys_url_alias_audit_survey_bill_alias($arg1 = NULL) {
  drush_confirm('Are you sure you want to Clear The Survey Table and run a url alias survey ?', $indent = 0);
  $retval = nys_url_alias_audit_survey_bill_alias($arg1);
  drush_log($retval, 'ok');

  // Log to the command line with an OK status.
  drush_log('Completed Survey All Schools.', 'ok');
}


/**
 * Callback function for drush alias-duplicates.
 *
 * Callback is called by using drush_hook_command() where
 * hook is the name of the module (MYMODULE) and command is the name of
 * the Drush command with all "-" characters
 * converted to "_" characters (my_command).
 *
 * $arg1
 *   An optional argument
 */
function drush_nys_url_alias_audit_alias_duplicates($arg1 = NULL) {
  //drush_confirm('Are you sure you want to Clear The Survey Table and run a url alias survey ?', $indent = 0);
  $retval = nys_url_alias_audit_alias_duplicates($arg1);
  drush_log($retval, 'ok');

  // Log to the command line with an OK status.
  drush_log('Completed alias-duplicates.', 'ok');
}

/**
 * Callback function for drush alias-duplicates.
 *
 * Callback is called by using drush_hook_command() where
 * hook is the name of the module (MYMODULE) and command is the name of
 * the Drush command with all "-" characters
 * converted to "_" characters (my_command).
 *
 * $arg1
 *   An optional argument
 */
function drush_nys_url_alias_audit_remove_duplicates($arg1 = NULL) {
  drush_confirm('Are you sure you want to Clear The Duplicate url aliases and rebuild the table. ?', $indent = 0);
  $retval = nys_url_alias_audit_remove_duplicates($arg1);
  drush_log($retval, 'ok');

  // Log to the command line with an OK status.
  drush_log('Completed remove-alias-duplicates.', 'ok');
}

/**
 * Callback function for drush alias-short-amendments.
 *
 * Callback is called by using drush_hook_command() where
 * hook is the name of the module (MYMODULE) and command is the name of
 * the Drush command with all "-" characters
 * converted to "_" characters (my_command).
 *
 * $arg1
 *   An optional argument
 */
function drush_nys_url_alias_audit_alias_short_amendments($arg1 = NULL) {
  //drush_confirm('Are you sure you want to Clear The Survey Table and run a url alias survey ?', $indent = 0);
  $retval = nys_url_alias_audit_alias_short_amendments($arg1);
  drush_log($retval, 'ok');

  // Log to the command line with an OK status.
  drush_log('Completed alias-short-amendments.', 'ok');
}

/**
 * Callback function for drush remove-alias-short-amendments.
 *
 * Callback is called by using drush_hook_command() where
 * hook is the name of the module (MYMODULE) and command is the name of
 * the Drush command with all "-" characters
 * converted to "_" characters (my_command).
 *
 * $arg1
 *   An optional argument
 */
function drush_nys_url_alias_audit_remove_alias_short_amendments($arg1 = NULL) {
  //drush_confirm('Are you sure you want to Clear The Survey Table and run a url alias survey ?', $indent = 0);
  $retval = nys_url_alias_audit_remove_alias_short_amendments($arg1);
  drush_log($retval, 'ok');

  // Log to the command line with an OK status.
  drush_log('Completed alias-short-amendments.', 'ok');
}

/**
 * Callback function for drush clear-all-schools.
 *
 * Callback is called by using drush_hook_command() where
 * hook is the name of the module (MYMODULE) and command is the name of
 * the Drush command with all "-" characters
 * converted to "_" characters (my_command).
 *
 * $arg1
 *   An optional argument
 */
function drush_nys_url_alias_audit_alias_not_original($arg1 = NULL) {
  //drush_confirm('Are you sure you want to DElETE ALL THE SCHOOL NODES - clear-all-schools ?', $indent = 0);
  $retval = nys_url_alias_alias_not_original($arg1);
  drush_log($retval, 'ok');

  // Log to the command line with an OK status.
  drush_log('Completed Alias Not Original.', 'ok');
}

/**
 * Callback function for drush clear-all-schools.
 *
 * Callback is called by using drush_hook_command() where
 * hook is the name of the module (MYMODULE) and command is the name of
 * the Drush command with all "-" characters
 * converted to "_" characters (my_command).
 *
 * $arg1
 *   An optional argument
 */
function drush_nys_url_alias_audit_remove_not_original($arg1 = NULL) {
  drush_confirm('Are you sure you want to remove the conflicting duplicates ?', $indent = 0);
  $retval = nys_url_alias_audit_remove_not_original($arg1);
  drush_log($retval, 'ok');

  // Log to the command line with an OK status.
  drush_log('Completed Remove Conflicting Duplicates.', 'ok');
}

/**
 * Callback function for drush alias-empty - amt.
 *
 * Callback is called by using drush_hook_command() where
 * hook is the name of the module (MYMODULE) and command is the name of
 * the Drush command with all "-" characters
 * converted to "_" characters (my_command).
 *
 * $arg1
 *   An optional argument
 */
function drush_nys_url_alias_audit_alias_empty($arg1 = NULL) {
  //drush_confirm('Are you sure you want to Clear The Survey Table and run a url alias survey ?', $indent = 0);
  $retval = nys_url_alias_audit_alias_empty($arg1);
  drush_log($retval, 'ok');

  // Log to the command line with an OK status.
  drush_log('Completed alias-empty.', 'ok');
}

/**
 * Callback function for drush survey-laws - sla.
 *
 * Callback is called by using drush_hook_command() where
 * hook is the name of the module (MYMODULE) and command is the name of
 * the Drush command with all "-" characters
 * converted to "_" characters (my_command).
 *
 * $arg1
 *   An optional argument
 */
function drush_nys_url_alias_audit_survey_laws($arg1 = NULL) {
  drush_confirm('Are you sure you want to Clear the nys_url_alias_audit table and load the laws ?', $indent = 0);
  $retval = nys_url_alias_audit_survey_laws($arg1);
  drush_log($retval, 'ok');

  // Log to the command line with an OK status.
  drush_log('Completed Survey Laws.', 'ok');
}

/**
 * Callback function for drush survey-laws-report - slr.
 *
 * Callback is called by using drush_hook_command() where
 * hook is the name of the module (MYMODULE) and command is the name of
 * the Drush command with all "-" characters
 * converted to "_" characters (my_command).
 *
 * $arg1
 *   An optional argument
 */
function drush_nys_url_alias_audit_survey_laws_report($arg1 = NULL) {
  //drush_confirm('Are you sure you want to remove the duplicate url aliases and compact / rebuild the url_alias table- remove-duplicates ?', $indent = 0);
  $retval = nys_url_alias_audit_survey_laws_report($arg1);
  drush_log($retval, 'ok');

  // Log to the command line with an OK status.
  drush_log('Completed Survey Laws Report.', 'ok');
}

/**
 * Callback function for drush audit-url-alias - aua.
 *
 * Callback is called by using drush_hook_command() where
 * hook is the name of the module (MYMODULE) and command is the name of
 * the Drush command with all "-" characters
 * converted to "_" characters (my_command).
 *
 * $arg1
 *   An optional argument
 */
function drush_nys_url_alias_audit_audit_url_alias($arg1 = NULL) {
  //drush_confirm('Are you sure you want to remove the duplicate url aliases and compact / rebuild the url_alias table- remove-duplicates ?', $indent = 0);
  $retval = nys_url_alias_audit_audit_ur_alias($arg1);
  drush_log($retval, 'ok');

  // Log to the command line with an OK status.
  drush_log('Completed Audit URL Aliases Report.', 'ok');
}