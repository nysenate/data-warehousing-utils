<?php
require_once __DIR__ . '/vendor/autoload.php';

require_once 'class.logger.php';
require_once 'class.configbase.inc';
require_once 'class.config.inc';
require_once 'class.apiobject.inc';

// The Disqus API wrapper
require_once 'disqusapi/disqusapi.php';

// Drupal's Database Abstraction Layer
require_once 'database/database.inc';
require_once 'database/query.inc';
require_once 'database/select.inc';
require_once 'database/mysql/database.inc';
require_once 'database/mysql/query.inc';


/**
 * Miscellaneous helper functions
 */

function array_ifelse($index, $source, $default=null) {
  $ret = $default;
  switch (true) {
    case is_array($source):
      if (array_key_exists($index, $source)) {
        $ret = $source[$index];
      }
      break;
    case is_object($source):
      if (property_exists($source, $index)) {
        $ret = $source->{$index};
      }
      break;
  }
  return $ret;
}