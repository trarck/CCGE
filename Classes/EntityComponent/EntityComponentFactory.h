#ifndef CCGE_ENTITYCOMPONENT_ENTITYCOMPONENTFACTORY_H_
#define CCGE_ENTITYCOMPONENT_ENTITYCOMPONENTFACTORY_H_

#include "cocos2d.h"
#include "CCGEMacros.h"
#include "GameEntity.h"

NS_CC_GE_BEGIN

class EntityFactory;

class EntityComponentFactory:public CCObject
{
public:
    
	EntityComponentFactory();
    
	~EntityComponentFactory();
    
    virtual bool init();
    
    static EntityComponentFactory* getInstance();
    
    void addBattleRendererComponent(GameEntity* entity);
    
    void addBattleAnimationComponent(GameEntity* entity);
    
    void addBattleComponent(GameEntity* entity);
    
    void addDieComponent(GameEntity* entity);
    
    void addHealthBarComponent(GameEntity* entity);
    
    void addHurtComponent(GameEntity* entity);
    
    void addBattlePositionComponent(GameEntity* entity);
    
    void addBattleStateMachineComponent(GameEntity* entity);
    
    void addAIComponent(GameEntity* entity);
    
    void addPositionComponent(GameEntity* entity);
    
    void addMoveComponent(GameEntity* entity);
        
    void addSkillComponents(GameEntity* entity);
    
    void addSkillComponent(GameEntity* entity);
    
    void addStateComponent(GameEntity* entity);
    
    void addDamageComponent(GameEntity* entity);
    
    void addVisibleMoveComponent(GameEntity* entity);
    
    void addTipComponent(GameEntity* entity);
    
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
    
    CCArray* createEightAnimations(const yhge::Json::Value& configData);
    
    CCArray* createTwoAnimations(const yhge::Json::Value& configData);
    
protected:
    //对实体创建工厂的弱引用
    EntityFactory* m_entityFactory;
};

NS_CC_GE_END



#endif // CCGE_ENTITYCOMPONENT_ENTITYCOMPONENTFACTORY_H_
