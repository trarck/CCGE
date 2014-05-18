//
//  Box.cpp
//
//

#include "MenuItemUtil.h"
#include "SceneDirector/GameSceneDirector.h"


NS_CC_GE_BEGIN

GotoSceneProxy::~GotoSceneProxy()
{
	CCLOG("GotoSceneProxy destroy");
}

void GotoSceneProxy::menuItemCallback(CCObject* pSender)
{
    std::vector<<#typename _Tp#>>
	GameSceneDirector::getInstance()->pushScene(m_gotoSceneName);
}

CCMenuItemLabel* MenuItemUtil::createTestMenuItemLabel(const std::string& name,const std::string& gotoSceneName,CCObject* param)
{
	GotoSceneProxy* proxy=new GotoSceneProxy();
	proxy->init(gotoSceneName,param);

	CCMenuItemLabel *pItem=CCMenuItemLabel::create(CCLabelTTF::create(name.c_str(), "Arial", 20),
                                                      proxy, 
                                                      menu_selector(GotoSceneProxy::menuItemCallback));
	pItem->setUserObject(proxy);

	proxy->release();

	return pItem;
}

NS_CC_GE_END