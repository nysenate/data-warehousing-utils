<?php
function nys_disqus_processor_remove_thread($arg1, $arg2) {

  $forum = variable_get('disqus_domain', 'nysenateopenleg');

  $disqus = disqus_api();
  if ($disqus) {
      try {
        // Load the thread data from disqus. Passing thread is required to allow the thread:ident call to work correctly. There is a pull request to fix this issue.
        $thread = $disqus->threads->details(array('forum' => $forum, 'thread:ident' => $arg1, 'thread' => '1', 'version' => '3.0'));

        //$thread = $disqus->threads->details(array('forum' => $forum, 'thread:ident' => $arg1, 'thread' => '1', 'version' => '3.0'));
      }
      catch (Exception $exception) {
        print "There was an error loading the thread details from Disqus.\r\n";
        //drupal_set_message(t('There was an error loading the thread details from Disqus.'), 'error');
        //watchdog('disqus', 'Erro
      }
        if (isset($thread->id)) {
        
          try {
            $disqus->threads->remove(array('access_token' => variable_get('disqus_useraccesstoken', ''), 'thread' => $thread->id, 'forum' => $forum, 'version' => '3.0'));
          }
          catch (Exception $exception) {
            print "There was an error removing the thread on Disqus.\r\n";
            //drupal_set_message(t('There was an error removing the thread on Disqus.'), 'error');
            //watchdog('disqus', 'Error removing thread for node @nid. Check your user access token.', array('@nid' => $node->nid), WATCHDOG_ERROR, 'admin/config/services/disqus');
          }
      }
      
   }
      
}