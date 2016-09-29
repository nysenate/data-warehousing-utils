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
    ),
    'api-secret' => array(
      'val' => 1,
      'label' => 'API Secret Key',
      'description' => 'The API secret key used to connect to the Disqus API.  See your Disqus admin dashboard.',
      'required' => TRUE,
    ),
    'db-name' => array(
      'val' => 1,
      'label' => 'Database Name',
      'short' => 'D',
      'description' => 'Name of the database used to hold the mirrored comments.',
      'default' => 'disqus_mirror',
    ),
    'db-user' => array(
      'val' => 1,
      'label' => 'Database Username',
      'short' => 'u',
      'description' => 'Username to use for the database connection.',
      'required' => TRUE,
    ),
    'db-pass' => array(
      'val' => 1,
      'label' => 'Database Password',
      'short' => 'p',
      'description' => 'Password to use for the database connection.',
      'required' => TRUE,
    ),
    'db-host' => array(
      'val' => 1,
      'label' => 'Database Host',
      'short' => 'H',
      'description' => 'IP address or resolvable DNS name of the database host.',
      'default' => 'localhost',
    ),
    'db-port' => array(
      'val' => 1,
      'label' => 'Database Port',
      'short' => 'P',
      'description' => 'Port to use for the database connection.',
      'default' => '3306',
    ),
    'error-log' => array(
      'val' => 1,
      'label' => 'Error Log Filename',
      'description' => 'Full path/filename to use for the application error log.',
      'default' => 'error_log',
    ),
    'error-log-level' => array(
      'val' => 1,
      'label' => 'Error Log Level',
      'description' => 'Detail level for logging engine.  Can be any of the labels: FATAL, ERROR, WARN, INFO, DEBUG.  Numeric values 0-4 will be translated respectfully.  Values less than 0 are considered FATAL; greater than 4 are considered CUSTOM.',
      'default' => 'WARN',
    )
  );

}