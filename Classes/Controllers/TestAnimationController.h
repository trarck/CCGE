#ifndef CCGE_CONTROLLERS_TestAnimationController_H_
#define CCGE_CONTROLLERS_TestAnimationController_H_

#include <yhge/yhge.h>
#include <yhmvc/yhmvc.h>
#include <yhge/isometric.h>
#include "CCGEMacros.h"
#include "BaseController.h"
#include "Animations/FcaInfo.h"

NS_CC_GE_BEGIN

/**
 *
 */
class TestAnimationController:public BaseController,public CCTouchDelegate
{
public:
	
    TestAnimationController(void);
    
	~TestAnimationController(void);

	void viewDidLoad();
    
    void onViewExit();
    
    CREATE_FUNC(TestAnimationController);
    
    void update(float delta);
    
    void showAction(FcaInfo* fcaInfo,const std::string& actionName);
    
    
    void createTestMenu();
    
    void onNext(CCObject* target);
    
private:
    
    yhge::AnimationManager* m_animationManager;

};
NS_CC_GE_END

#endif //CCGE_CONTROLLERS_TestAnimationController_H_
