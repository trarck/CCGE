//
//  Game.cpp
//  CCMVC
//
//  Created by duanhouhai on 13-11-1.
//
//

#include "Game.h"
#include <yhge/yhge.h>

#include "Scenes/GameSceneDirector.h"

#include "Scenes/SceneDefine.h"
#include "Scenes/SceneRegisterData.h"

USING_NS_CC;
USING_NS_CC_YHMVC;
USING_NS_CC_YHGE;
USING_NS_CC_YHGE_ISOMETRIC;
USING_NS_CC_YHGUI;

NS_CC_GE_BEGIN

static const float kGameTileWidth=120;
static const float kGameTileHeight=60;

static Game* s_gameInstance=NULL;
Game* Game::getInstance()
{
    if (!s_gameInstance) {
        s_gameInstance=new Game();
    }
    return s_gameInstance;
}

Game::Game()
:m_interactiveOrganizer(NULL)
{

}

Game::~Game()
{
    CC_SAFE_RELEASE_NULL(m_interactiveOrganizer);
}

/**
 * 执行初始化的工作
 */
void Game::setup()
{
    ISOStaticCoordinate::initTileSize(kGameTileWidth, kGameTileHeight);
    setupGui();
    setupSceneDirector();
}

void Game::setupGui()
{
    m_interactiveOrganizer=new DocumentTreeOrganizer();
    m_interactiveOrganizer->init();
    m_interactiveOrganizer->registerWithTouchDispatcher();
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
