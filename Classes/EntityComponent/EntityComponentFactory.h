#ifndef CCGE_ENTITYCOMPONENT_ENTITYCOMPONENTFACTORY_H_
#define CCGE_ENTITYCOMPONENT_ENTITYCOMPONENTFACTORY_H_

#include "cocos2d.h"
#include "CCGEMacros.h"
#include "GameEntity.h"

NS_CC_GE_BEGIN

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
    
protected:
    
    CCArray* createEightAnimations(const yhge::Json::Value& configData);
    
    CCArray* createTwoAnimations(const yhge::Json::Value& configData);
};

NS_CC_GE_END



#endif // CCGE_ENTITYCOMPONENT_ENTITYCOMPONENTFACTORY_H_
