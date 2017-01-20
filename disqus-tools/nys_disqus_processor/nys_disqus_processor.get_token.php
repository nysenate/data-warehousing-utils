<?php

function nys_disqus_processor_disqus_get_token($arg1) {
  //$token = variable_get('nys_disqus_processor_token',  '');
  $token = variable_get('disqus_useraccesstoken',  '');
  print "\r\nToken = $token\r\n";
}