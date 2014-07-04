#ifndef CCGE_ENTITYCOMPONENT_GAMEENGINE_H_
#define CCGE_ENTITYCOMPONENT_GAMEENGINE_H_

#include "cocos2d.h"
#include <yhge/yhge.h>
#include "CCGEMacros.h"
#include "EntityFactory.h"

NS_CC_GE_BEGIN

class GameEngine:public yhge::Engine
{
public:
    
	GameEngine();
    
	~GameEngine();
    
    bool init();
    
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
    
private:

	EntityFactory* m_entityFactory;
 
};

NS_CC_GE_END



#endif // CCGE_ENTITYCOMPONENT_GAMEENGINE_H_
