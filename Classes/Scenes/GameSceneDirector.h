//
//  GameSceneDirector.h
//  CCMVC
//
//  Created by duanhouhai on 13-11-1.
//
//

#ifndef CCGE_GAMESCENEDIRECTOR_H_
#define CCGE_GAMESCENEDIRECTOR_H_

#include <yhmvc/yhmvc.h>
#include "CCGEMacros.h"
#include "SceneDefine.h"

NS_CC_GE_BEGIN

class GameSceneDirector:public yhmvc::SceneDirector
{
public:
    
    GameSceneDirector();
    ~GameSceneDirector();
    
    static GameSceneDirector* getInstance();

	//======================场景操作 同时加上message=====================//
	/**
     * 开始运行一个Scene,使用注册的名子
     */
    void runWithScene(const std::string& name);
    
    /**
     * 叠加一个Scene。
     * 这个Scene,使用name创建一个新的Scene，并显示在最上方
     */
    void pushScene(const std::string& name);
    
    /**
     * 替换一个Scene。
     * 这个Scene,使用name创建一个新的Scene，并替换当前运行的Scene
     */
    void replaceScene(const std::string& name);
    
    /**
     * 退出当前Scene栈上的最上面的Scene,并把下面的显示出来
     */
    void popScene();
    
    /**
     * 退出到栈底,并把栈底的Scene显示出来
     */
    void popToRootScene();
    
    /**
     * 弹出栈元素，直到栈还有level个元素,并把栈顶的Scene显示出来
     */
	void popToSceneStackLevel(int level);
    
public:
    
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
    
protected:
    /**
	 * 场景切换上下文变量
	 */
    CCObject* m_sceneContext;
};

NS_CC_GE_END

#endif /* defined(CCGE_GAMESCENEDIRECTOR_H_) */
