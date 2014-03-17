
#ifndef CCGE_ENTITYCOMPONENT_ENTITYFACTORY_H_
#define CCGE_ENTITYCOMPONENT_ENTITYFACTORY_H_

#include "cocos2d.h"
#include "CCGEMacros.h"
#include "GameEntity.h"
#include "EntityPropertyFactory.h"

NS_CC_GE_BEGIN

class EntityFactory:public CCObject
{
public:
    
	EntityFactory();
    
	~EntityFactory();
    
    virtual bool init();
    
    static EntityFactory* getInstance();
    
    /**
     * 创建一个空的游戏实体
     */
    GameEntity* createEntity(int entityId);
    
    /**
     * 从配置文件中创建游戏实体
     */
    GameEntity* createEntityWithParams(int entityId,CCDictionary* params);
    
    /**
     * 根据id创建游戏实体
     */
    GameEntity* createEntityById(int entityId);
    
    /**
     * 创建一个人物
     */
    GameEntity* createPlayer(int entityId,CCDictionary* param=NULL);
    
    /**
     * 创建战斗中的人物
     */
    GameEntity* createBattlePlayer(int entityId,CCDictionary* param=NULL);
    
    /**
     * @brief 给entity添加地图相关组件
     */
    void addMapComponents(GameEntity* entity);
    
    /**
     * @brief 给entity添加战斗相关组件
     */
    void addBattleComponents(GameEntity* entity);
    
public:
    
    inline void setEntityPropertyFactory(EntityPropertyFactory* entityPropertyFactory)
    {
        CC_SAFE_RETAIN(entityPropertyFactory);
        CC_SAFE_RELEASE(m_entityPropertyFactory);
        m_entityPropertyFactory = entityPropertyFactory;
    }
    
    inline EntityPropertyFactory* getEntityPropertyFactory()
    {
        return m_entityPropertyFactory;
    }

protected:

    CCArray* createEightAnimations(const yhge::Json::Value& configData);
    
    CCArray* createTwoAnimations(const yhge::Json::Value& configData);

protected:
    
    EntityPropertyFactory* m_entityPropertyFactory;
};

NS_CC_GE_END



#endif // CCGE_ENTITYCOMPONENT_ENTITYFACTORY_H_
