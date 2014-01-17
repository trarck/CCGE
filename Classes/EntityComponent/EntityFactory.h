
#ifndef CCGE_ENTITYCOMPONENT_ENTITYFACTORY_H_
#define CCGE_ENTITYCOMPONENT_ENTITYFACTORY_H_

#include "cocos2d.h"
#include "CCGEMacros.h"
#include "GameEntity.h"

NS_CC_GE_BEGIN

class EntityFactory:public CCObject
{
public:
    
	EntityFactory();
    
	~EntityFactory();
    
    virtual bool init();
    
    static EntityFactory* getInstance();
    
    /**
     * 从配置文件中创建一个游戏实体
     */
    GameEntity* createEntity(CCDictionary* data);
    
    /**
     * 创建一个人物
     */
    GameEntity* createPlayer(CCDictionary* param);
};

NS_CC_GE_END



#endif // CCGE_ENTITYCOMPONENT_ENTITYFACTORY_H_
