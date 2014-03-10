#include "HeaderController.h"
#include "yhmvc/Core/View.h"
#include "SceneDirector/GameSceneDirector.h"

USING_NS_CC;
USING_NS_CC_YHMVC;

NS_CC_GE_BEGIN

HeaderController::HeaderController(void)
{
	m_sName="HeaderController";
}


HeaderController::~HeaderController(void)
{
    CCLOG("HeaderController destroy");
}

void HeaderController::viewDidLoad()
{
    CCSize contentSize=getPreferredContentSize();

	m_title=CCLabelTTF::create("", "Arial", 20);
    
    m_title->setPosition(ccp(contentSize.width/2,contentSize.height/2));

    m_view->addChild(m_title);
   
}

void HeaderController::setTitle(const std::string& title)
{
	m_title->setString(title.c_str());
}

void HeaderController::showUserInfoCallback(CCObject* pSender)
{
    
//    GameSceneDirector::getInstance()->popScene();
}

NS_CC_GE_END