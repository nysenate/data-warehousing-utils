<?php

function nys_disqus_processor_callback() {

  parse_str($_SERVER['QUERY_STRING']);
  
  variable_set('nys_disqus_processor_token',  $code);

  watchdog('nys_dpc', 'nys_disqus_processor_callback ' . $code);

// puts ards indo

print ' bye code = ' . $code;


}