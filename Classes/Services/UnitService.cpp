#include "UnitService.h"
#include "Consts/DataDefine.h"

USING_NS_CC;

NS_CC_GE_BEGIN


UnitService::UnitService()
{
    
}

UnitService::~UnitService()
{

}

UnitProperty* UnitService::createUnitPropertyFromLevel(int level,const yhge::Json::Value& entityConfig)
{
    
    //根据属生成长计算某个等级的元素属性
    int growType=entityConfig[CCGE_UNIT_GROW_TYPE].asInt();
    
    float finalValue=0.0f;
    
    UnitProperty* unitProperty=new UnitProperty();
    
    //id
    unitProperty->setUnitId(entityConfig[CCGE_UNIT_ID].asInt());
    
    //level
    unitProperty->setLevel(level);
    
    //health
    finalValue=calcGrow(
                              entityConfig[CCGE_UNIT_HEALTH].asDouble(),
                              entityConfig[CCGE_UNIT_GROW_HEALTH].asDouble(),
                              level,growType);
    
    unitProperty->setHealth(finalValue);
    //max the same
    unitProperty->setMaxHealth(finalValue);
    
    //mana
    finalValue=calcGrow(
                              entityConfig[CCGE_UNIT_MANA].asDouble(),
                              entityConfig[CCGE_UNIT_GROW_MANA].asDouble(),
                              level,growType);
    unitProperty->setMana(finalValue);
    //max the same
    unitProperty->setMaxMana(finalValue);
    
    //damage
    finalValue=calcGrow(
                              entityConfig[CCGE_UNIT_DAMAGE].asDouble(),
                              entityConfig[CCGE_UNIT_GROW_DAMAGE].asDouble(),
                              level,growType);
    unitProperty->setDamage(finalValue);
    
    //defence
    finalValue=calcGrow(
                              entityConfig[CCGE_UNIT_DEFENCE].asDouble(),
                              entityConfig[CCGE_UNIT_GROW_DEFENCE].asDouble(),
                              level,growType);
    unitProperty->setDefence(finalValue);
    
    unitProperty->autorelease();
    
    return unitProperty;
}

NS_CC_GE_END
