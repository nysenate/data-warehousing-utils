/**
 * @file
 * Grouper.js.
 */

Drupal.behaviors.grouper = {
  attach: function (context, settings) {

    jQuery("#exercise-pages").click(function() {
        exercise_pages();
    });

    jQuery(".repro-button").click(function() {
      grouper_reproduce(jQuery(this).attr('location'));
    });

  }
}

function exercise_pages() {
  var page_num = 1;
  var num_pages = jQuery("a.access-denied").length;
  var page_size = 0;

  jQuery("a.access-denied").each(function(index) {

    uri = jQuery(this).attr("href");
    page_size = grouper_load_page(uri);

    // Emit status.
    jQuery("#exercise-status").text('Page ' + page_num + ' of ' + num_pages + ' - - ' + page_size + ' Bytes - - ' + uri);

    console.log('Page ' + page_num + ' of ' + num_pages + ' - - ' + page_size + ' Bytes - - ' + uri);

    page_num++;

  });

}

function grouper_load_page(uri) {
  var result_len = 0;

  jQuery.ajax({
            async: false,
            type: "GET",
            url: uri,
            success: function (response) {
              result_len = response.length;

            }
        });

  return result_len;

}

function grouper_get_max_wid() {
  var max_wid = 0;

  jQuery.ajax({
            async: false,
            type: "GET",
            url: '/admin/grouper/max-wid/',
            success: function (response) {
                max_wid = response.max_wid;
            }
          });

  return max_wid;

}

function grouper_rollback(wid) {

  jQuery.ajax({
            async: false,
            type: "GET",
            url: '/admin/grouper/rollback/' + wid + '/',
            success: function (response) {

            }
          });

  window.close();

}

function grouper_reproduce(location) {
  // Dertermine max wid.
  var current_max_wid = grouper_get_max_wid();

  // Exercise.
  var num_bytes_loaded = grouper_load_page(location);

  var encoded_location = encodeURI(location);

  var repro_window_uri = "/admin/grouper/repro/" + current_max_wid + "/" + num_bytes_loaded + "/?loc=" + encoded_location;

  // Open new window to show and path in max_wid so it knows where to START.
  var repro_window = window.open(repro_window_uri, "_blank", width = "500", height = "500");

}
