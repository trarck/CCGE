
#ifndef CCGE_ENTITYCOMPONENT_EntityPropertyFactory_H_
#define CCGE_ENTITYCOMPONENT_EntityPropertyFactory_H_

#include "cocos2d.h"
#include "CCGEMacros.h"
#include "GameEntity.h"

NS_CC_GE_BEGIN

class EntityPropertyFactory:public CCObject
{
public:
    
	EntityPropertyFactory();
    
	~EntityPropertyFactory();
    
    virtual bool init();
    
    static EntityPropertyFactory* getInstance();
    
    /**
     * @brief 添加物体地图相关属性
     * 创建的属性没有被赋值
     */
    void createMapProperties(GameEntity* entity);
    
    /**
     * @brief 添加物体战斗相关属性
     * 创建的属性没有被赋值
     */
    void createBattleProperties(GameEntity* entity);
    
    void createBattleProperties(GameEntity* entity,CCDictionary* params);
    
    void createBattleProperties(GameEntity* entity,const yhge::Json::Value& params);
    
};

NS_CC_GE_END



#endif // CCGE_ENTITYCOMPONENT_EntityPropertyFactory_H_
