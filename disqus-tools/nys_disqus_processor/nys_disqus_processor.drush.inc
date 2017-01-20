<?php

/**
 * @file
 * File nys_statute_delete.drush.inc.
 */

/**
 * Implements hook_drush_help().
 */
function nys_disqus_processor_drush_help($command) {
  switch ($command) {

    case 'drush:load-token':
      return dt('Run load-token');

    case 'drush:get-token':
      return dt('Run get-token');

    case 'drush:get-thread':
      return dt('Run get-thread');

    case 'drush:get-posts':
      return dt('Run get-posts');

    case 'drush:get-post':
      return dt('Run get-post');

    case 'drush:get-post':
      return dt('Run get-post');

    case 'drush:update-thread-id':
      return dt('Run update-post-id');

    case 'drush:update-thread-link':
      return dt('Run update-thread-link');

    case 'drush:survey-threads':
      return dt('Run survey-threads');

    case 'drush:remove-thread':
      return dt('Run remove-thread');


  }
}

/**
 * Implements hook_drush_command().
 */
function nys_disqus_processor_drush_command() {
  $items = array();

  $items['disqus-load-token'] = array(
    'description' => dt('disqus-load-token'),
    'arguments'   => array(
      'arg1'    => dt('An optional argument'),
    ),
    'examples' => array(
      'Standard example' => 'drush disqus-load-token',
      'Argument example' => 'drush disqus-load-token',
    ),
    'aliases' => array('dlt'),
  );

  $items['get-token'] = array(
    'description' => dt('get-token'),
    'arguments'   => array(
      'arg1'    => dt('An optional argument'),
    ),
    'examples' => array(
      'Standard example' => 'drush get-token',
      'Argument example' => 'drush get-token',
    ),
    'aliases' => array('dtoken'),
  );

  $items['get-thread'] = array(
    'description' => dt('get-thread'),
    'arguments'   => array(
      'arg1'    => dt('Identifier or link'),
      'arg2'    => dt('ident or link'),
    ),
    'examples' => array(
      'Standard example' => 'drush get-thread 12345678',
      'Argument example' => 'drush get-thread http://youridentifier',
      'Argument example' => 'drush get-thread http://youridentifier ident',
      'Argument example' => 'drush get-thread http://yourlink link',
    ),
    'aliases' => array('dthread'),
  );

  $items['get-posts'] = array(
    'description' => dt('get-posts'),
    'arguments'   => array(
      'arg1'    => dt('An optional argument'),
    ),
    'examples' => array(
      'Standard example' => 'drush get-posts',
      'Argument example' => 'drush get-posts',
    ),
    'aliases' => array('dposts'),
  );

  $items['get-post'] = array(
    'description' => dt('get-post'),
    'arguments'   => array(
      'arg1'    => dt('An optional argument'),
    ),
    'examples' => array(
      'Standard example' => 'drush get-posts',
      'Argument example' => 'drush get-posts',
    ),
    'aliases' => array('dpost'),
  );

  $items['update-thread-id'] = array(
    'description' => dt('update-thread-id'),
    'arguments'   => array(
      'arg1'    => dt('thread id or url'),
      'arg2'    => dt('new ID'),
    ),
    'examples' => array(
      'Standard example' => 'drush update-thread-id 123456 node/3',
      'Argument example' => 'drush update-thread-id 123456 node/3',
    ),
    'aliases' => array('uthrid'),
  );

  $items['update-thread-link'] = array(
    'description' => dt('update-thread-link'),
    'arguments'   => array(
      'arg1'    => dt('thread id or url'),
      'arg2'    => dt('new ID'),
    ),
    'examples' => array(
      'Standard example' => 'drush update-thread-link 123456 http://new.com',
      'Argument example' => 'drush update-thread-link 123456 http://new.com',
    ),
    'aliases' => array('uthrfl'),
  );

  $items['survey-threads'] = array(
    'description' => dt('survey-threads'),
    'arguments'   => array(
      'arg1'    => dt('table name'),
      'arg2'    => dt('new ID'),
    ),
    'examples' => array(
      'Standard example' => 'drush table_name_special',
      'Argument example' => 'drush table_name_special',
    ),
    'aliases' => array('survey'),
  );

  $items['remove-thread'] = array(
    'description' => dt('remove-thread'),
    'arguments'   => array(
      'arg1'    => dt('table name'),
      'arg2'    => dt('new ID'),
    ),
    'examples' => array(
      'Standard example' => 'drush remove-thread',
      'Argument example' => 'drush remove-thread',
    ),
    'aliases' => array('rmtd'),
  );


  return $items;
}

/**
 * Callback function for drush load-token.
 *
 * $arg1
 *   An optional argument
 */
function drush_nys_disqus_processor_disqus_load_token($arg1 = NULL) {

  $retval = nys_disqus_processor_disqus_load_token($arg1);
  drush_log($retval, 'ok');

  drush_log('Completed Load Token.', 'ok');
}

/**
 * Callback function for drush get-token.
 *
 * $arg1
 *   An optional argument
 */
function drush_nys_disqus_processor_get_token($arg1 = NULL) {

  $retval = nys_disqus_processor_disqus_get_token($arg1);
  drush_log($retval, 'ok');

  drush_log('Completed Get Token.', 'ok');
}


/**
 * Callback function for drush get-thread.
 *
 * $arg1
 *   Thread Id.
 * $arg2
 *   nothing for thread id `ident` for identifier `link` for link.
 
 */
function drush_nys_disqus_processor_get_thread($arg1 = NULL, $arg2 = NULL) {

  $retval = nys_disqus_processor_disqus_get_thread($arg1, $arg2);
  drush_log($retval, 'ok');

  drush_log('Completed Get Thread.', 'ok');
}


/**
 * Callback function for drush get-posts.
 *
 * $arg1
 *   A Thread ID.
 */
function drush_nys_disqus_processor_get_posts($arg1 = NULL) {

  $retval = nys_disqus_processor_disqus_get_posts($arg1);
  drush_log($retval, 'ok');

  drush_log('Completed Get Posts.', 'ok');
}


/**
 * Callback function for drush get-post.
 *
 * $arg1
 *   A post argument
 */
function drush_nys_disqus_processor_get_post($arg1 = NULL) {

  $retval = nys_disqus_processor_disqus_get_post($arg1);
  drush_log($retval, 'ok');

  drush_log('Completed Get Post.', 'ok');
}

/**
 * Callback function for drush update-thread-id.
 *
 * $arg1
 *   A Thread ID.
 * $arg1
 *   New Thread ID. 
 */
function drush_nys_disqus_processor_update_thread_id($arg1 = NULL, $arg2 = NULL) {

  nys_disqus_processor_disqus_update_thread_id($arg1, $arg2);

  drush_log($retval, 'ok');

  drush_log('Completed Update Thread ID.', 'ok');
}

/**
 * Callback function for drush update-thread-link.
 *
 * $arg1
 *   A Thread ID.
 * $arg1
 *   New Thread Link. 
 */
function drush_nys_disqus_processor_update_thread_link($arg1 = NULL, $arg2 = NULL) {

  nys_disqus_processor_disqus_update_thread_link($arg1, $arg2);

  drush_log($retval, 'ok');

  drush_log('Completed Update Thread Link.', 'ok');
}

/**
 * Callback function for drush survey-threads.
 *
 * $arg1
 *   Batch Size.
 */
function drush_nys_disqus_processor_survey_threads($arg1 = NULL, $arg2 = NULL) {
  if (empty($arg1) == TRUE) {
    $default_survey_table_name = NYS_SURVEY_DEFAULT_TABLE_NAME;
    drush_confirm("No table name was supplied for the survey_threads command the default table `$default_survey_table_name` will be used. ?", $indent = 0);
  }

  nys_disqus_processor_survey_threads($arg1, $arg2);

  drush_log($retval, 'ok');

  drush_log('Completed Survey Threads.', 'ok');
}

/**
 * Callback function for drush remove-thread.
 *
 * $arg1
 *   A Thread ID.
 */
function drush_nys_disqus_processor_remove_thread($arg1 = NULL, $arg2 = NULL) {

  nys_disqus_processor_remove_thread($arg1, $arg2);

  drush_log($retval, 'ok');

  drush_log('Completed Remove Thread.', 'ok');
}

