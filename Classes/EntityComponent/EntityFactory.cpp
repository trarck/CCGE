#include "EntityFactory.h"
#include <yhge/yhge.h>

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
GameEntity* EntityFactory::createEntity(CCDictionary* data)
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
    
    //添加组件
    
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
    
    //8方向空闲动画
    CCArray* idleEightAnimations=AnimationComponent::eightDirectionActionListWithDir("characters/2/0", 10, CCSizeMake(62, 91), 0.15f, "%s/%02d%03d.png");
    animation->addAnimationList(idleEightAnimations,"idle");
    
    //8方向移动动画
    CCArray* moveEightAnimations=AnimationComponent::eightDirectionActionListWithDir("characters/2/1", 8, CCSizeMake(74, 93), 0.1f, "%s/%02d%03d.png");
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
GameEntity* EntityFactory::createPlayer(CCDictionary* param)
{
    GameEntity* player=GameEntity::create();
    
    //添加组件
    
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
    
    //8方向空闲动画
    CCArray* idleEightAnimations=AnimationComponent::eightDirectionActionListWithDir("characters/2/0", 10, CCSizeMake(62, 91), 0.15f, "%s/%02d%03d.png");
    animation->addAnimationList(idleEightAnimations,"idle");
    
    //8方向移动动画
    CCArray* moveEightAnimations=AnimationComponent::eightDirectionActionListWithDir("characters/2/1", 8, CCSizeMake(74, 93), 0.1f, "%s/%02d%03d.png");
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

NS_CC_GE_END
