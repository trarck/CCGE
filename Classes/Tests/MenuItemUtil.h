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
	GotoSceneProxy()
    :m_gotoSceneName("")
    ,m_param(NULL)
	{
        
	}

	~GotoSceneProxy();

	bool init(const std::string& gotoSceneName)
	{
		m_gotoSceneName=gotoSceneName;
		return true;
	}
    
    bool init(const std::string& gotoSceneName,CCObject* param)
	{
		m_gotoSceneName=gotoSceneName;
        setParam(param);
		return true;
	}
    
    inline void setParam(CCObject* param)
    {
        CC_SAFE_RETAIN(param);
        CC_SAFE_RELEASE(m_param);
        m_param = param;
    }
    
    inline CCObject* getParam()
    {
        return m_param;
    }

	virtual void menuItemCallback(CCObject* pSender);

private:

	std::string m_gotoSceneName;
    
    CCObject* m_param;

};

class MenuItemUtil:public CCObject
{
public:
	static CCMenuItemLabel* createTestMenuItemLabel(const std::string& name,const std::string& gotoSceneName,CCObject* param=NULL);

};

NS_CC_GE_END

#endif /* defined(CCGE_TESTS_MENUITEMUTIL_H_) */
