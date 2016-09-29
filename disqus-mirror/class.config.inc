<?php
class Config extends ConfigBase {
  /**
   * Available options array.  Structure is:
   *   array( <long_option_name> = array(
   *            'index' => <string>,
   *            'val'   => ( 0 | 1 | 2 ),
   *            'label' => <string>,
   *            'short' => <character>,
   *            'description' => <string>
   *            'required' => <boolean>
   *            )
   *   )
   * 'index' = the index name to use in Config->options
   * 'val' = if a value is required (0 = No, 1 = Yes, 2 = Optional)
   * 'label' = a user-friendly name for this option
   * 'short' = an optional, single-character shortcut (e.g., -h vs --help)
   * 'description' = a user-friendly description for this option
   * 'required' = indicates if this option must be specified (by CLI or file)
   **/
  protected $_available_command_options = array(
    'forum' => array(
      'val' => 1,
      'label' => 'Disqus Forum',
      'short' => 'f',
      'description' => "The shortname of the Disqus forum to reference in API calls",
      'required' => TRUE,
    ),
    'create-tables' => array(
      'val' => 1,
      'label' => 'Create DB Tables',
      'description' => 'Force the script to run the SQL necessary to create the underlying database tables.  The script will exit once the queries are complete. Requires a secondary value of the filename containing the SQL.',
      'required' => FALSE,
    )
  );

}