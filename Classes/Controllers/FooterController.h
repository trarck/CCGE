#ifndef CCGE_CONTROLLERS_FOOTERCONTROLLER_H_
#define CCGE_CONTROLLERS_FOOTERCONTROLLER_H_

#include "BaseController.h"

NS_CC_GE_BEGIN
class FooterController:public BaseController
{
public:
	
    FooterController(void);
    
	~FooterController(void);

	void viewDidLoad();

	void backCallback(CCObject* pSender);
    
    void exitCallback(CCObject* pSender);

	void showBackButton(){
		m_backButton->setVisible(true);
	}

	void hideBackButton(){
		m_backButton->setVisible(false);
	}

private:

	CCMenuItemLabel* m_backButton;

};
NS_CC_GE_END

#endif //CCGE_CONTROLLERS_FOOTERCONTROLLER_H_
