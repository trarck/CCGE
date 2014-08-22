CREATE TABLE "units" (
	 "id" integer NOT NULL,
	 "name" text NOT NULL DEFAULT '',
	 "health" real NOT NULL DEFAULT '0',
	 "mana" real NOT NULL DEFAULT '0',
	 "base_strength" real NOT NULL DEFAULT '0.5',--基础力量
	 "base_agility" real NOT NULL DEFAULT '0',	  --基础敏捷
	 "base_intellect" real NOT NULL DEFAULT '0',  --基础智力
	 "grow_strength" real NOT NULL DEFAULT '0',	  --智力增长
	 "grow_agility" real NOT NULL DEFAULT '0',	  --敏捷增长
	 "grow_intellect" real NOT NULL DEFAULT '0',  --智力增长
	 "grow_type" integer NOT NULL DEFAULT '0',    --增长类型
	 
	 "armor" real NOT NULL DEFAULT '0',--护甲
	 "magic_resistance" real NOT NULL DEFAULT '0',--魔法抗性 对魔法伤害类型的抵抗，即对魔法伤害的值的减少
	 "attack_damage" real NOT NULL DEFAULT '0', --物理攻击力 初始的
	 "ability_power" real NOT NULL DEFAULT '0' , --法术强度   初始的
	 "attack_speed" real NOT NULL DEFAULT '0',  --攻击速度 HAST[haste]
	 "crit" real NOT NULL DEFAULT '0',  --物理暴击
	 "magic_crit" real NOT NULL DEFAULT '0',  --魔法暴击
	 "armor_penetrate" real NOT NULL DEFAULT '0',  --穿透物理护甲
	 "magic_resistance_ignore" real NOT NULL DEFAULT '0',  --忽视魔法抗性
	 
	 "main_attribute" integer NOT NULL DEFAULT '1', --主属性
	 "walk_speed" real NOT NULL DEFAULT '0',  --行走速度
	 "hit"  real NOT NULL DEFAULT '0',  --命中
	 "dodg" real NOT NULL DEFAULT '0',  --闪避
	 "health_regenerate" real NOT NULL DEFAULT '0',  --生命回复
	 "mana_regenerate" real NOT NULL DEFAULT '0',  --魔法值回复
	 "heal" real NOT NULL DEFAULT '0',  --治疗效果提高
	 "life_drain" real NOT NULL DEFAULT '0',  --吸血等级 表示吸血的能力
	 "mana_cost_reduced" real NOT NULL DEFAULT '0',  --魔法消耗降低
	 --"level" integer NOT NULL DEFAULT '0',
	 "description" text NOT NULL DEFAULT '',
	 "icon" text NOT NULL DEFAULT '',
	 "unit_type" integer NOT NULL DEFAULT '0', --单位类型 0-未确定,1-英雄(Hero),2-怪物(Monster)
	 "gender" integer NOT NULL DEFAULT '0', --姓别 0-待定,1-男,2-女
	 --extend property
	 "basic_skill" integer NOT NULL DEFAULT '0', --普通攻击
	 "flyable" integer NOT NULL DEFAULT '0',
	 "max_stars" integer NOT NULL DEFAULT '0', --最大星级
	 "initial_stars" integer NOT NULL DEFAULT '0', --初始星级
	 "dps_statistics_ratio" real NOT NULL DEFAULT '1',  --伤害统计比率
	 "mana_gain_rate" real NOT NULL DEFAULT '1',  --失去血量回复魔法比
	 "script" text NOT NULL DEFAULT '',--英雄脚本
	 "puppet" text NOT NULL DEFAULT '',--英雄动画
	 "art" text NOT NULL DEFAULT '',--卡牌大图
	 "portrait" text NOT NULL DEFAULT '',--卡牌缩略图
	 "puppet_switch" text NOT NULL DEFAULT '',--英雄动画反转
	 "art_switch" text NOT NULL DEFAULT '',--卡牌反转大图
	 "portrait_switch" text NOT NULL DEFAULT '',--卡牌反转缩略图
	 
	 "mp_type" integer NOT NULL DEFAULT '0',--能量条类型
	 
	 "puppet_id" integer NOT NULL DEFAULT '0', --元素动画id
	 "collide_radius" real NOT NULL DEFAULT '0',  --碰撞半径
	 
	PRIMARY KEY("id")
);