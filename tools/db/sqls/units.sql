/*
 Navicat Premium Data Transfer

 Source Server         : ccge_game
 Source Server Type    : SQLite
 Source Server Version : 3006022
 Source Database       : main

 Target Server Type    : SQLite
 Target Server Version : 3006022
 File Encoding         : utf-8

 Date: 04/17/2014 14:30:19 PM
*/

-- ----------------------------
--  Table structure for "units"
-- ----------------------------
DROP TABLE IF EXISTS "units";
CREATE TABLE "units" (
	 "id" integer NOT NULL,
	 "name" text NOT NULL DEFAULT '',
	 "description" text NOT NULL DEFAULT '',
	 "level" integer NOT NULL DEFAULT '0',
	 "base_health" real NOT NULL DEFAULT '0',
	 "base_mana" real NOT NULL DEFAULT '0',
	 "base_defence" real NOT NULL DEFAULT '0',
	 "base_damage" real NOT NULL DEFAULT '0',
	 "base_agility" real NOT NULL DEFAULT '0', -- 敏捷值，目前只提供攻击速度。对换比是0.02即50点敏捷加一点攻击速度。对换比是可以调的
	 "base_attack_speed" real NOT NULL DEFAULT '0.5', -- 基础攻击速度，值越大攻击速度越快
	 "grow_health" real NOT NULL DEFAULT '0',
	 "grow_mana" real NOT NULL DEFAULT '0',
	 "grow_defence" real NOT NULL DEFAULT '0',
	 "grow_damage" real NOT NULL DEFAULT '0',
	 "grow_agility" real NOT NULL DEFAULT '0',
	 "grow_type" integer NOT NULL DEFAULT '0',
	 "icon" text NOT NULL DEFAULT '',
	PRIMARY KEY("id")
);

