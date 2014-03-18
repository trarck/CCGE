#ifndef CCGE_CONTROLLERS_MissionController_H_
#define CCGE_CONTROLLERS_MissionController_H_

#include <yhge/yhge.h>
#include <yhmvc/yhmvc.h>
#include <yhge/isometric.h>
#include "CCGEMacros.h"
#include "BaseController.h"
#include "StepGameWorldController.h"
#include "Layers/GameWorld.h"

NS_CC_GE_BEGIN

/**
 * 单独的。
 * 由Scene来组合controller。
 * 可以添加其它controller来作为显示内容
 * 由于结构简单不容易出错。
 */
class MissionController:public BaseController
{
public:
	
    MissionController(void);
    
	~MissionController(void);

	void viewDidLoad();
    
    void onViewExit();
    
    
    void doStepEvent();
    
    void onStepEvent(CCObject* sender);

private:
    
    StepGameWorldController* m_gameWorld;
    
    //key=y*mapWith+x,value事件数据;
    CCDictionary* m_stepEvents;
    
};
NS_CC_GE_END

#endif //CCGE_CONTROLLERS_MissionController_H_
