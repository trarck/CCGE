#include "EntityPropertyFactory.h"
#include <yhge/yhge.h>
#include "Consts/PropertyDefine.h"
#include "Consts/DataDefine.h"

#include "Properties/UnitProperty.h"
#include "Properties/BattleProperty.h"
#include "EntityFactory.h"

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

EntityPropertyFactory::EntityPropertyFactory()
:m_entityFactory(NULL)
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

void EntityPropertyFactory::addUnitProperty(GameEntity* entity)
{
    UnitProperty* unitProperty=new UnitProperty();
    
    entity->addProperty(unitProperty, CCGE_PROPERTY_UNIT);
    unitProperty->release();
    entity->setUnitProperty(unitProperty);
}

void EntityPropertyFactory::addUnitProperty(GameEntity* entity,const yhge::Json::Value& value)
{
    UnitProperty* unitProperty=new UnitProperty();
    
    setUnitPropertyValue(unitProperty, value);
    
    entity->addProperty(unitProperty, CCGE_PROPERTY_UNIT);
    unitProperty->release();
    entity->setUnitProperty(unitProperty);
}

void EntityPropertyFactory::addBattleProperty(GameEntity* entity)
{
    BattleProperty* battleProperty=new BattleProperty();
    entity->addProperty(battleProperty, CCGE_PROPERTY_BATTLECELL);
    battleProperty->release();
    entity->setBattleProperty(battleProperty);
}

void EntityPropertyFactory::addBattleProperty(GameEntity* entity,const yhge::Json::Value& value)
{
    BattleProperty* battleProperty=new BattleProperty();
    
    setBattlePropertyValue(battleProperty, value);
    
    entity->addProperty(battleProperty, CCGE_PROPERTY_BATTLECELL);
    battleProperty->release();
    entity->setBattleProperty(battleProperty);
}

void EntityPropertyFactory::addBattleProperty(GameEntity* entity,int col,int row,int side,float scale)
{
    BattleProperty* battleProperty=new BattleProperty();
    
//    battleProperty->setCol(col);
//    battleProperty->setRow(row);
    battleProperty->setSide(side);
    battleProperty->setScale(scale);
    
    entity->addProperty(battleProperty, CCGE_PROPERTY_BATTLECELL);
    battleProperty->release();
    entity->setBattleProperty(battleProperty);
}

void EntityPropertyFactory::addRealtimeBattleProperty(GameEntity* entity,float x,float y,int side,float scale)
{
    BattleProperty* battleProperty=new BattleProperty();
    
    battleProperty->setX(x);
    battleProperty->setY(y);
    battleProperty->setSide(side);
    battleProperty->setScale(scale);
    
    entity->addProperty(battleProperty, CCGE_PROPERTY_BATTLECELL);
    battleProperty->release();
    entity->setBattleProperty(battleProperty);
}

/**
 * @brief 添加物体地图相关属性
 */
void EntityPropertyFactory::addMapProperties(GameEntity* entity)
{
    addUnitProperty(entity);
}

/**
 * @brief 添加物体战斗相关属性
 */
void EntityPropertyFactory::addBattleProperties(GameEntity* entity)
{
    addUnitProperty(entity);
    
    addBattleProperty(entity);
}

void EntityPropertyFactory::addBattleProperties(GameEntity* entity,CCDictionary* params)
{
    
}

void EntityPropertyFactory::addBattleProperties(GameEntity* entity,const yhge::Json::Value& params)
{
    //unit property
    addUnitProperty(entity,params[CCGE_DATA_PROPERTY_CONFIG_ENTITY]);
    
    //battle property
    addBattleProperty(entity, params[CCGE_DATA_PROPERTY_CONFIG_BATTLE]);

}

void EntityPropertyFactory::setUnitPropertyValue(UnitProperty* property,const yhge::Json::Value& value)
{    
    if (!value.isNull()) {
        
        property->setUnitId(value[CCGE_UNIT_ID].asInt());
        
        property->setDamage(value[CCGE_UNIT_DAMAGE].asDouble());
        property->setDefence(value[CCGE_UNIT_DEFENCE].asDouble());
        property->setHealth(value[CCGE_UNIT_HEALTH].asDouble());
        property->setMaxHealth(value[CCGE_UNIT_HEALTH].asDouble());
        property->setMana(value[CCGE_UNIT_MANA].asDouble());
        property->setMaxMana(value[CCGE_UNIT_MANA].asDouble());
        property->setAgility(value[CCGE_UNIT_AGILITY].asDouble());
        property->setAttackSpeed(value[CCGE_UNIT_ATTACK_SPEED].asDouble());
        property->setIcon(value[CCGE_UNIT_ICON].asString());
        property->setAttackType(value[CCGE_UNIT_ATTACK_TYPE].asInt());
        
        property->setLevel(value[CCGE_UNIT_LEVEL].asInt());
    }
}

void EntityPropertyFactory::setBattlePropertyValue(BattleProperty* property,const yhge::Json::Value& value)
{
    if (!value.isNull()) {
        
//        property->setCol(value[CCGE_BATTLE_CELL_COL].asInt());
//        property->setRow(value[CCGE_BATTLE_CELL_ROW].asInt());
        property->setSide(value[CCGE_BATTLE_CELL_SIDE].asInt());
        property->setScale(value[CCGE_BATTLE_CELL_SCALE].asDouble());
    }
}

NS_CC_GE_END
