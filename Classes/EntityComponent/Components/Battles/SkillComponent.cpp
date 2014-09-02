#include "SkillComponent.h"
#include "Game.h"
#include "Consts/GameMessage.h"
#include "Consts/GameDefine.h"
#include "Consts/DataDefine.h"
#include "Consts/PropertyDefine.h"
#include "Consts/AnimationDefine.h"
#include "EntityComponent/GameEntity.h"
#include "DamageComponent.h"


USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

SkillComponent::SkillComponent()
:GameComponent("SkillComponent")
,m_cdRemaining(0)
,m_casting(false)
,m_target(NULL)
,m_currentPhaseIdx(0)
,m_currentPhase(NULL)
,m_currentPhaseElapsed(0)
,m_nextEventIdx(NULL)
,m_nextEvent(NULL)
,m_attackCounter(NULL)
,m_maxRangeSq(0)
,m_minRangeSq(0)
,m_update(true)
,m_canCast(false)
,m_canCastTick(-1)
,m_battleUpdateManager(NULL)
,m_battleProperty(NULL)
,m_unitProperty(NULL)
,m_moveProperty(NULL)
{
    
}

SkillComponent::~SkillComponent()
{
    CC_SAFE_DELETE(m_currentPhase);
    CC_SAFE_DELETE(m_nextEvent);
}

void SkillComponent::setup()
{
    GameComponent::setup();

    if (m_maxRangeSq==0) {
        m_maxRangeSq=MAXFLOAT;
    }
    
    m_battleUpdateManager=Game::getInstance()->getEngine()->getBattleUpdateManager();
    
    m_battleProperty=static_cast<BattleProperty*>(m_owner->getProperty(CCGE_PROPERTY_BATTLE));
    m_unitProperty=static_cast<UnitProperty*>(m_owner->getProperty(CCGE_PROPERTY_UNIT));
    m_moveProperty=static_cast<MoveProperty*>(m_owner->getProperty(CCGE_PROPERTY_MOVE));
    
    rebuildPhaseList(m_unitProperty->getPuppetFromInfo());
}

void SkillComponent::cleanup()
{
    GameComponent::cleanup();
}

bool SkillComponent::registerMessages()
{
    if(Component::registerMessages()){
    
        yhge::MessageManager* messageManager=this->getMessageManager();
        
//        messageManager->registerReceiver(messageManager->getGlobalObject(), MSG_ENTITY_DIE, m_owner, message_selector(SkillComponent::onEntityDie),this);
        
        return true;
    }
    return false;
}

void SkillComponent::cleanupMessages()
{
    yhge::MessageManager* messageManager=this->getMessageManager();
    
//    messageManager->removeReceiver(messageManager->getGlobalObject(), MSG_ENTITY_DIE, m_owner);
    
    Component::cleanupMessages();
}

void SkillComponent::update(float delta)
{
    if (m_casting){
        //attck phase
        m_currentPhaseElapsed+=delta;
        
        while (m_nextEvent && m_nextEvent->getTime()< m_currentPhaseElapsed) {
            
            if (m_nextEvent->getType()==kSkillPhaseEventAttack) {
                onAttackFrame();
                
            }
            
            int idx=m_nextEventIdx+1;
            
            if (idx<m_currentPhase->getEventList().size()) {
                m_nextEventIdx=idx;
                
                SkillPhaseEvent* event=new SkillPhaseEvent();
                *event=m_currentPhase->getEvent(idx);
                setNextEvent(event);
                
            }else{
                m_nextEvent=NULL;
                m_nextEventIdx=-1;
                
                //next phase
                
                onPhaseFinished();
            }
        }
        
    }else{
        m_cdRemaining-=delta;
    }
}

bool SkillComponent::canCastWithTarget(GameEntity* target)
{
    if (m_canCastTick==m_battleUpdateManager->getTicks()) {
        return m_canCast;
    }
    
    m_canCastTick=m_battleUpdateManager->getTicks();
    
    m_canCast=false;
    
    if (m_info[CCGE_SKILL_COST_MP].asDouble()>m_unitProperty->getMana()) {
        return false;
    }
    
    if (m_cdRemaining>0) {
        return false;
    }
    
    //TODO check buff
    
    //check distance
    MoveProperty* targetMoveProperty=static_cast<MoveProperty*>(target->getProperty(CCGE_PROPERTY_MOVE));
    
    float distanceSQ=(targetMoveProperty->getPosition()-m_moveProperty->getPosition()).getLengthSq();
    if (distanceSQ>m_maxRangeSq) {
        return false;
    }
    
    if (distanceSQ<m_minRangeSq) {
        return false;
    }
    
    m_canCast=true;
    
    return true;
}

bool SkillComponent::willCast()
{
    return true;
}


bool SkillComponent::isManual()
{
    return m_info[CCGE_SKILL_MANUAL].asBool();
}

void SkillComponent::cast(GameEntity* target)
{
    //TODO check alive
    
    //TODO change state
    CCLOG("skill cast:%d",m_info[CCGE_SKILL_ID].asInt());
    start(target);
}

void SkillComponent::start(GameEntity* target)
{
    setTarget(target);
    
    m_cdRemaining=m_info[CCGE_SKILL_CD].asDouble();
    m_casting=true;
    m_attackCounter=0;
    
    startPhase(0);
    
    m_update=true;
    
    m_unitProperty->setGlobalCd(m_info[CCGE_SKILL_GLOBAL_CD].asDouble());
    
    float mp=m_unitProperty->getMana();
    
    //TODO use reduce cost mp
    m_unitProperty->setMana(mp-m_info[CCGE_SKILL_COST_MP].asDouble());
    
    //TODO run launch effect
    
    
    //run
}

void SkillComponent::finish()
{
    if (m_unitProperty->isManuallyCasting()) {
        m_unitProperty->setManuallyCasting(false);
    }
    
    m_casting=false;
    //remove current skill
    Game::getInstance()->getEngine()->getSkillManager()->setEntityCurrentSkill(m_owner->m_uID, NULL);
    //TODO set owner idle
    
}

void SkillComponent::interrupt()
{
    if(m_attackCounter==0){
        m_cdRemaining=m_info[CCGE_SKILL_CD].asDouble()*0.5;
        m_unitProperty->setGlobalCd(m_info[CCGE_SKILL_GLOBAL_CD].asDouble()*0.5);
    }
    
    finish();
}

void SkillComponent::onAttackFrame()
{
    //TODO parse unfreeze manually skill
    CCLOG("on Attack Frame");
    ++m_attackCounter;
    
    if (m_info[CCGE_SKILL_TARGET_TYPE].asInt()==kSkillTargetTypeRandom || m_target==NULL ||
        !(static_cast<UnitProperty*>(m_target->getProperty(CCGE_PROPERTY_UNIT)))->isAlive()) {
        //TODO select new target
    }
    
    if (!m_target) {
        return;
    }
    
    int trackType=m_info[CCGE_SKILL_TRACK_TYPE].asInt();
    
    switch (trackType) {
        case kSkillTrackTypeNone:{
            //show effect
            MoveProperty* moveProperty=static_cast<MoveProperty*>(m_target->getProperty(CCGE_PROPERTY_MOVE));
            takeEffectAt(moveProperty->getPosition());
            break;
        }
        case kSkillTrackTypeProjectile:
            //show projectile
            break;
        case kSkillTrackTypeChain:
            //show chain
            break;
        default:
            break;
    }
    //攻击后回魔法
    m_unitProperty->setMana(m_unitProperty->getMana()+ m_info[CCGE_SKILL_GAIN_MP].asDouble() * Game::getInstance()->getEngine()->getBattleManager()->getManaBonus());
    //是否移动
    float moveForward=m_info[CCGE_SKILL_MOVE_FORWARD].asDouble();
    if (moveForward!=0) {
        CCPoint pos=m_moveProperty->getPosition();
        pos.x+= moveForward* m_moveProperty->getDirection();
        m_moveProperty->setPosition(pos);
    }
}

void SkillComponent::takeEffectAt(const CCPoint& location,GameEntity* source)
{
    int aoeOrigin=m_info[CCGE_SKILL_AOE_ORIGIN].asInt();
    
    int direction=m_moveProperty->getDirection();
    
    CCPoint origin=location;
    
    if (aoeOrigin==kSkillAOEOriginSelf) {
        origin=m_moveProperty->getPosition();
    }
    
    origin.x+=m_info[CCGE_SKILL_X_SHIFT].asDouble()* direction;
    
    if (aoeOrigin) {

        int aoeShape=m_info[CCGE_SKILL_AOE_SHAPE].asInt();
        float arg1=m_info[CCGE_SKILL_SHAPE_ARG1].asDouble();
        float arg2=m_info[CCGE_SKILL_SHAPE_ARG2].asDouble();
        
        int damageType=m_info[CCGE_SKILL_DAMAGE_TYPE].asInt();
        
        BattleManager* battleManager=Game::getInstance()->getEngine()->getBattleManager();
        
        GameEntityVector unitList=battleManager->getAliveUnitsOfCamp(affectedCamp());
        
    
        GameEntity* entity=NULL;

        CCPoint dis;
        
        for (GameEntityVector::iterator iter=unitList.begin(); iter!=unitList.end(); ++iter) {
            
            entity=*iter;
            
            if ( (damageType==kSkillDamageTypePhysical || damageType==kSkillDamageTypeMagic) && entity==m_owner) {
                //can't attack self
            }else{
                MoveProperty* moveProperty=static_cast<MoveProperty*>(entity->getProperty(CCGE_PROPERTY_MOVE));
                
                dis=moveProperty->getPosition()-origin;
                
                dis.x*=direction;
                
                if (testPointInShape(dis,aoeShape,arg1,arg2)) {
                    takeEffectOn(entity);
                }
            }
        }
        
    }else{
        takeEffectOn(m_target,source);
    }
    
    //TODO play point effect
}

void SkillComponent::takeEffectOn(GameEntity* target,GameEntity* source)
{
    GameEntity* caster= static_cast<GameEntity*>(m_owner);
    
    source=source==NULL?caster:source;
    
    UnitProperty* targetUnitProperty=static_cast<UnitProperty*>(m_target->getProperty(CCGE_PROPERTY_UNIT));
    BattleProperty* targetBattleProperty=static_cast<BattleProperty*>(m_target->getProperty(CCGE_PROPERTY_BATTLE));
    
    UnitProperty* sourceUnitProperty=source==m_owner?m_unitProperty:static_cast<UnitProperty*>(source->getProperty(CCGE_PROPERTY_UNIT));
    
    if (!targetUnitProperty->isAlive() || (targetUnitProperty->isManuallyCasting() && targetUnitProperty->getCamp()!=sourceUnitProperty->getCamp())) {
        return;
    }
    
    float power=getPower(source, target);
    
    int damageType=m_info[CCGE_SKILL_DAMAGE_TYPE].asInt();
    int affectFieldType=m_info[CCGE_SKILL_AFFECT_FIELD].asInt();
    
    float dmg=0;
    
    switch (damageType) {
        case kSkillDamageTypeHeal:{
            float heal=affectFieldType==kBattleAttributeHP?m_battleProperty->getHeal():0;
            power=power*(1+heal/100);
            
            //TODO take heal
            
            break;
        }
        case kSkillDamageTypePhysical:{
            
            if (!m_info[CCGE_SKILL_NO_DODGE].asBool()) {
                float dodg=MAX(0, targetBattleProperty->getDodg()-m_battleProperty->getHit());
                float prob=dodg/(100+dodg);
                
                float dice=rand();
                
                bool hit=prob<=dice;
                
                if (!hit) {
                    //TODO take hit miss
                    
                    //TODO show miss
                    
                    return;
                }
            }
            
            break;
        }
        default:
            break;
    }
    
    dmg=getDamage(target, power, damageType, affectFieldType, source, m_info[CCGE_SKILL_CRIT_RATIO].asDouble()/100);
    
    if (dmg==0) {
        return;
    }
    
    float ldr=m_info[CCGE_SKILL_LIFE_DRAIN_RATIO].asDouble();
    
    if (0<ldr) {
        float lfs=m_battleProperty->getLifeDrain();
        float heal=dmg*lfs/(100+lfs+targetUnitProperty->getLevel())*ldr*0.01;
        
        if (heal>1) {
            //TODO take heal
        }
    }
    
    //TODO parse buff
    
    //TODO show impact effect
}

void SkillComponent::onPhaseFinished()
{
    CCLOG("tt:%d,%lu",m_currentPhaseIdx,m_phaseList.size());
    if (m_currentPhaseIdx<m_phaseList.size()-1) {
        startPhase(m_currentPhaseIdx+1);
    }else{
        //attack finished
        finish();
    }
}

void SkillComponent::rebuildPhaseList(const std::string& puppetName)
{
    m_phaseList.clear();
    
    Json::Value actions=m_info[CCGE_SKILL_ACTIONS];
    
    std::string animName;
    float duration=0.916667f;
    for (int i=0; i<actions.size(); ++i) {
        animName=actions[i]["name"].asString();
        
        //TODO get duration from AnimDuration
        
        
        //TODO look up AnimAtkFrame for events;
        
        //TEST
        SkillPhaseEvent e;
        e.setX(357.3);
        e.setY(991.75);
        e.setTime(0.33333);
        e.setType(1);
        e.setAction(animName);
        
        std::vector<SkillPhaseEvent> eventList;
        
        eventList.push_back(e);
        
        SkillPhase phase;
        phase.setDuration(duration);
        phase.setActionName(animName);
        phase.setEventList(eventList);
        
        m_phaseList.push_back(phase);
    }
}

void SkillComponent::startPhase(int idx)
{
    m_currentPhaseIdx=idx;
    m_currentPhaseElapsed=0;
    SkillPhase* phase=new SkillPhase();
    *phase=m_phaseList[idx];
    setCurrentPhase(phase);
    
    m_nextEventIdx=0;
    
    SkillPhaseEvent* event=new SkillPhaseEvent();
    *event=m_currentPhase->getEvent(m_nextEventIdx);
    setNextEvent(event);
    
    //改变角色动作
    CCDictionary* data=new CCDictionary();
    data->setObject(CCString::create(CCGE_ANIMATION_ATTACK), CCGE_ANIMATION_NAME);
    data->setObject(CCInteger::create(kEightDirctionRightBottom), CCGE_ANIMATION_DIRECTION);
    MessageManager::defaultManager()->dispatchMessage(MSG_CHANGE_ANIMATION, NULL, m_owner,data);
}

int SkillComponent::affectedCamp()
{
    return m_unitProperty->getFoecamp() * m_info[CCGE_SKILL_AFFECTED_CAMP].asInt()* -1;
}

int SkillComponent::targetCamp()
{
    return m_unitProperty->getFoecamp() * m_info[CCGE_SKILL_TARGET_CAMP].asInt()* -1;
}

float SkillComponent::getPower(GameEntity* source,GameEntity* target)
{
    float multiplier=m_info[CCGE_SKILL_PLUS_RATIO].asDouble();
    float basicNum =m_info[CCGE_SKILL_BASIC_NUM].asDouble();
    
    int plusAttrType=m_info[CCGE_SKILL_PLUS_ATTR].asInt();
    float baseAttr=m_battleProperty->getAttributeByType(plusAttrType);
    return multiplier*baseAttr+basicNum;
}

float SkillComponent::getDamage(GameEntity* target,float power,int damageType,int field,GameEntity* source,float critMod)
{
    DamageComponent* targetDamageComponent=static_cast<DamageComponent*>(target->getComponent("DamageComponent"));
    
    return targetDamageComponent->takeDamage(power, damageType, field, source,critMod);
}

bool SkillComponent::testPointInShape(const CCPoint& pos,int shape,float arg1,float arg2)
{
    bool ret=false;
    
    switch (shape) {
        case kSkillAOEShapeRectangle:
            ret= pos.x >= 0 && arg1 >= pos.x && pos.y >= -arg2 * 0.5 && pos.y <= arg2 * 0.5;
            break;
        case kSkillAOEShapeCircle:
            ret=pos.x * pos.x + pos.y * pos.y <= arg1 * arg1;
            break;

        case kSkillAOEShapeHalfCircle:
            ret= pos.x >= 0 && pos.x * pos.x + pos.y * pos.y <= arg1 * arg1;
            break;

        case kSkillAOEShapeQuarterCircle:
            ret=pos.x >= 0 && pos.y <= pos.x && pos.y >= -pos.x && pos.x >= 0 && pos.x * pos.x + pos.y * pos.y <= arg1 * arg1;
            break;
        default:
            break;
    }
    
    return ret;
}

void SkillComponent::setTarget(GameEntity* target)
{
    CC_SAFE_RETAIN(target);
    CC_SAFE_RELEASE(m_target);
    m_target = target;
}

NS_CC_GE_END

