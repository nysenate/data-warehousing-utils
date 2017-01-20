<?php
function nys_disqus_processor_remove_thread($arg1, $arg2) {

  $forum = variable_get('disqus_domain', 'nysenateopenleg');

  if (empty($arg1) == FALSE) {
    $thread_ident = $arg1;
  }
  else {
	  print "No thread ID or url was supplied.\r\n";
      return; 
  }

  $disqus = disqus_api();
  if ($disqus) {

    try {
      $disqus->threads->remove(array('access_token' => variable_get('disqus_useraccesstoken', ''), 'thread' => $arg1, 'forum' => $forum, 'version' => '3.0'));
    }
	catch (Exception $exception) {
      print "There was an error removing thread $arg1 on Disqus.  \r\n";
      //drupal_set_message(t('There was an error removing the thread on Disqus.'), 'error');
      //watchdog('disqus', 'Error removing thread for node @nid. Check your user access token.', array('@nid' => $node->nid), WATCHDOG_ERROR, 'admin/config/services/disqus');
    }
 
  }
 
}



