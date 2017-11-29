<?php

/**
 * @file
 * File nys_url_alias_audit.drush.inc.
 */

/**
 * Implements hook_drush_help().
 */
function exerciser_drush_help($command) {
  switch ($command) {
    case 'drush:exercise':
      return dt('Run exercise');

  }
}

/**
 * Implements hook_drush_command().
 */
function exerciser_drush_command() {
  $items = array();

  $items['exercise-nodes'] = array(
    'description' => dt('Exercises (renders) the pages of a Content Type.'),
    'arguments'   => array(
      'arg1'    => dt('An optional content type.'),
    ),
    'options' => array(
      'continue' => 'continue going with failed run.',
      'flush' => 'Reset Run Data.',
      'quietly' => 'Only Show if messages.',
      'showall' => 'Show every node.',
      'debugging' => 'Emit a message for each row.',
      'uri' => 'The domain to exercise.',
      'db' => 'A foreign database to scan.',
      'alias' => 'A foreign database to scan and uri to test.',
    ),
    'examples' => array(
      'Standard example' => 'exercise',
      'Argument example' => 'exercise basic',
    ),
    'aliases' => array('exns'),
  );

  $items['exercise-terms'] = array(
    'description' => dt('Exercises (renders) the pages of a Taxonomy Vocabulary.'),
    'arguments'   => array(
      'arg1'    => dt('An optional vocabulary id type.'),
    ),
    'examples' => array(
      'Standard example' => 'exercise-terms',
      'Argument example' => 'exercise-terms 11',
    ),
    'options' => array(
      'db' => 'Emit a message for each row.',
    ),
    'aliases' => array('exts'),
  );

  $items['exercise-node'] = array(
    'description' => dt('Exercises (renders) a Node Page.'),
    'arguments'   => array(
      'arg1'    => dt('An optional nid or path.'),
    ),
    'options' => array(
      'continue' => 'continue going with failed run.',
      'flush' => 'Reset Run Data.',
      'quietly' => 'Only Show if messages.',
    ),
    'examples' => array(
      'Standard example' => 'exercise',
      'Argument example' => 'exercise basic',
    ),
    'aliases' => array('exn'),
  );

  $items['exercise-term'] = array(
    'description' => dt('Exercies (renders) a Term Page.'),
    'arguments'   => array(
      'arg1'    => dt('An optional tid or path.'),
    ),
    'examples' => array(
      'Standard example' => 'exercise-terms',
      'Argument example' => 'exercise-terms 11',
    ),
    'aliases' => array('ext'),
  );


  $items['exercise-status'] = array(
    'description' => dt('Shows System Status.'),
    'arguments'   => array(
      'arg1'    => dt('An optional tid or path.'),
    ),
    'examples' => array(
      'Standard example' => 'exercise-status',
      'Argument example' => 'exercise-status',
    ),
    'aliases' => array('est'),
  );

  $items['exercise-status-ping'] = array(
  'description' => dt('Shows Detailed Status.'),
  'arguments'   => array(
    'arg1'    => dt('An optional tid or path.'),
  ),
  'examples' => array(
    'Standard example' => 'exercise-terms',
    'Argument example' => 'exercise-terms 11',
  ),
  'aliases' => array('esp'),
  );

  $items['exercise-stop'] = array(
    'description' => dt('Shows System Status.'),
    'arguments'   => array(
      'arg1'    => dt('An optional tid or path.'),
    ),
    'options' => array(
      'full' => 'Clear previous run also.',
    ),
    'examples' => array(
      'Standard example' => 'exercise-stop',
      'Argument example' => 'exercise-stop',
    ),
    'aliases' => array('estp'),
  );

  $items['exercise-all'] = array(
    'description' => dt('Generates Drush Script.'),
    'arguments'   => array(
      'arg1'    => dt('Static or Active using next.'),
    ),
    'examples' => array(
      'Standard example' => 'exercise-all',
      'Argument example' => 'exercise-all',
    ),
    'aliases' => array('exa'),
  );

  $items['exercise-get-last-complete-run'] = array(
    'description' => dt('Gets the type of the last complete run.'),
    'arguments'   => array(
      'arg1'    => dt('No Options ????.'),
    ),
    'examples' => array(
      'Standard example' => 'exercise-get-last-complete-run',
      'Argument example' => 'exercise-get-last-complete-run',
    ),
    'aliases' => array('exlcr'),
  );

  $items['exercise-get-next-run'] = array(
    'description' => dt('Gets the name of the next type to run.'),
    'arguments'   => array(
      'arg1'    => dt('No options.'),
    ),
    'options' => array(
      'command' => 'Get as a drush command.',
    ),
    'examples' => array(
      'Standard example' => 'exercise-get-next-run',
      'Argument example' => 'exercise-get-next-run',
    ),
    'aliases' => array('exgnr'),
  );

  $items['exercise-report'] = array(
    'description' => dt('Shows Detailed Status.'),
    'arguments'   => array(
      'arg1'    => dt('A Content Type.'),
    ),
    'options' => array(
      'uri' => 'The domain to exercise.',
      'database' => 'A foreign database to scan.',
    ),
    'examples' => array(
      'Standard example' => 'exercise-report',
      'Argument example' => 'exercise-report article',
    ),
    'aliases' => array('erp'),
  );

  $items['exercise-test'] = array(
    'description' => dt('Shows Detailed Status.'),
    'arguments'   => array(
      'arg1'    => dt('A Content Type.'),
    ),
    'options' => array(
      'uri' => 'The domain to exercise.',
      'db' => 'A foreign database to scan.',
      'alias' => 'A foreign database to scan.',
    ),
    'examples' => array(
      'Standard example' => 'exercise-test',
      'Argument example' => 'exercise-test article',
    ),
    'aliases' => array('et'),
  );

  return $items;
}

/**
 * Callback function for drush exercise-nodes - exns.
 *
 * Callback is called by using drush_hook_command() where
 * hook is the name of the module (MYMODULE) and command is the name of
 * the Drush command with all "-" characters
 * converted to "_" characters (my_command).
 *
 * $arg1
 *   An optional argument
 */
function drush_exerciser_exercise_nodes($arg1 = NULL) {

  $status = exerciser_exercise_get_status($arg1);
  if ($status != 'ready') {
    print "Current Status - $status.\r\n";
    print "Run the exercise-stop command to stop previous runs and try again.\r\n";
    print "You may want to add the --full option     drush exercise-stop --full..\r\n";
    return;
  }

  $should_truncate = FALSE;
  $restarting = FALSE;
  $abort = FALSE;
  $exerciser_run_type = variable_get(EXERCISE_RUN_TYPE, '');
  $exerciser_run_content_type = variable_get(EXERCISE_RUN, '');
  $exerciser_run_size = variable_get(EXERCISE_RUN_SIZE, '');
  $exerciser_run_current_position = variable_get(EXERCISE_RUN_CURRENT_POSITION, '');
  $exerciser_row_count = exerciser_get_row_count();

  if (!empty($exerciser_run_type) &&
      !empty($exerciser_run_content_type) &&
      !empty($exerciser_run_size) &&
      !empty($exerciser_run_current_position)) {

    $options_arr_1 = array('1' => 'Restart Existing Job', '2' => 'Clear Old Job And Start New Run');

    $choice = drush_choice($options_arr_1, "  There is an existing $exerciser_run_type job for the $exerciser_run_content_type content type
    Completed $exerciser_run_current_position/$exerciser_run_size
    Do you want to restart that job?");
    if ($choice != 0) {
      if ($choice == 1) {
        $should_truncate = FALSE;
        $restarting = TRUE;
      }
      elseif($choice == 2) {
        $should_truncate = TRUE;
        $restarting = FALSE;
      }
    }
    else {
      return;
    }
  }
  elseif ($exerciser_row_count > 0) {

    $options_arr_2 = array('1' => 'Continue With New Run.', '2' => 'View Data.');

    $choice = drush_choice($options_arr_2, "  There are $exerciser_row_count rows of data available from the last run.
    Do you want to continue with a new job ?");
    if ($choice != 0) {
      if ($choice == 1) {
        $should_truncate = TRUE;
        $restarting = FALSE;
      }
      elseif($choice == 2) {
        // View data.
        drush_exerciser_exercise_report();
        return 0;
      }
    }
    else {
      return;
    }
  }

  $continue = drush_get_option('continue', FALSE);
  $flush = drush_get_option('flush', FALSE);
  if ($continue != FALSE || $flush == TRUE || $should_truncate == TRUE) {
    exerciser_truncate();
  }

  if ($restarting == TRUE) {
    $retval = exerciser_exercise_nodes($exerciser_run_content_type);
  }
  else {
    $retval = exerciser_exercise_nodes($arg1);
  }

  drush_log($retval, 'ok');
  drush_log('Completed Exercise Nodes.', 'ok');
  // Log to the command line with an OK status.

}

/**
 * Callback function for drush exercise-terms - exts.
 *
 * Callback is called by using drush_hook_command() where
 * hook is the name of the module (MYMODULE) and command is the name of
 * the Drush command with all "-" characters
 * converted to "_" characters (my_command).
 *
 * $arg1
 *   An optional argument
 */
function drush_exerciser_exercise_terms($arg1 = NULL) {
  $retval = exerciser_exercise_terms($arg1);
  drush_log($retval, 'ok');

  // Log to the command line with an OK status.
  drush_log('Completed Exercise Terms.', 'ok');
}

/*
 * Callback function for drush exercise-node - exn.
 *
 * Callback is called by using drush_hook_command() where
 * hook is the name of the module (MYMODULE) and command is the name of
 * the Drush command with all "-" characters
 * converted to "_" characters (my_command).
 *
 * $arg1
 *   An optional argument
 */
function drush_exerciser_exercise_node($arg1 = NULL) {
  $retval = exerciser_exercise_node_drush($arg1);
  drush_log($retval, 'ok');

  // Log to the command line with an OK status.
  drush_log('Completed Exercise Node.', 'ok');
}


/**
 * Callback function for drush exercise-term - ext.
 *
 * Callback is called by using drush_hook_command() where
 * hook is the name of the module (MYMODULE) and command is the name of
 * the Drush command with all "-" characters
 * converted to "_" characters (my_command).
 *
 * $arg1
 *   An optional argument
 */
function drush_exerciser_exercise_term($arg1 = NULL) {
  $retval = exerciser_exercise_term_drush($arg1);
  drush_log($retval, 'ok');

  // Log to the command line with an OK status.
  drush_log('Completed Exercise Term.', 'ok');
}

/**
 * Callback function for drush exercise-status - est.
 *
 * Callback is called by using drush_hook_command() where
 * hook is the name of the module (MYMODULE) and command is the name of
 * the Drush command with all "-" characters
 * converted to "_" characters (my_command).
 *
 * $arg1
 *   An optional argument
 */
function drush_exerciser_exercise_status($arg1 = NULL) {
  $retval = exerciser_exercise_status($arg1);
  drush_log($retval, 'ok');

  // Log to the command line with an OK status.
  drush_log('Completed Exercise Status.', 'ok');
}

/**
 * Callback function for drush exercise-status-ping - esp.
 *
 * Callback is called by using drush_hook_command() where
 * hook is the name of the module (MYMODULE) and command is the name of
 * the Drush command with all "-" characters
 * converted to "_" characters (my_command).
 *
 * $arg1
 *   An optional argument
 */
function drush_exerciser_exercise_status_ping($arg1 = NULL) {
  $retval = exerciser_exercise_status_ping($arg1);
  drush_log($retval, 'ok');

  // Log to the command line with an OK status.
  drush_log('Completed Exercise Status Ping.', 'ok');
}

/**
 * Callback function for drush exercise-status - estp.
 *
 * Callback is called by using drush_hook_command() where
 * hook is the name of the module (MYMODULE) and command is the name of
 * the Drush command with all "-" characters
 * converted to "_" characters (my_command).
 *
 * $arg1
 *   An optional argument
 */
function drush_exerciser_exercise_stop($arg1 = NULL) {
  $status = exerciser_exercise_get_status($arg1);
  drush_confirm("Are you sure you want to stop the `$status` run ?", $indent = 0);

  $retval = exerciser_exercise_stop($arg1);
  drush_log($retval, 'ok');

  // Log to the command line with an OK status.
  drush_log('Stop the exerciser.', 'ok');
}

/**
 * Callback function for drush exercise-all - exa.
 *
 * Callback is called by using drush_hook_command() where
 * hook is the name of the module (MYMODULE) and command is the name of
 * the Drush command with all "-" characters
 * converted to "_" characters (my_command).
 *
 * $arg1
 *   An optional argument
 */
function drush_exerciser_exercise_all($arg1 = NULL) {

  $retval = exerciser_exercise_all($arg1);
}

/**
 * Callback function for drush exercise-get-last-complete-run - exlcr.
 *
 * Callback is called by using drush_hook_command() where
 * hook is the name of the module (MYMODULE) and command is the name of
 * the Drush command with all "-" characters
 * converted to "_" characters (my_command).
 *
 * $arg1
 *   An optional argument
 */
function drush_exerciser_exercise_get_last_complete_run($arg1 = NULL) {

  $retval = exerciser_exercise_get_last_complete_run($arg1);
}

/**
 * Callback function for drush exercise-get-next-run - exgnr.
 *
 * Callback is called by using drush_hook_command() where
 * hook is the name of the module (MYMODULE) and command is the name of
 * the Drush command with all "-" characters
 * converted to "_" characters (my_command).
 *
 * $arg1
 *   An optional argument
 */
function drush_exerciser_exercise_get_next_run($arg1 = NULL) {

  $retval = exerciser_exercise_get_next_run($arg1);
}

//-------------------------------------------------------------
// ask which kind
function drush_exerciser_exercise_report($arg1 = NULL) {
  $row_count = 0;
  $validated_count = 0;
  $un_validated_count = 0;

  $options_arr = array('1' => 'Show All', '2' => 'Show Validated Nodes', '3' => 'Show Unvalidated Nodes');

  $choice = drush_choice($options_arr, "  What type of report to display ?");
  if ($choice != 0) {
    if ($choice == 1) {
      $sql = 'SELECT * FROM `exerciser`';
    }
    elseif($choice == 2) {
      $sql = 'SELECT * FROM `exerciser` WHERE `size` > 0 AND `validated` = 1';
    }
    elseif($choice == 3) {
      $sql = 'SELECT * FROM `exerciser` WHERE `size` = 0 OR `validated` = 0';
    }

    if ($choice > 0 &&  $choice < 4) {

    }

    print "\r\n";
    print "+-------------+-------------+-------------+\r\n";
    print "| nid         | size        | validated   |\r\n";
    print "+-------------+-------------+-------------+\r\n";
    $results = db_query($sql);
    foreach ($results as $row) {
      print '| ' . str_pad($row->nid, 12) . '| ' . str_pad($row->size, 12) . '| ' . str_pad($row->validated, 12) . "|\r\n";
      $row_count++;
      if ($row->validated == 0) {
        $un_validated_count++;
      }
      elseif ($row->validated == 1) {
        $validated_count++;
      }
    }

    print "+-------------+-------------+-------------+\r\n";
    print "$row_count rows in set\r\n";
    print "$validated_count were Validated\r\n";
    print "$un_validated_count could not be Validated\r\n";

  }

  drush_log($retval, 'ok');

  // Log to the command line with an OK status.
  drush_log('Completed Exercise Status Report.', 'ok');
}



// $arg1 content type
//'uri' => 'The domain to exercise.',
//'database' => 'A foreign database to scan.',

function drush_exerciser_exercise_test($arg1 = NULL) {

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
