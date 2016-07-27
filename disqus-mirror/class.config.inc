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
   *            )
   *   )
   * 'index' = the index name to use in Config->options
   * 'val' = if a value is required (0 = No, 1 = Yes, 2 = Optional)
   * 'label' = a user-friendly name for this option
   * 'short' = an optional, single-character shortcut (e.g., -h vs --help)
   * 'description = a user-friendly description for this option
   **/
  protected static $_available_command_options = array(
    'config' => array(
      'index' => 'config_file',
      'val' => 1,
      'label' => 'Config file',
      'short' => 'c',
      'description' => "File holding all runtime configurations",
    ),
    'forum' => array(
      'index' => 'disqus_forum',
      'val' => 1,
      'label' => 'Disqus Forum',
      'short' => 'f',
      'description' => "The shortname of the Disqus forum to reference in API calls",
    ),
    'help' => array(
      'index' => 'help',
      'val' => 0,
      'label' => 'Help',
      'description' => 'This help text',
    ),
  );
}