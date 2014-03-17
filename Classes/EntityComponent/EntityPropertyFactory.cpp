#include "EntityPropertyFactory.h"
#include <yhge/yhge.h>
#include "Consts/PropertyDefine.h"
#include "Datas/DataFactory.h"

#include "Properties/UnitProperty.h"
#include "Properties/BattleProperty.h"

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

EntityPropertyFactory::EntityPropertyFactory()
{

}

EntityPropertyFactory::~EntityPropertyFactory()
{

}

static EntityPropertyFactory* s_instance=NULL;

EntityPropertyFactory* EntityPropertyFactory::getInstance()
{
    if (!s_instance) {
        s_instance=new EntityPropertyFactory();
        s_instance->init();
    }
    return s_instance;
}

bool EntityPropertyFactory::init()
{
    return true;
}

/**
 * @brief 添加物体地图相关属性
 */
void EntityPropertyFactory::createMapProperties(GameEntity* entity)
{
    UnitProperty* unitProperty=new UnitProperty();
    
    entity->addProperty(unitProperty, CCGE_PROPERTY_UNIT);
    unitProperty->release();
    entity->setUnitProperty(unitProperty);
    
}

/**
 * @brief 添加物体战斗相关属性
 */
void EntityPropertyFactory::createBattleProperties(GameEntity* entity)
{
    UnitProperty* unitProperty=new UnitProperty();
    
    entity->addProperty(unitProperty, CCGE_PROPERTY_UNIT);
    unitProperty->release();
    entity->setUnitProperty(unitProperty);
    
    BattleProperty* battleProperty=new BattleProperty();
    entity->addProperty(battleProperty, CCGE_PROPERTY_BATTLECELL);
    battleProperty->release();
    entity->setBattleProperty(battleProperty);
    
}

NS_CC_GE_END
