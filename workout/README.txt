
------------------------------------------------------------------------------------------
DRUSH COMMANDS
------------------------------------------------------------------------------------------
workout         wo      Exercises every node on a site.
exercise-page   exp     Exercises a single page by path.
stop-workout    sw      Stops a running workout.
restart-workout rw      Restarts a running workout or start anywhere.
clear-workout   cw      Ends a workout and clears variables.
workout-status  wstat   Shows the current status of a workout.
workout-report  wrp     Shows results of last workout.
workout-test    wt      Tests alias, uri and db options.

------------------------------------------------------------------------------------------
workout

Attempts to Exercises every public page on a site anonymously.
You can pass in the number of pages to limit the processing to as arg1.


Examples:
 Standard example                          workout
 Argument example                          workout 42

Arguments:
 arg1                                      An optional number of pages to
                                           exercise.

Options:
  --alias                                   A foreign database to scan.
  --db                                      A foreign database to scan.
  --threads                                 The number of threads to use
  --uri                                     The domain to exercise.


Aliases: wo

------------------------------------------------------------------------------------------
exercise-page

Exercises (renders) a Node Page.

Examples:
 Standard example                          exercise-page
 Argument example                          exercise-page path
 Argument example                          exercise-page path 42

Arguments:
 arg1                                      A path to a page.
 arg2                                      An optional reference number that
                                           will be set in the position
                                           variable.

Aliases: exp

------------------------------------------------------------------------------------------
stop-workout

Stops a running workout.

Examples:
 Standard example                          stop-workout

Aliases: sw

------------------------------------------------------------------------------------------
restart-workout

Re starts a stopped workout.


Examples:
 Standard example                          restart-workout
 Argument example                          restart-workout 42 36

Arguments:
 arg1                                      An optional starting position.
 arg2                                      An optional number of pages to
                                           exercise.

Options:
 --threads                                 The number of threads to use
 --uri                                     The domain to exercise.

Aliases: rw

------------------------------------------------------------------------------------------
clear-workout

Clears the stopped status and workout position for and ends a workout.

Examples:
 Standard example                          clear-workout

Arguments:
 arg1                                      An optional number of pages to
                                           exercise.

Aliases: cw

------------------------------------------------------------------------------------------
workout-status

Shows the current status of a running workout.

Examples:
 Standard example                          workout-status

Aliases: wstat

------------------------------------------------------------------------------------------
workout-report

Shows results of last workout.

Examples:
 Standard example                          exercise-report
 Argument example                          exercise-report article

Arguments:
 arg1                                      A Content Type.

Aliases: wrp
------------------------------------------------------------------------------------------
workout-test

Tests alias, uri and db options.

Examples:
 Standard example                          workout-test
 Argument example                          workout-test path

Arguments:
 arg1                                      A path to a page.

Options:
 --alias                                   A foreign database to scan.
 --db                                      A foreign database to scan.
 --uri                                     The domain to exercise.
