<?php
// special log level for logging API returns
const NYSS_LOG_LEVEL_DEBUGAPI = 5;

class API_Object {
  protected static $table_name;
  protected static $object_name;
  protected static $object_action;
  protected static $field_map;
  protected static $mangle_map;
  protected $config;
  protected $disqus;

  public function __construct($disqus) {
    $this->config = Config::getInstance();
    $this->log = Logger::getInstance();
    $this->disqus = $disqus;
  }

  public static function insertFromData($data) {
    // Get a Logger instance
    $log = Logger::getInstance();

    $log->log("insertFromData() called in ".get_called_class(), NYSS_LOG_LEVEL_DEBUG);
    $log->log("passed data = \n".var_export($data,1), NYSS_LOG_LEVEL_DEBUGAPI);

    $fields = array();

    // Build the array used for the db_insert() call.  Note that certain fields
    // may need special handling due to how they get translated by the DAL.  The
    // $mangle_map array references these requirements.
    foreach (static::$field_map as $orig=>$dest) {
      $data_point = property_exists($data, $orig) ? $data->{$orig} : NULL;
      switch(array_ifelse($orig, static::$mangle_map)) {
        case 'boolean': $fields[$dest] = (int) ((boolean)$data_point); break;
        case 'string':  $fields[$dest] = (string) $data_point; break;
        case 'integer': $fields[$dest] = intval($data_point); break;
        case 'float':   $fields[$dest] = floatval($data_point); break;
        default: $fields[$dest] = $data_point; break;
      }
    }
    $log->log("Final fields for INSERT:\n" . var_export($fields,1), NYSS_LOG_LEVEL_DEBUG);

    // Insert the new record.
    try {
      $insert_id = db_insert(static::$table_name)
        ->fields($fields)
        ->execute();
    }
    catch (Exception $e) {
      $log->log("Exception generated during INSERT in " .get_called_class() .
        ":\nCode: ".var_export($e->getCode(),1)."\nMessage: ".var_export($e->getMessage(),1),
        NYSS_LOG_LEVEL_ERROR);
      return NULL;
    }
    $log->log("Inserted " . static::$object_name . " as id={$insert_id}", NYSS_LOG_LEVEL_INFO);

    return $insert_id;
  }

  protected function preInsert(&$data) {
  }

  protected function postInsert($insert_id, $data) {
  }

  protected function getCursorName() {
    return static::$object_name . '_' . static::$object_action . '_cursor';
  }

  protected function setCursor($cursor) {
    if ($cursor) {
      try {
        $ret = db_merge('settings')
          ->key(array('name' => static::getCursorName()))
          ->fields(array('value' => serialize($cursor)))
          ->execute();
      }
      catch (Exception $e) {
        $this->log->log("Exception generated during cursor MERGE:\nCode: ".var_export($e->getCode(),1)."\nMessage: ".var_export($e->getMessage(),1), NYSS_LOG_LEVEL_ERROR);
        return NULL;
      }
      $this->log->log("setCursor set value.  ret=" . var_export($ret, 1), NYSS_LOG_LEVEL_DEBUG);
    }
  }

  protected function fetchCursor() {
    // Try to read cursor information from the db.
    try {
    $cursor_value = db_select('settings', 's')
      ->fields('s', array('value'))
      ->condition('name', static::getCursorName())
      ->execute()
      ->fetchField();
    }
    catch (Exception $e) {
      $this->log->log("Exception generated during cursor SELECT:\nCode: ".var_export($e->getCode(),1)."\nMessage: ".var_export($e->getMessage(),1), NYSS_LOG_LEVEL_ERROR);
      return NULL;
    }
    $this->log->log("fetchCursor found ".var_export($cursor_value,1), NYSS_LOG_LEVEL_DEBUG);

    // Set the return.
    $ret = $cursor_value
      ? unserialize($cursor_value)
      : (object) array('hasNext'=>false, 'next'=>NULL);

    return $ret;
  }

  public function executeSearch() {
    $this->log->log("Executing API search for: " . get_called_class(), NYSS_LOG_LEVEL_INFO);

    // Initialize the cursor.
    $cursor = $this->fetchCursor();
    if (!is_object($cursor)) {
      $this->log->log("Aborting - failed to find cursor for: " . get_called_class(), NYSS_LOG_LEVEL_ERROR);
      return NULL;
    }

    // Repeat this loop until the cursor comes back empty.
    do {
      // Generate options for this API call.
      $req_opts = array('forum'=>$this->config->disqus_forum, 'order'=>'asc', 'limit'=>100);
      if ($cursor->next) {
        $req_opts['cursor']=$cursor->next;
      }
      $this->log->log("Final request options:\n".var_export($req_opts,1), NYSS_LOG_LEVEL_DEBUG);

      // Execute the call using the established Disqus object.
      $retry = 0;
      $ret = NULL;
      do {
        try {
          $this->log->log("Attempting call to Disqus API " . static::$object_name . ":" . static::$object_action, NYSS_LOG_LEVEL_DEBUG);
          $ret = $this->disqus->{static::$object_name}->{static::$object_action}($req_opts);
        }
        catch (Exception $e) {
          $this->log->log("Exception generated during API call:\nCode: ".var_export($e->getCode(),1)."\nMessage: ".var_export($e->getMessage(),1), NYSS_LOG_LEVEL_ERROR);
        }
        $retry++;
        $this->log->log("Full API return:\n" . var_export($ret,1), NYSS_LOG_LEVEL_DEBUGAPI);
      } while ($retry<5 && is_null($ret));
      if (is_null($ret)) {
        $this->log->log("Aborting - API call to Disqus did not return.", NYSS_LOG_LEVEL_ERROR);
        return NULL;
      }

      $this->log->log("Found " . count($ret) . " returns", NYSS_LOG_LEVEL_INFO);

      // Get the most recent cursor returned.
      $cursor = DisqusAPICursor::getCursor();
      $this->log->log("Request cursor object:\n" . var_export($cursor,1), NYSS_LOG_LEVEL_DEBUG);

      // Process the records from the API call.
      foreach ($ret as $index=>&$data) {
        $this->log->log("Processing " . static::$object_name . " id={$data->id}", NYSS_LOG_LEVEL_INFO);
        // For each record, check to make sure this object has not already been inserted.
        // Every object has an ID generated by Disqus.
        try {
          $exists = db_select(static::$table_name)
            ->condition(static::$field_map['id'], $data->id)
            ->countQuery()
            ->execute()
            ->fetchField();
          $this->log->log(" .. (check for existing found $exists)", NYSS_LOG_LEVEL_INFO);
        }
        catch (Exception $e) {
          $this->log->log("Exception generated during record search:\nCode: ".var_export($e->getCode(),1)."\nMessage: ".var_export($e->getMessage(),1), NYSS_LOG_LEVEL_ERROR);
          continue;
        }

        // If the object does not exist, insert it.
        if (!$exists) {
          $this->log->log("Generating INSERT", NYSS_LOG_LEVEL_DEBUG);

          // Call the preInsert() method so children can do special stuff.
          $this->preInsert($data);

          try {
            $insert_id = static::insertFromData($data);
          }
          catch (Exception $e) {
            $this->log->log("Exception generated during record INSERT:\nCode: ".var_export($e->getCode(),1)."\nMessage: ".var_export($e->getMessage(),1), NYSS_LOG_LEVEL_ERROR);
          }

          // Call the postInsert() method so children can do special stuff.
          $this->postInsert($insert_id, $data);
        }
        $this->log->log("Done processing " . static::$object_name . " {$data->id}", NYSS_LOG_LEVEL_DEBUG);
      }
      $this->log->log("Done processing request, cursor->hasNext = " . var_export($cursor->hasNext,1), NYSS_LOG_LEVEL_DEBUG);

      // Save the current cursor to retain "last read" status
      $this->setCursor($cursor);
    } while ($cursor->hasNext);
    $this->log->log("Finished executing API search for: " . get_called_class(), NYSS_LOG_LEVEL_INFO);
  }
}

class API_Object_Categories extends API_Object {
  protected static $table_name = 'categories';
  protected static $object_name = 'categories';
  protected static $object_action = 'list';
  protected static $field_map = array(
    'title' => 'title',
    'isDefault' => 'is_default',
    'order' => 'dq_order',
    'forum' => 'forum',
    'id' => 'cid'
  );
  protected static $mangle_map = array();
}

class API_Object_Threads extends API_Object {
  protected static $table_name = 'threads';
  protected static $object_name = 'threads';
  protected static $object_action = 'list';
  protected static $field_map = array(
    'feed' => 'feed',
    'dislikes' => 'dislikes',
    'likes' => 'likes',
    'message' => 'message',
    'id' => 'tid',
    'createdAt' => 'created_at',
    'category' => 'category',
    'author' => 'author',
    'userScore' => 'user_score',
    'isSpam' => 'is_spam',
    'signedLink' => 'signed_link',
    'isDeleted' => 'is_deleted',
    'raw_message' => 'raw_message',
    'isClosed' => 'is_closed',
    'link' => 'link',
    'slug' => 'slug',
    'forum' => 'forum',
    'clean_title' => 'clean_title',
    'posts' => 'posts',
    'userSubscription' => 'user_sub',
    'title' => 'title',
    'highlightedPost' => 'highlighted',
    );
  protected static $mangle_map = array(
    'isSpam' => 'boolean',
    'isDeleted' => 'boolean',
    'isClosed' => 'boolean',
    'userSubscription' => 'boolean',
  );

  protected function postInsert($insert_id, $data) {
    // Threads can have "identifiers" attached to them.  Make sure they get recorded.
    if ((int)$insert_id && count($data->identifiers)) {
      $query = db_insert('thread_ident')->fields(array('tid','thread_id','ident'));
      foreach ($data->identifiers as $key=>$val) {
        $query->values(array($data->id, $insert_id, $val));
      }
      try {
        $query->execute();
      }
      catch (Exception $e) {
        $this->log->log("Exception generated during identifier INSERT:\nCode: ".var_export($e->getCode(),1)."\nMessage: ".var_export($e->getMessage(),1), NYSS_LOG_LEVEL_ERROR);
      }
    }
  }
}

class API_Object_Posts extends API_Object {
  protected static $table_name = 'posts';
  protected static $object_name = 'posts';
  protected static $object_action = 'list';
  protected static $field_map = array(
    'isHighlighted' => 'is_highlighted',
    'isFlagged' => 'is_flagged',
    'forum' => 'forum',
    'parent' => 'parent',
    'author' => 'author',
    'points' => 'points',
    'isApproved' => 'is_approved',
    'dislikes' => 'dislikes',
    'raw_message' => 'raw_message',
    'isSpam' => 'is_spam',
    'thread' => 'thread',
    'numReports' => 'num_reports',
    'isDeletedByAuthor' => 'is_author_deleted',
    'createdAt' => 'created_at',
    'isEdited' => 'is_edited',
    'id' => 'pid',
    'isDeleted' => 'is_deleted',
    'likes' => 'likes',
  );
  protected static $mangle_map = array(
    'isHighlighted' => 'boolean',
    'isFlagged' => 'boolean',
    'isApproved' => 'boolean',
    'isSpam' => 'boolean',
    'isDeletedByAuthor' => 'boolean',
    'isEdited' => 'boolean',
    'isDeleted' => 'boolean',
  );

  protected function preInsert(&$data) {
    $this->log->log("Attempting to insert author:\n".var_export($data->author,1), NYSS_LOG_LEVEL_DEBUGAPI);
    $ret = API_Object_Authors::insertFromData($data->author);
    $this->log->log("Inserting author returned ".var_export($ret,1), NYSS_LOG_LEVEL_DEBUG);
    $data->author = $ret;
  }
}

class API_Object_Authors extends API_Object {
  protected static $table_name = 'authors';
  protected static $object_name = '';
  protected static $object_action = '';
  protected static $field_map = array(
    'username' => 'username',
    'about' => 'about',
    'name' => 'name',
    'disable3rdPartyTrackers' => 'disable_trackers',
    'isPowerContributor' => 'power_contrib',
    'joinedAt' => 'joined_at',
    'rep' => 'rep',
    'location' => 'location',
    'isPrivate' => 'is_private',
    'signedUrl' => 'signed_url',
    'isPrimary' => 'is_primary',
    'isAnonymous' => 'is_anon',
    'id' => 'aid',
  );
  protected static $mangle_map = array(
    'username' => 'string',
    'about' => 'string',
    'name' => 'string',
    'rep' => 'float',
    'location' => 'string',
    'signedUrl' => 'string',
    'id' => 'integer',
    'disable3rdPartyTrackers' => 'boolean',
    'isPowerContributor' => 'boolean',
    'isPrivate' => 'boolean',
    'isPrimary' => 'boolean',
    'isAnonymous' => 'boolean',
  );
}

