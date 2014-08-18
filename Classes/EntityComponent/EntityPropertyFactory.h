
#ifndef CCGE_ENTITYCOMPONENT_ENTITYPROPERTYFACTORY_H_
#define CCGE_ENTITYCOMPONENT_ENTITYPROPERTYFACTORY_H_

#include "cocos2d.h"
#include "CCGEMacros.h"
#include "GameEntity.h"
#include "Properties/UnitProperty.h"
#include "Properties/BattleProperty.h"
#include "Properties/SkillProperty.h"
#include "Properties/MoveProperty.h"

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
    
    void addUnitProperty(GameEntity* entity,const yhge::Json::Value& config,const yhge::Json::Value& info);
    
    void addBattleProperty(GameEntity* entity);
    
    void addBattleProperty(GameEntity* entity,const yhge::Json::Value& value);
        
    void addRealtimeBattleProperty(GameEntity* entity,const yhge::Json::Value& config,const yhge::Json::Value& unitInfo);
    
    void addMoveProperty(GameEntity* entity,const yhge::Json::Value& config);
    
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
    
    void setUnitPropertyValue(UnitProperty* property,const yhge::Json::Value& config,const yhge::Json::Value& info);
    
    void setBattlePropertyValue(BattleProperty* property,const yhge::Json::Value& config,const yhge::Json::Value& unitInfo);
    
    void setMovePropertyValue(MoveProperty* property,const yhge::Json::Value& config);
    
    void setSkillPropertyValue(SkillProperty* property,const yhge::Json::Value& value);
    
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


#endif // CCGE_ENTITYCOMPONENT_ENTITYPROPERTYFACTORY_H_
