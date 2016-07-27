-- MySQL dump 10.13  Distrib 5.7.13, for Linux (x86_64)
--
-- Host: 127.0.0.1    Database: disqus_mirror
-- ------------------------------------------------------
-- Server version	5.7.13-0ubuntu0.16.04.2

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `authors`
--

DROP TABLE IF EXISTS `authors`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
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
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `categories`
--

DROP TABLE IF EXISTS `categories`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `categories` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `title` varchar(50) NOT NULL,
  `is_default` tinyint(4) NOT NULL,
  `dq_order` int(11) NOT NULL,
  `forum` varchar(50) NOT NULL,
  `cid` bigint(20) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `posts`
--

DROP TABLE IF EXISTS `posts`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
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
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `settings`
--

DROP TABLE IF EXISTS `settings`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `settings` (
  `name` varchar(50) NOT NULL,
  `value` text NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `thread_ident`
--

DROP TABLE IF EXISTS `thread_ident`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `thread_ident` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `tid` bigint(20) unsigned NOT NULL DEFAULT '0',
  `thread_id` bigint(20) unsigned NOT NULL,
  `ident` varchar(255) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `threads`
--

DROP TABLE IF EXISTS `threads`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
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
/*!40101 SET character_set_client = @saved_cs_client */;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2016-07-27 13:23:59
