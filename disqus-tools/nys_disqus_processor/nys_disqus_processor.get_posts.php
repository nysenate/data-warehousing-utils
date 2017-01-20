<?php

function nys_disqus_processor_disqus_get_posts($arg1) {

 $json = nys_disqus_processor_disqus_get_posts_json($arg1, $arg2);

  // Display the response/ 
  print_r(json_decode($json));
  print "\r\n\r\n";
  print "\r\n=======================================================\r\n";
  print_r($json);
  print "\r\n=======================================================\r\n";

}

function nys_disqus_processor_disqus_get_posts_json($arg1, $arg2) {

  if (empty($arg1) == TRUE) {
    print "\r\nNo Thread Id argument was supplied.\r\n";
    return;
  }

  ini_set('display_errors', 'on');
  
  $forum = variable_get('disqus_domain', 'nysenateopenleg');
  $key = variable_get('disqus_publickey');
  	
  if (is_numeric($arg1) == TRUE) {
  	// Arg is a thread ID.
  	$thread = $arg1;
  	$endpoint = 'http://disqus.com/api/3.0/posts/list.json?api_key='.urlencode($key).'&forum='.$forum.'&thread='.urlencode($thread);
  }

  // Setup curl to make a call to the endpoint.
  $session = curl_init($endpoint);

  // Indicates that we want the response back rather than just returning a "TRUE" string.
  curl_setopt($session, CURLOPT_RETURNTRANSFER, true);

  // Execute GET and get the session back.
  $result = curl_exec($session);

  // Close connection.
  curl_close($session);

  // Display the response/ 
  return $result;

}
