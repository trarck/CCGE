//
//  GameSceneDirector.cpp
//  CCMVC
//
//  Created by duanhouhai on 13-11-1.
//
//

#include "GameSceneDirector.h"
#include <yhge/yhge.h>
#include "Messages.h"


USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

static GameSceneDirector* s_gameSceneDirectorInstance=NULL;

GameSceneDirector* GameSceneDirector::getInstance()
{
    if (!s_gameSceneDirectorInstance) {
        s_gameSceneDirectorInstance=new GameSceneDirector();
        s_gameSceneDirectorInstance->init();
    }
    
    return s_gameSceneDirectorInstance;
}

//======================场景操作 同要加上message=====================//
/**
* 开始运行一个Scene,使用注册的名子
*/
void GameSceneDirector::runWithScene(const std::string& name)
{
	SceneDirector::runWithScene(name);
	MessageManager* mm=MessageManager::defaultManager();
	mm->dispatchMessage(kChangeScene,this,mm->getGlobalObject(),m_runningScene);
}
    
/**
* 叠加一个Scene。
* 这个Scene,使用name创建一个新的Scene，并显示在最上方
*/
void GameSceneDirector::pushScene(const std::string& name)
{
	SceneDirector::pushScene(name);
	MessageManager* mm=MessageManager::defaultManager();
	mm->dispatchMessage(kChangeScene,this,mm->getGlobalObject(),m_runningScene);
}
    
/**
* 替换一个Scene。
* 这个Scene,使用name创建一个新的Scene，并替换当前运行的Scene
*/
void GameSceneDirector::replaceScene(const std::string& name)
{
	SceneDirector::replaceScene(name);
	MessageManager* mm=MessageManager::defaultManager();
	mm->dispatchMessage(kChangeScene,this,mm->getGlobalObject(),m_runningScene);
}
    
/**
* 退出当前Scene栈上的最上面的Scene,并把下面的显示出来
*/
void GameSceneDirector::popScene()
{
	SceneDirector::popScene();
	MessageManager* mm=MessageManager::defaultManager();
	mm->dispatchMessage(kChangeScene,this,mm->getGlobalObject(),m_runningScene);
}
    
   
/**
* 弹出栈元素，直到栈还有level个元素,并把栈顶的Scene显示出来
*/
void GameSceneDirector::popToSceneStackLevel(int level)
{
	SceneDirector::popToSceneStackLevel(level);
	MessageManager* mm=MessageManager::defaultManager();
	mm->dispatchMessage(kChangeScene,this,mm->getGlobalObject(),m_runningScene);
}

NS_CC_GE_END