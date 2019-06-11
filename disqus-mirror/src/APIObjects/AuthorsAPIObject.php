<?php
namespace DisqusImporter\APIObjects;

class AuthorsAPIObject extends APIObjectTemplate {

	protected static $table_name = 'authors';

	protected static $object_name = '';

	protected static $object_action = '';

	protected static $field_map = [
		'username'                => 'username',
		'about'                   => 'about',
		'name'                    => 'name',
		'disable3rdPartyTrackers' => 'disable_trackers',
		'isPowerContributor'      => 'power_contrib',
		'joinedAt'                => 'joined_at',
		'rep'                     => 'rep',
		'location'                => 'location',
		'isPrivate'               => 'is_private',
		'signedUrl'               => 'signed_url',
		'isPrimary'               => 'is_primary',
		'isAnonymous'             => 'is_anon',
		'id'                      => 'aid',
	];

	protected static $mangle_map = [
		'username'                => 'string',
		'about'                   => 'string',
		'name'                    => 'string',
		'rep'                     => 'float',
		'location'                => 'string',
		'signedUrl'               => 'string',
		'id'                      => 'integer',
		'disable3rdPartyTrackers' => 'boolean',
		'isPowerContributor'      => 'boolean',
		'isPrivate'               => 'boolean',
		'isPrimary'               => 'boolean',
		'isAnonymous'             => 'boolean',
	];
}

