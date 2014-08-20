#ifndef CCGE_ENTITYCOMPONENT_COMPONENTS_BATTLES_SKILLPHASE_H_
#define CCGE_ENTITYCOMPONENT_COMPONENTS_BATTLES_SKILLPHASE_H_

#include "cocos2d.h"
#include <yhge/yhge.h>
#include "CCGEMacros.h"

NS_CC_GE_BEGIN

class SkillPhaseEvent
{
public:
    
    SkillPhaseEvent()
    :m_x(0.0f)
    ,m_y(0.0f)
    ,m_time(0.0f)
    ,m_type(0)
    ,m_action("")
    {
        
    }
    
    SkillPhaseEvent& operator=(const SkillPhaseEvent& other)
    {
        if (this != &other) {
            m_x=other.m_x;
            m_y=other.m_y;
            m_time=other.m_time;
            m_type=other.m_type;
            m_action=other.m_action;
        }
        return *this;
    }
    
    inline void setX(float x)
    {
        m_x = x;
    }
    
    inline float getX()
    {
        return m_x;
    }
    
    inline void setY(float y)
    {
        m_y = y;
    }
    
    inline float getY()
    {
        return m_y;
    }
    
    inline void setTime(float time)
    {
        m_time = time;
    }
    
    inline float getTime()
    {
        return m_time;
    }
    
    inline void setType(int type)
    {
        m_type = type;
    }
    
    inline int getType()
    {
        return m_type;
    }
    
    inline void setAction(const std::string& action)
    {
        m_action = action;
    }
    
    inline const std::string& getAction()
    {
        return m_action;
    }
    
private:
    float m_x;
    float m_y;
    float m_time;
    int m_type;
    std::string m_action;
};

class SkillPhase
{
public:
    
    SkillPhase()
    :m_duration(0)
    ,m_actionName("")
    {
        
    }
    
    SkillPhase& operator=(const SkillPhase& other)
    {
        if (this != &other) {
            m_duration=other.m_duration;
            m_actionName=other.m_actionName;
            m_eventList=other.m_eventList;
        }
        return *this;
    }
    
    inline void setDuration(float duration)
    {
        m_duration = duration;
    }
    
    inline float getDuration()
    {
        return m_duration;
    }
    
    inline void setActionName(const std::string& actionName)
    {
        m_actionName = actionName;
    }
    
    inline const std::string& getActionName()
    {
        return m_actionName;
    }
    
    inline void setEventList(const std::vector<SkillPhaseEvent>& eventList)
    {
        m_eventList = eventList;
    }
    
    inline const std::vector<SkillPhaseEvent>& getEventList()
    {
        return m_eventList;
    }
    
    inline const SkillPhaseEvent& getEvent(int idx)
    {
        return m_eventList[idx];
    }

private:
    float m_duration;
    std::string m_actionName;
    std::vector<SkillPhaseEvent> m_eventList;
};

typedef yhge::smart_ptr::shared_ptr<SkillPhaseEvent>  SkillPhaseEventPtr;
typedef yhge::smart_ptr::shared_ptr<SkillPhase>  SkillPhasePtr;

NS_CC_GE_END

#endif // CCGE_ENTITYCOMPONENT_COMPONENTS_BATTLES_SKILLPHASE_H_
