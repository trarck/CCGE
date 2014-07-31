CREATE TABLE "buffs" (
	 "id" integer NOT NULL,
	 "name" text NOT NULL DEFAULT '',
	 "time" real NOT NULL DEFAULT '0',--持续时间
	 "clear_on_death" integer NOT NULL DEFAULT '0',    --死亡清除
	 "shield_type" integer NOT NULL DEFAULT '0', --护盾类型 0-无护盾,1-防物理(AD),2-防魔法(AP),3-暗影盾(shallow grave)[死亡后任然可以存活一段时间],255-all
	 "shield_value" real NOT NULL DEFAULT '0', --护盾的值
	 "level_check_dice" integer NOT NULL DEFAULT '0',--命中等级.主要是负面buff作用于目标的时候
	 --对属性的影响
	 "strength" real NOT NULL DEFAULT '0.5',--力量 STR
	 "agility" real NOT NULL DEFAULT '0',	  --敏捷 AGI
	 "intellect" real NOT NULL DEFAULT '0',  --智力 INT
	 
	 "armor" real NOT NULL DEFAULT '0',--护甲 ARM
	 "magic_resistance" real NOT NULL DEFAULT '0',--魔法抗性 对魔法伤害类型的抵抗，即对魔法伤害的值的减少
	 "attack_damage" real NOT NULL DEFAULT '0', --物理攻击力 初始的
	 "ability_power" real NOT NULL DEFAULT '0' , --法术强度   初始的
	 "attack_speed" real NOT NULL DEFAULT '0',  --攻击速度
	 "crit" real NOT NULL DEFAULT '0',  --物理暴击
	 "magic_crit" real NOT NULL DEFAULT '0',  --魔法暴击 MCRIT
	 "armor_penetrate" real NOT NULL DEFAULT '0',  --穿透物理护甲
	 "magic_resistance_ignore" real NOT NULL DEFAULT '0',  --忽视魔法抗性 MRI
	 "physical_immune" integer NOT NULL DEFAULT '1', --物理免疫 PIMU
	 "magic_immune" integer NOT NULL DEFAULT '1', --魔法免疫    MIMU
	 "main_attribute" integer NOT NULL DEFAULT '1', --主属性
	 "walk_speed" real NOT NULL DEFAULT '0',  --行走速度
	 "hit"  real NOT NULL DEFAULT '0',  --命中 HIT
	 "dodg" real NOT NULL DEFAULT '0',  --闪避 DODG
	 "health_regenerate" real NOT NULL DEFAULT '0',  --生命回复 HPR
	 "mana_regenerate" real NOT NULL DEFAULT '0',  --魔法值回复 MPR
	 "heal" real NOT NULL DEFAULT '0',  --治疗效果提高
	 "life_drain" real NOT NULL DEFAULT '0',  --吸血等级 表示吸血的能力
	 "mana_cost_reduced" real NOT NULL DEFAULT '0',  --魔法消耗降低
	 --"level" integer NOT NULL DEFAULT '0',
	 "description" text NOT NULL DEFAULT '',
	 "icon" text NOT NULL DEFAULT '',
	 --extend property
	 "basic_skill" integer NOT NULL DEFAULT '0', --普通攻击
	 "flyable" integer NOT NULL DEFAULT '0',
	 "max_stars" integer NOT NULL DEFAULT '0', --最大星级
	 "initial_stars" integer NOT NULL DEFAULT '0', --初始星级
	PRIMARY KEY("id")
);