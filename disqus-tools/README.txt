---------------------------------------------------------------------
NYS DISQUS TOOLS AND UTILITIES
---------------------------------------------------------------------

nys_disqus_processor
A drush module that contains utility commands.
Most are just wrappers for disqus API calls.

get-thread              Gets the data about a thread.

update-thread-id        Updates the threads Identifier.

update-thread-link      Updates the threads Link.

survey-threads          Surveys the threads in an input table

get-posts               Gets the posts for a thread.

get-post                Gets a single post.


---------------------------------------------------------------------
process_disqus_export_file.php script.

Loads the `nys_disqus_comments` table from a disqus export file.


---------------------------------------------------------------------
extract_nids_from disqus_xml_file.php

Parses the disqus xml export file.
Creates multiple output csv files for the different styles of identifiers.

---------------------------------------------------------------------
nys_scraper

Contains 4 drush commands for processing a Survey created with the
survey-threads drush command.

---------------------------------------------------------------------



