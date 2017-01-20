<?php

function nys_disqus_processor_disqus_update_thread_link($arg1, $arg2) {

  $forum = variable_get('disqus_domain', 'nysenateopenleg');

  if (empty($arg1) == FALSE) {
    $thread_ident = $arg1;
  }
  elseif (empty($arg1) == TRUE || empty($arg1) == TRUE) {
	  print "A thread ID or identifier must be supplied as the first argument.\r\n";
      return;
  }

  $disqus = disqus_api();
  if ($disqus) {

    try {
      // Load the thread data from disqus. Passing thread is required to allow the thread:ident call to work correctly. There is a pull request to fix this issue.
      if (is_numeric($thread_ident) == TRUE) {
        $thread = $disqus->threads->details(array('forum' => $forum, 'thread' => $thread_ident, 'version' => '3.0'));
      }
      else {
        $thread = $disqus->threads->details(array('forum' => $forum, 'thread:ident' => $thread_ident, 'thread' => '1', 'version' => '3.0'));
      }
    }
    catch (Exception $exception) {
      print t('There was an error loading the thread details from Disqus.');
      //drupal_set_message(t('There was an error loading the thread details from Disqus.'), 'error');
      //watchdog('disqus', 'Error loading thread details for node @nid. Check your API keys.', array('@nid' => $node->nid), WATCHDOG_ERROR, 'admin/config/services/disqus');
    }

    print "ThreadID: ";
    print_r($thread->id);
    print "\r\n";

	if (empty($arg2) == TRUE) {
      print "No new link argumwnt was supplied as teh second argument.\r\n";
      return;
	}

    if (isset($thread->id)) {
      try {

         $disqus->threads->update(array('access_token' => variable_get('disqus_useraccesstoken', ''),
        								'thread' => $thread->id,
        								'forum' => $forum,
        								//'title' => 'New title',
        								'url' => $arg2,
        								//'old_identifier' => $thread_identifier,
        								//'identifier' => $arg2,
        								'version' => '3.0'));
      }
      catch (Exception $exception) {
        print t("There was an error updating the thread details on Disqus.\r\n");
		print_r($exception);
        //drupal_set_message(t('There was an error updating the thread details on Disqus.'), 'error');
        //watchdog('disqus', 'Error updating thread details for node @nid. Check your user access token.', array('@nid' => $node->nid), WATCHDOG_ERROR, 'admin/config/services/disqus');
      }
    }

  }

}
