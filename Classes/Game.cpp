//
//  Game.cpp
//  CCMVC
//
//  Created by duanhouhai on 13-11-1.
//
//

#include "Game.h"
#include <yhge/yhge.h>

#include "SceneDirector/SceneDefine.h"
#include "SceneDirector/SceneRegisterData.h"

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
,m_sceneDirector(NULL)
,m_random(NULL)
{

}

Game::~Game()
{
    CC_SAFE_RELEASE_NULL(m_interactiveOrganizer);
    CC_SAFE_RELEASE_NULL(m_sceneDirector);
    CC_SAFE_DELETE(m_random);
}

/**
 * 执行初始化的工作
 */
void Game::setup()
{
    ISOStaticCoordinate::initTileSize(kGameTileWidth, kGameTileHeight);
    
    
    float tileWidth=150;
    
    float sideHeight=tileWidth/6;
    
    float topHeight=tileWidth*0.4;
    
    dimetric::StaticSideViewCoordinateFormulae::initTileSize(tileWidth, sideHeight);
    
    dimetric::StaticTopViewCoordinateFormulae::initTileSize(tileWidth, topHeight);
    
    setupRandom();
 
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
    
    setSceneDirector(sceneDirector);
}

void setupEngine()
{
    
}

void Game::setupRandom()
{
    struct timeval now;
    
    gettimeofday(&now, NULL);
    
    m_random=new RandomMT(now.tv_sec*1000000+now.tv_usec);
}


NS_CC_GE_END
