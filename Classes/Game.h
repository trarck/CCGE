//
//  Game.h
//  CCMVC
//
//  Created by duanhouhai on 13-11-1.
//
//

#ifndef __CCMVC__Game__
#define __CCMVC__Game__

#include "cocos2d.h"
#include "CCGEMacros.h"

NS_CC_GE_BEGIN

class Game:public CCObject
{
public:
    
	Game();
	~Game();
    
    static Game* getInstance();

    /**
	 * 设置场景管理
	 */
    void setupSceneDirector();
    
    
    inline void setSceneContext(CCObject* sceneContext)
    {
        CC_SAFE_RETAIN(sceneContext);
        CC_SAFE_RELEASE(m_sceneContext);
        m_sceneContext = sceneContext;
    }
    
    inline CCObject* getSceneContext()
    {
        return m_sceneContext;
    }
    
private:
    /**
	 * 场景切换上下文变量
	 */
    CCObject* m_sceneContext;
};

NS_CC_GE_END



#endif /* defined(__CCMVC__Game__) */
