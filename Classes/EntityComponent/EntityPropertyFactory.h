
#ifndef CCGE_ENTITYCOMPONENT_EntityPropertyFactory_H_
#define CCGE_ENTITYCOMPONENT_EntityPropertyFactory_H_

#include "cocos2d.h"
#include "CCGEMacros.h"
#include "GameEntity.h"

NS_CC_GE_BEGIN

class EntityFactory;

class EntityPropertyFactory:public CCObject
{
public:
    
	EntityPropertyFactory();
    
	~EntityPropertyFactory();
    
    virtual bool init();
    
    static EntityPropertyFactory* getInstance();
    
    void addUnitProperty(GameEntity* entity);
    
    void addUnitProperty(GameEntity* entity,const yhge::Json::Value& value);
    
    void addBattleProperty(GameEntity* entity);
    
    void addBattleProperty(GameEntity* entity,const yhge::Json::Value& value);
    
    void addBattleProperty(GameEntity* entity,int col,int row,int side,float scale);
    
    void addRealtimeBattleProperty(GameEntity* entity,float x,float y,int side,float scale);
    
    /**
     * @brief 添加物体地图相关属性
     * 创建的属性没有被赋值
     */
    void addMapProperties(GameEntity* entity);
    
    /**
     * @brief 添加物体战斗相关属性
     * 创建的属性没有被赋值
     */
    void addBattleProperties(GameEntity* entity);
    
    void addBattleProperties(GameEntity* entity,CCDictionary* params);
    
    void addBattleProperties(GameEntity* entity,const yhge::Json::Value& params);
    
    void setUnitPropertyValue(UnitProperty* property,const yhge::Json::Value& value);
    
    void setBattlePropertyValue(BattleProperty* property,const yhge::Json::Value& value);
    
public:
    inline void setEntityFactory(EntityFactory* entityFactory)
    {
        m_entityFactory = entityFactory;
    }
    
    inline EntityFactory* getEntityFactory()
    {
        return m_entityFactory;
    }
protected:
    //对实体创建工厂的弱引用
    EntityFactory* m_entityFactory;
};

NS_CC_GE_END


#endif // CCGE_ENTITYCOMPONENT_EntityPropertyFactory_H_
