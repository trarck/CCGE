#include "HeaderController.h"
#include "yhmvc/Core/Layer.h"
#include "Scenes/GameSceneDirector.h"

USING_NS_CC;
USING_NS_CC_YHMVC;

NS_CC_GE_BEGIN

HeaderController::HeaderController(void)
{
	m_sName="HeaderController";
}


HeaderController::~HeaderController(void)
{
    
}

void HeaderController::layerDidLoad()
{
    CCSize contentSize=getPreferredContentSize();

	m_title=CCLabelTTF::create("", "Arial", 20);
    
    m_title->setPosition(ccp(contentSize.width/2,contentSize.height/2));

    m_layer->addChild(m_title);
   
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