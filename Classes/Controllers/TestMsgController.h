#ifndef CCGE_CONTROLLERS_TESTMSGCONTROLLER_H_
#define CCGE_CONTROLLERS_TESTMSGCONTROLLER_H_

#include <yhge/yhge.h>
#include <yhmvc/yhmvc.h>
#include "CCGEMacros.h"
#include "BaseController.h"

NS_CC_GE_BEGIN

/**
 */
class TestMsgController:public BaseController
{
public:
	
    TestMsgController(void);
    
	~TestMsgController(void);

	void viewDidLoad();
    
    void onMsg1(yhge::Message* message);
    void onMsg2(yhge::Message* message);
    void onMsg3(yhge::Message* message);
    void onMsg4(yhge::Message* message);
    
    void onMsg11(yhge::Message* message);
    void onMsg12(yhge::Message* message);
    void onMsg21(yhge::Message* message);
    void onMsg22(yhge::Message* message);
    
    void onMsg31(yhge::Message* message);
    void onMsg32(yhge::Message* message);
    void onMsg33(yhge::Message* message);
    void onMsg34(yhge::Message* message);
    
private:
    
    yhge::MessageManager* m_mm;
    CCObject* m_sender;
    
    CCObject* m_receiver1;
    CCObject* m_receiver2;
    CCObject* m_receiver3;
    

};
NS_CC_GE_END

#endif //CCGE_CONTROLLERS_TESTMSGCONTROLLER_H_
