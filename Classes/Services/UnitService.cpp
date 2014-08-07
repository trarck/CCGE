#include "UnitService.h"
#include "Consts/DataDefine.h"
#include "Formula/AttackSpeedFormula.h"

USING_NS_CC;

NS_CC_GE_BEGIN


UnitService::UnitService()
{
    
}

UnitService::~UnitService()
{

}

UnitProperty* UnitService::createUnitPropertyFromLevel(int level,const yhge::Json::Value& unitProto)
{
    
    //根据属生成长计算某个等级的元素属性
    int growType=unitProto[CCGE_UNIT_GROW_TYPE].asInt();
    
    float finalValue=0.0f;
    
    UnitProperty* unitProperty=new UnitProperty();
    
    //id
    unitProperty->setUnitId(unitProto[CCGE_UNIT_ID].asInt());
    
    //level
    unitProperty->setLevel(level);
    
    //health
    finalValue=calcGrow(
                              unitProto[CCGE_UNIT_BASE_HEALTH].asDouble(),
                              unitProto[CCGE_UNIT_GROW_HEALTH].asDouble(),
                              level,growType);
    
    unitProperty->setHealth(finalValue);
    //max the same
    unitProperty->setMaxHealth(finalValue);
    
    //mana
    finalValue=calcGrow(
                              unitProto[CCGE_UNIT_BASE_MANA].asDouble(),
                              unitProto[CCGE_UNIT_GROW_MANA].asDouble(),
                              level,growType);
    unitProperty->setMana(finalValue);
    //max the same
    unitProperty->setMaxMana(finalValue);
    
    //damage
    finalValue=calcGrow(
                              unitProto[CCGE_UNIT_BASE_DAMAGE].asDouble(),
                              unitProto[CCGE_UNIT_GROW_DAMAGE].asDouble(),
                              level,growType);
    unitProperty->setAttackDamage(finalValue);
    
    //defence
    finalValue=calcGrow(
                              unitProto[CCGE_UNIT_BASE_DEFENCE].asDouble(),
                              unitProto[CCGE_UNIT_GROW_DEFENCE].asDouble(),
                              level,growType);
    unitProperty->setArmor(finalValue);
    
    //agility
    finalValue=calcGrow(
                        unitProto[CCGE_UNIT_BASE_AGILITY].asDouble(),
                        unitProto[CCGE_UNIT_GROW_AGILITY].asDouble(),
                        level,growType);
    unitProperty->setAgility(finalValue);
    
    //base attack speed
    
    //attack speed
    unitProperty->setAttackSpeed(AttackSpeedFormula::calcAttackSpeed(0, 0, unitProperty->getAgility(), kAgilityToAttackSpeedParam));
    
    //walk speed
    unitProperty->setWalkSpeed(unitProto[CCGE_UNIT_WALK_SPEED].asDouble());
    
    //icon
    unitProperty->setIcon(unitProto[CCGE_UNIT_ICON].asString());
        
    unitProperty->autorelease();
    
    return unitProperty;
}

NS_CC_GE_END
