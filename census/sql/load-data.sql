/* Commented to prevent accidents.  These commands can be used
   to load specific source tables straight from the appropriate
   CSV file.  Alternatively, the <table>.sql series of files
   may be run to pre-load the data for their respective tables.
   */
/* Load counties from the CSV */
/*
CREATE TEMPORARY TABLE t_counties(
	`state_geopart` CHAR(2) NOT NULL COLLATE 'utf8_general_ci',
	`geopart` CHAR(3) NOT NULL COLLATE 'utf8_general_ci',
	`name` VARCHAR(50) NOT NULL DEFAULT '' COLLATE 'utf8_general_ci'
);

LOAD DATA LOCAL INFILE 'geocorr2014.csv'
INTO TABLE t_counties
CHARACTER SET latin1
FIELDS TERMINATED BY ',' OPTIONALLY ENCLOSED BY '"'
LINES TERMINATED BY '\n'
IGNORE 2 LINES
(@statecounty, @dummy, @dummy, @dummy, @dummy, @dummy, @dummy, @dummy, name, @dummy, @dummy, @dummy)
SET state_geopart = SUBSTR(@statecounty,1,2),
geopart = SUBSTR(@statecounty,3,3);

INSERT INTO counties (state_geopart, geopart, `name`)
SELECT distinct state_geopart, geopart, `name`
FROM t_counties ORDER BY state_geopart, geopart;

DROP TEMPORARY TABLE t_counties;
*/

/* Load district_upper from the CSV */
/*
CREATE TEMPORARY TABLE t_district (
	`state_geopart` CHAR(2) NOT NULL COLLATE 'utf8_general_ci',
	`county_geopart` CHAR(3) NOT NULL COLLATE 'utf8_general_ci',
	`tract` CHAR(6) NOT NULL COLLATE 'utf8_general_ci',
	`district` CHAR(3) NOT NULL COLLATE 'utf8_general_ci'
	);

LOAD DATA LOCAL INFILE 'd:/dev/vm_xfer/geocorr2014.csv'
    INTO TABLE t_district
    CHARACTER SET latin1
    FIELDS TERMINATED BY ',' OPTIONALLY ENCLOSED BY '"'
    LINES TERMINATED BY '\n'
    IGNORE 2 LINES
    (@statecounty, @tractcode, @dummy, @dummy, @dummy, district, @dummy, @dummy, @dummy, @dummy, @dummy, @dummy)
    SET state_geopart = SUBSTR(@statecounty, 1, 2),
        county_geopart = SUBSTR(@statecounty, 3, 3),
        tract = REPLACE(@tractcode, '.', '');

INSERT INTO district_upper (state_geopart, county_geopart, tract, district)
SELECT distinct state_geopart, county_geopart, tract, district
FROM t_district ORDER BY state_geopart, county_geopart;

DROP TEMPORARY TABLE t_district;
 */

/* Load ZCTA from the CSV */
/*
LOAD DATA LOCAL INFILE 'geocorr2014.csv'
    INTO TABLE zcta_data
    CHARACTER SET latin1
    FIELDS TERMINATED BY ',' OPTIONALLY ENCLOSED BY '"'
    LINES TERMINATED BY '\n'
    IGNORE 2 LINES
    (@statecounty, @tractcode, @dummy, zcta5, @dummy, @dummy, @dummy, @dummy, @dummy, zcta_name, @dummy, @dummy)
    SET state_code = SUBSTR(@statecounty, 1, 2),
        county_code = SUBSTR(@statecounty, 3, 3),
        tract = REPLACE(@tractcode, '.', '');


 */

/* Pre-load geo-type names */
INSERT INTO geo_type (code, name)
VALUES ('0100000', 'National'),
       ('0200000', 'Region'),
       ('0400000', 'State'),
       ('0500000', 'County'),
       ('0600000', 'County Subdivision'),
       ('1400000', 'Census Tract'),
       ('1600000', 'Incorporated Place'),
       ('1700000', 'Consolidated Cities'),
       ('2500000', 'Reservation/Native Hawaiian'),
       ('2560000', 'Tribal Census Tract'),
       ('5001600', 'Congressional District');

/* Pre-load states */
INSERT INTO `states` (name, geopart, abbr)
VALUES ('Alabama', '01', 'AL'),
       ('Alaska', '02', 'AK'),
       ('Arizona', '04', 'AZ'),
       ('Arkansas', '05', 'AR'),
       ('California', '06', 'CA'),
       ('Colorado', '08', 'CO'),
       ('Connecticut', '09', 'CT'),
       ('Delaware', '10', 'DE'),
       ('District of Columbia', '11', 'DC'),
       ('Florida', '12', 'FL'),
       ('Georgia', '13', 'GA'),
       ('Hawaii', '15', 'HI'),
       ('Idaho', '16', 'ID'),
       ('Illinois', '17', 'IL'),
       ('Indiana', '18', 'IN'),
       ('Iowa', '19', 'IA'),
       ('Kansas', '20', 'KS'),
       ('Kentucky', '21', 'KY'),
       ('Louisiana', '22', 'LA'),
       ('Maine', '23', 'ME'),
       ('Maryland', '24', 'MD'),
       ('Massachusetts', '25', 'MA'),
       ('Michigan', '26', 'MI'),
       ('Minnesota', '27', 'MN'),
       ('Mississippi', '28', 'MS'),
       ('Missouri', '29', 'MO'),
       ('Montana', '30', 'MT'),
       ('Nebraska', '31', 'NE'),
       ('Nevada', '32', 'NV'),
       ('New Hampshire', '33', 'NH'),
       ('New Jersey', '34', 'NJ'),
       ('New Mexico', '35', 'NM'),
       ('New York', '36', 'NY'),
       ('North Carolina', '37', 'NC'),
       ('North Dakota', '38', 'ND'),
       ('Ohio', '39', 'OH'),
       ('Oklahoma', '40', 'OK'),
       ('Oregon', '41', 'OR'),
       ('Pennsylvania', '42', 'PA'),
       ('Rhode Island', '44', 'RI'),
       ('South Carolina', '45', 'SC'),
       ('South Dakota', '46', 'SD'),
       ('Tennessee', '47', 'TN'),
       ('Texas', '48', 'TX'),
       ('Utah', '49', 'UT'),
       ('Vermont', '50', 'VT'),
       ('Virginia', '51', 'VA'),
       ('Washington', '53', 'WA'),
       ('West Virginia', '54', 'WV'),
       ('Wisconsin', '55', 'WI'),
       ('Wyoming', '56', 'WY'),
       ('American Samoa', '60', 'AS'),
       ('Federated States of Micronesia', '64', 'FM'),
       ('Guam', '66', 'GU'),
       ('Marshall Islands', '68', 'MH'),
       ('Commonwealth of the Northern Mariana Islands', '69', 'MP'),
       ('Palau', '70', 'PW'),
       ('Puerto Rico', '72', 'PR'),
       ('U.S. Minor Outlying Islands', '74', 'UM'),
       ('U.S. Virgin Islands', '78', 'VI'),
       ('Baker Island', '81', ''),
       ('Howland Island', '84', ''),
       ('Jarvis Island', '86', ''),
       ('Johnston Atoll', '67', ''),
       ('Kingman Reef', '89', ''),
       ('Midway Islands', '71', ''),
       ('Navassa Island', '76', ''),
       ('Palmyra Atoll', '95', ''),
       ('Wake Island', '79', '');
