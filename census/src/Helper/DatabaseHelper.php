<?php
/**
 * @file DatabaseHelper.php
 */

namespace NYS_Census\Helper;

/**
 * Class DatabaseHelper
 *
 * @package NYS_Census\Helper
 */
class DatabaseHelper {

  /**
   * Maps API field names to database field names.
   * These names must be used consistently in the schema for this to work.
   *
   * @var string[]
   */
  public static $field_map = [
    'COUSUB' => 'cousub',
    'STATE' => 'state',
    'NATION' => 'country',
    'AIANHH' => 'native',
    'RESP_DATE' => 'ts',
    'COUNTY' => 'county',
    'PLACE' => 'place',
    'REGION' => 'region',
    'GEO_ID' => 'geoid',
    'TTRACT' => 'ttract',
    'CD' => 'cd',
    'TRACT' => 'tract',
    'NAME' => 'name',
    'CINTMIN' => 'cintmin',
    'CINTAVG' => 'cintavg',
    'CINTMED' => 'cintmed',
    'DMED' => 'dmed',
    'DRRALL' => 'drrall',
    'DMIN' => 'dmin',
    'CMIN' => 'cmin',
    'CAVG' => 'cavg',
    'CRRINT' => 'crrint',
    'CMED' => 'cmed',
    'CINTMAX' => 'cintmax',
    'DMAX' => 'dmax',
    'CRRALL' => 'crrall',
    'DINTMIN' => 'dintmin',
    'DINTAVG' => 'dintavg',
    'DINTMED' => 'dintmed',
    'SUMLEVEL' => 'sumlevel',
    'DAVG' => 'davg',
    'DINTMAX' => 'dintmax',
    'DRRINT' => 'drrint',
    'CMAX' => 'cmax',
    'GEOCOMP' => '',
    'CONCIT' => '',
  ];

  /**
   * Fetch application parameters from the database
   *
   * @param string $name name of the parameter
   * @param mixed $default a default value to return if no value is found
   *
   * @return mixed
   */
  public static function fetchParam($name, $default = NULL) {
    $result = db_select('params', 'p')
      ->fields('p', ['value'])
      ->condition('p.name', $name)
      ->execute();
    return $result->rowCount() ? $result->fetchField() : $default;
  }

  /**
   * Sets an application parameter in the database.
   *
   * @param string $name
   * @param mixed $value
   *
   * @throws \InvalidMergeQueryException
   */
  public static function setParam($name, $value) {
    $result = db_merge('params')
      ->key(['name' => $name])
      ->fields(['value' => $value])
      ->execute();
  }

  /**
   * Takes an associate array having Census API field names as
   * the keys.  Returns an associative array with the keys names
   * replaced with their respective database field names.  If
   * an API field does not have a related database field, that
   * key is removed from the set.
   *
   * @param mixed[] $data
   *
   * @return mixed[]
   */
  public static function prepFields($data) {
    // Get the new keys, as mapped by the static array.
    $h = array_map(
      function ($v) {
        return static::$field_map[$v] ?? 'nofield';
      },
      array_keys($data[0])
    );

    // build the new array, with the keys replaced.
    $new_data = array_map(
      function ($v) use ($h) {
        return array_combine($h, $v);
      },
      $data
    );

    // Remove any keys not successfully translated.
    // Also, reset the timestamp field to an epoch timestamp.
    foreach ($new_data as $k=>&$v) {
      unset($v['nofield']);
      if (isset($v['ts']) && $t=strtotime($v['ts'])) {
        $v['ts'] = $t;
      }
    }

    return $new_data;
  }

  /**
   * Pushes data into a database table.  Field names are
   * the responsibility of the caller.
   *
   * @param string $table
   * @param array $data
   *
   * @return int
   * @throws \InvalidMergeQueryException
   */
  public static function uploadData($table, $data = []) {
    $done = 0;
    if (is_array($data) && count($data)) {
      // swap out the existing keys with our db field names
      $new_data = static::prepFields($data);

      // turn off indexing
      db_query('ALTER TABLE `' . $table . '` DISABLE KEYS');

      // Any better way?  perhaps...for now, merge each row.
      foreach ($new_data as $key=>$val) {
        $result = db_merge($table)
          ->key(['geoid' => $val['geoid'], 'ts' => $val['ts']])
          ->fields($val)
          ->execute();

        // Track the successes.
        if ($result) {
          $done++;
        }
      }

      // turn indexing back on
      db_query('ALTER TABLE `' . $table . '` ENABLE KEYS');
    }

    // Return number of rows successfully inserted/merged.
    return $done;
  }
}
