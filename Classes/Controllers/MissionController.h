#ifndef CCGE_CONTROLLERS_MissionController_H_
#define CCGE_CONTROLLERS_MissionController_H_

#include <yhge/yhge.h>
#include <yhmvc/yhmvc.h>
#include <yhge/isometric.h>
#include "CCGEMacros.h"
#include "BaseController.h"
#include "StepGameWorldController.h"
#include "Layers/GameWorld.h"

NS_CC_GE_BEGIN

/**
 * 单独的。
 * 由Scene来组合controller。
 * 可以添加其它controller来作为显示内容
 * 由于结构简单不容易出错。
 */
class MissionController:public BaseController
{
public:
	
    MissionController(void);
    
	~MissionController(void);

	void viewDidLoad();
    
    void onViewExit();
    
    void doStepEvent();
    
    void onStepEvent(CCObject* sender);
    
    /**
     * @brief 人物移动完成
     */
    void onPlayerMoveComplete(yhge::Message* message);
    
    /**
     * @brief 显示步骤事件
     */
    void showStepEvent();
    
protected:
    
    void generateStepPathEvent();
    
    /**
     * @brief 执行战斗事件
     */
    void doBattleEvent();

    /**
     * @brief 获取金钱事件
     */
    void doGetMoneyEvent();
    
    /**
     * @brief 获取经验事件
     */
    void doGetExpEvent();
    
    /**
     * @brief 获取物品事件
     */
    void doGetItemEvent();
    
    /**
     * @brief pvp事件
     */
    void doPvpEvent();
    
    /**
     * 把坐标位置转成step的key
     */
    int positionToStepKey(const CCPoint& pos);
    
    
public:
    
    inline void setLeftStep(int leftStep)
    {
        m_leftStep = leftStep;
    }
    
    inline int getLeftStep()
    {
        return m_leftStep;
    }
    
private:
    
    StepGameWorldController* m_gameWorld;
    
    //key=y*mapWith+x,value事件数据;
    CCDictionary* m_stepEvents;
    
    int m_leftStep;
    
};
NS_CC_GE_END

#endif //CCGE_CONTROLLERS_MissionController_H_
