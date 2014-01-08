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

//======================�������� ͬҪ����message=====================//
/**
* ��ʼ����һ��Scene,ʹ��ע�������
*/
void GameSceneDirector::runWithScene(const std::string& name)
{
	SceneDirector::runWithScene(name);
	MessageManager* mm=MessageManager::defaultManager();
	mm->dispatchMessage(kChangeScene,this,mm->getGlobalObject(),m_runningScene);
}
    
/**
* ����һ��Scene��
* ���Scene,ʹ��name����һ���µ�Scene������ʾ�����Ϸ�
*/
void GameSceneDirector::pushScene(const std::string& name)
{
	SceneDirector::pushScene(name);
	MessageManager* mm=MessageManager::defaultManager();
	mm->dispatchMessage(kChangeScene,this,mm->getGlobalObject(),m_runningScene);
}
    
/**
* �滻һ��Scene��
* ���Scene,ʹ��name����һ���µ�Scene�����滻��ǰ���е�Scene
*/
void GameSceneDirector::replaceScene(const std::string& name)
{
	SceneDirector::replaceScene(name);
	MessageManager* mm=MessageManager::defaultManager();
	mm->dispatchMessage(kChangeScene,this,mm->getGlobalObject(),m_runningScene);
}
    
/**
* �˳���ǰSceneջ�ϵ��������Scene,�����������ʾ����
*/
void GameSceneDirector::popScene()
{
	SceneDirector::popScene();
	MessageManager* mm=MessageManager::defaultManager();
	mm->dispatchMessage(kChangeScene,this,mm->getGlobalObject(),m_runningScene);
}
    
   
/**
* ����ջԪ�أ�ֱ��ջ����level��Ԫ��,����ջ����Scene��ʾ����
*/
void GameSceneDirector::popToSceneStackLevel(int level)
{
	SceneDirector::popToSceneStackLevel(level);
	MessageManager* mm=MessageManager::defaultManager();
	mm->dispatchMessage(kChangeScene,this,mm->getGlobalObject(),m_runningScene);
}

NS_CC_GE_END