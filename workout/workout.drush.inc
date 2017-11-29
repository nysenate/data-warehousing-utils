<?php

/**
 * @file
 * File nys_url_alias_audit.drush.inc.
 */

/**
 * Implements hook_drush_help().
 */
function workout_drush_help($command) {
  switch ($command) {
    case 'drush:exercise2':
      return dt('Run exercise multi');

  }
}

/**
 * Implements hook_drush_command().
 */
function workout_drush_command() {
  $items = array();

  $items['workout'] = array(
    'description' => dt('Attempts to Exercises Every Page on a site anonymously.'),
    'arguments'   => array(
      'arg1'    => dt('An optional number of pages to exercise.'),
    ),
    'options' => array(
      'threads' => 'The number of threads to use',
      'uri' => 'The domain to exercise.',
      'db' => 'A foreign database to scan.',
      'alias' => 'A foreign database to scan.',
    ),
    'examples' => array(
      'Standard example' => 'workout',
      'Argument example' => 'workout 42',
    ),
    'aliases' => array('wo'),
  );

  $items['exercise-page'] = array(
    'description' => dt('Exercises (renders) a Node Page.'),
    'arguments'   => array(
      'arg1'    => dt('A path to a page.'),
      'arg2'    => dt('An optional reference number that will be set in the position variable.'),
    ),
    'examples' => array(
      'Standard example' => 'exercise-page',
      'Argument example' => 'exercise-page path',
      'Argument example' => 'exercise-page path 42',
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_ROOT,
    'aliases' => array('exp'),
  );

  $items['stop-workout'] = array(
    'description' => dt('Stops a running workout.'),
    'examples' => array(
      'Standard example' => 'stop-workout',
    ),

    'aliases' => array('sw'),
  );

  $items['restart-workout'] = array(
    'description' => dt('Re starts a stopped workout.'),
    'arguments'   => array(
      'arg1'    => dt('An optional starting position.'),
      'arg2'    => dt('An optional number of pages to exercise.'),
    ),
    'options' => array(
      'threads' => 'The number of threads to use',
      'uri' => 'The domain to exercise.',
    ),
    'examples' => array(
      'Standard example' => 'restart-workout',
      'Argument example' => 'restart-workout 42',
      'Argument example' => 'restart-workout 42 36',
    ),
    'aliases' => array('rw'),
  );

  $items['clear-workout'] = array(
    'description' => dt('Clears the stopped status and workout position for a new workout.'),
    'arguments'   => array(
      'arg1'    => dt('An optional number of pages to exercise.'),
    ),
    'examples' => array(
      'Standard example' => 'clear-workout',
    ),
    'aliases' => array('cw'),
  );

  $items['workout-status'] = array(
    'description' => dt('Shows the status and workout position for the current workout.'),
    'examples' => array(
      'Standard example' => 'workout-status',
    ),
    'aliases' => array('wstat'),
  );

  $items['workout-report'] = array(
    'description' => dt('Shows results of last workout.'),
    'arguments'   => array(
      'arg1'    => dt('Type.'),
    ),
    'examples' => array(
      'Standard example' => 'exercise-report',
      'Argument example' => 'exercise-report type',
    ),
    'aliases' => array('wrp'),
  );

  $items['workout-test'] = array(
    'description' => dt('Tests alias, uri and db options.'),
    'arguments'   => array(
      'arg1'    => dt('A path to a page.'),
    ),
    'options' => array(
      'uri' => 'The domain to exercise.',
      'db' => 'A foreign database to scan.',
      'alias' => 'A foreign database to scan.',
  ),
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
 * Callback function for drush workout - wo.
 *
 * Callback is called by using drush_hook_command() where
 * hook is the name of the module (MYMODULE) and command is the name of
 * the Drush command with all "-" characters
 * converted to "_" characters (my_command).
 *
 * $arg1
 *   An optional argument
 */
function drush_workout($arg1 = NULL) {
  global $base_url;
  $current_status = workout_run_in_progress();
  $drush_alias = drush_get_option('alias', '');

  if (strstr($base_url, 'default') !== FALSE) {
    print 'The drupal $base_url contains ' . $base_url . " You should provide a uri --uri=your_base_url_here\r\n";
    return;
  }
  elseif ($current_status == 1) {
    // Running.
    print "There is already a workout running. You must stop-workout and clear-workout first. \r\n";
    return;
  }
  elseif ($current_status == 2) {
    print "There is already a Stopped workout. You must clear-workout first. \r\n";
    return;
  }
  elseif ($current_status == 3) {
    print "There is already a Stuck workout. You must clear-workout first. \r\n";
    return;
  }
  elseif (!empty($drush_alias)) {
    drush_confirm("Are you sure you want to exercise every page at  $drush_alias  ?\r\n", $indent = 0);
  }
  else {
    drush_confirm("Are you sure you want to exercise every page at  $base_url  ?\r\n", $indent = 0);
  }

  $retval = workout_workout($arg1);
  drush_log($retval, 'ok');

  // Log to the command line with an OK status.
  drush_log('Completed Workout.', 'ok');
}

/**
 * Callback function for drush exercise-page - exp.
 *
 * Callback is called by using drush_hook_command() where
 * hook is the name of the module (MYMODULE) and command is the name of
 * the Drush command with all "-" characters
 * converted to "_" characters (my_command).
 *
 * $arg1
 *   An optional argument
 */
function drush_workout_exercise_page($arg1 = NULL, $arg2 = NULL) {
  $retval = workout_exercise_page($arg1, $arg2);
  drush_log($retval, 'ok');
}

/**
 * Callback function for drush stop-workout - sw.
 *
 * Callback is called by using drush_hook_command() where
 * hook is the name of the module (MYMODULE) and command is the name of
 * the Drush command with all "-" characters
 * converted to "_" characters (my_command).
 *
 * $arg1
 *   An optional argument
 */
function drush_workout_stop_workout($arg1 = NULL) {
  drush_confirm("Are you sure you want to STOP RUN  ?\r\n", $indent = 0);

  $retval = workout_stop_workout($arg1);
  drush_log($retval, 'ok');

  // Log to the command line with an OK status.
  drush_log('Stopped The Workout For Now.', 'ok');
}

/**
 * Callback function for drush restart-workout - rw.
 *
 * Callback is called by using drush_hook_command() where
 * hook is the name of the module (MYMODULE) and command is the name of
 * the Drush command with all "-" characters
 * converted to "_" characters (my_command).
 *
 * $arg1
 *   An optional argument
 */
function drush_workout_restart_workout($arg1 = NULL, $arg2 = NULL) {
  $current_status = workout_run_in_progress();

  if ($current_status == 1) {
    // Running.
    print "There is already a workout running. You can not restart it unless it's Stopped or Stuck. \r\n";
    return;
  }
  else {
    if (($arg1 != NULL && !empty($arg1) && !is_numeric($arg1)) ||
        ($arg2 != NULL && !empty($arg2) && !is_numeric($arg2))) {
      // Two valid args were supplied.
      print "The arguments must be numbers.\r\n";
      return;
    }

    if (($arg1 == NULL || empty($arg1)) &&
        ($arg2 == NULL || empty($arg2))) {

      // No args were supplied.
      $index = variable_get(WORKOUT_RUN_CURRENT_POSITION);
      if (empty($index) || !is_numeric($index)) {
        print "No Starting Position could be found from a previous run.\r\n";
        print "Supply a Starting Position as an argument.\r\n";
      }

    }

  }

  if ($arg1 == NULL && $arg2 == NULL && isset($index)) {
    drush_confirm("Are you sure you want to restart workout starting at index $index. To the End.  ?\r\n", $indent = 0);
  }
  elseif ($arg1 != NULL && !empty($arg1) && $arg2 == NULL || empty($arg2)) {
    drush_confirm("Are you sure you want to restart workout starting at index $arg1. To the End.  ?\r\n", $indent = 0);
  }
  elseif ($arg1 != NULL && !empty($arg1) && $arg2 != NULL && !empty($arg2)) {
    drush_confirm("Are you sure you want to restart workout starting at index $arg1. For $arg2 Pages.  ?\r\n", $indent = 0);
  }

  $retval = workout_restart_workout($arg1, $arg2);
  drush_log($retval, 'ok');

  // Log to the command line with an OK status.
  drush_log('Completed Restarted Workout.', 'ok');
}

/**
 * Callback function for drush clear-workout - cw.
 *
 * Callback is called by using drush_hook_command() where
 * hook is the name of the module (MYMODULE) and command is the name of
 * the Drush command with all "-" characters
 * converted to "_" characters (my_command).
 *
 * $arg1
 *   An optional argument
 */
function drush_workout_clear_workout($arg1 = NULL) {
  drush_confirm("Are you sure you want to CLEAR THE PREVIOUS RUNS POSITION DATA to prepare for another run ?\r\n", $indent = 0);
  $retval = workout_clear_workout($arg1);
  drush_log($retval, 'ok');

  // Log to the command line with an OK status.
  drush_log('Cleared Previous Workout Position Data.', 'ok');
}

/**
 * Callback function for drush clear-workout - cw.
 *
 * Callback is called by using drush_hook_command() where
 * hook is the name of the module (MYMODULE) and command is the name of
 * the Drush command with all "-" characters
 * converted to "_" characters (my_command).
 *
 * $arg1
 *   An optional argument
 */
function drush_workout_status($arg1 = NULL) {
  $retval = workout_status($arg1);
  drush_log($retval, 'ok');

  // Log to the command line with an OK status.
  drush_log('Completed Workout Status.', 'ok');
}

function drush_workout_report($arg1 = NULL) {
  $row_count = 0;
  $validated_count = 0;
  $un_validated_count = 0;

  $options_arr = array('1' => 'Show All', '2' => 'Show Validated Pages', '3' => 'Show Unvalidated Pages');

  $choice = drush_choice($options_arr, "  What type of report to display ?");
  if ($choice != 0) {
    if ($choice == 1) {
      $sql = 'SELECT * FROM `workout`';
    }
    elseif($choice == 2) {
      $sql = 'SELECT * FROM `workout` WHERE `size` > 0 AND `validated` = 1';
    }
    elseif($choice == 3) {
      $sql = 'SELECT * FROM `workout` WHERE `size` = 0 OR `validated` = 0';
    }

    if ($choice > 0 &&  $choice < 4) {

    }

    print "\r\n";
    print "+------------------------------------------------------------------------------------------------------------------------+-------------+-------------+\r\n";
    print "| alias                                                                                                                  | size        | validated   |\r\n";
    print "+------------------------------------------------------------------------------------------------------------------------+-------------+-------------+\r\n";
    $results = db_query($sql);
    foreach ($results as $row) {
      print '| ' . str_pad($row->alias, 120) . '| ' . str_pad($row->size, 12) . '| ' . str_pad($row->validated, 12) . "|\r\n";
      $row_count++;
      if ($row->validated == 0) {
        $un_validated_count++;
      }
      elseif ($row->validated == 1) {
        $validated_count++;
      }
    }

    print "+------------------------------------------------------------------------------------------------------------------------+-------------+-------------+\r\n";
    print "$row_count rows in set\r\n";
    print "$validated_count were Validated\r\n";
    print "$un_validated_count could not be Validated\r\n";

  }

  drush_log($retval, 'ok');

  // Log to the command line with an OK status.
  drush_log('Completed Exercise Status Report.', 'ok');
}

function drush_workout_test($arg1='') {

  $mysql_uri = drush_get_option('db', '');
  $uri = drush_get_option('uri', '');
  $drush_alias = drush_get_option('alias', '');

  if (empty($mysql_uri) && empty($uri) && empty($drush_alias)) {
    print "\r\n\r\n";
    print "This command is for testing --alias, --uri and --database options.\r\n";
    print "Remote aliases to servers are specified in this form.\r\n";
    print "--alias=@site-alias\r\n";
    print "Alternately you can provide separate --db and --uri options.\r\n";
    print "Remote databases are specified in this form.\r\n";
    print "--db=mysql://<username>:<password>@<host>:<port>/<database>\r\n";
    print "\r\n";
    print "Remote servers to exercise are specified in this form.\r\n";
    print "--uri=https://yourserver.com\r\n";
    print "\r\n\r\n";
    $local_node_count = db_query("SELECT COUNT(*) FROM `node`")->fetchField();
    print "Local Node COUNT $local_node_count\r\n";
    print "\r\n\r\n";
  }

  if (!empty($drush_alias) || !empty($mysql_uri)) {
    $local_node_count = db_query("SELECT COUNT(*) FROM `node`")->fetchField();
    print "Local Node COUNT: $local_node_count\r\n";

      // Before the query see if a remote database is specified.
      $connection_arr = exerciser_mysql_url_connect();
      if ($connection_arr !== FALSE) {
        print "remote URI specified:\r\n";
        print_r($connection_arr);
        Database::addConnectionInfo('exerciser', 'default', $connection_arr);
        db_set_active('exerciser');
        //Database::addConnectionInfo('external_db', 'default', $connection_arr);
        //db_set_active('external_db');
      }

    $remote_node_count = db_query("SELECT COUNT(*) FROM `node`")->fetchField();
    print "Remote Node COUNT: $remote_node_count\r\n";

    // After the query set back to the default db.
    if ($connection_arr !== FALSE) {
      db_set_active(); // set back to the default db.
    }

  }

  // Show the title of the page.
  if (empty($uri) && !empty($drush_alias)) {
    $uri = exerciser_get_uri($drush_alias);
  }

  if (!empty($uri)) {
    $result = exerciser_do_curl($uri);
    $start = stripos($result, '<title>');
    $end = stripos($result, '</title>', $start);
    $title = substr($result, $start + strlen('<title>'), $end -  $start - strlen('<title>'));
    print "\r\n Page Title: $title \r\n\r\n\r\n";
  }

  // Log to the command line with an OK status.
  drush_log('Completed Exercise Status Test.', 'ok');
}
