CREATE TABLE "skill_groups" (
	 "id" integer NOT NULL,
	 "name" text NOT NULL DEFAULT '',--技能名称 和技能表相同
	 "display_name" text NOT NULL DEFAULT '',--技能显示名字
	 
	 "skill_id" integer NOT NULL DEFAULT '0',--技能id
	 "priority" integer NOT NULL DEFAULT '0',--
	 "slot" integer NOT NULL DEFAULT '0',--
	 "ratio" real NOT NULL DEFAULT '0',
	 -- "cd" real NOT NULL DEFAULT '0',
	 "init_level" integer NOT NULL DEFAULT '0',-- 初始等级
	 "interruptable" integer NOT NULL DEFAULT '0',--是否可打断
	 
	 "unlock" integer NOT NULL DEFAULT '0',-- 解锁进阶等级
	 "unlock_for_monster" integer NOT NULL DEFAULT '0',--怪物的解锁进阶等级
	 "caster_name" text NOT NULL DEFAULT '',--技能所属英雄
	 "caster_id" integer NOT NULL DEFAULT '0',--技能所属英雄id
	 "icon" text NOT NULL DEFAULT '',
	 
	 "skill_tag" integer NOT NULL DEFAULT '0',
	 
	 "basic_growth" real NOT NULL DEFAULT '0',
	 "max_value" real NOT NULL DEFAULT '0',
	 
	 "growth_field_1" integer NOT NULL DEFAULT '0',--升级提升类型
	 "growth_value_1" real NOT NULL DEFAULT '0',--升级提升值
	 "growth_multiplier_1" real NOT NULL DEFAULT '0',--升级提升比
	 "growth_summary_1" text NOT NULL DEFAULT '',--升级提升说明
	 "growth_popup_1" text NOT NULL DEFAULT '',--升级提升提示
	 
	 "growth_field_2" integer NOT NULL DEFAULT '0',--升级提升类型
	 "growth_value_2" real NOT NULL DEFAULT '0',--升级提升值
	 "growth_multiplier_2" real NOT NULL DEFAULT '0',--升级提升比
	 "growth_summary_2" text NOT NULL DEFAULT '',--升级提升说明
	 "growth_popup_2" text NOT NULL DEFAULT '',--升级提升提示
	 
	 "growth_field_3" integer NOT NULL DEFAULT '0',--升级提升类型
	 "growth_value_3" real NOT NULL DEFAULT '0',--升级提升值
	 "growth_multiplier_3" real NOT NULL DEFAULT '0',--升级提升比
	 "growth_summary_3" text NOT NULL DEFAULT '',--升级提升说明
	 "growth_popup_3" text NOT NULL DEFAULT '',--升级提升提示
	 
	 "growth_field_4" integer NOT NULL DEFAULT '0',--升级提升类型
	 "growth_value_4" real NOT NULL DEFAULT '0',--升级提升值
	 "growth_multiplier_4" real NOT NULL DEFAULT '0',--升级提升比
	 "growth_summary_4" text NOT NULL DEFAULT '',--升级提升说明
	 "growth_popup_4" text NOT NULL DEFAULT '',--升级提升提示
	 
	PRIMARY KEY("id")
);