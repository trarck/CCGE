CREATE TABLE "buff_exts" (
	 "id" integer NOT NULL,
	 
	 "strength" real NOT NULL DEFAULT '0.5',--力量 STR
	 "strength_mult" real NOT NULL DEFAULT '0.5',--力量 STR
	 "agility" real NOT NULL DEFAULT '0',	  --敏捷 AGI
	 "agility_mult" real NOT NULL DEFAULT '0',	  --敏捷 AGI
	 "intellect" real NOT NULL DEFAULT '0',  --智力 INT
	 "intellect_mult" real NOT NULL DEFAULT '0',  --智力 INT
	 "armor" real NOT NULL DEFAULT '0',--护甲 ARM
	 "armor_mult" real NOT NULL DEFAULT '0',--护甲 ARM
	 "magic_resistance" real NOT NULL DEFAULT '0',--魔法抗性 对魔法伤害类型的抵抗，即对魔法伤害的值的减少
	 "magic_resistance_mult" real NOT NULL DEFAULT '0',--魔法抗性 对魔法伤害类型的抵抗，即对魔法伤害的值的减少
	 "attack_damage" real NOT NULL DEFAULT '0', --物理攻击力 AD
	 "attack_damage_mult" real NOT NULL DEFAULT '0', --物理攻击力 AD
	 "ability_power" real NOT NULL DEFAULT '0' , --法术强度  AP
	 "ability_power_mult" real NOT NULL DEFAULT '0' , --法术强度  AP
	 "attack_speed" real NOT NULL DEFAULT '0',  --攻击速度 HAST
	 "attack_speed_mult" real NOT NULL DEFAULT '0',  --攻击速度 HAST
	 "crit" real NOT NULL DEFAULT '0',  --物理暴击 CRIT
	 "crit_mult" real NOT NULL DEFAULT '0',  --物理暴击 CRIT
	 "magic_crit" real NOT NULL DEFAULT '0',  --魔法暴击 MCRIT
	 "magic_crit_mult" real NOT NULL DEFAULT '0',  --魔法暴击 MCRIT
	 "armor_penetrate" real NOT NULL DEFAULT '0',  --穿透物理护甲 ARMP
	 "armor_penetrate_mult" real NOT NULL DEFAULT '0',  --穿透物理护甲 ARMP
	 "magic_resistance_ignore" real NOT NULL DEFAULT '0',  --忽视魔法抗性 MRI
	 "magic_resistance_ignore_mult" real NOT NULL DEFAULT '0',  --忽视魔法抗性 MRI
	 "physical_immune" integer NOT NULL DEFAULT '1', --物理免疫 PIMU
	 "physical_immune_mult" integer NOT NULL DEFAULT '1', --物理免疫 PIMU
	 "magic_immune" integer NOT NULL DEFAULT '1', --魔法免疫    MIMU
	 "magic_immune_mult" integer NOT NULL DEFAULT '1', --魔法免疫    MIMU
	 "hit"  real NOT NULL DEFAULT '0',  --命中 HIT
	 "hit_mult"  real NOT NULL DEFAULT '0',  --命中 HIT
	 "dodg" real NOT NULL DEFAULT '0',  --闪避 DODG
	 "dodg_mult" real NOT NULL DEFAULT '0',  --闪避 DODG
	 "health_regenerate" real NOT NULL DEFAULT '0',  --生命回复 HPS
	 "health_regenerate_mult" real NOT NULL DEFAULT '0',  --生命回复 HPS
	 "mana_regenerate" real NOT NULL DEFAULT '0',  --魔法值回复 MPS
	 "mana_regenerate_mult" real NOT NULL DEFAULT '0',  --魔法值回复 MPS
	 "heal" real NOT NULL DEFAULT '0',  --治疗效果 HEAL
	 "heal_mult" real NOT NULL DEFAULT '0',  --治疗效果 HEAL
	 "life_drain" real NOT NULL DEFAULT '0',  --吸血等级 LFS
	 "life_drain_mult" real NOT NULL DEFAULT '0',  --吸血等级 LFS
	 "mana_cost_reduced" real NOT NULL DEFAULT '0',  --魔法消耗降低 CDR
	 "mana_cost_reduced_mult" real NOT NULL DEFAULT '0',  --魔法消耗降低 CDR
	 "model_speeder" real NOT NULL DEFAULT '0',  --模型速度 MSPD
	 "model_speeder_mult" real NOT NULL DEFAULT '0',  --模型速度 MSPD
	 
	PRIMARY KEY("id")
);