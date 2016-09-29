DROP TABLE IF EXISTS `authors`;
CREATE TABLE `authors` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `username` varchar(50) NOT NULL DEFAULT 'Not Provided in API',
  `about` text NOT NULL,
  `name` varchar(100) NOT NULL,
  `disable_trackers` tinyint(4) NOT NULL DEFAULT '0',
  `power_contrib` tinyint(4) NOT NULL DEFAULT '0',
  `joined_at` datetime DEFAULT NULL,
  `rep` float(25,17) NOT NULL DEFAULT '0.00000000000000000',
  `location` varchar(50) NOT NULL DEFAULT '',
  `is_private` tinyint(4) NOT NULL DEFAULT '0',
  `signed_url` text NOT NULL,
  `is_primary` tinyint(4) NOT NULL DEFAULT '0',
  `is_anon` tinyint(4) NOT NULL DEFAULT '0',
  `aid` bigint(20) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_bin;

DROP TABLE IF EXISTS `categories`;
CREATE TABLE `categories` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `title` varchar(50) NOT NULL,
  `is_default` tinyint(4) NOT NULL,
  `dq_order` int(11) NOT NULL,
  `forum` varchar(50) NOT NULL,
  `cid` bigint(20) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_bin;

DROP TABLE IF EXISTS `posts`;
CREATE TABLE `posts` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `is_highlighted` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `is_flagged` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `forum` varchar(50) COLLATE utf8mb4_bin NOT NULL,
  `parent` bigint(20) DEFAULT NULL,
  `author` bigint(20) NOT NULL,
  `points` bigint(20) NOT NULL,
  `is_approved` tinyint(4) NOT NULL DEFAULT '0',
  `dislikes` int(11) NOT NULL DEFAULT '0',
  `raw_message` text COLLATE utf8mb4_bin NOT NULL,
  `is_spam` tinyint(4) NOT NULL DEFAULT '0',
  `thread` bigint(20) NOT NULL,
  `num_reports` int(11) NOT NULL,
  `is_author_deleted` tinyint(4) NOT NULL DEFAULT '0',
  `created_at` datetime NOT NULL,
  `is_edited` tinyint(4) NOT NULL DEFAULT '0',
  `pid` bigint(20) NOT NULL,
  `is_deleted` tinyint(4) NOT NULL DEFAULT '0',
  `likes` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_bin;

DROP TABLE IF EXISTS `settings`;
CREATE TABLE `settings` (
  `name` varchar(50) NOT NULL,
  `value` text NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_bin;

DROP TABLE IF EXISTS `thread_ident`;
CREATE TABLE `thread_ident` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `tid` bigint(20) unsigned NOT NULL DEFAULT '0',
  `thread_id` bigint(20) unsigned NOT NULL,
  `ident` varchar(255) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_bin;

DROP TABLE IF EXISTS `threads`;
CREATE TABLE `threads` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `feed` varchar(255) NOT NULL DEFAULT '',
  `dislikes` int(10) unsigned NOT NULL DEFAULT '0',
  `likes` int(10) unsigned NOT NULL DEFAULT '0',
  `message` text NOT NULL,
  `tid` bigint(20) unsigned NOT NULL,
  `created_at` datetime NOT NULL,
  `category` bigint(20) unsigned NOT NULL,
  `author` bigint(20) unsigned NOT NULL,
  `user_score` float(9,2) NOT NULL,
  `is_spam` tinyint(4) unsigned NOT NULL DEFAULT '0',
  `signed_link` text NOT NULL,
  `is_deleted` tinyint(4) unsigned NOT NULL DEFAULT '0',
  `raw_message` text NOT NULL,
  `is_closed` tinyint(4) unsigned NOT NULL DEFAULT '0',
  `link` text NOT NULL,
  `slug` varchar(255) NOT NULL,
  `forum` varchar(50) NOT NULL,
  `clean_title` varchar(255) NOT NULL,
  `posts` int(11) unsigned NOT NULL,
  `user_sub` tinyint(4) unsigned NOT NULL DEFAULT '0',
  `title` varchar(255) NOT NULL,
  `highlighted` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_bin;
