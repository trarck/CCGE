#include "EntityFactory.h"
#include <yhge/yhge.h>
#include "Consts/PropertyDefine.h"
#include "Datas/DataFactory.h"

#include "Properties/UnitProperty.h"
#include "Properties/BattleProperty.h"

#include "Components/GameAttackComponent.h"
#include "Components/DieComponent.h"
#include "Components/HealthBarComponent.h"

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

static const CCSize kDefaultInnerOffset=CCSizeMake(64.0f, 32.0f);

EntityFactory::EntityFactory()
{

}

EntityFactory::~EntityFactory()
{

}

static EntityFactory* s_instance=NULL;

EntityFactory* EntityFactory::getInstance()
{
    if (!s_instance) {
        s_instance=new EntityFactory();
        s_instance->init();
    }
    return s_instance;
}

bool EntityFactory::init()
{
    return true;
}

/**
 * 从配置文件中创建一个游戏实体
 */
GameEntity* EntityFactory::createEntity(int entityId,CCDictionary* data)
{
    return NULL;
}

/**
 * 根据id创建游戏实体
 * 从配置文件中根据id，查找entity的相关数据，然后创建一个entity
 */
GameEntity* EntityFactory::createEntityById(int entityId)
{
    GameEntity* entity=GameEntity::create();
    entity->setEntityId(entityId);
    
    //==========添加属性==========//
    UnitProperty* unitProperty=new UnitProperty();
    entity->addProperty(unitProperty, CCGE_PROPERTY_UNIT);
    unitProperty->release();
    entity->setUnitProperty(unitProperty);
    
    //==========添加组件==========//
    
    //显示组件
    SpriteRendererComponent* renderer=new SpriteRendererComponent();
    renderer->init();
    entity->addComponent(renderer);
    renderer->release();
    entity->setRendererComponent(renderer);
    
    //位置组件
//    ISOPositionComponent* isoPosition=new ISOPositionComponent();
//    isoPosition->init();
//    entity->addComponent(isoPosition);
//    isoPosition->release();
//    entity->setISOPositionComponent(isoPosition);
    
    //使用自动排序的位置组件
    ISOAutoZOrderPositionComponent* isoPosition=new ISOAutoZOrderPositionComponent();
    isoPosition->init();
    entity->addComponent(isoPosition);
    isoPosition->release();
    entity->setISOPositionComponent(isoPosition);
    
    //动画组件
    AnimationComponent* animation=new AnimationComponent();
    animation->init();
    
    AnimationData* animationData=DataFactory::getInstance()->getAnimationData();
    yhge::Json::Value moveAnimationData=animationData->getEntityAnimateData(entityId,"move");
    
    //8方向空闲动画
    CCArray* idleEightAnimations=createEightAnimations(moveAnimationData["idle"]);
    animation->addAnimationList(idleEightAnimations,"idle");
    
    //8方向移动动画
    CCArray* moveEightAnimations=createEightAnimations(moveAnimationData["move"]);
    animation->addAnimationList(moveEightAnimations,"move");
    
    entity->addComponent(animation);
    animation->release();
    
    float speed=2.0f;
    
    CameraFlowGridMoveComponent* gridMove=new CameraFlowGridMoveComponent();
    gridMove->init(speed);
    gridMove->setInnerOffset(kDefaultInnerOffset);
    
    //相机的引用和中心点在外面设置。有可能地图不是全屏的
    
    entity->addComponent(gridMove);
    gridMove->release();
    
    return entity;
}

/**
 * 创建一个人物
 */
GameEntity* EntityFactory::createPlayer(int entityId,CCDictionary* param)
{
    GameEntity* player=GameEntity::create();
    player->setEntityId(entityId);

    //==========添加组件==========//
    
    //显示组件
    SpriteRendererComponent* renderer=new SpriteRendererComponent();
    renderer->init();
    player->addComponent(renderer);
    renderer->release();
    player->setRendererComponent(renderer);

    //位置组件
    ISOPositionComponent* isoPosition=new ISOPositionComponent();
    isoPosition->init();
    player->addComponent(isoPosition);
    isoPosition->release();
    player->setISOPositionComponent(isoPosition);
    
//    //使用自动排序的位置组件
//    ISOAutoZOrderPositionComponent* isoPosition=new ISOAutoZOrderPositionComponent();
//    isoPosition->init();
//    player->addComponent(isoPosition);
//    isoPosition->release();
//    player->setISOPositionComponent(isoPosition);

    //动画组件
    AnimationComponent* animation=new AnimationComponent();
    animation->init();

    AnimationData* animationData=DataFactory::getInstance()->getAnimationData();
    yhge::Json::Value moveAnimationData=animationData->getEntityAnimateData(entityId,"move");

    //8方向空闲动画
    CCArray* idleEightAnimations=createEightAnimations(moveAnimationData["idle"]);
    animation->addAnimationList(idleEightAnimations,"idle");
    
    //8方向移动动画
    CCArray* moveEightAnimations=createEightAnimations(moveAnimationData["move"]);
    animation->addAnimationList(moveEightAnimations,"move");
    
    player->addComponent(animation);
    animation->release();
    
    float speed=1.5f;
    
    CameraFlowGridMoveComponent* gridMove=new CameraFlowGridMoveComponent();
    gridMove->init(speed);
    gridMove->setInnerOffset(kDefaultInnerOffset);
    
    //相机的引用和中心点在外面设置。有可能地图不是全屏的
    
    player->addComponent(gridMove);
    gridMove->release();
    
    return player;
}

/**
 * 创建战斗中的人物
 */
GameEntity* EntityFactory::createBattlePlayer(int entityId,CCDictionary* param)
{
    GameEntity* player=GameEntity::create();
    player->setEntityId(entityId);

    //战斗中的人物需要战斗相关的属性
    
    //==========添加属性==========//
    UnitProperty* unitProperty=new UnitProperty();
    player->addProperty(unitProperty, CCGE_PROPERTY_UNIT);
    unitProperty->release();
    player->setUnitProperty(unitProperty);
    
    BattleProperty* battleProperty=new BattleProperty();
    player->addProperty(battleProperty, CCGE_PROPERTY_BATTLECELL);
    battleProperty->release();
    player->setBattleProperty(battleProperty);
    
    //==========添加组件==========//
    //不需要移动相关组件
    
    //显示组件
    SpriteRendererComponent* renderer=new SpriteRendererComponent();
    renderer->init();
    player->addComponent(renderer);
    renderer->release();
    player->setRendererComponent(renderer);
    
    //动画组件
    AnimationComponent* animation=new AnimationComponent();
    animation->init();
    
    AnimationData* animationData=DataFactory::getInstance()->getAnimationData();
    yhge::Json::Value battleAnimationData=animationData->getEntityAnimateData(entityId,"battle");

    //空闲动画
    CCArray* idleEightAnimations=createEightAnimations(battleAnimationData["idle"]);
    animation->addAnimationList(idleEightAnimations,"idle");
    
    //战斗动画
    CCArray* moveEightAnimations=createEightAnimations(battleAnimationData["attack"]);
    animation->addAnimationList(moveEightAnimations,"attack");
    
    player->addComponent(animation);
    animation->release();
    
    
    //战斗组件
    GameAttackComponent* attackComponent=new GameAttackComponent();
    attackComponent->init();
    player->addComponent(attackComponent);
    attackComponent->release();
    player->setAttackComponent(attackComponent);
    
    //死亡组件
    DieComponent* dieComponent=new DieComponent();
    dieComponent->init();
    player->addComponent(dieComponent);
    dieComponent->release();
    
    //血条组件
    HealthBarComponent* healthBarComponent=new HealthBarComponent();
    healthBarComponent->init();
    player->addComponent(healthBarComponent);
    healthBarComponent->release();
    player->setHealthBarComponent(healthBarComponent);
    
    return player;
}

CCArray* EntityFactory::createEightAnimations(const yhge::Json::Value& configData)
{
    int frameQuantity=configData["frame_quantity"].asInt();
    float frameWidth=configData["frame_width"].asDouble();
    float frameHeight=configData["frame_height"].asDouble();
    float frameDelay=configData["frame_delay"].asDouble();
    std::string ext=configData["ext"].asString();
    int loops=configData.get("loops", -1).asInt();

    return AnimationComponent::eightDirectionActionListWithDirResource(
        ext.c_str(),frameQuantity, CCSizeMake(frameWidth, frameHeight), frameDelay,loops);
}

NS_CC_GE_END
