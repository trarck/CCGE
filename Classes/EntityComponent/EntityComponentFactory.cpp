#include "EntityComponentFactory.h"
#include <yhge/yhge.h>
#include "Game.h"
#include "Consts/PropertyDefine.h"
#include "Consts/DataDefine.h"
#include "Consts/GameDefine.h"
#include "Consts/AnimationDefine.h"

#include "Properties/UnitProperty.h"
#include "Properties/BattleProperty.h"

#include "Components/GameAttackComponent.h"
#include "Components/DieComponent.h"
#include "Components/HealthBarComponent.h"
#include "Components/HurtComponent.h"
#include "Components/BattlePositionComponent.h"
#include "Components/BattleStateMachineComponent.h"

#include "Components/Battles/AIComponent.h"
#include "Components/Battles/MoveComponent.h"
#include "Components/Battles/SkillComponent.h"
#include "Components/Battles/VisibleMoveComponent.h"


#include "EntityFactory.h"

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

EntityComponentFactory::EntityComponentFactory()
:m_entityFactory(NULL)
{

}

EntityComponentFactory::~EntityComponentFactory()
{

}

static EntityComponentFactory* s_instance=NULL;

EntityComponentFactory* EntityComponentFactory::getInstance()
{
    if (!s_instance) {
        s_instance=new EntityComponentFactory();
        s_instance->init();
    }
    return s_instance;
}

bool EntityComponentFactory::init()
{
    return true;
}

void EntityComponentFactory::addBattleRendererComponent(GameEntity* entity)
{
    UnitProperty* unitProperty=static_cast<UnitProperty*>(entity->getProperty(CCGE_PROPERTY_UNIT));
    
    SpriteRendererComponent* rendererComponent=new SpriteRendererComponent();
    rendererComponent->init();
    
    CCNode* renderer=rendererComponent->getRenderer();
    renderer->setScale(unitProperty->getSizeMod());
//    renderer->setZOrder(battleProperty->getCol());
    
    //目前的人物是朝向右，对手要做镜像
    rendererComponent->getSpriteRenderer()->setFlipX(unitProperty->getCamp()==kCampEnemy);
    
    entity->addComponent(rendererComponent);
    rendererComponent->release();
    entity->setRendererComponent(rendererComponent);

}

void EntityComponentFactory::addBattleAnimationComponent(GameEntity* entity)
{
    UnitProperty* unitProperty=static_cast<UnitProperty*>(entity->getProperty(CCGE_PROPERTY_UNIT));
    
    EightDirectionAnimationComponent* animation=new EightDirectionAnimationComponent();
    animation->init();
    
    //从配置文件中取得动画数据
    AnimationDAO* animationDAO=Game::getInstance()->getDataFactory()->getAnimationDAO();
    yhge::Json::Value battleAnimationData=animationDAO->getEntityAnimateData(unitProperty->getPuppetIdFromInfo(),CCGE_ANIMATION_TYPE_BATTLE);

    CCAssert(!battleAnimationData.isNull(), "no animation data");
    
    //把数据加入到动画组件里
    yhge::Json::Value::Members members=battleAnimationData.getMemberNames();
    CCArray* twoAnimations=NULL;
    for (yhge::Json::Value::Members::iterator iter=members.begin(); iter!=members.end(); ++iter) {
        twoAnimations=createTwoAnimations(battleAnimationData[*iter]);
        animation->addAnimationList(twoAnimations,*iter);
    }
    
    entity->addComponent(animation);
    animation->release();
    
    //设置默认动画
    CCDictionary* data=new CCDictionary();
    data->setObject(CCString::create(CCGE_ANIMATION_IDLE), CCGE_ANIMATION_NAME);
    data->setObject(CCInteger::create(kEightDirctionRightBottom), CCGE_ANIMATION_DIRECTION);
    data->setObject(CCBool::create(true), CCGE_ANIMATION_SHOWFIRSTFRAME);
    MessageManager::defaultManager()->dispatchMessage(MSG_CHANGE_ANIMATION, NULL, entity,data);
}

void EntityComponentFactory::addBattleComponent(GameEntity* entity)
{
    GameAttackComponent* attackComponent=new GameAttackComponent();
    attackComponent->init();
    entity->addComponent(attackComponent);
    attackComponent->release();
}

void EntityComponentFactory::addDieComponent(GameEntity* entity)
{
    DieComponent* dieComponent=new DieComponent();
    dieComponent->init();
    entity->addComponent(dieComponent);
    dieComponent->release();
}

void EntityComponentFactory::addHealthBarComponent(GameEntity* entity)
{
    UnitProperty* unitProperty=static_cast<UnitProperty*>(entity->getProperty(CCGE_PROPERTY_UNIT));
    BattleProperty* battleProperty=static_cast<BattleProperty*>(entity->getProperty(CCGE_PROPERTY_BATTLE));
        
    HealthBarComponent* healthBarComponent=new HealthBarComponent();
    healthBarComponent->init();
    
    entity->addComponent(healthBarComponent);
    healthBarComponent->release();
    
    healthBarComponent->setMaxHp(battleProperty->getHealth());
    healthBarComponent->setCurrentHp(unitProperty->getHealth());
    
    //设置血条显示在人物上面
    AnimationComponent* animationComponent=static_cast<AnimationComponent*>(entity->getComponent("AnimationComponent"));
    CCAnimation* animation=animationComponent->getLastAnimation();
    CCSpriteFrame* spriteFrame=static_cast<CCAnimationFrame*>(animation->getFrames()->objectAtIndex(0))->getSpriteFrame();
    
    CCSize entitySize=spriteFrame->getOriginalSize();
    CCPoint offset=spriteFrame->getOffset();
    
    healthBarComponent->setRendererContentSize(entitySize,offset);
    
}

void EntityComponentFactory::addHurtComponent(GameEntity* entity)
{
    HurtComponent* hurtComponent=new HurtComponent();
    hurtComponent->init();
    entity->addComponent(hurtComponent);
    hurtComponent->release();
}

void EntityComponentFactory::addBattlePositionComponent(GameEntity* entity)
{
    BattlePositionComponent* battlePositionComponent=new BattlePositionComponent();
    battlePositionComponent->init();
    entity->addComponent(battlePositionComponent);
    battlePositionComponent->release();
    battlePositionComponent->updateRendererPosition();

}

void EntityComponentFactory::addBattleStateMachineComponent(GameEntity* entity)
{
    BattleStateMachineComponent* battleStateMachineComponent=new BattleStateMachineComponent();
    battleStateMachineComponent->init();
    entity->addComponent(battleStateMachineComponent);
    battleStateMachineComponent->release();

}

void EntityComponentFactory::addAIComponent(GameEntity* entity)
{
    AIComponent* aiComponent=new AIComponent();
    aiComponent->init();
    
    entity->addComponent(aiComponent);
    
    m_entityFactory->getEngine()->getBattleUpdateManager()->addUpdaterToGroup(entity->m_uID, aiComponent, schedule_selector(AIComponent::update),kAIUpdate);
    
    
    aiComponent->release();
}

void EntityComponentFactory::addPositionComponent(GameEntity* entity)
{

}

void EntityComponentFactory::addMoveComponent(GameEntity* entity)
{
    MoveComponent* moveComponent=new MoveComponent();
    moveComponent->init();
    
    entity->addComponent(moveComponent);
    
    m_entityFactory->getEngine()->getBattleUpdateManager()->addUpdaterToGroup(entity->m_uID, moveComponent, schedule_selector(MoveComponent::update),kMoveUpdate);
    
    moveComponent->release();
}

void EntityComponentFactory::addSkillComponents(GameEntity* entity)
{
    //get skill data from table
    BaseSqlDAO* skillGroupDAO=Game::getInstance()->getDataFactory()->getSkillGroupDAO();
    SkillDAO* skillDAO=Game::getInstance()->getDataFactory()->getSkillDAO();
    
    UnitProperty* unitProperty=static_cast<UnitProperty*>(entity->getProperty(CCGE_PROPERTY_UNIT));
    
    int unitId=unitProperty->getUnitId();
    
    Json::Value skillGroupInfo=skillGroupDAO->findAll("caster_id",unitId);
    
    int skillCount=skillGroupInfo.size();
    
    for (int i=0; i<skillCount; ++i) {
        
        Json::Value skillInfo=skillDAO->getDataById(skillGroupInfo[i]["skill_id"].asInt());
        
        SkillComponent* skillComponent=new SkillComponent();
        skillComponent->init();
        
        skillComponent->setProto(skillInfo);
        
        if (!skillInfo[CCGE_SKILL_INIT_CD].isNull()) {
            skillComponent->setCdRemaining(skillInfo[CCGE_SKILL_INIT_CD].asDouble());
        }
        
        float maxRange=skillInfo[CCGE_SKILL_MAX_RANGE].asDouble();
        skillComponent->setMaxRangeSq(maxRange* maxRange);
        
        float minRange=skillInfo[CCGE_SKILL_MIN_RANGE].asDouble();
        skillComponent->setMinRangeSq(minRange*minRange);
        
        entity->addComponent(skillComponent);
        
        entity->addSkillComponent(skillComponent, 0);
        
        m_entityFactory->getEngine()->getBattleUpdateManager()->addUpdaterToGroup(entity->m_uID, skillComponent, schedule_selector(SkillComponent::update),kSkillUpdate);
        
        skillComponent->release();
    }
}

void EntityComponentFactory::addSkillComponent(GameEntity* entity)
{
    SkillComponent* skillComponent=new SkillComponent();
    skillComponent->init();
    
    entity->addComponent(skillComponent);
    
    skillComponent->release();
}

void EntityComponentFactory::addVisibleMoveComponent(GameEntity* entity)
{
    VisibleMoveComponent* visibleMoveComponent=new VisibleMoveComponent();
    visibleMoveComponent->init();
    
    entity->addComponent(visibleMoveComponent);
    
//    m_entityFactory->getEngine()->getBattleUpdateManager()->addUpdaterToGroup(entity->m_uID, visibleMoveComponent, schedule_selector(VisibleMoveComponent::update),kRendererMoveUpdate);
    
    visibleMoveComponent->release();
}

CCArray* EntityComponentFactory::createEightAnimations(const yhge::Json::Value& configData)
{
    int frameQuantity=configData["frame_quantity"].asInt();
    //    float frameWidth=configData["frame_width"].asDouble();
    //    float frameHeight=configData["frame_height"].asDouble();
    float frameDelay=configData["frame_delay"].asDouble();
    std::string ext=configData["ext"].asString();
    int loops=configData.get("loops", -1).asInt();
    std::string frameIndexPrefix=configData["frame_index_prefix"].asString();
    
    return EightDirectionAnimationComponent::createDirectionActionListWithResource(
                                                                                   ext.c_str(),frameIndexPrefix.c_str(),8,frameQuantity, frameDelay,loops);
}

CCArray* EntityComponentFactory::createTwoAnimations(const yhge::Json::Value& configData)
{
    int frameQuantity=configData["frame_quantity"].asInt();
    //    float frameWidth=configData["frame_width"].asDouble();
    //    float frameHeight=configData["frame_height"].asDouble();
    float frameDelay=configData["frame_delay"].asDouble();
    std::string ext=configData["ext"].asString();
    int loops=configData.get("loops", -1).asInt();
    std::string frameIndexPrefix=configData["frame_index_prefix"].asString();
    
    return EightDirectionAnimationComponent::createDirectionActionListWithResource(
                                                                                   ext.c_str(),frameIndexPrefix.c_str(),1,frameQuantity, frameDelay,loops);
}

NS_CC_GE_END
