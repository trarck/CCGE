CREATE TABLE "buffs" (
	 "id" integer NOT NULL,
	 "control_effect" integer NOT NULL DEFAULT '0', --控制效果。数组。这里是映射id
	 "name" text NOT NULL DEFAULT '', --名称
	PRIMARY KEY("id")
);