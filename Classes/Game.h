#ifndef CCGE_GAME_H_
#define CCGE_GAME_H_

#include "cocos2d.h"
#include "CCGEMacros.h"
#include <yhge/yhge.h>
#include <yhgui/yhgui.h>

#include "EntityComponent/GameEngine.h"
#include "Datas/DataFactory.h"

#include "SceneDirector/GameSceneDirector.h"

NS_CC_GE_BEGIN

class Game:public CCObject
{
public:
    
	Game();
    
	~Game();
    
    static Game* getInstance();

    /**
     * 执行初始化的工作
     */
    void setup();
    
    /**
     * 初始化数据
     */
    void setupData();
    
    /**
     * 初始化gui
     */
    void setupGui();
    
    /**
	 * 设置场景管理
	 */
    void setupSceneDirector();
    
    /**
	 * 设置引擎
	 */
    void setupEngine();
    
protected:
    
    void setupRandom();
    
public:
    
    inline static yhge::MessageManager* getMessageManager()
    {
        return yhge::MessageManager::defaultManager();
    }
    
    inline void setInteractiveOrganizer(yhgui::DocumentTreeOrganizer* interactiveOrganizer)
    {
        CC_SAFE_RETAIN(interactiveOrganizer);
        CC_SAFE_RELEASE(m_interactiveOrganizer);
        m_interactiveOrganizer = interactiveOrganizer;
    }
    
    inline yhgui::DocumentTreeOrganizer* getInteractiveOrganizer()
    {
        return m_interactiveOrganizer;
    }
    
    inline void setSceneDirector(GameSceneDirector* sceneDirector)
    {
        CC_SAFE_RETAIN(sceneDirector);
        CC_SAFE_RELEASE(m_sceneDirector);
        m_sceneDirector = sceneDirector;
    }
    
    inline GameSceneDirector* getSceneDirector()
    {
        return m_sceneDirector;
    }
    
    inline yhge::RandomMT* getRandom()
    {
        return m_random;
    }
    
    inline void setEngine(GameEngine* engine)
    {
        CC_SAFE_RETAIN(engine);
        CC_SAFE_RELEASE(m_engine);
        m_engine = engine;
    }
    
    inline GameEngine* getEngine()
    {
        return m_engine;
    }
    
    inline void setDataFactory(DataFactory* dataFactory)
    {
        CC_SAFE_RETAIN(dataFactory);
        CC_SAFE_RELEASE(m_dataFactory);
        m_dataFactory = dataFactory;
    }
    
    inline DataFactory* getDataFactory()
    {
        return m_dataFactory;
    }
    
private:
    
    yhgui::DocumentTreeOrganizer* m_interactiveOrganizer;
    
    GameSceneDirector* m_sceneDirector;
    
    yhge::RandomMT* m_random;
    
    GameEngine*	m_engine;
    
    DataFactory* m_dataFactory;
};

NS_CC_GE_END



#endif //CCGE_GAME_H_
