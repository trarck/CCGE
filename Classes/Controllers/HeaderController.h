#ifndef CCGE_CONTROLLERS_HEADERCONTROLLER_H_
#define CCGE_CONTROLLERS_HEADERCONTROLLER_H_

#include "BaseController.h"

NS_CC_GE_BEGIN
class HeaderController:public BaseController
{
public:
	
    HeaderController(void);
    
	~HeaderController(void);

	void viewDidLoad();

	void showUserInfoCallback(CCObject* pSender);

	void setTitle(const std::string& title);
    
    CREATE_FUNC(HeaderController);

private:
	CCLabelTTF* m_title;
};
NS_CC_GE_END

#endif //CCGE_CONTROLLERS_HEADERCONTROLLER_H_
