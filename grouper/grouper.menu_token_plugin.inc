<?php
/**
 * @file
 * Grouper Menu Token Plugin.
 */

/**
 * Function grouper_get_user_link().
 *
 * Returns the users path on the system.
 */
function grouper_get_user_link() {
  global $user;
  $path = 'user/' . $user->uid;
  $path_start = drupal_get_path_alias($path);
  if ($path_start != $path) {
    return $path_start;
  }
  return FALSE;
}

/**
 * Function grouper_resolve_menu_token_link_path().
 *
 * Resolves embedded tokens for NYS.
 * $path contains the path with embedded tokens
 * The function returns a path with the tokens resolved.
 */
function grouper_resolve_menu_token_link_path($path) {

  global $user;

  if (strpos($path, '[user:uid]') !== FALSE) {
    return token_replace($path, array('user' => $user));
  }

  if (strpos($path, '[node:url]') !== FALSE) {
    $user_link = grouper_get_user_link();
    if ($user_link != FALSE) {
      return str_replace('[node:url]', $user_link, $path);
    }
  }

  // NYS senators/.
  if (strpos($path, '[node:senator_microsite]') !== FALSE) {
    $alias = db_query("SELECT `alias` FROM `url_alias` WHERE `alias` LIKE 'senators/%' LIMIT 1")->fetchField();
    return str_replace('[node:senator_microsite]', $alias, $path);
  }

  // NYS district/15/.
  if (strcmp($path, '[node:district_tid]') == 0 || strpos($path, '[node:district_tid]') !== FALSE) {
    $tid = db_query("SELECT `tid` FROM `taxonomy_term_data` WHERE `vid` = 8 LIMIT 1")->fetchField();
    return str_replace('[node:district_tid]', 'district/' . $tid, $path);
  }

  return FALSE;

}
