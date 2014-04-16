#include "InitializeController.h"
#include <yhmvc/Core/View.h>
#include <yhge/isometric.h>
#include "Game.h"
#include "SceneDirector/GameSceneDirector.h"
#include "Services/ServiceFactory.h"
#include "Tests/MenuItemUtil.h"

USING_NS_CC;
USING_NS_CC_YHGE;
USING_NS_CC_YHGE_ISOMETRIC;
USING_NS_CC_YHMVC;

NS_CC_GE_BEGIN


InitializeController::InitializeController(void)
{
    
}


InitializeController::~InitializeController(void)
{
    CCLOG("InitializeController destroy");
}

void InitializeController::viewDidLoad()
{
    initGameData();
    //goto main scene
    Game::getInstance()->getSceneDirector()->replaceScene(kMainScene);
}

void InitializeController::initGameData()
{
    ServiceFactory::getInstance()->getMissionService()->setCurrentZone(1);
    ServiceFactory::getInstance()->getMissionService()->setCurrentMap(1);
}

NS_CC_GE_END