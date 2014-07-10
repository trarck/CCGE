#ifndef CCGE_ENTITYCOMPONENT_GAMEENGINE_H_
#define CCGE_ENTITYCOMPONENT_GAMEENGINE_H_

#include "cocos2d.h"
#include <yhge/yhge.h>
#include "CCGEMacros.h"
#include "EntityFactory.h"
#include "Managers/BattleUpdateManager.h"
#include "Managers/BattleManager.h"

NS_CC_GE_BEGIN

class GameEngine:public yhge::Engine
{
public:
    
	GameEngine();
    
	~GameEngine();
    
    bool init();
    
    void setupManagers();
    
    CREATE_FUNC(GameEngine);

public:
    
	void setEntityFactory(EntityFactory* entityFactory)
	{
		CC_SAFE_RETAIN(entityFactory);
		CC_SAFE_RELEASE(m_entityFactory);
		m_entityFactory = entityFactory;
		m_entityFactory->setEngine(this);
	}

	EntityFactory* getEntityFactory()
	{
		return m_entityFactory;
	}
    
    inline void setBattleUpdateManager(BattleUpdateManager* battleUpdateManager)
    {
        CC_SAFE_RETAIN(battleUpdateManager);
        CC_SAFE_RELEASE(m_battleUpdateManager);
        m_battleUpdateManager = battleUpdateManager;
    }
    
    inline BattleUpdateManager* getBattleUpdateManager()
    {
        return m_battleUpdateManager;
    }
    
    inline void setBattleManager(BattleManager* battleManager)
    {
        CC_SAFE_RETAIN(battleManager);
        CC_SAFE_RELEASE(m_battleManager);
        m_battleManager = battleManager;
    }
    
    inline BattleManager* getBattleManager()
    {
        return m_battleManager;
    }
    
protected:

	EntityFactory* m_entityFactory;
    
    BattleUpdateManager* m_battleUpdateManager;
    
    //战斗管理
    BattleManager* m_battleManager;
 
};

NS_CC_GE_END



#endif // CCGE_ENTITYCOMPONENT_GAMEENGINE_H_
