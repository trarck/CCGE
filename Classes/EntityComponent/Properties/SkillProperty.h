#ifndef CCGE_ENTITYCOMPONENT_PROPERTIES_SKILLPROPERTY_H_
#define CCGE_ENTITYCOMPONENT_PROPERTIES_SKILLPROPERTY_H_

#include "cocos2d.h"
#include <yhge/yhge.h>
#include "CCGEMacros.h"

NS_CC_GE_BEGIN

class GameEntity;

class SkillProperty : public yhge::Property
{
public:
    
    SkillProperty()
    :m_cdRemaining(0)
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
    {
        
    }

    inline void setProto(const yhge::Json::Value& proto)
    {
        m_proto = proto;
    }
    
    inline const yhge::Json::Value& getProto()
    {
        return m_proto;
    }
    
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
    
    inline void setCurrentPhase(CCDictionary* currentPhase)
    {
        CC_SAFE_RETAIN(currentPhase);
        CC_SAFE_RELEASE(m_currentPhase);
        m_currentPhase = currentPhase;
    }
    
    inline CCDictionary* getCurrentPhase()
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
    
    inline void setNextEventIdx(int nextEventIdx)
    {
        m_nextEventIdx = nextEventIdx;
    }
    
    inline int getNextEventIdx()
    {
        return m_nextEventIdx;
    }
    
    inline void setNextEvent(CCDictionary* nextEvent)
    {
        CC_SAFE_RETAIN(nextEvent);
        CC_SAFE_RELEASE(m_nextEvent);
        m_nextEvent = nextEvent;
    }
    
    inline CCDictionary* getNextEvent()
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
    
protected:
    
    yhge::Json::Value m_proto;
    
    //剩余时间
    float m_cdRemaining;
    //正在施放
    bool m_casting;
    //当前目标
    GameEntity* m_target;
    //当前技能施放阶段编号
    int m_currentPhaseIdx;
    //当前技能施放阶段
    CCDictionary* m_currentPhase;
    //当前技能施放阶段用时
    float m_currentPhaseElapsed;
    //下个事件的编号
    int m_nextEventIdx;
    //下个事件
    CCDictionary* m_nextEvent;
    //攻击计数。当攻击到伤害帧，则计数加1.当计数不为0时，不能被打断。
    int m_attackCounter;
    //最大攻击距离平方
    float m_maxRangeSq;
    //最小攻击距离平方
    float m_minRangeSq;
    
};

NS_CC_GE_END

#endif // CCGE_ENTITYCOMPONENT_PROPERTIES_SKILLPROPERTY_H_
