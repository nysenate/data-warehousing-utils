<?php

function nys_disqus_processor_survey_threads($arg1) {

  $tbl_name_qty = db_query("SELECT COUNT(*) FROM information_schema.tables WHERE table_schema = 'nysenate' AND table_name = :tblname", array(":tblname" => $arg1))->fetchField();
  if ($tbl_name_qty == 0) {
    $arg1 =  NYS_SURVEY_DEFAULT_TABLE_NAME;
  }

  _process($arg1);

print  $arg1;

print "\r\nnys_disqus_processor_disqus_survey_threads($arg1)\r\n";
}

// Iterator
function _process($table_name) {

  drupal_set_time_limit(2000000);
  $number_of_threads_processed = 0;

  $connection = new MongoClient();
  $dbname = $connection->selectDB('nys_disqus');
  $threads = $dbname->threads;

  //$results = db_query("SELECT * FROM `$table_name` WHERE 1");
  // NOT IN MAKES IT EAY TO RESTART.
  $results = db_query("SELECT * FROM `$table_name` WHERE `line_id` NOT IN (SELECT `line_id` FROM `nys_disqus_processed` WHERE 1)");
  foreach ($results AS $row) {

    $number_of_threads_processed++;

    $line_id  = $row->line_id;
    $identifier = $row->id;
    $forum  = $row->forum;
    $category = $row->category;
    $link = $row->link;
    $title = $row->title;
    $message = $row->message;
    $createdAt = $row->createdAt;
    $author_email = $row->author_email;
    $author_name = $row->author_name;
    $author_isAnonymous = $row->author_isAnonymous;
    $author_username = $row->author_username;
    $ipAddress = $row->ipAddress;
    $isClosed = $row->isClosed;
    $isDeleted = $row->isDeleted;


    // Load the json form dsqus web service.
    if (empty($identifier) == FALSE) {
      $json = nys_disqus_processor_disqus_get_thread_json($identifier, 'ident');
    }
    else {
      $json = nys_disqus_processor_disqus_get_thread_json(_encode_if_necessary($link), 'link');
    }



    // Decode the json
    $thread_data = json_decode($json);

    if ($thread_data != NULL && $thread_data != FALSE) {

      if (is_array($thread_data->response->identifiers) == TRUE) {
        if (count($thread_data->response->identifiers) == 1) {
          $identifier2 = $thread_data->response->identifiers[0];
        }
        elseif (count($thread_data->response->identifiers) > 1) {
          $identifier2 = '';
          foreach ($thread_data->response->identifiers as $individual_identifier) {
            if (empty($identifier2) == TRUE) {
              $identifier2 = $identifier;
            }
            else {
              $identifier2 = $identifier2 . ',' . $identifier;
            }
          }

        }
        $id = $thread_data->response->id;
        $num_posts = $thread_data->response->posts;
        $moved = 0;
        $deleted = 0;
        $num_identifiers = count($thread_data->response->identifiers);
        $spare = time ();

        print "$id | $num_posts | $number_of_threads_processed | \r\n";

        nys_disqus_processed_add($line_id, $identifier, $identifier2, $id, $link, $num_posts, $moved, $deleted, $num_identifiers, $spare, $title);

        $threads->insert($thread_data);

        usleep(3500000);
      } // Valid data.

    } // Got data.

 } // Of foreach thread.

}

/**
 *  Insert or Update Thread Info
 */
function nys_disqus_processed_add($line_id, $identifier, $identifier2, $id, $link, $num_posts, $moved, $deleted, $num_identifiers, $spare, $title) {

  $title = addslashes($title);

  // Upsert
  $num_rows = db_query("SELECT COUNT(*) FROM `nys_disqus_processed` WHERE line_id = :line_id", array(":line_id" => $line_id))->fetchField();

  if ($num_rows == 0) {
    $sql = "INSERT INTO `nys_disqus_processed` (`line_id`, `identifier`, `identifier2`, `id`, `link`, `num_posts`, `moved`, `deleted`, `num_identifiers`, `spare`, `title`)
                                      VALUES ($line_id, '$identifier','$identifier2','$id','$link', $num_posts,  $moved , $deleted , $num_identifiers , $spare ,'$title')
                ";
  }
  elseif ($num_rows > 0) {

    $sql = "UPDATE `nys_disqus_processed` SET  `identifier` = '$identifier', `identifier2` = '$identifier2', `id` = '$id', `link` = '$link', `num_posts` = $num_posts, `moved` = $moved,  `deleted` = $deleted, `num_identifiers` = $num_identifiers, `spare` = $spare, `title` = '$title'
                WHERE line_id = $line_id";


  }

  db_query($sql);

}

/**
 *  Insert or Update Thread Info
 */
function nys_disqus_processed_data_add($line_id, $thread_json) {

  $num_rows = db_query("SELECT COUNT(*) FROM `nys_disqus_processed_data` WHERE line_id = :line_id", array(":line_id" => $line_id))->fetchField();

  if ($num_rows == 0) {
    $sql = "INSERT INTO `nysenate`.`nys_disqus_processed_data` (`line_id`, `thread_json`)
                                                       VALUES ('$line_id','$thread_json')";
  }
  elseif ($num_rows > 0) {
    $sql = "UPDATE `nys_disqus_processed_data` SET `thread_json` = '$thread_json' WHERE `line_id` = $line_id";

  }

  db_query($sql);

}

/**
 *  URL Encode in necesary for some links
 */
function _encode_if_necessary($url) {

    if (strpos($url, '?') !== FALSE || strpos($url, '&') !== FALSE || strpos($url, '%') !== FALSE    ) {
      return urlencode($url);
    }
    else {
    	return $url;
    }

}
