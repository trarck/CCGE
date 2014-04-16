#ifndef CCGE_GAME_H_
#define CCGE_GAME_H_

#include "cocos2d.h"
#include "CCGEMacros.h"
#include <yhge/yhge.h>
#include <yhgui/yhgui.h>

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
     * 初始化gui
     */
    void setupGui();
    
    /**
	 * 设置场景管理
	 */
    void setupSceneDirector();
    
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
    
private:
    
    yhgui::DocumentTreeOrganizer* m_interactiveOrganizer;
    
    GameSceneDirector* m_sceneDirector;
    
    yhge::RandomMT* m_random;
};

NS_CC_GE_END



#endif //CCGE_GAME_H_
