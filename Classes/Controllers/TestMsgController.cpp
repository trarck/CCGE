#include "TestMsgController.h"
#include <yhge/yhge.h>
#include <yhgui/yhgui.h>

USING_NS_CC;
USING_NS_CC_YHGE;
USING_NS_CC_YHMVC;
USING_NS_CC_YHGUI;
USING_NS_CC_YHGE_SQLITE;

NS_CC_GE_BEGIN

static const float kGameTileWidth=100;
static const float kGameTileHeight=90;

static const int kMsgTest=10110;

TestMsgController::TestMsgController(void)
{
    m_sName="TestMsgController";
}

TestMsgController::~TestMsgController(void)
{
    CCLOG("TestMsgController destroy");
}

void TestMsgController::viewDidLoad()
{
    
    m_receiver1=new CCObject();
    m_receiver2=new CCObject();
    m_receiver3=new CCObject();
    
    CCLog("1:%d,2:%d,3:%d,this:%d",m_receiver1->m_uID,m_receiver2->m_uID,m_receiver3->m_uID,m_uID);
    
    MessageManager* mm=new MessageManager();
    mm->init();
    
    m_mm=mm;
    
    CCObject* sender=new CCObject();
    m_sender=sender;
    
    mm->registerReceiver(this, kMsgTest, sender, message_selector(TestMsgController::onMsg1),this);
    mm->registerReceiver(this, kMsgTest, sender, message_selector(TestMsgController::onMsg2),this);
    mm->registerReceiver(this, kMsgTest, sender, message_selector(TestMsgController::onMsg3),this);
    mm->registerReceiver(this, kMsgTest, sender, message_selector(TestMsgController::onMsg4),this);
    
    mm->registerReceiver(m_receiver1, kMsgTest, sender, message_selector(TestMsgController::onMsg11),this);
    mm->registerReceiver(m_receiver1, kMsgTest, sender, message_selector(TestMsgController::onMsg12),this);
    mm->registerReceiver(m_receiver2, kMsgTest, sender, message_selector(TestMsgController::onMsg21),this);
    mm->registerReceiver(m_receiver2, kMsgTest, sender, message_selector(TestMsgController::onMsg22),this);
    
    mm->registerReceiver(m_receiver3, kMsgTest, sender, message_selector(TestMsgController::onMsg31),this);
    mm->registerReceiver(m_receiver3, kMsgTest, sender, message_selector(TestMsgController::onMsg32),this);
    mm->registerReceiver(m_receiver3, kMsgTest, sender, message_selector(TestMsgController::onMsg33),this);
    mm->registerReceiver(m_receiver3, kMsgTest, sender, message_selector(TestMsgController::onMsg34),this);
    
    
    mm->dispatchMessage(kMsgTest, sender, NULL);
    mm->dispatchMessage(kMsgTest, sender, NULL);
    
    sender->release();
    mm->release();
    
    m_receiver1->release();
    m_receiver2->release();
    m_receiver3->release();
    
    
}

void TestMsgController::onMsg1(yhge::Message* message)
{
    CCLOG("msg1");
}

void TestMsgController::onMsg2(yhge::Message* message)
{
    CCLOG("msg2");
//    m_mm->removeReceiver(this, kMsgTest, m_sender, message_selector(TestMsgController::onMsg2));
//    m_mm->removeReceiver(this, kMsgTest, m_sender, message_selector(TestMsgController::onMsg3));
    m_mm->removeReceiver(m_receiver1);
    m_mm->removeReceiver(m_receiver2);
    m_mm->removeReceiver(m_receiver3);
    m_mm->removeReceiver(this);
}

void TestMsgController::onMsg3(yhge::Message* message)
{
    CCLOG("msg3");
}

void TestMsgController::onMsg4(yhge::Message* message)
{
    CCLOG("msg4");
}

void TestMsgController::onMsg11(yhge::Message* message)
{
    CCLOG("msg11");
}

void TestMsgController::onMsg12(yhge::Message* message)
{
    CCLOG("msg12");
}

void TestMsgController::onMsg21(yhge::Message* message)
{
    CCLOG("msg21");
}

void TestMsgController::onMsg22(yhge::Message* message)
{
    CCLOG("msg22");
}

void TestMsgController::onMsg31(yhge::Message* message)
{
    CCLOG("msg31");
}

void TestMsgController::onMsg32(yhge::Message* message)
{
    CCLOG("msg32");
}

void TestMsgController::onMsg33(yhge::Message* message)
{
    CCLOG("msg33");
}

void TestMsgController::onMsg34(yhge::Message* message)
{
    CCLOG("msg34");
}

NS_CC_GE_END