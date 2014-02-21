#ifndef CCGE_CONTROLLERS_MAINCONTROLLER_H_
#define CCGE_CONTROLLERS_MAINCONTROLLER_H_

#include "yhmvc/Core/Controller.h"
#include "yhmvc/Core/View.h"
#include "CCGEMacros.h"

NS_CC_GE_BEGIN

class MainController:public yhmvc::Controller
{
public:
	MainController(void);
	~MainController(void);

	void viewDidLoad();

	void menuCloseCallback(CCObject* pSender);
    
    void menuRunCallback(CCObject* pSender);
    void menuStopCallback(CCObject* pSender);
    void menuMoveToCallback(CCObject* pSender);

protected:

	void createTestMenuItem(const std::string& name,const std::string& gotoSceneName,CCObject* param=NULL);

private:

	CCArray* m_menuItems;
	CCArray* m_proxys;
};

NS_CC_GE_END

#endif //CCGE_CONTROLLERS_MAINCONTROLLER_H_
