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
:m_entityPropertyFactory(NULL)
{

}

EntityFactory::~EntityFactory()
{
    CC_SAFE_RELEASE_NULL(m_entityPropertyFactory);
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
    m_entityPropertyFactory=new EntityPropertyFactory();
    m_entityPropertyFactory->init();
    
    return true;
}

/**
 * 从配置文件中创建一个游戏实体
 */
GameEntity* EntityFactory::createEntity(int entityId)
{
    GameEntity* entity=GameEntity::create();
    entity->setEntityId(entityId);
    return entity;
}

GameEntity* EntityFactory::createEntityWithParams(int entityId,CCDictionary* params)
{
    GameEntity* entity=GameEntity::create();
    entity->setEntityId(entityId);
    return entity;
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
    
    //添加组件
    
    addMapComponents(entity);
    
    return entity;
}

/**
 * 创建一个人物
 */
GameEntity* EntityFactory::createPlayer(int entityId,CCDictionary* param)
{
    GameEntity* player=GameEntity::create();
    player->setEntityId(entityId);

    //添加组件
    addMapComponents(player);
    
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
    
    //添加属性
    m_entityPropertyFactory->createBattleProperties(player);
    
    //添加组件
    addBattleComponents(player);
    
    return player;
}

/**
 * @brief 给entity添加地图相关组件
 */
void EntityFactory::addMapComponents(GameEntity* entity)
{
    //显示组件
    SpriteRendererComponent* renderer=new SpriteRendererComponent();
    renderer->init();
    entity->addComponent(renderer);
    renderer->release();
    entity->setRendererComponent(renderer);
    
    //位置组件
    ISOPositionComponent* isoPosition=new ISOPositionComponent();
    isoPosition->init();
    entity->addComponent(isoPosition);
    isoPosition->release();
    entity->setISOPositionComponent(isoPosition);
    
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
    yhge::Json::Value moveAnimationData=animationData->getEntityAnimateData(entity->getEntityId(),"move");
    
    //8方向空闲动画
    CCArray* idleEightAnimations=createEightAnimations(moveAnimationData["idle"]);
    animation->addAnimationList(idleEightAnimations,"idle");
    
    //8方向移动动画
    CCArray* moveEightAnimations=createEightAnimations(moveAnimationData["move"]);
    animation->addAnimationList(moveEightAnimations,"move");
    
    entity->addComponent(animation);
    animation->release();
    
    float speed=1.5f;
    
    CameraFlowGridMoveComponent* gridMove=new CameraFlowGridMoveComponent();
    gridMove->init(speed);
    gridMove->setInnerOffset(kDefaultInnerOffset);
    
    //相机的引用和中心点在外面设置。有可能地图不是全屏的
    
    entity->addComponent(gridMove);
    gridMove->release();
}

/**
 * @brief 给entity添加战斗相关组件
 */
void EntityFactory::addBattleComponents(GameEntity* entity)
{
    //显示组件
    SpriteRendererComponent* renderer=new SpriteRendererComponent();
    renderer->init();
    entity->addComponent(renderer);
    renderer->release();
    entity->setRendererComponent(renderer);
    
    //动画组件
    AnimationComponent* animation=new AnimationComponent();
    animation->init();
    
    AnimationData* animationData=DataFactory::getInstance()->getAnimationData();
    yhge::Json::Value battleAnimationData=animationData->getEntityAnimateData(entity->getEntityId(),"battle");
    
    yhge::Json::Value::Members members=battleAnimationData.getMemberNames();
    
    CCArray* twoAnimations=NULL;
    for (yhge::Json::Value::Members::iterator iter=members.begin(); iter!=members.end(); ++iter) {
        twoAnimations=createTwoAnimations(battleAnimationData[*iter]);
        animation->addAnimationList(twoAnimations,*iter);
    }
    
    entity->addComponent(animation);
    animation->release();
    
    
    //战斗组件
    GameAttackComponent* attackComponent=new GameAttackComponent();
    attackComponent->init();
    entity->addComponent(attackComponent);
    attackComponent->release();
    entity->setAttackComponent(attackComponent);
    
    //死亡组件
    DieComponent* dieComponent=new DieComponent();
    dieComponent->init();
    entity->addComponent(dieComponent);
    dieComponent->release();
    
    //血条组件
    HealthBarComponent* healthBarComponent=new HealthBarComponent();
    healthBarComponent->init();
    entity->addComponent(healthBarComponent);
    healthBarComponent->release();
    entity->setHealthBarComponent(healthBarComponent);

}

CCArray* EntityFactory::createEightAnimations(const yhge::Json::Value& configData)
{
    int frameQuantity=configData["frame_quantity"].asInt();
//    float frameWidth=configData["frame_width"].asDouble();
//    float frameHeight=configData["frame_height"].asDouble();
    float frameDelay=configData["frame_delay"].asDouble();
    std::string ext=configData["ext"].asString();
    int loops=configData.get("loops", -1).asInt();
    std::string frameIndexPrefix=configData["frame_index_prefix"].asString();

    return AnimationComponent::createDirectionActionListWithResource(
        ext.c_str(),frameIndexPrefix.c_str(),8,frameQuantity, frameDelay,loops);
}

CCArray* EntityFactory::createTwoAnimations(const yhge::Json::Value& configData)
{
    int frameQuantity=configData["frame_quantity"].asInt();
//    float frameWidth=configData["frame_width"].asDouble();
//    float frameHeight=configData["frame_height"].asDouble();
    float frameDelay=configData["frame_delay"].asDouble();
    std::string ext=configData["ext"].asString();
    int loops=configData.get("loops", -1).asInt();
    std::string frameIndexPrefix=configData["frame_index_prefix"].asString();
    
    return AnimationComponent::createDirectionActionListWithResource(
                                                                     ext.c_str(),frameIndexPrefix.c_str(),1,frameQuantity, frameDelay,loops);
}

NS_CC_GE_END
