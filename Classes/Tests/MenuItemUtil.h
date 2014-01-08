//
//  Box.h
//
//

#ifndef CCGE_TESTS_MENUITEMUTIL_H_
#define CCGE_TESTS_MENUITEMUTIL_H_

#include "cocos2d.h"

#include "CCGEMacros.h"

NS_CC_GE_BEGIN

class GotoSceneProxy:public CCObject
{
public:
	GotoSceneProxy():m_gotoSceneName("")
	{

	}

	~GotoSceneProxy();

	bool init(const std::string& gotoSceneName)
	{
		m_gotoSceneName=gotoSceneName;
		return true;
	}

	void menuItemCallback(CCObject* pSender);

private:

	std::string m_gotoSceneName;

};

class MenuItemUtil:public CCObject
{
public:
	static CCMenuItemLabel* createTestMenuItemLabel(const std::string& name,const std::string& gotoSceneName);

};

NS_CC_GE_END

#endif /* defined(CCGE_TESTS_MENUITEMUTIL_H_) */
