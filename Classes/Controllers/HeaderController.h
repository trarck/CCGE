#ifndef CCGE_CONTROLLERS_HEADERCONTROLLER_H_
#define CCGE_CONTROLLERS_HEADERCONTROLLER_H_

#include "yhmvc/Core/LayerController.h"
#include "yhmvc/Core/Layer.h"
#include "CCGEMacros.h"

NS_CC_GE_BEGIN
class HeaderController:public yhmvc::LayerController
{
public:
	
    HeaderController(void);
    
	~HeaderController(void);

	void layerDidLoad();

	void showUserInfoCallback(CCObject* pSender);

	void setTitle(const std::string& title);

private:
	CCLabelTTF* m_title;
};
NS_CC_GE_END

#endif //CCGE_CONTROLLERS_HEADERCONTROLLER_H_
