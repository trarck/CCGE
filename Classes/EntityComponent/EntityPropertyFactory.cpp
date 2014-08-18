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
}

void EntityPropertyFactory::addUnitProperty(GameEntity* entity,const yhge::Json::Value& config,const yhge::Json::Value& info)
{
    UnitProperty* unitProperty=new UnitProperty();
    
    setUnitPropertyValue(unitProperty, config,info);
    
    entity->addProperty(unitProperty, CCGE_PROPERTY_UNIT);
    unitProperty->release();
}

void EntityPropertyFactory::addBattleProperty(GameEntity* entity)
{
    BattleProperty* battleProperty=new BattleProperty();
    entity->addProperty(battleProperty, CCGE_PROPERTY_BATTLECELL);
    battleProperty->release();
}

void EntityPropertyFactory::addBattleProperty(GameEntity* entity,const yhge::Json::Value& value)
{
    BattleProperty* battleProperty=new BattleProperty();
    
//    setBattlePropertyValue(battleProperty, value);
    
    entity->addProperty(battleProperty, CCGE_PROPERTY_BATTLECELL);
    battleProperty->release();
}

void EntityPropertyFactory::addRealtimeBattleProperty(GameEntity* entity,const yhge::Json::Value& config,const yhge::Json::Value& unitInfo)
{
    BattleProperty* battleProperty=new BattleProperty();
    
    setBattlePropertyValue(battleProperty, config,unitInfo);
    
    entity->addProperty(battleProperty, CCGE_PROPERTY_BATTLE);
    battleProperty->release();
}

void EntityPropertyFactory::addMoveProperty(GameEntity* entity,const yhge::Json::Value& config)
{
    MoveProperty* moveProperty=new MoveProperty();
    
    setMovePropertyValue(moveProperty, config);
    
    entity->addProperty(moveProperty, CCGE_PROPERTY_MOVE);
    moveProperty->release();
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
    addUnitProperty(entity,params[CCGE_DATA_PROPERTY_CONFIG],params[CCGE_DATA_PROPERTY_CONFIG_ENTITY]);
    
    //battle property
    addBattleProperty(entity, params[CCGE_DATA_PROPERTY_CONFIG_BATTLE]);

}

void EntityPropertyFactory::setUnitPropertyValue(UnitProperty* property,const yhge::Json::Value& config,const yhge::Json::Value& info)
{    
    if (!config.isNull()) {
        
        property->setUnitId(info[CCGE_UNIT_ID].asInt());
        
        property->setCamp(config[CCGE_UNIT_CAMP].asInt());
        property->setFoecamp(-property->getCamp());
        
        property->setHealth(info[CCGE_UNIT_HEALTH].asDouble());
        property->setMana(info[CCGE_UNIT_MANA].asDouble());
        property->setRadius(info[CCGE_UNIT_COLLIDE_RADIUS].asDouble());
        
        if (!config[CCGE_UNIT_SIZE_MOD].isNull()) {
            property->setSizeMod(config[CCGE_UNIT_SIZE_MOD].asDouble());
        }
        
        property->setLevel(config[CCGE_COMMON_LEVEL].asInt());
        property->setRank(config[CCGE_COMMON_RANK].asInt());
        property->setStars(config[CCGE_COMMON_STARS].asInt());
        property->setAttackRange(config[CCGE_UNIT_ATTACK_RANGE].asDouble());
        
        property->setSizeMod(config[CCGE_UNIT_SIZE_MOD].asDouble());
        
        property->setInfo(info);
    }
}

void EntityPropertyFactory::setBattlePropertyValue(BattleProperty* property,const yhge::Json::Value& config,const yhge::Json::Value& unitInfo)
{
    if (!config.isNull()) {
        
        property->setHealth(unitInfo[CCGE_UNIT_HEALTH].asDouble());
        property->setMana(unitInfo[CCGE_UNIT_MANA].asDouble());
        property->setArmor(unitInfo[CCGE_UNIT_ARMOR].asDouble());
        property->setMagicResistance(unitInfo[CCGE_UNIT_MAGIC_RESISTANCE].asDouble());
        property->setAttackDamage(unitInfo[CCGE_UNIT_ATTACK_DAMAGE].asDouble());
        property->setAbilityPower(unitInfo[CCGE_UNIT_ABILITY_POWER].asDouble());
        property->setAttackSpeed(unitInfo[CCGE_UNIT_ATTACK_SPEED].asDouble());
        property->setCrit(unitInfo[CCGE_UNIT_CRIT].asDouble());
        property->setMagicCrit(unitInfo[CCGE_UNIT_MAGIC_CRIT].asDouble());
        property->setArmorPenetrate(unitInfo[CCGE_UNIT_ARMOR_PENETRATE].asDouble());
        property->setMagicResistanceIgnore(unitInfo[CCGE_UNIT_MAGIC_RESISTANCE_IGNORE].asDouble());
        property->setHit(unitInfo[CCGE_UNIT_HIT].asDouble());
        property->setDodg(unitInfo[CCGE_UNIT_DODG].asDouble());
        property->setHealthRegenerate(unitInfo[CCGE_UNIT_HEALTH_REGENERATE].asDouble());
        property->setManaRegenerate(unitInfo[CCGE_UNIT_MANA_REGENERATE].asDouble());
        property->setHeal(unitInfo[CCGE_UNIT_HEAL].asDouble());
        property->setLifeDrain(unitInfo[CCGE_UNIT_LIFE_DRAIN].asDouble());
        property->setManaCostReduced(unitInfo[CCGE_UNIT_MANA_COST_REDUCED].asDouble());

        int level=config[CCGE_COMMON_LEVEL].asInt();
        int stars=config[CCGE_COMMON_STARS].asInt();
        int rank=config[CCGE_COMMON_RANK].asInt();
        
        float baseValue;
        float growValue;
        
        //str
        baseValue=unitInfo[CCGE_UNIT_BASE_STRENGTH].asDouble();
        growValue=unitInfo[CCGE_UNIT_GROW_STRENGTH].asDouble();
        property->setStrength(baseValue+growValue*stars*level);
        
        //agi
        baseValue=unitInfo[CCGE_UNIT_BASE_AGILITY].asDouble();
        growValue=unitInfo[CCGE_UNIT_GROW_AGILITY].asDouble();
        property->setAgility(baseValue+growValue*stars*level);
        
        //int
        baseValue=unitInfo[CCGE_UNIT_BASE_INTELLECT].asDouble();
        growValue=unitInfo[CCGE_UNIT_GROW_INTELLECT].asDouble();
        property->setIntellect(baseValue+growValue*stars*level);
        
        //TODO add rank property
        
        //TODO add equip property
    }
}

void EntityPropertyFactory::setMovePropertyValue(MoveProperty* property,const yhge::Json::Value& config)
{
    if (!config.isNull()) {
        CCPoint pos;
        pos.x=config[CCGE_COMMON_X].asDouble();
        pos.y=config[CCGE_COMMON_Y].asDouble();
        
        property->setPosition(pos);
        
        property->setDirection(config[CCGE_UNIT_CAMP].asInt());
    }
}

void EntityPropertyFactory::setSkillPropertyValue(SkillProperty* property,const yhge::Json::Value& value)
{
    CCAssert(property!=NULL, "EntityPropertyFactory::setSkillPropertyValue property is null");
    
    if (!value.isNull()) {

    }
}

NS_CC_GE_END
