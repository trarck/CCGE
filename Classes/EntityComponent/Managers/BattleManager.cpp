#include "BattleManager.h"
#include "Consts/GameDefine.h"
#include "Consts/DataDefine.h"
#include "Consts/PropertyDefine.h"
#include "Game.h"
#include "Services/ServiceFactory.h"
#include "EntityComponent/Properties/BuffEffects.h"
#include "EntityComponent/Components/Battles/StateComponent.h"

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

BattleManager::BattleManager()
:m_enabled(true)
,m_aliveAllianceCount(0)
,m_aliveEnemyCount(0)
,m_deadAllianceCount(0)
,m_deadEnemyCount(0)
,m_arenaMode(false)
,m_crusadeMode(false)
,m_excavateMode(false)
,m_guildInstanceMode(false)
,m_replayMode(false)
,m_stageRect(CCRectMake(0, -120, 800, 240))
,m_manaBonus(1.0f)
{
    YHDEBUG("BattleManager create");
}

BattleManager::~BattleManager()
{
    YHDEBUG("BattleManager destroy");
}

bool BattleManager::init()
{
    if (ECManager::init()) {
        
        reset();
        
        return true;
    }
    
    return false;
}

void BattleManager::reset()
{
    resetUnits();
    resetAliveUnits();
    
    m_aliveAllianceCount=0;
    m_aliveEnemyCount=0;
    m_deadAllianceCount=0;
    m_deadEnemyCount=0;
    
    m_arenaMode=false;
    m_crusadeMode=false;
    m_excavateMode=false;
    m_replayMode=false;
    m_guildInstanceMode=false;
    
    //清除操作列表
    m_oprationList.clear();
}

void BattleManager::resetUnits()
{
    m_units.clear();
}

void BattleManager::resetAliveUnits()
{
    m_aliveUnits.clear();
    
    m_aliveUnits[kCampPlayer]=GameEntityVector();
    m_aliveUnits[kCampEnemy]=GameEntityVector();
    m_aliveUnits[kCampBoth]=GameEntityVector();
}

void BattleManager::resetStage()
{
    
}

void BattleManager::addUnit(GameEntity* entity)
{
    m_units.push_back(entity);
    
    //TODO if alive then add to alive list
    UnitProperty* unitProperty=static_cast<UnitProperty*>(entity->getProperty(CCGE_PROPERTY_UNIT));
    int camp=unitProperty->getCamp();
    
    if(unitProperty->isAlive()){
        m_aliveUnits[camp].push_back(entity);
        if (camp==kCampPlayer) {
            ++m_aliveAllianceCount;
        }else if (camp==kCampEnemy){
            ++m_aliveEnemyCount;
        }
    }else{
        if (camp==kCampPlayer) {
            ++m_deadAllianceCount;
        }else if (camp==kCampEnemy){
            ++m_deadEnemyCount;
        }
    }
}

//进入关卡
void BattleManager::enterStage(yhge::Json::Value& stageInfo,HeroVector& heroList,bool isBot,int startWaveId)
{
    resetStage();
    
    setupSelfEntities(heroList,isBot);
    
}

//进入竞技场
void BattleManager::enterArena(HeroVector& heroList,HeroVector& enemyList,bool heroIsBot,bool enemyIsBot)
{
    resetStage();
    
    setupSelfEntities(heroList,heroIsBot);
    
    setupEnemyEntities(enemyList, enemyIsBot);
}

//进入远程

void BattleManager::enterCrusade(HeroVector& heroList,HeroVector& enemyList,bool enemyisBot,yhge::Json::Value& selfCrusade,yhge::Json::Value& enemyCrusade,int stageId)
{
    
}

//进入矿场
void BattleManager::enterExcavate(HeroVector& heroList,HeroVector& enemyList,bool enemyisBot,yhge::Json::Value& selfDynaList,yhge::Json::Value& enemyDynaList,int stageId)
{
    
}

//初始化己方战斗单位
void BattleManager::setupSelfEntities(HeroVector& heroList,bool isBot)
{
    //short hero by attack range
    heroList=sortEntity(heroList);
    
    int i=0;
    float x=0,y=0;
    
    for (HeroVector::iterator iter=heroList.begin(); iter!=heroList.end(); ++iter) {
        x=i*-80;
        y=i&1?-40:40;
        (*iter)["position_x"]=x;
        
        (*iter)["position_y"]=y;
        
//        CCLOG("pos:%d,%f,%f",i,x,y);
        
        ++i;
        
        GameEntity* heroEntity=createEntity(*iter);
        
        if (heroEntity) {
            
            addUnit(heroEntity);
            
            
        }else{
            CCAssert(false, "BattleManager::setupSelfEntities create entity faile");
        }
    }
}

// 初始化敌方战斗单位
void BattleManager::setupEnemyEntities(HeroVector& heroList,bool isBot)
{
    heroList=sortEntity(heroList);
    
    int i=0;
    for (HeroVector::iterator iter=heroList.begin(); iter!=heroList.end(); ++iter) {

        (*iter)["position_x"]=800+i*80;
        
        (*iter)["position_y"]=i&1?-40:40;
        
        ++i;
        
        GameEntity* heroEntity=createEntity(*iter);
        
        if (heroEntity) {
            
            addUnit(heroEntity);
        
        }else{
            CCAssert(false, "BattleManager::setupSelfEntities create entity faile");
        }
    }
}


HeroVector BattleManager::sortEntity(const HeroVector& entityList)
{
    HeroVector sortedList;

    DataFactory* dataFactory=Game::getInstance()->getDataFactory();
    UnitDAO* unitDAO=dataFactory->getUnitDAO();
    SkillDAO* skillDAO=dataFactory->getSkillDAO();
    CharacterDAO* characterDAO=dataFactory->getCharacterDAO();
    
    int entityId=0;
    
    //calc attack range
    std::map<int, float> entityRange;
    
    for (HeroVector::const_iterator iter=entityList.begin();iter!=entityList.end(); ++iter) {
        
        entityId=(*iter)["id"].asInt();
        
        Json::Value characterConfig=characterDAO->getDataById(entityId);
        
        int unitId=characterConfig[CCGE_PLAYER_UNIT_ID].asInt();
        
        Json::Value unitProto=unitDAO->getDataById(unitId);

        
        int baseSkillId=unitProto["basic_skill"].asInt();
        Json::Value skillProto=skillDAO->getDataById(baseSkillId);
        float attackRange=skillProto["max_range"].asDouble();
        
        entityRange[entityId]=attackRange;
    }
    
    int innerEntityId=0;
    float attackRange=0,innerAttackRange=0;
    bool haveInserted=false;
    
    for (HeroVector::const_iterator iter=entityList.begin();iter!=entityList.end(); ++iter) {
        
        entityId=(*iter)["id"].asInt();
        attackRange=entityRange[entityId];
        haveInserted=false;
        
        for (HeroVector::iterator inner=sortedList.begin(); inner!=sortedList.end(); ++inner) {
            innerEntityId=(*inner)["id"].asInt();
            innerAttackRange=entityRange[innerEntityId];
            
            if (attackRange<innerAttackRange) {
                sortedList.insert(inner, *iter);
                haveInserted=true;
                break;
            }
        }
        
        if (!haveInserted) {
            sortedList.push_back(*iter);
        }
    }
    
    return sortedList;
}

GameEntity* BattleManager::createEntity(yhge::Json::Value& hero)
{
    GameEntity* entity=NULL;
    
    EntityFactory* entityFactory=Game::getInstance()->getEngine()->getEntityFactory();
    DataFactory* dataFactory=Game::getInstance()->getDataFactory();
    
    UnitService* unitService=ServiceFactory::getInstance()->getUnitService();
    CharacterDAO* characterDAO=dataFactory->getCharacterDAO();
    
    UnitDAO* unitDAO=dataFactory->getUnitDAO();
    SkillDAO* skillDAO=dataFactory->getSkillDAO();
    
    int entityId=hero["id"].asInt();
    
    float x=hero["position_x"].asDouble();
    float y=hero["position_y"].asDouble();
    int camp=hero["camp"].asInt();
    
    entity=entityFactory->createEntity(entityId);
    

    
    Json::Value characterConfig=characterDAO->getDataById(entityId);
    
    int unitId=characterConfig[CCGE_PLAYER_UNIT_ID].asInt();
    float scale=characterConfig[CCGE_PLAYER_SCALE].asDouble();
    int level=characterConfig[CCGE_PLAYER_LEVEL].asInt();
    int rank=2;
    int stars=3;

    //设置单位属性
    Json::Value unitConfig;
    Json::Value unitInfo=unitDAO->getDataById(unitId);
    
    unitConfig[CCGE_UNIT_CAMP]=camp;
    unitConfig[CCGE_COMMON_LEVEL]=level;
    unitConfig[CCGE_COMMON_RANK]=rank;
    unitConfig[CCGE_COMMON_STARS]=stars;
    unitConfig[CCGE_UNIT_SIZE_MOD]=scale;
    
    //get attack range for sort hero
    int baseSkillId=unitInfo[CCGE_UNIT_BASIC_SKILL].asInt();
    Json::Value skillProto=skillDAO->getDataById(baseSkillId);
    float attackRange=skillProto[CCGE_SKILL_MAX_RANGE].asDouble();
    unitConfig[CCGE_UNIT_ATTACK_RANGE]=attackRange;
    
    entityFactory->getEntityPropertyFactory()->addUnitProperty(entity, unitInfo, unitConfig);

    //设置战斗属性
    Json::Value battleConfig;
    battleConfig[CCGE_COMMON_LEVEL]=level;
    battleConfig[CCGE_COMMON_RANK]=rank;
    battleConfig[CCGE_COMMON_STARS]=stars;
    
    entityFactory->getEntityPropertyFactory()->addRealtimeBattleProperty(entity,unitInfo,battleConfig);
    
    //设置移动属性
    Json::Value moveConfig;
    moveConfig[CCGE_COMMON_X]=x;
    moveConfig[CCGE_COMMON_Y]=y;
    moveConfig[CCGE_UNIT_CAMP]=camp;
    
    entityFactory->getEntityPropertyFactory()->addMoveProperty(entity, moveConfig);
    
    //add buff effects
    entityFactory->getEntityPropertyFactory()->addBuffEffectsProperty(entity);
    
    
    //添加组件
    entityFactory->addRealtimeBattleComponents(entity);
    
    //构建entity属性
    rebuildEntity(entity);
    
    return entity;
}

void BattleManager::rebuildEntity(GameEntity* entity)
{
    UnitProperty* unitProperty=static_cast<UnitProperty*>(entity->getProperty(CCGE_PROPERTY_UNIT));
    BattleProperty* battleProperty=static_cast<BattleProperty*>(entity->getProperty(CCGE_PROPERTY_BATTLE));
    
    GameEngine* gameEngine=static_cast<GameEngine*>(m_engine);
    
    //base
    gameEngine->getEntityFactory()
                ->getEntityPropertyFactory()
                    ->setBattlePropertyValue(battleProperty,
                             unitProperty->getInfo(),
                             unitProperty->getLevel(),unitProperty->getStars(),unitProperty->getRank());
    
    //TODO add equips attribute
    
    //被动技能加层//
    SkillManager* skillManager=gameEngine->getSkillManager();
    Json::Value& passiveSkillList=skillManager->getEntityPassiveSkillInfos(entity->m_uID);
    if (!passiveSkillList.isNull()) {
        int passiveAttr=0;
        float baseNumber=0;
        float val=0;
        for (int i=0; i<passiveSkillList.size(); ++i) {
            Json::Value& skillInfo=passiveSkillList[i];
            passiveAttr=skillInfo[CCGE_SKILL_PASSIVE_ATTR].asInt();
            baseNumber=skillInfo[CCGE_SKILL_BASIC_NUM].asDouble();
            val=battleProperty->getAttributeByType(passiveAttr)+baseNumber;
            battleProperty->setAttributeByType(passiveAttr, val);
        }
    }
    
    if (m_enabled) {
        
        int passiveAttr=0;
        float baseNumber=0;
        float val=0;
        
        //处理己方光环加层//
        GameEntityVector& campUnits=m_aliveUnits[unitProperty->getCamp()];
        for (GameEntityVector::iterator iter=campUnits.begin(); iter!=campUnits.end(); ++iter) {
            Json::Value& auraSkillList=skillManager->getEntityAuraSkillInfos((*iter)->m_uID);
            
            for (int i=0; i<auraSkillList.size(); ++i) {
                //TODO check hero tag
                
                Json::Value& skillInfo=auraSkillList[i];
                passiveAttr=skillInfo[CCGE_SKILL_PASSIVE_ATTR].asInt();
                baseNumber=skillInfo[CCGE_SKILL_BASIC_NUM].asDouble();
                val=battleProperty->getAttributeByType(passiveAttr)+baseNumber;
                battleProperty->setAttributeByType(passiveAttr, val);
            }
        }
        
        //处理敌方光环加层//
        int camp= unitProperty->getCamp()==kCampPlayer?kCampEnemy:kCampPlayer;
        GameEntityVector& enemyUnits=m_aliveUnits[camp];
        
        for (GameEntityVector::iterator iter=enemyUnits.begin(); iter!=enemyUnits.end(); ++iter) {
            Json::Value& enemyAuraSkillList=skillManager->getEntityNegativeAuraSkillInfos((*iter)->m_uID);
            
            for (int i=0; i<enemyAuraSkillList.size(); ++i) {
                //TODO check hero tag
                
                Json::Value& skillInfo=enemyAuraSkillList[i];
                passiveAttr=skillInfo[CCGE_SKILL_PASSIVE_ATTR].asInt();
                baseNumber=skillInfo[CCGE_SKILL_BASIC_NUM].asDouble();
                val=battleProperty->getAttributeByType(passiveAttr)+baseNumber;
                battleProperty->setAttributeByType(passiveAttr, val);
            }
        }
    }
    
    //重置buff effects
    BuffEffects* buffEffects=static_cast<BuffEffects*>(entity->getProperty(CCGE_PROPERTY_BUFF_EFFECTS));
    buffEffects->reset();
    
    BuffManager* buffManager=gameEngine->getBuffManager();
    
    BuffManager::BuffList& buffList=buffManager->getEntityBuffs(entity->m_uID);
    
    for (BuffManager::BuffList::iterator iter=buffList.begin(); iter!=buffList.end(); ++iter) {
        (*iter)->apply();
    }
    
    //check state
    StateComponent* stateComponent=static_cast<StateComponent*>(entity->getComponent("StateComponent"));
    if (buffEffects->isImmoblilize() && unitProperty->getState()==kUnitStateWalk) {
        stateComponent->idle();
    }
    
    //check current skill
    SkillComponent* currentSkill=skillManager->getEntityCurrentSkill(entity->m_uID);
    if (buffEffects->isStun()) {
        stateComponent->hurt();
    }else if(currentSkill){
        int damageType=currentSkill->getInfo()[CCGE_SKILL_DAMAGE_TYPE].asInt();
        if ((damageType==kSkillDamageTypePhysical && buffEffects->isDisarm()) || (damageType==kSkillDamageTypeMagic && buffEffects->isSilence())) {
            currentSkill->interrupt();
        }
    }
    
    //处理魅惑效果//
    unitProperty->setFoecamp(buffEffects->isEnchanted()?unitProperty->getCamp():-unitProperty->getCamp());
    
    
    //处理三维对属性的加层
    //STR
    battleProperty->setHeal(battleProperty->getHeal()+battleProperty->getStrength()*BattleProperty::StrengthToHealth);
    battleProperty->setArmor(battleProperty->getArmor()+battleProperty->getStrength()*BattleProperty::StrengthToArmor);
    //AGi
    battleProperty->setAttackDamage(battleProperty->getAttackDamage()+battleProperty->getAgility()*BattleProperty::AgilityToAttackDamage);
    battleProperty->setCrit(battleProperty->getCrit()+battleProperty->getAgility()*BattleProperty::AgilityToCrit);
    battleProperty->setArmor(battleProperty->getArmor()+battleProperty->getAgility()*BattleProperty::AgilityToArmor);
    //INT
    battleProperty->setAbilityPower(battleProperty->getAbilityPower()+battleProperty->getIntellect()*BattleProperty::IntellectToAbilityPower);
    battleProperty->setMagicResistance(battleProperty->getMagicResistance()+battleProperty->getIntellect()*BattleProperty::IntellectToMagicResistance);
    
    unitProperty->setHealth(unitProperty->getHealth()*unitProperty->getHealthMod());
    
    battleProperty->setPerDamageMod(unitProperty->getDpsMod());
    
    //处理主属性加层
    int mainAttributeType=unitProperty->getInfo()[CCGE_UNIT_MAIN_ATTRIBUTE].asInt();
    battleProperty->setAttackDamage(battleProperty->getAttackDamage()+battleProperty->getAttributeByType(mainAttributeType));
    
    //TODO 计算战斗力
    
    //检查血量和魔法值是否超出范围
    if (unitProperty->getHealth()>battleProperty->getHealth()) {
        unitProperty->setHealth(battleProperty->getHealth());
    }
    
    if (unitProperty->getMana()>battleProperty->getMana()) {
        unitProperty->setMana(battleProperty->getMana());
    }
}

void BattleManager::onUnitDie(GameEntity* unit,GameEntity* killer)
{
    UnitProperty* unitProperty=static_cast<UnitProperty*>(unit->getProperty(CCGE_PROPERTY_UNIT));
    
    int camp=unitProperty->getCamp();
    
    m_aliveUnits[camp].eraseObject(unit);
    
    if (camp==kCampPlayer) {
        --m_aliveAllianceCount;
        ++m_deadAllianceCount;
    }else if (camp==kCampEnemy){
        --m_aliveEnemyCount;
        ++m_deadEnemyCount;
    }
    
    RendererComponent* rendererComponent=static_cast<RendererComponent*>(unit->getComponent("RendererComponent"));
    rendererComponent->getRenderer()->removeFromParent();

    GameEngine* engine=static_cast<GameEngine*>(m_engine);
    
    engine->getBattleUpdateManager()->removeGroup(unit->m_uID);
    
    unit->cleanup();
}

NS_CC_GE_END
