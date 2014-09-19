CREATE TABLE "buff_control_effects" (
	 "id" integer NOT NULL,
	 "control_effect" integer NOT NULL DEFAULT '0', --控制效果。数组。这里是映射id
	 "effect" text NOT NULL DEFAULT '', --buff effect name
	 "effect_type" integer NOT NULL DEFAULT '0', --buff effect type
	PRIMARY KEY("id")
);