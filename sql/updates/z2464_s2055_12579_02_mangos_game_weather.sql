ALTER TABLE  `db_version` CHANGE `required_r2464_01_mangos_gameobject_template` `required_r2464_02_mangos_game_weather` BIT(1) NULL DEFAULT NULL;

ALTER TABLE `game_weather` ADD `ScriptName` varchar(64) NOT NULL DEFAULT '' AFTER `winter_storm_chance`;
