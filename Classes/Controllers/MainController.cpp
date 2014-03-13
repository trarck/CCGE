#include "MainController.h"
#include <yhmvc/Core/View.h>
#include <yhge/isometric.h>
#include "Game.h"
#include "SceneDirector/GameSceneDirector.h"
#include "Tests/MenuItemUtil.h"

USING_NS_CC;
USING_NS_CC_YHGE;
USING_NS_CC_YHGE_ISOMETRIC;
USING_NS_CC_YHMVC;

NS_CC_GE_BEGIN

class MyGotoSceneProxy:public GotoSceneProxy
{
    void menuItemCallback(CCObject* pSender)
    {
        GameSceneDirector::getInstance()->setSceneContext(this->getParam());
        GotoSceneProxy::menuItemCallback(pSender);
    }
};


MainController::MainController(void)
	:m_menuItems(NULL)
	,m_proxys(NULL)
{

}


MainController::~MainController(void)
{
    CCLOG("MainController destroy");
	CC_SAFE_RELEASE_NULL(m_menuItems);
	CC_SAFE_RELEASE_NULL(m_proxys);
}

void MainController::viewDidLoad()
{
	m_menuItems=new CCArray();
	m_menuItems->init();

	m_proxys=new CCArray();
	m_proxys->init();

    createTestMenuItem("battle",kBattleScene,NULL);
    createTestMenuItem("mission",kMissionScene,CCInteger::create(ISOTileMapBuilder::BatchLayerType));
	createTestMenuItem("test iso normal",kTestISOScene,CCInteger::create(ISOTileMapBuilder::NormalLayerType));
    createTestMenuItem("test iso dynamic",kTestISOScene,CCInteger::create(ISOTileMapBuilder::DynamicLayerType));
    createTestMenuItem("test iso batch",kTestISOScene,CCInteger::create(ISOTileMapBuilder::BatchLayerType));
    createTestMenuItem("test iso batch dynamic",kTestISOScene,CCInteger::create(ISOTileMapBuilder::BatchDynamicLayerType));
    createTestMenuItem("test sqlite",kTestSqlite,NULL);

	CCSize screenSize=CCDirector::sharedDirector()->getWinSize();

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::createWithArray(m_menuItems);
	pMenu->setPosition( ccp(screenSize.width/2,0) );
	pMenu->alignItemsVertically();
    m_view->addChild(pMenu, 1);
    
}

void MainController::createTestMenuItem(const std::string& name,const std::string& gotoSceneName,CCObject* param)
{

    MyGotoSceneProxy* proxy=new MyGotoSceneProxy();
	proxy->init(gotoSceneName,param);
    
	CCMenuItemLabel *pItem=CCMenuItemLabel::create(CCLabelTTF::create(name.c_str(), "Arial", 30),
                                                   proxy,
                                                   menu_selector(GotoSceneProxy::menuItemCallback));
	pItem->setUserObject(proxy);
    
	proxy->release();
    
//	return pItem;
    
//	CCMenuItemLabel *pItem=MenuItemUtil::createTestMenuItemLabel(name,gotoSceneName,param);
	m_menuItems->addObject(pItem);
}

void MainController::menuCloseCallback(CCObject* pSender)
{
    m_view->removeAllChildrenWithCleanup(true);
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void MainController::menuRunCallback(CCObject* pSender)
{
    //GameSceneDirector::getInstance()->pushScene(kShopScene);
}

void MainController::menuStopCallback(CCObject* pSender)
{
    //GameSceneDirector::getInstance()->pushScene(kOneScene);
}

void MainController::menuMoveToCallback(CCObject* pSender)
{
    
}

NS_CC_GE_END