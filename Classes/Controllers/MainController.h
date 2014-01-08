#ifndef CCGE_CONTROLLERS_MAINCONTROLLER_H_
#define CCGE_CONTROLLERS_MAINCONTROLLER_H_

#include "yhmvc/Core/LayerController.h"
#include "yhmvc/Core/Layer.h"
#include "CCGEMacros.h"

NS_CC_GE_BEGIN

class MainController:public yhmvc::LayerController
{
public:
	MainController(void);
	~MainController(void);

	void layerDidLoad();

	void menuCloseCallback(CCObject* pSender);
    
    void menuRunCallback(CCObject* pSender);
    void menuStopCallback(CCObject* pSender);
    void menuMoveToCallback(CCObject* pSender);

protected:

	void createTestMenuItem(const std::string& name,const std::string& gotoSceneName);

private:

	CCArray* m_menuItems;
	CCArray* m_proxys;
};

NS_CC_GE_END

#endif //CCGE_CONTROLLERS_MAINCONTROLLER_H_
