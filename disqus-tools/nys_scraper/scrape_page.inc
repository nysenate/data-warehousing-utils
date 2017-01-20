<?php

include 'phpQuery-onefile.inc';
    

// it gets the element text unless an attribute is specified
    
function get_container_text($url, $selector, $attribute = null)
{

	$ctx1 = stream_context_create(array( 
      'http' => array( 
          'timeout' => 2400
          ) 
      ) 
  	);  

    $page_contents =  file_get_contents($url, 0, $ctx1);
    if ($page_contents !== false)
    {

        $doc = phpQuery::newDocument($page_contents);
    
        phpQuery::selectDocument($doc);

        if (empty($attribute) == false)
            $results = pq($selector)->attr($attribute);
        else
            $results = pq($selector)->text();
    
        if (empty($results) == false)
            return $results;
        else
            return false;
        
    }
    else
        return false;
    

}
  

