#ifndef CCMVC_CONSTROLLERS_BASECONTROLLER_H_
#define CCMVC_CONSTROLLERS_BASECONTROLLER_H_

#include <yhgui/yhgui.h>
#include <yhmvc/yhmvc.h>
#include "CCGEMacros.h"

NS_CC_GE_BEGIN

/**
 *
 */
class BaseController:public cocos2d::yhmvc::Controller
{
public:
	
    BaseController(void);
    
	~BaseController(void);

    /**
     * @brief 创建事件管理器
     */
    virtual yhgui::ElementEventParser* createEventParser();
    
    CREATE_FUNC(BaseController);
};

NS_CC_GE_END

#endif //CCMVC_CONSTROLLERS_BASECONTROLLER_H_
