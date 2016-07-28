<?php

/**
 * Configuration class
 *
 * Reads and processes command line options and configuration file (INI)
 * settings.  Available CLI options are defined in a static structure.  Any
 * arguments without a matching definition entry are ignored.  Options may
 * also be stored in a configuration file (defaults to config.ini), or
 * passed in during runtime.
 *
 * This class should be extended for the application using it.  The child
 * class must provide its own definition for self::$_available_command_options.
 */
class ConfigBase {

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
   * 'description' = a user-friendly description for this option
   * 'required' = indicates if this option must be specified (by CLI or file)
   * 'default' = default value assigned if no other value is provided
   **/
  protected static $_available_command_options = array();

  // Default configuration file.
  protected static $_default_config_file = 'config.ini';

  // Resolved configuration array
  protected $options = array();

  // Raw command line options
  protected $cli_options = array();

  // Instance property for singleton pattern
  protected static $_instance = array();

  // Ensures config file is only read once.
  private $_config_loaded = FALSE;

  public static function getUsage() {
    $msg = array();
    foreach (static::$_available_command_options as $key=>$val) {
      $onemsg = '';
      if (array_ifelse('short',$val)) {
        $onemsg = "-{$val['short']} | ";
      }
      $onemsg .= "--{$key}";
      if (!array_ifelse('required',$val)) {
        $onemsg = "[$onemsg]";
      } else {
        $onemsg .= "  (required)";
      }
      $onemsg .= " {$val['label']}\n{$val['description']}";
      if (array_ifelse('default',$val)) {
        $onemsg .= " Default: {$val['default']}";
      }
      $msg[] = $onemsg;
    }
    return "\n\nUsage: \n\n" . implode("\n\n", $msg) . "\n";
  }

  /**
   * Config constructor.
   * @param array $options
   */
  protected function __construct(Array $options = array()) {
    // initialize CLI options
    $this->cli_options = ((php_sapi_name() == 'cli') ? static::parse_cli_options() : array());
    if (array_ifelse('help', $this->cli_options, FALSE)) {
      die(static::getUsage());
    }

    // merge with passed options
    $this->options = array_merge(
      array_map(function($v){return array_ifelse('default',$v,'');}, static::$_available_command_options),
      $options,
      $this->cli_options
    );

    // read the config file
    $conf_options = $this->readConfig();
    $this->options = array_merge($conf_options, $this->options);

    // validate required config
    $this->validateConfig();
  }

  public static function getInstance(Array $options = array()) {
    $classname = get_called_class();
    if (array_key_exists($classname, self::$_instance)) {
      $ret = self::$_instance[$classname];
    } else {
      $ret = new $classname($options);
      self::$_instance[$classname] = $ret;
    }
    if ($options) {
      $ret->options = array_merge($ret->options, $options);
    }
    return $ret;
  }

  public function __get($name) {
    $ret = array_key_exists($name, $this->options) ? $this->options[$name] : null;
    return $ret;
  }

  protected function readConfig($refresh = FALSE) {
    // Read the config file and add anything found to the options
    $ret = array();
    if (!$this->_config_loaded || $refresh) {
      $ini = @parse_ini_file($this->options['config_file']);
      $this->_config_loaded = TRUE;
      if ($ini) {
        foreach ($ini as $key => $val) {
          // Don't allow the config file to reset the config_file option.
          if ($key !== 'config_file') {
            $ret[$key] = $val;
          }
        }
      }
      else {
        echo "WARNING: Config file {$this->options['config_file']} is missing or blank!\n";
      }
    }
    return $ret;
  }

  protected function validateConfig($error_on_invalid = TRUE) {
    $has_error = array();
    foreach (static::$_available_command_options as $key=>$req_index) {
      if ($req_index['required'] && !array_ifelse($key, $this->options, FALSE)) {
        echo "ERROR: Missing config parameter $key!\n";
        $has_error[] = $key;
      }
    }

    if (count($has_error) && $error_on_invalid) {
      $msg = implode(',',$has_error);
      throw new RuntimeException("Invalid/Missing configuration items: $msg");
    }
  }

  protected static function parse_cli_options() {
    // string of short option characters, e.g., -c -h -a
    $shortopts = '';
    // array of long option names, e.g., --help --config
    $longopts = array();
    // a convenience array to reverse map short options to long options
    $opt_map = array();

    // The static declared above should hold *all* available options possible.
    // Iterate through them to build the short/long lists.
    foreach (static::$_available_command_options as $key => $val) {
      // Force-type the 'val' property to integer.
      // 0 = Not required, 1 = Required, 2 = Optional
      $v = (int)$val['val'];

      // Create the long option entry.
      $longopts[] = $key . ($v > 0 ? ':' : '') . ($v > 1 ? ':' : '');

      // If the long option defines a shortcut, create the short option entry.
      // Also, add it to the reverse map for future reference.
      if (array_ifelse('short', $val, FALSE)) {
        $shortopts .= $val['short'] . ($v > 0 ? ':' : '') . ($v > 1 ? ':' : '');
        $opt_map[$val['short']] = $key;
      }
    }

    // Parse the command line parameters
    $cmd_options = getopt($shortopts, $longopts);

    // Initialize the return variable
    $ret = array();

    // For each entry in $cmd_options, translate the option into its
    // config equivalent.
    foreach ($cmd_options as $key => $val) {
      // The long key is either in the reverse map array, or it is the actual key.
      $long_key = array_key_exists($key, $opt_map) ? $opt_map[$key] : $key;

      // If the long key exists, add it to the return
      if (array_key_exists($long_key, static::$_available_command_options)) {
        // The return key is the 'index' property of this option's definition.
        $ret[$long_key] = $val;
        // Options which don't require values get set to boolean false by
        // getopt().  Correct this to show the option is selected.
        if (static::$_available_command_options[$long_key]['val'] == 0) {
          $ret[$long_key] = TRUE;
        }
      }
    }

    return $ret;
  }

}