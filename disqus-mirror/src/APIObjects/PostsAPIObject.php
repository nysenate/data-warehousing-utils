<?php
namespace DisqusImporter\APIObjects;

use DisqusImporter\Logger;

class PostsAPIObject extends APIObjectTemplate {

	protected static $table_name = 'posts';

	protected static $object_name = 'posts';

	protected static $object_action = 'list';

	protected static $field_map = [
		'isHighlighted'     => 'is_highlighted',
		'isFlagged'         => 'is_flagged',
		'forum'             => 'forum',
		'parent'            => 'parent',
		'author'            => 'author',
		'points'            => 'points',
		'isApproved'        => 'is_approved',
		'dislikes'          => 'dislikes',
		'raw_message'       => 'raw_message',
		'isSpam'            => 'is_spam',
		'thread'            => 'thread',
		'numReports'        => 'num_reports',
		'isDeletedByAuthor' => 'is_author_deleted',
		'createdAt'         => 'created_at',
		'isEdited'          => 'is_edited',
		'id'                => 'pid',
		'isDeleted'         => 'is_deleted',
		'likes'             => 'likes',
	];

	protected static $mangle_map = [
		'isHighlighted'     => 'boolean',
		'isFlagged'         => 'boolean',
		'isApproved'        => 'boolean',
		'isSpam'            => 'boolean',
		'isDeletedByAuthor' => 'boolean',
		'isEdited'          => 'boolean',
		'isDeleted'         => 'boolean',
	];

	protected function preInsert(&$data) {
		$this->log->log("Attempting to insert author:\n" . var_export($data->author, 1), self::NYSS_LOG_LEVEL_DEBUGAPI);
		$ret = AuthorsAPIObject::insertFromData($data->author);
		$this->log->log("Inserting author returned " . var_export($ret, 1), Logger::NYSS_LOG_LEVEL_DEBUG);
		$data->author = $ret;
	}
}
