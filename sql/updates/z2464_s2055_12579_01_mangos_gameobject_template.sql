ALTER TABLE  `db_version` CHANGE `required_r2441_01_mangos_db_version` `required_r2464_01_mangos_gameobject_template` BIT(1) NULL DEFAULT NULL;

ALTER TABLE `gameobject_template` ADD `AIName` char(64) NOT NULL DEFAULT '' AFTER `maxgold`;
