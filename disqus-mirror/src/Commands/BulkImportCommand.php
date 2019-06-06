<?php

namespace DisqusImporter\Commands;

use GetOpt\Command;
use GetOpt\GetOpt;
use GetOpt\Operand;

class BulkImportCommand extends CommandTemplate {

  public function handle() {
    global $disqus;

    // run categories
    $a = new API_Object_Categories($disqus);
    $a->executeSearch();

    // run threads
    $b = new API_Object_Threads($disqus);
    $b->executeSearch();

    // run posts
    $c = new API_Object_Posts($disqus);
    $c->executeSearch();
  }
}