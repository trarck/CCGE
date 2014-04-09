#include "EntityService.h"
#include "Consts/DataDefine.h"

USING_NS_CC;

NS_CC_GE_BEGIN


EntityService::EntityService()
{
    
}

EntityService::~EntityService()
{

}

UnitProperty* EntityService::calcLevelUnitProperty(int level,const yhge::Json::Value& entityConfig)
{
    
    //根据属生成长计算某个等级的元素属性
    int growType=entityConfig[CCGE_ENTITY_GROW_TYPE].asInt();
    
    float finalValue=0.0f;
    
    UnitProperty* unitProperty=new UnitProperty();
    
    //level
    unitProperty->setLevel(level);
    
    //health
    finalValue=calcGrow(
                              entityConfig[CCGE_ENTITY_GROW_HEALTH].asDouble(),
                              entityConfig[CCGE_ENTITY_HEALTH].asDouble(),
                              level,growType);
    
    unitProperty->setHealth(finalValue);
    //max the same
    unitProperty->setMaxHealth(finalValue);
    
    //mana
    finalValue=calcGrow(
                              entityConfig[CCGE_ENTITY_GROW_MANA].asDouble(),
                              entityConfig[CCGE_ENTITY_MANA].asDouble(),
                              level,growType);
    unitProperty->setMana(finalValue);
    //max the same
    unitProperty->setMaxMana(finalValue);
    
    //damage
    finalValue=calcGrow(
                              entityConfig[CCGE_ENTITY_GROW_DAMAGE].asDouble(),
                              entityConfig[CCGE_ENTITY_DAMAGE].asDouble(),
                              level,growType);
    unitProperty->setDamage(finalValue);
    
    //defence
    finalValue=calcGrow(
                              entityConfig[CCGE_ENTITY_GROW_DEFENCE].asDouble(),
                              entityConfig[CCGE_ENTITY_DEFENCE].asDouble(),
                              level,growType);
    unitProperty->setDefence(finalValue);
    
    unitProperty->autorelease();
    return unitProperty;
}

NS_CC_GE_END
