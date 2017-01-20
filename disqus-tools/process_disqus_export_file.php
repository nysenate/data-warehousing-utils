<?php

/**
 * @file
 * Reads an input disqus export file and parses it it.
 * Each thread is inserted into the `nys_disqus_comments` table.
 * Place at the root of frupal install.
 */

/**
 * Root directory of Drupal installation.
 */
define('DRUPAL_ROOT', getcwd());

include_once DRUPAL_ROOT . '/includes/bootstrap.inc';
drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);


/**
 * Put the thread in the database.
 */
function add_disqus_thread($id, $forum, $category, $link, $title, $message, $createdAt, $author_email, $author_name, $author_isAnonymous, $author_username, $ipAddress, $isClosed, $isDeleted) {

  $sql = "INSERT INTO `nys_disqus_comments` (`line_id`, `id`, `forum`, `category`, `link`, `title`, `message`, `createdAt`, `author_email`, `author_name`, `author_isAnonymous`, `author_username`, `ipAddress`, `isClosed`, `isDeleted`)
                                              VALUES (NULL,     '$id','$forum','$category','$link','$title','$message','$createdAT','$author_email','$author_name','$author_isAnonymous','$author_username','$ipAddress','$isClosed','$isDeleted')";

  db_query($sql);

}


/**
 * Handle the thread and map toadd_disqus_thread() function.
 */
function handle_thread_object($thread) {

     add_disqus_thread($thread->id->__toString(), //?? SOME ARE EMPTY SOME ARE FULL
                       $thread->forum->__toString(),
                       $thread->category->__toString(),//?? ALL EMPTY
                       $thread->link->__toString(),
                       addslashes($thread->title->__toString()),
                       $thread->message->__toString(),//?? THERE IS ONE
                       $thread->createdAt->__toString(),
                       $thread->author->email->__toString(),
                       $thread->author->name->__toString(),
                       $thread->author->isAnonymous->__toString(),
                       $thread->author->username->__toString(),
                       $thread->ipAddress->__toString(),
                       $thread->isClosed->__toString(),
                       $thread->isDeleted->__toString()
                      );


 }

// Main
$xml = simplexml_load_file('/Users/sethsnyder/Desktop/NYSENATE/DISQUS/disqus-db/SURVEY-3/nysenateopenleg-2017-01-15T22_28_20.381867-all.xml');

$count_of_threads = 0;


foreach ($xml->thread as $thread) {
   // Process the thread
   $fields = handle_thread_object($thread);

   // Increment Counter
   $count_of_threads++;

}

print '<h1>Complete</h1>';
print "<h3>$count_of_threads  Threads Imported.</h3>";
