<?php
/* 
 * Loads the xml export file from disqus 
 * splits it out to differnt output files depending on the data
*/

$xml = simplexml_load_file('/Users/sethsnyder/Desktop/NYSENATE/DISQUS/XML-EXTRACT-TNG/V1all.xml');

$count_of_threads = 0;

$node_slash_nid_style_identifiers = fopen("/Users/sethsnyder/Desktop/NYSENATE/DISQUS/XML-EXTRACT-TNG/node_slash_nid_style_identifiers.csv","w");
$other_style_identifiers = fopen("/Users/sethsnyder/Desktop/NYSENATE/DISQUS/XML-EXTRACT-TNG/other_style_identifiers.csv","w");
$links_for_empty_identifiers = fopen("/Users/sethsnyder/Desktop/NYSENATE/DISQUS/XML-EXTRACT-TNG/links_for_empty_identifiers.csv","w");

foreach ($xml->thread as $thread) {

  // Split it out and write it tothe appropriateoutput stream.
  process_thread($thread, $node_slash_nid_style_identifiers, $other_style_identifiers, $links_for_empty_identifiers);
  //fputcsv($file,$fields);

  $count_of_threads++;

//if ($count_of_threads == 100)
//  break;
}

fclose($node_slash_nid_style_identifiers);
fclose($other_style_identifiers);
fclose($links_for_empty_identifiers);

print "\r\n\r\nNumber of threads processed = $count_of_threads \r\n";

print 'done';


function process_thread($thread, $node_slash_nid_style_identifiers, $other_style_identifiers, $links_for_empty_identifiers) {
  // Get the thee identifier
  $thread_identifier = $thread->id->__toString();

  if (empty($thread_identifier) == TRUE)  {
    // Empty Identifier.
  	$thread_link = $thread->link->__toString();
  	fputcsv($links_for_empty_identifiers, array($thread_link));

  }
  else {
  	// Non empty identifier.
  	// if node/nnnnn style
    if (strncmp($thread_identifier, 'node/', 5 ) == 0) {
      $thread_identifier_array = explode ('/', $thread_identifier);
      if (count($thread_identifier_array) == 2) {
        $node_id = $thread_identifier_array[1];
        fputcsv($node_slash_nid_style_identifiers, array($node_id));
      }
    }
    else {
        // A link or some other style identifier.
		fputcsv($other_style_identifiers, array($thread_identifier));
    }

  }

}
