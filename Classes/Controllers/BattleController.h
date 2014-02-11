#ifndef CCGE_CONTROLLERS_BATTLECONTROLLER_H_
#define CCGE_CONTROLLERS_BATTLECONTROLLER_H_

#include <yhge/yhge.h>
#include <yhmvc/yhmvc.h>
#include <yhge/isometric.h>
#include "CCGEMacros.h"

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
    
private:

    //区域id
    int m_zoneId;
    
    //地图id
    int m_mapId;
    
};
NS_CC_GE_END

#endif //CCGE_CONTROLLERS_BATTLECONTROLLER_H_
