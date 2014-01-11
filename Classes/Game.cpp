//
//  Game.cpp
//  CCMVC
//
//  Created by duanhouhai on 13-11-1.
//
//

#include "Game.h"

#include "Scenes/GameSceneDirector.h"

#include "Scenes/SceneDefine.h"
#include "Scenes/SceneRegisterData.h"

USING_NS_CC;
USING_NS_CC_YHMVC;

NS_CC_GE_BEGIN

static Game* s_gameInstance=NULL;
Game* Game::getInstance()
{
    if (!s_gameInstance) {
        s_gameInstance=new Game();
    }
    return s_gameInstance;
}

Game::Game()
:m_sceneContext(NULL)
{

}

Game::~Game()
{
	CC_SAFE_RELEASE_NULL(m_sceneContext);
}

void Game::setupSceneDirector()
{
    GameSceneDirector* sceneDirector=GameSceneDirector::getInstance();
    
    int registerDataSize=sizeof(kSceneRegisterData)/sizeof(SceneRegisterItem);
    
    CCLOG("scene register data size=%d",registerDataSize);
    
    for (int i=0; i<registerDataSize; ++i) {
        sceneDirector->registerSceneCreate(kSceneRegisterData[i].name,kSceneRegisterData[i].createFun);
    }
}


NS_CC_GE_END
