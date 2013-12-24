ALTER TABLE  `db_version` CHANGE `required_r2464_02_mangos_game_weather` `required_r2464_03_mangos_quest_template` BIT(1) NULL DEFAULT NULL;

ALTER TABLE `quest_template` ADD COLUMN `MaxLevel` tinyint(3) unsigned NOT NULL DEFAULT '0' AFTER `MinLevel`;
