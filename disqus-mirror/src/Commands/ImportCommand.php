<?php

namespace DisqusImporter\Commands;

use DisqusImporter\APIObjects;
use DisqusImporter\Config;

class ImportCommand extends CommandTemplate {
	public function handle() {

		// instantiate Disqus API
		$disqus = new \DisqusAPI(Config::getInstance()->api_secret);

		foreach (['Categories', 'Threads', 'Posts'] as $val) {
			$obj = APIObjects\APIObjectTemplate::createFromTemplate($val, $disqus);
			if ($obj) {
				$obj->executeSearch();
			}
			else {
				echo "No Class\n";
			}
		}
	}
}