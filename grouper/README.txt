Grouper Slicer and Dicer
Not to be confused with Bass O Matic 76

Grouper reports on php warnings and errors gathered by Drupals dblog watchdog module.
Without dblog being enabled this module will be of little use.

The module allows you to reproduce errors by clicking on a link to a page.

For pages with Access Denied warnings and menu links, Grouper
can load all the pages in order to reproduce warnings and errors.

Other tools like Workout or Exerciser can be used to load all
public pages and create weaning or error messages if there are issues.


Pages
---------------------------------------------------------------
Groups of PHP Errors
Sorted PHP Errors
Pages With Errors
Error Distribution
Access Denied
Not Found
Menu Links
Drupal DB Log



---------------------------------------------------------------
Groups of PHP Errors

Sorted by the quantity of warnings the message is producing.

Groups your php error and warning messages together depending on their cause.
A list of individual error / warning messages is displayed
along with the number of pages which this message appears.

If you click on one of the error messages you will see a list of
pages where this error / warning occurred.

you can click on the link to go to the page and reproduce the
error / warning message.

If you click on Details you go to the message page.

If you click on  [L] It will open one of the pages that caused the warning message which should reproduce the error.

If you click on  ( ) It will load the page which should reproduce the condition and open a new window to see the messages produced by loading the page.

The ( ) button is useful for determining when and if the underlying issue has been fixed.

Before fixing the issue you will see the warnnigs/errors in the repro window when you click the ( ) button.

After fixing the issue you wont see the warnnigs/errors in the repro window when you click the ( ) button.

When you are done with the repro window click the `Roll Back and Close This Window` button to delete the warning/error messages from the message log and close the repro window.

---------------------------------------------------------------
Sorted PHP Errors

Sorted by the path and file name of the source file.

Groups your php error and warning messages together depending on their cause.
A list of individual error / warning messages is displayed
along with the number of pages which this message appears.

If you click on one of the error messages you will see a list of
pages where this error / warning occurred.

you can click on the link to go to the page and reproduce the
error / warning message.

If you click on Details you go to the message page.

If you click on  [L] It will open one of the pages that caused the warning message which should reproduce the error.

If you click on  ( ) It will load the page which should reproduce the condition and open a new window to see the messages produced by loading the page.

The ( ) button is useful for determining when and if the underlying issue has been fixed.

Before fixing the issue you will see the warnnigs/errors in the repro window when you click the ( ) button.

After fixing the issue you wont see the warnnigs/errors in the repro window when you click the ( ) button.

When you are done with the repro window click the `Roll Back and Close This Window` button to delete the warning/error messages from the message log and close the repro window.
---------------------------------------------------------------
Pages With Errors

Shows a list of pages with errors and the number of times that page
had errors and

You can click on the link to go to a list of the pages that relate to error / warning message.

If you click on Details you go to the error page.

---------------------------------------------------------------
Error Distribution

Shows the different types of messages in the watchdog / dblog
and how many messages are in there for each type.

---------------------------------------------------------------
Access Denied

Shows a list of pages that had Access Denied Errors / Warnings.

Clicking on a page will load the page if you are logged in.
This will reproduce the error or warning.

To load all the listed pages click the Start Exercising These Pages button.

If its a long list you should open up the Javascript Console in your browser
BEFORE CLICKING THE BUTTON in order to monitor your status.

If you don't your Browser will appear to be frozen until
all the pages have been loaded and will probably tell you
that a script is running uncontrollably and repeatedly
verifying that you want to continue.


---------------------------------------------------------------
Not Found

These are the pages that were requested but do not exist on
the server. They could be old or mistakes. The link could
be researched on Yahoo and Google to see where its being used on the internet.

---------------------------------------------------------------
Menu Links

Shows a list of the menu links on the site .

Clicking on a page will load the page if you are logged in.
This could reproduce the error or warning if there were one.

To load all the listed pages click the Start Exercising These Pages button.

If its a long list you should open up the Javascript Console in your browser
BEFORE CLICKING THE BUTTON in order to monitor your status.

If you don't your Browser will appear to be frozen until
all the pages have been loaded and will probably tell you
that a script is running uncontrollably and repeatedly
verifying that you want to continue.


---------------------------------------------------------------
Drupal DB Log

Brings you the normal Drupal dblog page.
/admin/reports/dblog

---------------------------------------------------------------
---------------------------------------------------------------
---------------------------------------------------------------
Drush Commands

---------------------------------------------------------------
marker name_of_marker_to_create
Creates a marker in the error log.

The argument name_of_marker_to_create above is the name of the marker to create.

---------------------------------------------------------------
marker-trim name_of_marker_to_trim
Clears all the log entries above the marker.

The argument name_of_marker_to_trim above is the name of the marker to trim.

---------------------------------------------------------------
grouper-get-uri
Gets grouper uri.

---------------------------------------------------------------
grouper-set-uri  uri_to_use
Creates and sets a grouper uri.

uri_to_use is the uri of the server that you are testing.
If you are testing a different system this uri will replace the uri in
the warning log so you can reproduce the errors on a specific system
without creating a link by hand copying and pasting the path onto a different domain.

You probably will need to set CORS authorization headers on the system under test
to utilize the reproduce errors links on the Groups of PHP Errors, Sorted PHP Errors or Menu links pages.


More Info

https://www.drupal.org/project/cors


https://enable-cors.org/server_apache.html
https://developer.mozilla.org/en-US/docs/Web/HTTP/Access_control_CORS
https://docs.microsoft.com/en-us/aspnet/core/security/cors

---------------------------------------------------------------
grouper-delete-uri
Delete grouper uri.

---------------------------------------------------------------

Created by Seth Snyder for Drupal 7

SELECT COUNT(*) FROM `watchdog`;
