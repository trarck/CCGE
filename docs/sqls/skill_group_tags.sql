CREATE TABLE "skill_group_tags" (
	 "id" integer NOT NULL,
	 
	 "skill_group_id" integer NOT NULL DEFAULT '0',--技能id
	 "tag" text NOT NULL DEFAULT '',
	 
	PRIMARY KEY("id")
);