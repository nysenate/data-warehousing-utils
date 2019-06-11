<?php
namespace DisqusImporter\APIObjects;

class CategoriesAPIObject extends APIObjectTemplate {

	protected static $table_name = 'categories';

	protected static $object_name = 'categories';

	protected static $object_action = 'list';

	protected static $field_map = [
		'title'     => 'title',
		'isDefault' => 'is_default',
		'order'     => 'dq_order',
		'forum'     => 'forum',
		'id'        => 'cid',
	];

	protected static $mangle_map = [];
}
