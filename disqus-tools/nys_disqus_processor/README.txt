NYS DISQUS PROCESSOR DSQUS DRUSH COMMANDS
---------------------------------------------------------------------
load-token	
Unused

---------------------------------------------------------------------
get-token 
Returns the disqus token

---------------------------------------------------------------------
get-thread (ThreadID | Thread Identifier | Thread Link)
Gets the data about a thread.
Argument 1:
You can pass in a numeric ThreadID
You can pass in an alphanumeric identifier
You can pass in a Thread Link 

Argument 2
Nothing for a numeric ThreadID
Nothing for an alphanumeric identifier
`ident` for a numeric identifier
`link`  for a link.

---------------------------------------------------------------------
update-thread-id (ThreadId, New Thread Identifier)
Updates the threads Identifier.

Argument 1:
You can pass in a numeric ThreadID.

Argument 2
You pass in the new thread identifier.

---------------------------------------------------------------------
update-thread-link (ThreadId, New Thread Link)
Updates the threads Link.

Argument 1:
You can pass in a numeric ThreadID.

Argument 2
You pass in the new Thread Link.

---------------------------------------------------------------------
survey-threads (Input Table Name)
Surveys the threads in an input table.
Input tables are loaded from disqus export files
using the process_disqus_export_file.php script.

---------------------------------------------------------------------
remove-thread (ThreadId)
Removes a thread
This Disqus API call does not seem to actually work as advertised.

Argument 1:
You can pass in a numeric ThreadID.

---------------------------------------------------------------------
get-posts (ThreadId)
Gets the posts for a thread.
One of the items returned is the Post ID.

Argument 1:
You can pass in a numeric ThreadID.

---------------------------------------------------------------------
get-post (PostId)
Gets the data for a post.

Argument 1:
You can pass in a numeric PostID.

---------------------------------------------------------------------

