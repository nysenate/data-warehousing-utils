------------------------------------------------------------------------------------------
LIVE MONITOR WEB PAGE
------------------------------------------------------------------------------------------
/exercise-monitor

This web page will show you the values of the drupal variables.
The page refreshes itself every five seconds.

The values shown indicate the type of run and progress.


------------------------------------------------------------------------------------------
DRUSH COMMANDS
------------------------------------------------------------------------------------------
exercise-nodes  exns
exercise-nodes  exns senator
exercise-nodes  exns senator --db



Exercises (renders) every page of a content type.
If no content type argument is supplied a list of all content types
will be displayed for your choice.


Argument: type
A run for the content type specified by the type argument.

Arguments: none.
A Select List will appear up to choose a content type.

Options : --alias
A foreign database to scan and uri to test.

Options : --db
A foreign database to scan.

Options : --uri
The domain to exercise.
This will override the uri provided by --alias option.
Substitutes the value of the --uri option into the domain of the url to lookup.

Example for my local server.
--uri=http://nysenate.dd:8083




------------------------------------------------------------------------------------------
exercise-node   exn

Exercises (renders) a Node Page.


argument nid or path ????

Options : --uri
--uri May be required if curl not responding and the system runs  really really fast.

Substitutes the value of the --uri option into the domain of the url to lookup.

Example for my local server.
--uri=http://nysenate.dd:8083/



------------------------------------------------------------------------------------------
exercise-terms  exts
exercise-terms  districts

Exercises (renders) the pages of a Taxonomy Vocabulary.

Options : --db
Emits information for each row.

Options : --uri
--uri May be required if curl not responding and the system runs  really really fast.

Substitutes the value of the --uri option into the domain of the url to lookup.

Example for my local server.
--uri=http://nysenate.dd:8083/


------------------------------------------------------------------------------------------
exercise-term  ext

Exercies (renders) a Term Page.

argument tid or path


Options : --uri
--uri May be required if curl not responding and the system runs  really really fast.

Substitutes the value of the --uri option into the domain of the url to lookup.

Example for my local server.
--uri=http://nysenate.dd:8083/



------------------------------------------------------------------------------------------
exercise-status  est

Shows System Status.

------------------------------------------------------------------------------------------
exercise-status-ping  esp

Shows Detailed Status.

No argument - shows status a single time

numeric argument - repeat interval in seconds.

Control C to exit.

------------------------------------------------------------------------------------------
exercise-stop  estp
exercise-stop  estp full

Stops runs or ends stuck or orphaned runs.

Running exercise-stop does not clear the drush exercise_run_previous variable.
In order to clear that as well add the --full option

Options : --full
--full clears all the variables including the exercise_run_previous variable.


------------------------------------------------------------------------------------------
exercise-all  exa

Generates a static Drush Script.

Future - generate an active script to run via cron regularly.


------------------------------------------------------------------------------------------
exercise-get-last-complete-run  exclr

Gets the type of the last complete run.



------------------------------------------------------------------------------------------
exercise-get-next-run  exgnr

Gets the name of the next type to run.

If a another run is running it returns `not-ready`

A series runs logic might be check this if not-ready ignore
if a type is returned do a run of that type.
if `done`` is returned stop.


Argument :
A drush alias to use with the --command option.
If a valid drush alias is supplied as an argument it will be used in the command.
If no alia is supplied the alias stored from a previous exercise-all run will be used in drush commands.

Options : --command
--command returns the drush command for the next type.

------------------------------------------------------------------------------------------


------------------------------------------------------------------------------------------
DRUPAL VARIABLES
------------------------------------------------------------------------------------------
exercise_run_type					node or term
exercise_run                        content type or vocabulary name of current run.
exercise_run_size                   nnnn number of items being processed.
exercise_run_current_position       nnnn current item being processed.
exercise_run_current_id             nnnn the node (nid) or term id (tid).
exercise_run_current_timestamp      nnnn The time the item was processed.
exercise_run_previous               content type or vocabulary name of last complet run.
exercise_all_stop                   TRUE or FALSE
exercise_drush_alias                @multidev-3-drush-alias  drush alias
s
Drupal Variables are available using drush vget and vset
------------------------------------------------------------------------------------------


