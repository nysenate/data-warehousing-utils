<?php

/**
 * @file
 * File nyc_statute_import.drush.inc.
 */

/**
 * Implements hook_drush_help().
 */
function nys_scraper_drush_help($command) {
  switch ($command) {

    case 'drush:scrape-body-tags':
      return dt('Run scrape-body-tags');

    case 'drush:scrape-body-tags-1':
      return dt('Run scrape-body-tags-1');

    case 'drush:scrape-body-tags-2':
      return dt('Run scrape-body-tags-2');

    case 'drush:scrape-body-tags-3':
      return dt('Run scrape-body-tags-3');

  }
}

/**
 * Implements hook_drush_command().
 */
function nys_scraper_drush_command() {
  $items = array();

  $items['scrape-body-tags'] = array(
    'description' => dt('Run Import All Statute Nodes.'),
    'arguments'   => array(
      'arg1'    => dt('An optional lawID or lawID-locationID argument'),
    ),
    'examples' => array(
      'Standard example' => 'drush scrape-body-tags',
      'lawID example' => 'drush scrape-body-tags',
      'lawID-locationID example' => 'drush scrape-body-tags',
    ),
    'aliases' => array('sbd'),
  );

  $items['scrape-body-tags-1'] = array(
    'description' => dt('Restart Import All Statute Nodes.'),
    'arguments'   => array(
      'arg1'    => dt('A required lawID argument'),
    ),
    'examples' => array(
      'Standard example' => 'drush scrape-body-tags-1',
    ),
    'aliases' => array('sbd1'),
  );

  $items['scrape-body-tags-2'] = array(
    'description' => dt('Prints Import All Statute Nodes individual drush commands.'),
    'arguments'   => array(
      'arg1'    => dt('An optional lawID argument'),
    ),
    'examples' => array(
      'Standard example' => 'drush scrape-body-tags-2',
      'lawID example' => 'drush scrape-body-tags-2',
    ),
    'aliases' => array('sbd2'),
  );

  $items['scrape-body-tags-3'] = array(
    'description' => dt('Prints Import All Statute Nodes individual drush commands.'),
    'arguments'   => array(
      'arg1'    => dt('An optional lawID argument'),
    ),
    'examples' => array(
      'Standard example' => 'drush scrape-body-tags-3',
      'lawID example' => 'drush scrape-body-tags-3',
    ),
    'aliases' => array('sbd3'),
  );

  return $items;
}

/**
 * Callback function for drush import-all-statutes.
 *
 * Callback is called by using drush_hook_command() where
 * hook is the name of the module (MYMODULE) and command is the name of
 * the Drush command with all "-" characters
 * converted to "_" characters (my_command).
 *
 * $arg1.
 *   An optional argument
 */
function drush_nys_scraper_scrape_body_tags($arg1 = NULL) {
/*
  if (empty($arg1) == TRUE) {
    drush_confirm('Are you sure you want to continue import-all-statutes?', $indent = 0);
  }
  elseif(strpos($arg1, NYS_STATUTE_STATUTE_ID_DELIMITER) === FALSE) {
    drush_confirm("Are you sure you want to continue import-all-statutes. \r\nFor LawID - $arg1  ?", $indent = 0);
  }
  else {
    drush_confirm("Are you sure you want to continue import-all-statutes. \r\nFor StatuteID - $arg1  ?", $indent = 0);
  }
*/
  $retval = nys_scraper_scrape_body_tags($arg1);
  drush_log($retval, 'ok');

  // Log to the command line with an OK status.
  drush_log('Completed Import All Statutes.', 'ok');
}

/**
 * Callback function for drush restart-import-all-statutes.
 *
 * Callback is called by using drush_hook_command() where
 * hook is the name of the module (MYMODULE) and command is the name of
 * the Drush command with all "-" characters
 * converted to "_" characters (my_command).
 *
 * $arg1
 *   An optional argument
 */
function drush_nys_scraper_scrape_body_tags_1($arg1 = NULL) {
/*
  if (empty($arg1) == TRUE) {
    drush_confirm("Are you sure you want to continue restart-import-all-statutes. \r\nBeginning from the last complete LawID ?", $indent = 0);
  }
  elseif(strpos($arg1, NYS_STATUTE_STATUTE_ID_DELIMITER) === FALSE) {
    drush_confirm("Are you sure you want to continue restart-import-all-statutes. \r\nBeginning from LawID - $arg1  ?", $indent = 0);
  }
*/

  $retval = nys_scraper_scrape_body_tags_1($arg1);
  drush_log($retval, 'ok');

  // Log to the command line with an OK status.
  drush_log('Completed Restart Import All Statutes.', 'ok');
}

/**
 * Callback function for drush describe-import-all-statutes.
 *
 * Callback is called by using drush_hook_command() where
 * hook is the name of the module (MYMODULE) and command is the name of
 * the Drush command with all "-" characters
 * converted to "_" characters (my_command).
 *
 * $arg1
 *   An optional argument
 */
function drush_nys_scraper_scrape_body_tags_2($arg1 = NULL) {
  // A drush_confirm('Are you sure you want to continue?', $indent = 0);.
  $retval = nys_scraper_scrape_body_tags_2($arg1);
  drush_log($retval, 'ok');

  // Log to the command line with an OK status.
  // A drush_log('Completed Describe Import All Statutes.', 'ok');.
}

/**
 * Callback function for drush describe-import-all-statutes.
 *
 * Callback is called by using drush_hook_command() where
 * hook is the name of the module (MYMODULE) and command is the name of
 * the Drush command with all "-" characters
 * converted to "_" characters (my_command).
 *
 * $arg1
 *   An optional argument
 */
function drush_nys_scraper_scrape_body_tags_3($arg1 = NULL) {
  // A drush_confirm('Are you sure you want to continue?', $indent = 0);.
  $retval = nys_scraper_scrape_body_tags_3($arg1);
  drush_log($retval, 'ok');

  // Log to the command line with an OK status.
  // A drush_log('Completed Describe Import All Statutes.', 'ok');.
}

