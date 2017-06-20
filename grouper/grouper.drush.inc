<?php

/**
 * @file
 * File grouper.drush.inc.
 */

/**
 * Implements hook_drush_help().
 */
function grouper_drush_help($command) {
  switch ($command) {
    case 'drush:exercise2':
      return dt('Run exercise multi');

  }
}

/**
 * Implements hook_drush_command().
 */
function grouper_drush_command() {
  $items = array();

  $items['marker'] = array(
    'description' => dt('Creates a marker in the error log.'),
    'arguments'   => array(
      'arg1'    => dt('Name of marker.'),
    ),
    'examples' => array(
      'Standard example' => 'marker',
      'Argument example' => 'workout M1',
    ),
    'aliases' => array('mrk'),
  );

  $items['marker-trim'] = array(
    'description' => dt('Clears all the log entries above the marker.'),
    'arguments'   => array(
      'arg1'    => dt('wid.'),
    ),
    'options' => array(
      'continue' => 'continue going with failed run.',
      'flush' => 'Reset Run Data.',
      'quietly' => 'Only Show if messages.',
    ),
    'examples' => array(
      'Standard example' => 'workout-test',
      'Argument example' => 'workout-test path',
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_ROOT,
    'aliases' => array('wt'),
  );



  $items['grouper-get-uri'] = array(
    'description' => dt('Gets grouper uri'),
    'required-arguments' => FALSE,
    'examples' => array(
      'Standard example' => 'grouper-get-uri',
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_ROOT,
    'aliases' => array('ggu'),
  );

  $items['grouper-set-uri'] = array(
    'description' => dt('Set or Delete grouper uri.'),
    'arguments'   => array(
      'arg1'    => dt('Uri'),
    ),
    'required-arguments' => FALSE,
    'examples' => array(
      'Standard example' => 'grouper-set-uri',
      'Argument example' => 'workout-test http://....',
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_ROOT,
    'aliases' => array('gsu'),
  );

  $items['grouper-delete-uri'] = array(
    'description' => dt('Delete grouper uri.'),
    'required-arguments' => FALSE,
    'examples' => array(
      'Standard example' => 'grouper-delete-uri',
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_ROOT,
    'aliases' => array('gdu'),
  );


  $items['grouper-test'] = array(
    'description' => dt('Tests.'),
  //  'arguments'   => array(
  //    'arg1'    => dt('gt.'),
  //  ),
    'examples' => array(
      'Standard example' => 'workout-test',
      'Argument example' => 'workout-test path',
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_ROOT,
    'aliases' => array('wt'),
  );

  return $items;
}



/**
 * Callback function for drush marker - mrk.
 *
 * $arg1
 *   An optional argument
 */
function drush_grouper_marker($arg1) {

  if (empty($arg1)) {
    $arg = time();
  }

  watchdog('marker', $arg1, NULL, WATCHDOG_WARNING, date("h:i : s a S") );




  //$retval = workout_exercise_page($arg1, $arg2);
  drush_log($retval, 'ok');

  // Log to the command line with an OK status.
  //drush_log('Completed Exercise Nodes Multi.', 'ok');
}



/**
 * Callback function for drush marker-trim - mt.
 *
 * $arg1
 *   An optional argument
 */
function drush_grouper_marker_trim($arg1) {
  if (!empty($arg1) && is_numeric($arg1)) {
    db_query("DELETE FROM `watchdog` WHERE `wid` > :wid", array('wid' => $arg1));
    print "Cleared messages above $arg1\r\n";
  }
  else {
    print "You need tp pass in a wid to delete after.\r\n";
  }

  //$retval = workout_exercise_page($arg1, $arg2);
  drush_log($retval, 'ok');

  // Log to the command line with an OK status.
  //drush_log('Completed Exercise Nodes Multi.', 'ok');
}

/**
 * Callback function for drush grouper-get-uri - ggu.
 *
 * $arg1
 *   An optional argument
 */
function drush_grouper_get_uri() {
  $grouper_uri = variable_get('grouper_uri', '');
  if (empty($grouper_uri)) {
    print "The Grouper URI is currently empty.";
  }
  else {
    print $grouper_uri;
  }

  //$retval = workout_exercise_page($arg1, $arg2);
  drush_log($retval, 'ok');

  // Log to the command line with an OK status.
  //drush_log('Completed Exercise Nodes Multi.', 'ok');
}

/**
 * Callback function for drush grouper-set-uri - gsu.
 *
 * $arg1
 *   An optional argument
 */
function drush_grouper_set_uri($arg1) {

  variable_set('grouper_uri', $arg1);
  print "\r\ngrouper_uri set to : $arg1  \r\n";


  //$retval = workout_exercise_page($arg1, $arg2);
  drush_log($retval, 'ok');

  // Log to the command line with an OK status.
  //drush_log('Completed Exercise Nodes Multi.', 'ok');
}

/**
 * Callback function for drush grouper-delete-uri - gsu.
 *
 * $arg1
 *   An optional argument
 */
function drush_grouper_delete_uri($arg1) {
  variable_del('grouper_uri');

  print "Grouper URI deleted.";

  //$retval = workout_exercise_page($arg1, $arg2);
  drush_log($retval, 'ok');

  // Log to the command line with an OK status.
  //drush_log('Completed Exercise Nodes Multi.', 'ok');
}


/**
 * Callback function for drush marker-trim - mt.
 *
 * $arg1
 *   An optional argument
 */
function drush_grouper_test($arg1) {

  $path = '/srv/bindings/f7282c87a7a94337847fbf668a7d0e27/code/includes/path.inc';
print "\r\nJELLO $path \r\n";

}


///////ALTER TABLE `watchdog` ADD INDEX(`variables`);its a longblob no deal
