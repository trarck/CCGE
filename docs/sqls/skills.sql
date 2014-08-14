CREATE TABLE "skills" (
	 "id" integer NOT NULL,
	 "name" text NOT NULL DEFAULT '',
	 "attack_type" integer NOT NULL DEFAULT '0',--攻击类型 普通攻击,法术攻击,其它攻击
	 "damage_type" integer NOT NULL DEFAULT '0',--伤害类型 物理伤害,魔法伤害,忽视护甲抗性伤害
	 "target_type" integer NOT NULL DEFAULT '0',--目标类型 默认,自己,最近,最远,随机,最弱,最强,最多魔法,最少魔法,最大智力,最少血量
	 "target_camp" integer NOT NULL DEFAULT '0',--目标阵营
	 "max_range" real NOT NULL DEFAULT '0',--攻击最大范围
	 "min_range" real NOT NULL DEFAULT '0',--攻击最小范围
	 "init_cd" real NOT NULL DEFAULT '0',--技能cd
	 "global_cd" real NOT NULL DEFAULT '0',--公用cd
	 "cd" real NOT NULL DEFAULT '0',--打断后继续的cd
	 "manual" integer NOT NULL DEFAULT '0',--是手动技能还是自动释放。大招是手动，其它小技能都自动释放
	 "cost_mp" real NOT NULL DEFAULT '0',--消耗的魔法值
	 "active_type" integer NOT NULL DEFAULT '0',--技能作用方式 0-主动(active)需要施放(手动或自动),1-被动(passive)加属性类,2-光环(aura),3-负光环(negative_aura)
	 "knock_up" real NOT NULL DEFAULT '0',--击飞，z方向偏移
	 "knock_back" real NOT NULL DEFAULT '0',--击退，x方向
	 "move_forward" real NOT NULL DEFAULT '0',--攻击的时候是移动距离。0-不移动
	 "affected_camp" integer NOT NULL DEFAULT '0', --作用的阵营 -1-对方,0-所有,1-己方
	 "affect_field" integer NOT NULL DEFAULT '0',--影响的属性 0-hp,1-mp
	 "gain_mp" real NOT NULL DEFAULT '0',  --回复mp的参数
	 "level" integer NOT NULL DEFAULT '0',--等级
	 "buff_id" integer NOT NULL DEFAULT '0',--技能附带的Buff
	 "life_drain_ratio" real NOT NULL DEFAULT '0',--吸血比。0-不吸血。使用百分比,50表示50%即0.5，也可以是小数，根据公式实际调整 
	 "crit_ratio" real NOT NULL DEFAULT '0',--暴击伤害比。
	 
	 "outside_screen" real NOT NULL DEFAULT '0',  --攻击屏幕外
	 
	 "basic_num" real NOT NULL DEFAULT '0',
	 "passive_attr" integer NOT NULL DEFAULT '0',--被动属性类型
	 "plus_attr" integer NOT NULL DEFAULT '0',--附加属性类型
	 "plus_ratio" real NOT NULL DEFAULT '0',  --附加属性比例
	 --链式技能 生命吸取等
	 "chain_gap" real NOT NULL DEFAULT '0', --攻击链的持续时间
	 "chain_jumps" integer NOT NULL DEFAULT '0',--攻击链跳跃次数
	 --子弹类技能
	 "tile_gravity" real NOT NULL DEFAULT '0',
	 "tile_xy_speed" real NOT NULL DEFAULT '0', -- use for projectile
	 "tile_z_speed" real NOT NULL DEFAULT '0',  --use for projectile
	 "tile_ott_height" real NOT NULL DEFAULT '0',  --use for projectile
	 "tile_piercing" integer NOT NULL DEFAULT '0', --子弹是否穿透
	 "tile_distance" real NOT NULL DEFAULT '0', --子弹的攻击距离 0-无限大
	 "aim_target" integer NOT NULL DEFAULT '0',--是否瞄准目标
	 
	 "action_id" integer NOT NULL DEFAULT '0',--主角在施放技能执行的动画名称。通常只有一个动作，但有的会有多个，通过映射表来取
	 
	 --效果
	 "x_shift" real NOT NULL DEFAULT '0',--技能效果播放的x轴偏移
	 "launch_effect" text NOT NULL DEFAULT '',--起手动画
	 "impact_effect" text NOT NULL DEFAULT '',--
	 "impact_zorder" real NOT NULL DEFAULT '0',
	 "point_effect" text NOT NULL DEFAULT '',
	 "point_zorder" real NOT NULL DEFAULT '0',
	 --范围攻击
	 "aoe_shape" integer NOT NULL DEFAULT '0',--范围攻击类型 0-不是范围攻击 1-rectangle,2-circle,3-halfcircle,4-quartercircle
	 "shape_arg1" real NOT NULL DEFAULT '0',--
	 "shape_arg2" real NOT NULL DEFAULT '0',--
	 
	 --功能参数
	 "script_arg1" real NOT NULL DEFAULT '0',
	 "script_arg2" real NOT NULL DEFAULT '0',
	 "script_arg3" real NOT NULL DEFAULT '0',
	 "script_arg4" real NOT NULL DEFAULT '0',
	 "script_arg5" real NOT NULL DEFAULT '0',
	 "script_arg6" real NOT NULL DEFAULT '0',


	 "description" text NOT NULL DEFAULT '',

	PRIMARY KEY("id")
);