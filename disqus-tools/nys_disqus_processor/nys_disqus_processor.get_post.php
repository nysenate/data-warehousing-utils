<?php

function nys_disqus_processor_disqus_get_post($arg1) {

$json = nys_disqus_processor_disqus_get_post_json($arg1, $arg2);

  // Display the response/ 
  print_r(json_decode($json));
  print "\r\n\r\n";
  print "\r\n=======================================================\r\n";
  print_r($json);
  print "\r\n=======================================================\r\n";

}


function nys_disqus_processor_disqus_get_post_json($arg1, $arg2) {

  if (empty($arg1) == TRUE) {
    print "\r\nNo Post Id was supplied as the argument.\r\n";
    return;
  }

  ini_set('display_errors', 'on');
  
  $key = variable_get('disqus_publickey');
  	
  if (is_numeric($arg1) == TRUE) {
  	// Arg is a thread ID.
  	$postId = $arg1;
  	$endpoint = 'http://disqus.com/api/3.0/posts/details.json?api_key='.urlencode($key).'&post='.$postId;
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