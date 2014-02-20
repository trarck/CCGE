#ifndef CCGE_CONTROLLERS_BATTLECONTROLLER_H_
#define CCGE_CONTROLLERS_BATTLECONTROLLER_H_

#include <yhge/yhge.h>
#include <yhmvc/yhmvc.h>
#include <yhge/isometric.h>
#include "CCGEMacros.h"
#include "Consts/GameDefine.h"

NS_CC_GE_BEGIN

/**
 * 战斗直接使用直角坐标系
 * 显示可以使用斜视角
 */
class BattleController:public yhmvc::LayerController,public CCTouchDelegate
{
public:
	
    BattleController(void);
    
	~BattleController(void);

	void layerDidLoad();
    
    void onLayerExit();
    
    /**
     * @brief 加载背景
     */
    void loadBattleGround();

    /**
     * @brief 加载战斗单元
     */
    void loadEntities();
    
    /**
     * @brief 加载自己
     */
    void loadSelfEntities();

    /**
     * @brief 加载对方
     */
    void loadOppEntities();

    /**
     * @brief 开始战斗
     */
    void start();
    
    /**
     * @brief 暂停战斗
     */
    void pause();
    
    /**
     * @brief 停止战斗
     */
    void stop();
    
    /**
     * @brief 执行战斗步骤
     */
    void parseStep();
    
    /**
     * @brief 战斗结束操作
     */
    void doBattleEnd();
    
    void onSkip(CCObject* pSender);

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
public:
    
    inline void setZoneId(int zoneId)
    {
        m_zoneId = zoneId;
    }
    
    inline int getZoneId()
    {
        return m_zoneId;
    }
    
    inline void setMapId(int mapId)
    {
        m_mapId = mapId;
    }
    
    inline int getMapId()
    {
        return m_mapId;
    }
    
    inline void setStep(int step)
    {
        m_step = step;
    }
    
    inline int getStep()
    {
        return m_step;
    }
    
private:

    //区域id
    int m_zoneId;
    
    //地图id
    int m_mapId;
    
    //战斗回合数
    int m_step;
    
    //自己的队伍.3x3.按一行一行存储
    std::vector<int> m_selfTroops;
    
    //对手的队伍.3x3
    std::vector<int> m_oppTroops;
    
};
NS_CC_GE_END

#endif //CCGE_CONTROLLERS_BATTLECONTROLLER_H_
