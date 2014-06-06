#include "TestAnimationController.h"
#include <yhge/yhge.h>
#include "Game.h"
#include "SceneDirector/GameSceneDirector.h"
#include "Animations/FcaInfo.h"

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
    
    
    CCSize winSize=CCDirector::sharedDirector()->getWinSize();
    
    CCLayerColor* bg=CCLayerColor::create(ccc4(255, 255, 255, 255), winSize.width, winSize.height);
    
    m_view->addChild(bg);
    
    
    FcaInfo* fcaInfo=FcaInfo::create("characters/Coco");
    
    CCLOG("element size:%d,aciont count:%d",fcaInfo->getElements().size(),fcaInfo->getActions().size());
    CCLOG("first %s",fcaInfo->getActions().front().name.c_str());
    showAction(fcaInfo, "Idle");
    
    
    CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget(this, 0, false);
    
    
    createTestMenu();
    
}


void TestAnimationController::createTestMenu()
{
    CCSize screenSize=CCDirector::sharedDirector()->getWinSize();
    
    CCMenuItem* button=CCMenuItemLabel::create(CCLabelTTF::create("next", "Arial", 30),
                                         this,
                                         menu_selector(TestAnimationController::onNext));
    button->setPosition(ccp(60,20));
    button->setColor(ccc3(0, 0, 0));
    
    
    CCMenu* menu=CCMenu::create(button,NULL);
    
    menu->setPosition( CCPointZero );
    
    m_view->addChild(menu);
}

void TestAnimationController::onViewExit()
{
    Controller::onViewExit();
}

void TestAnimationController::update(float delta)
{
    m_animationManager->update(delta);
}

void TestAnimationController::showAction(FcaInfo* fcaInfo,const std::string& actionName)
{
    FcaAction action;
    
    for (std::vector<FcaAction>::iterator iter=fcaInfo->getActions().begin(); iter!=fcaInfo->getActions().end(); ++iter) {
        CCLOG("%s,%s,%f,%ld",iter->name.c_str(),actionName.c_str(),iter->fps,iter->frames.size());
        if ((*iter).name==actionName) {
            
            action=*iter;
            break;
        }
    }
    
    //get characters
    CCArray* characters=CCArray::createWithCapacity(fcaInfo->getElements().size());
    
    for (std::vector<FcaElement>::iterator iter=fcaInfo->getElements().begin(); iter!=fcaInfo->getElements().end(); ++iter) {
        
        Resource* res=new Resource();
        
        res->setId(iter->index);
        res->setSpriteFrame(fcaInfo->getSpriteFrame(iter->textureKey));
        res->setType(Resource::kPackTexture);
        
        Character* character=new Character();
        character->setId(iter->index);
        
        character->setResource(res);
        character->setAnchor(ccp(0.0,0.0));
        
        characters->addObject(character);
        
        res->release();
        character->release();
    }
    
    if (action.fps && action.frames.size()>0) {
        yhge::Animation* animation=new Animation();
        animation->init(1/action.fps);
        animation->setHaveTransform(true);
        animation->setHaveOpacity(true);
        
        m_animationManager->add(animation);
        
        int zOrder=0;
        
        CCLOG("action.frames:%ld",action.frames.size());
        
        float r=0.11;
        
        float rr=1/r;
        
        for (std::vector<FcaFrame>::iterator iter=action.frames.begin(); iter!=action.frames.end(); ++iter) {
            
            AvatarFrame* avatarFrame=new AvatarFrame();
            avatarFrame->init();
            
            zOrder=0;
            
            for (std::vector<FcaFrameElement>::iterator eleIter=(*iter).elements.begin(); eleIter!=(*iter).elements.end(); ++eleIter) {
                
                FcaElement fcaElement=fcaInfo->getElements().at((*eleIter).index-1);
                
                
                yhge::FrameElement* frameElement=new yhge::FrameElement();
                
                DisplayProperty* displayProperty=new DisplayProperty();
                displayProperty->init();
                displayProperty->setOpacity((*eleIter).alpha);
                
                float height=fcaElement.size.height;
                float width=fcaElement.size.width;
                
                CCAffineTransform transform;
                
                
                transform.a=eleIter->matrix.a;
                transform.b=-eleIter->matrix.b;
                transform.c=-eleIter->matrix.c;
                transform.d=eleIter->matrix.d;
                
//                r=0.11;
                
                float tx= -0.5*eleIter->matrix.a * width    +   0.5*eleIter->matrix.c*height  + eleIter->matrix.tx * r;
                float ty= 0.5*eleIter->matrix.b * width    -   0.5*eleIter->matrix.d*height   - eleIter->matrix.ty * r;


//                transform.a=eleIter->matrix.a*rr;
//                transform.b=-eleIter->matrix.b*rr;
//                transform.c=-eleIter->matrix.c*rr;
//                transform.d=eleIter->matrix.d*rr;
//                
//                float tx= -0.5*eleIter->matrix.a * width *rr    +   0.5*eleIter->matrix.c*height *rr + eleIter->matrix.tx;
//                float ty= 0.5*eleIter->matrix.b * width *rr   -   0.5*eleIter->matrix.d*height *rr  - eleIter->matrix.ty ;

                
//                float tx=eleIter->matrix.c*height+eleIter->matrix.tx;
//                float ty=-eleIter->matrix.d*height-eleIter->matrix.ty;
                
                transform.tx=tx;
                transform.ty=ty;
                
//                transform=eleIter->matrix;
                
//                transform.a=eleIter->matrix.a;
//                transform.b=-eleIter->matrix.b;
//                transform.c=-eleIter->matrix.c;
//                transform.d=eleIter->matrix.d;
//                transform.tx=eleIter->matrix.tx;
//                transform.ty=-eleIter->matrix.ty;
                
                
                
                
                displayProperty->setTransform(transform);
                
                CCLOG("%d:%s:z=%d",eleIter->index,fcaElement.name.c_str(),zOrder);
                
                displayProperty->setZOrder(zOrder++);
                
                frameElement->setDisplayProperty(displayProperty);
                displayProperty->release();
                
                frameElement->setCharacterId(fcaElement.index);
                
//                frameElement->setZOrder(zOrder++);
                
                avatarFrame->addElement(frameElement);
                
                frameElement->release();
            }
            
            animation->appendFrame(avatarFrame);
            
            avatarFrame->release();
            
        }
        
        //texture scheet
        CCSpriteFrame* firstSpriteFrame= fcaInfo->getSpriteFrame(fcaInfo->getElements().front().textureKey);
        
        AvatarSprite* avatarSprite=new AvatarSprite();
        avatarSprite->initWithTexture(firstSpriteFrame->getTexture(), action.frames.front().elements.size());
        avatarSprite->setupComponets(characters);
        
//        int index=5;
//        animation->setCurrentFrameIndex(index);
//        animation->setElapsed(index/24.0f);
        
        avatarSprite->setAnimation(animation);
        
//        avatarSprite->setScale(r);
        
        animation->release();
        
        avatarSprite->setPosition(ccp(400,200));
        m_view->addChild(avatarSprite);
        
    }
}

void TestAnimationController::onNext(cocos2d::CCObject *target)
{
    m_animationManager->update(1.0f/24);
}

NS_CC_GE_END