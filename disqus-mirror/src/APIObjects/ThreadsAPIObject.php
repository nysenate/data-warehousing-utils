<?php
namespace DisqusImporter\APIObjects;

use DisqusImporter\Logger;

class ThreadsAPIObject extends APIObjectTemplate {

	protected static $table_name = 'threads';

	protected static $object_name = 'threads';

	protected static $object_action = 'list';

	protected static $field_map = [
		'feed'             => 'feed',
		'dislikes'         => 'dislikes',
		'likes'            => 'likes',
		'message'          => 'message',
		'id'               => 'tid',
		'createdAt'        => 'created_at',
		'category'         => 'category',
		'author'           => 'author',
		'userScore'        => 'user_score',
		'isSpam'           => 'is_spam',
		'signedLink'       => 'signed_link',
		'isDeleted'        => 'is_deleted',
		'raw_message'      => 'raw_message',
		'isClosed'         => 'is_closed',
		'link'             => 'link',
		'slug'             => 'slug',
		'forum'            => 'forum',
		'clean_title'      => 'clean_title',
		'posts'            => 'posts',
		'userSubscription' => 'user_sub',
		'title'            => 'title',
		'highlightedPost'  => 'highlighted',
	];

	protected static $mangle_map = [
		'isSpam'           => 'boolean',
		'isDeleted'        => 'boolean',
		'isClosed'         => 'boolean',
		'userSubscription' => 'boolean',
	];

	protected function postInsert($insert_id, $data) {
		// Threads can have "identifiers" attached to them.  Make sure they get recorded.
		if ((int) $insert_id && count($data->identifiers)) {
			$query = db_insert('thread_ident')->fields(['tid', 'thread_id', 'ident']);
			foreach ($data->identifiers as $key => $val) {
				$query->values([$data->id, $insert_id, $val]);
			}
			try {
				$query->execute();
			}
			catch (\Exception $e) {
				$this->log->log("Exception generated during identifier INSERT:\nCode: " . var_export($e->getCode(), 1) . "\nMessage: " . var_export($e->getMessage(), 1), Logger::NYSS_LOG_LEVEL_ERROR);
			}
		}
	}
}
