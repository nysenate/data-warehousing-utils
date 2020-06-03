DROP TABLE IF EXISTS `params`;
CREATE TABLE `params`
(
    `name`  VARCHAR(50)  NOT NULL COLLATE 'utf8_general_ci',
    `value` VARCHAR(255) NOT NULL DEFAULT '' COLLATE 'utf8_general_ci',
    PRIMARY KEY (`name`)
)
    COLLATE = 'utf8_general_ci'
    ENGINE = InnoDB
;

DROP TABLE IF EXISTS `geo_type`;
CREATE TABLE `geo_type`
(
    `code` VARCHAR(7)   NOT NULL COLLATE 'utf8_general_ci',
    `name` VARCHAR(100) NOT NULL DEFAULT '' COLLATE 'utf8_general_ci',
    PRIMARY KEY (`code`)
)
    COLLATE = 'utf8_general_ci'
    ENGINE = InnoDB
;

DROP TABLE IF EXISTS `name_data`;
CREATE TABLE `name_data`
(
    `id`     INT(10) UNSIGNED NOT NULL AUTO_INCREMENT,
    `region` CHAR(1)          NULL DEFAULT NULL COLLATE 'utf8_general_ci',
    `state`  CHAR(2)          NULL DEFAULT NULL COLLATE 'utf8_general_ci',
    `county` CHAR(3)          NULL DEFAULT NULL COLLATE 'utf8_general_ci',
    `cousub` CHAR(5)          NULL DEFAULT NULL COLLATE 'utf8_general_ci',
    `tract`  CHAR(6)          NULL DEFAULT NULL COLLATE 'utf8_general_ci',
    `place`  CHAR(5)          NULL DEFAULT NULL COLLATE 'utf8_general_ci',
    `native` CHAR(4)          NULL DEFAULT NULL COLLATE 'utf8_general_ci',
    `ttract` CHAR(6)          NULL DEFAULT NULL COLLATE 'utf8_general_ci',
    `cd`     CHAR(2)          NULL DEFAULT NULL COLLATE 'utf8_general_ci',
    `name`   VARCHAR(150)     NULL DEFAULT NULL COLLATE 'utf8_general_ci',
    `geoid`  VARCHAR(25)      NOT NULL COLLATE 'utf8_general_ci',
    PRIMARY KEY (`id`),
    INDEX `region` (`region`),
    INDEX `state` (`state`),
    INDEX `county` (`county`),
    INDEX `cousub` (`cousub`),
    INDEX `tract` (`tract`),
    INDEX `place` (`place`),
    INDEX `native` (`native`),
    INDEX `ttract` (`ttract`),
    INDEX `cd` (`cd`),
    INDEX `geoid` (`geoid`)
)
    COLLATE = 'utf8_general_ci'
    ENGINE = InnoDB
;

DROP TABLE IF EXISTS `stat_data`;
CREATE TABLE `stat_data`
(
    `id`       INT(10) UNSIGNED NOT NULL AUTO_INCREMENT,
    `ts`       INT(10) UNSIGNED NOT NULL COMMENT 'Most recent data cutoff for responses received, point in time response rates are calculated for',
    `cintmin`  FLOAT(4, 1)      NULL DEFAULT NULL COMMENT 'Minimum Cumulative Internet Self-Response Rate',
    `cintavg`  FLOAT(4, 1)      NULL DEFAULT NULL COMMENT 'Average Cumulative Intenet Self-Response Rate',
    `cintmed`  FLOAT(4, 1)      NULL DEFAULT NULL COMMENT 'Median Cumulative Internet Self-Response Rate',
    `dmed`     FLOAT(4, 1)      NULL DEFAULT NULL COMMENT 'Median Daily Overall Self-Response Rate',
    `drrall`   FLOAT(4, 1)      NULL DEFAULT NULL COMMENT 'Daily Self-Response Rate - Overall',
    `dmin`     FLOAT(4, 1)      NULL DEFAULT NULL COMMENT 'Minimum Daily Overall Self-Response Rate',
    `cmin`     FLOAT(4, 1)      NULL DEFAULT NULL COMMENT 'Minimum Cumulative Overall Self-Response Rate',
    `cavg`     FLOAT(4, 1)      NULL DEFAULT NULL COMMENT 'Average Cumulative Overall Self-Response Rate',
    `crrint`   FLOAT(4, 1)      NULL DEFAULT NULL COMMENT 'Cumulative Self-Response Rate - Internet',
    `cmed`     FLOAT(4, 1)      NULL DEFAULT NULL COMMENT 'Median Cumulative Overall Self-Response Rate',
    `cintmax`  FLOAT(4, 1)      NULL DEFAULT NULL COMMENT 'Maximum Cumulative Intenet Self-Response Rate',
    `dmax`     FLOAT(4, 1)      NULL DEFAULT NULL COMMENT 'Maximum Daily Overall Self-Response Rate',
    `crrall`   FLOAT(4, 1)      NULL DEFAULT NULL COMMENT 'Cumulative Self-Response Rate - Overall',
    `dintmin`  FLOAT(4, 1)      NULL DEFAULT NULL COMMENT 'Minimum Daily Internet Self-Response Rate',
    `dintavg`  FLOAT(4, 1)      NULL DEFAULT NULL COMMENT 'Average Daily Inernet Self-Response Rate',
    `dintmed`  FLOAT(4, 1)      NULL DEFAULT NULL COMMENT 'Median Daily Internet Self-Response Rate',
    `sumlevel` FLOAT(4, 1)      NULL DEFAULT NULL COMMENT 'Summary Level code',
    `davg`     FLOAT(4, 1)      NULL DEFAULT NULL COMMENT 'Average Daily Overall Self-Response Rate',
    `dintmax`  FLOAT(4, 1)      NULL DEFAULT NULL COMMENT 'Maximum Daily Intenet Self-Response Rate',
    `drrint`   FLOAT(4, 1)      NULL DEFAULT NULL COMMENT 'Daily Self-Response Rate - Internet',
    `cmax`     FLOAT(4, 1)      NULL DEFAULT NULL COMMENT 'Maximum Cumulative Overall Self-Response Rate',
    `geoid`    VARCHAR(25)      NOT NULL COMMENT 'Combined codes for the reference geography' COLLATE 'utf8_general_ci',
    PRIMARY KEY (`id`),
    INDEX `ts` (`ts`),
    INDEX `geoid` (`geoid`)
)
    COLLATE = 'utf8_general_ci'
    ENGINE = InnoDB
;

DROP TABLE IF EXISTS `states`;
CREATE TABLE `states`
(
    `id`      INT(10) UNSIGNED NOT NULL AUTO_INCREMENT,
    `geopart` CHAR(2)          NOT NULL COLLATE 'utf8_general_ci',
    `abbr`    CHAR(2)          NULL DEFAULT NULL COLLATE 'utf8_general_ci',
    `name`    VARCHAR(50)      NOT NULL COLLATE 'utf8_general_ci',
    PRIMARY KEY (`id`),
    UNIQUE INDEX `geopart` (`geopart`),
    INDEX `abbr` (`abbr`)
)
    COLLATE = 'utf8_general_ci'
    ENGINE = InnoDB
;

DROP TABLE IF EXISTS `district_upper`;
CREATE TABLE `district_upper`
(
    `id`             INT(10) UNSIGNED NOT NULL AUTO_INCREMENT,
    `state_geopart`  CHAR(2)          NOT NULL COLLATE 'utf8_general_ci',
    `county_geopart` CHAR(3)          NOT NULL COLLATE 'utf8_general_ci',
    `tract`          CHAR(6)          NOT NULL COLLATE 'utf8_general_ci',
    `district`       CHAR(3)          NOT NULL COLLATE 'utf8_general_ci',
    PRIMARY KEY (`id`),
    INDEX `tract` (`tract`),
    INDEX `district` (`district`),
    INDEX `geopart` (`state_geopart`),
    INDEX `county` (`county_geopart`)
)
    COLLATE = 'utf8_general_ci'
    ENGINE = InnoDB
;

DROP TABLE IF EXISTS `counties`;
CREATE TABLE `counties`
(
    `id`            INT(10) UNSIGNED NOT NULL AUTO_INCREMENT,
    `state_geopart` CHAR(2)          NOT NULL COLLATE 'utf8_general_ci',
    `geopart`       CHAR(3)          NOT NULL COLLATE 'utf8_general_ci',
    `name`          VARCHAR(50)      NOT NULL DEFAULT '' COLLATE 'utf8_general_ci',
    PRIMARY KEY (`id`),
    UNIQUE INDEX `state_geopart_geopart` (`state_geopart`, `geopart`)
)
    COLLATE = 'utf8_general_ci'
    ENGINE = InnoDB
;

DROP TABLE IF EXISTS `zcta_data`;
CREATE TABLE `zcta_data`
(
    `id`          INT(10) UNSIGNED NOT NULL AUTO_INCREMENT,
    `zcta5`       CHAR(5)          NOT NULL COLLATE 'utf8_general_ci',
    `state_code`  CHAR(2)          NOT NULL COLLATE 'utf8_general_ci',
    `county_code` CHAR(3)          NOT NULL COLLATE 'utf8_general_ci',
    `tract`       CHAR(6)          NOT NULL COLLATE 'utf8_general_ci',
    `zcta_name`   VARCHAR(50)      NOT NULL DEFAULT '' COLLATE 'utf8_general_ci',
    PRIMARY KEY (`id`),
    INDEX `state_code_county_code_tract` (`state_code`, `county_code`, `tract`),
    INDEX `zcta5` (`zcta5`)
)
    COLLATE = 'utf8_general_ci'
    ENGINE = InnoDB
;
