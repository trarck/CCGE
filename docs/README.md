1.entity的说明
		entity
		
		 |
			
		unit
	   /	\
	  /	 	 \
	play    monster
	

注意entityId和unitId是不同的.
entityId是enitty的唯一标识.
unit可能被几个entity使用。
比如玩家队伍，同一个玩家可以拥有不同的unit,但entityId不同。
比如怪物，不同关卡，出现的怪物可以是同一个unit，只是等级装备不同。

unit是裸的物体，没有等级信息，没有装备，只提供一些属性和显示内容。
具体的entity，是有信息，有的时候还有buffer，装备等。
关于技能：
1.只接和unit放在一起。每个物体相同技能。
2.另外配置。可以实现玩家的更换技能，同种怪物，不同关卡可以携带不同技能。灵活。