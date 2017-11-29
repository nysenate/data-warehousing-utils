<?php

function exerciser_monitor_page($arg1) {
  // Need some handler for hook_menu().
}

// Gather page data.

$exercise_run_type = variable_get(EXERCISE_RUN_TYPE, '');
$exercise_run = variable_get(EXERCISE_RUN, '');
$exercise_run_size = variable_get(EXERCISE_RUN_SIZE, '');
$exercise_run_current_position = variable_get(EXERCISE_RUN_CURRENT_POSITION, '');
$exercise_run_current_id = variable_get(EXERCISE_RUN_CURRENT_ID, '');
$exercise_run_current_timestamp = variable_get(EXERCISE_RUN_CURRENT_TIMESTAMP, '');
if (!empty($exercise_run_current_timestamp) && is_numeric($exercise_run_current_timestamp) && $exercise_run_current_timestamp > 0) {
  $exercise_run_current_time = date('m/d/Y H:i:s', (int)$exercise_run_current_timestamp);
}
else {
  $exercise_run_current_time = '';
}

?><html>
<head>
<meta http-equiv="refresh" content="5">
<title>Exercise Monitor</title>

<style>
table {border-collapse: collapse;}
</style>


</head>
<body>


<h1>Exercise Monitor</h1>

<table style="width:100%" border="1">
 <tr>
   <th>Name</th>
   <th>Value</th>
 </tr>


 <tr>
   <td><b>run_type</b></td>
   <td><?php print $exercise_run_type; ?></td>
 </tr>
 <tr>
   <td><b>run</b></td>
   <td><?php print $exercise_run; ?></td>
 </tr>
 <tr>
   <td><b>run_current_position</b></td>
   <td><?php print $exercise_run_current_position; ?></td>
 </tr>
 <tr>
   <td><b>run_size</b></td>
   <td><?php print $exercise_run_size; ?></td>
 </tr>
 <tr>
   <td><b>run_current_id</b></td>
   <td><?php print $exercise_run_current_id; ?></td>
 </tr>
 <tr>
   <td><b>run_current_timestamp</b></td>
   <td><?php print $exercise_run_current_time ?></td>
 </tr>
</table>


</body>
</html>
