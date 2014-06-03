#include "TestAnimationController.h"
#include <yhge/yhge.h>
#include "Game.h"
#include "SceneDirector/GameSceneDirector.h"

USING_NS_CC;
USING_NS_CC_YHGE;
USING_NS_CC_YHMVC;

NS_CC_GE_BEGIN


TestAnimationController::TestAnimationController(void)
:m_animationManager(NULL)
{
    
}


TestAnimationController::~TestAnimationController(void)
{
    CCLOG("TestAnimationController destroy");
    CC_SAFE_RELEASE_NULL(m_animationManager);
}

void TestAnimationController::viewDidLoad()
{
    CCLabelTTF* label=CCLabelTTF::create("Hello", "Alats", 32);
    label->setPosition(ccp(100,100));
    
    m_view->addChild(label);
    
    m_animationManager=new AnimationManager();
    m_animationManager->init();
    
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("characters/Coco/plist");
    
    unsigned long  size=0;
    
    unsigned char* data=CCFileUtils::sharedFileUtils()->getFileData("characters/Coco/cha", "rb", &size);
    
    Buffer* buffer=new Buffer(data,size);
    
    InputStream* is=new InputStream();
    is->init(buffer);
    
    buffer->release();
    
    
    
    
    
    
    is->release();
    
//    CCSprite* sprite=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("22.png"));
//    sprite->setPosition(ccp(100,150));
//    m_view->addChild(sprite);
    
}

void TestAnimationController::onViewExit()
{
    Controller::onViewExit();
}

void TestAnimationController::update(float delta)
{
    m_animationManager->update(delta);
}
NS_CC_GE_END