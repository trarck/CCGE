#ifndef CCGE_ENTITYCOMPONENT_COMPONENTS_BATTLES_SKILLCOMPONENT_H_
#define CCGE_ENTITYCOMPONENT_COMPONENTS_BATTLES_SKILLCOMPONENT_H_

#include "cocos2d.h"
#include <yhge/yhge.h>
#include "CCGEMacros.h"
#include "EntityComponent/Managers/BattleUpdateManager.h"

#include "EntityComponent/Properties/BattleProperty.h"
#include "EntityComponent/Properties/UnitProperty.h"
#include "EntityComponent/Properties/MoveProperty.h"

#include "../GameComponent.h"
#include "SkillPhase.h"

NS_CC_GE_BEGIN

/**
 * 技能组件
 * 1.为了简单把普通攻击也做为技能攻击
 * 2.技能的伤害:物理伤害,魔法伤害，神圣伤害
 */
class SkillComponent : public GameComponent
{
public:
    
    SkillComponent();
    
    ~SkillComponent();
    
    /**
     * 设置
     */
    virtual void setup();
    
    /**
     * 消除
     */
    virtual void cleanup();
    
    virtual bool registerMessages();
    
    virtual void cleanupMessages();
    
    virtual void update(float delta);
    
    bool canCastWithTarget(GameEntity* target);
    
    virtual bool willCast();
    
    bool isManual();
    
    void cast(GameEntity* target);
    
    void start(GameEntity* target);
    
    void finish();
    
    void onAttackFrame();
    
    void takeEffectAt(const CCPoint& location,GameEntity* source=NULL);
    
    void takeEffectOn(GameEntity* target,GameEntity* source=NULL);
    
    void onPhaseFinished();
    
protected:
    
    void rebuildPhaseList(const std::string& puppetName);
    
    void startPhase(int idx);
    
    int affectedCamp();
    
    int targetCamp();
    
    float getPower(GameEntity* source,GameEntity* target);
    
    float getDamage(GameEntity* target,float power,int damageType,int field,GameEntity* source,float critMod);
    
    static bool testPointInShape(const CCPoint& pos,int shape,float arg1,float arg2);
    
public:
    
    
    inline void setCdRemaining(float cdRemaining)
    {
        m_cdRemaining = cdRemaining;
    }
    
    inline float getCdRemaining()
    {
        return m_cdRemaining;
    }
    
    inline void setCasting(bool casting)
    {
        m_casting = casting;
    }
    
    inline bool isCasting()
    {
        return m_casting;
    }
    
    inline void setTarget(GameEntity* target);
    
    inline GameEntity* getTarget()
    {
        return m_target;
    }
    
    inline void setCurrentPhaseIdx(int currentPhaseIdx)
    {
        m_currentPhaseIdx = currentPhaseIdx;
    }
    
    inline int getCurrentPhaseIdx()
    {
        return m_currentPhaseIdx;
    }
    
    inline void setCurrentPhase(SkillPhase* skillPhase)
    {
        if(m_currentPhase!=skillPhase){
            CC_SAFE_DELETE(m_currentPhase);
            m_currentPhase=skillPhase;
        }
    }
    
    inline const SkillPhase* getCurrentPhase()
    {
        return m_currentPhase;
    }
    
    inline void setCurrentPhaseElapsed(float currentPhaseElapsed)
    {
        m_currentPhaseElapsed = currentPhaseElapsed;
    }
    
    inline float getCurrentPhaseElapsed()
    {
        return m_currentPhaseElapsed;
    }
    
    inline void setPhaseList(const std::vector<SkillPhase>& phaseList)
    {
        m_phaseList = phaseList;
    }
    
    inline const std::vector<SkillPhase>& getPhaseList()
    {
        return m_phaseList;
    }
    
    inline const SkillPhase& getSkillPhase(int index)
    {
        return m_phaseList[index];
    }
    
    inline void setNextEventIdx(int nextEventIdx)
    {
        m_nextEventIdx = nextEventIdx;
    }
    
    inline int getNextEventIdx()
    {
        return m_nextEventIdx;
    }
    
    inline void setNextEvent(SkillPhaseEvent* skillPhaseEvent)
    {
        if(m_nextEvent!=skillPhaseEvent){
            CC_SAFE_DELETE(m_nextEvent);
            m_nextEvent=skillPhaseEvent;
        }
    }
    
    inline const SkillPhaseEvent* getNextEvent()
    {
        return m_nextEvent;
    }
    
    inline void setAttackCounter(int attackCounter)
    {
        m_attackCounter = attackCounter;
    }
    
    inline int getAttackCounter()
    {
        return m_attackCounter;
    }
    
    inline void setMaxRangeSq(float maxRangeSq)
    {
        m_maxRangeSq = maxRangeSq;
    }
    
    inline float getMaxRangeSq()
    {
        return m_maxRangeSq;
    }
    
    inline void setMinRangeSq(float minRangeSq)
    {
        m_minRangeSq = minRangeSq;
    }
    
    inline float getMinRangeSq()
    {
        return m_minRangeSq;
    }
    
    inline void setUpdate(bool update)
    {
        m_update = update;
    }
    
    inline bool isUpdate()
    {
        return m_update;
    }
    
    inline void setInfo(const yhge::Json::Value& info)
    {
        m_info = info;
    }
    
    inline const yhge::Json::Value& getInfo()
    {
        return m_info;
    }

protected:
    
    //剩余时间
    float m_cdRemaining;
    //正在施放
    bool m_casting;
    //当前目标
    GameEntity* m_target;
    //当前技能施放阶段编号
    int m_currentPhaseIdx;
    //当前技能施放阶段
    SkillPhase* m_currentPhase;//TODO use smart pointer
    //当前技能施放阶段用时
    float m_currentPhaseElapsed;
    
    std::vector<SkillPhase> m_phaseList;
    //下个事件的编号
    int m_nextEventIdx;
    //下个事件
    SkillPhaseEvent* m_nextEvent;//weak ref
    //攻击计数。当攻击到伤害帧，则计数加1.当计数不为0时，不能被打断。
    int m_attackCounter;
    //最大攻击距离的平方
    float m_maxRangeSq;
    //最小攻击距离的平方
    float m_minRangeSq;
    //是否在更新
    bool m_update;
    
    //在同一个帧内，判断技能能否施放，直接返回
    bool m_canCast;
    int m_canCastTick;
    
    
    yhge::Json::Value m_info;
    
    BattleUpdateManager* m_battleUpdateManager;
    
    BattleProperty* m_battleProperty;
    UnitProperty* m_unitProperty;
    MoveProperty* m_moveProperty;
};

NS_CC_GE_END

#endif //CCGE_ENTITYCOMPONENT_COMPONENTS_BATTLES_SKILLCOMPONENT_H_
