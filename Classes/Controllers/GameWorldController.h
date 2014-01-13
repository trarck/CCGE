#ifndef CCGE_CONTROLLERS_GAMEWORLDCONTROLLER_H_
#define CCGE_CONTROLLERS_GAMEWORLDCONTROLLER_H_

#include "cocos2d.h"
#include <yhge/yhge.h>
#include <yhmvc/yhmvc.h>
#include "CCGEMacros.h"

NS_CC_GE_BEGIN

class GameWorldController: public yhmvc::LayerController,
    public yhge::ISOCameraMoveDelegate,
    public CCTouchDelegate
{
public:
	
    GameWorldController();
    
	~GameWorldController();

    virtual bool init();  

	virtual bool init(int zoneId,int mapId);

    void layerDidLoad();

    void onLayerExit();

    /**
     * 设置游戏世界
     */
    void setup();
    
    /**
     * 设置工具集
     */
	void setupUtil();
    
    /**
     * 创建游戏地图
     */
	void createGameMap();

    /**
     * 加载游戏地图
     */
    yhge::ISOMapInfo* loadMapData();
    
//	void loadBackground();
//    
//	void loadInterMediate();
//    
//	void loadForeground();
    
//	void addInterMediateStaticEntity(WorldEntity* entity);
//	void addInterMediateDynamicEntity(Unit* entity);
//	void removeInterMediateDynamicEntity(Unit* entity);
//	void removeInterMediateStaticEntity(WorldEntity* entity);
    
    /**
     * 在游戏中添加一个角色
     */
	void addPlayerAtCoord(CCPoint coord);
    
    /**
     * 在游戏中添加一个队友
     */
	void addTeammateAtCoord(CCPoint coord);
	
    /**
     * 移除一个队友
     */
//    void removeTeammate(Player* player);
    
    /**
     * 把玩家移到一个屏幕坐标
     */
	void movePlayerToViewLocation(CCPoint location);
    
//	void moveEntity(Unit* entity,CCPoint coord);
//    
//	void moveViewEntity(Unit* entity,CCPoint location);
    
	//void addBuildingAt(CCPoint coord);
	//void removeBuilding(Building* building);
    
    /**
     * 查找可通过路径
     */
	CCArray* searchPathsFrom(int fromX,int fromY,int toX,int toY);
    
    /**
     * 查找可通过路径
     */
	CCArray* searchPathsFrom(CCPoint from,CCPoint to);
	
    /**
     * 把通过路径转成屏幕坐标
     */
    CCArray* mapPathsToViewPaths(CCArray* paths);
    
    /**
     * 游戏中某个点是否可以通过
     */
	bool isWorkable(int x ,int y);
    
    /**
     * 屏幕坐标转成地图坐标
     */
    CCPoint toGameCoordinate(const CCPoint& position);
    
    /**
     * 屏幕坐标转成地图坐标
     */
    CCPoint toGameCoordinate(float x,float y);
    
    /**
     * 相机移动
     * 参数为相机所在的地图位置
     */
    void onCameraMove(const CCPoint& worldPosition);
    
    /**
     * 更新地图位置
     * 这里的位置和相机的移动方向一致
     */
    void updateMapPosition(const CCPoint& position);
    void updateMapPosition(float x,float y);
   
	 // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    void menuRunCallback(CCObject* pSender);
    void menuStopCallback(CCObject* pSender);
    void menuMoveToCallback(CCObject* pSender);

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent); 
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent); 
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent); 
	   
	//get set
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
    
    inline void setMapColumn(int iMapColumn)
    {
        m_iMapColumn = iMapColumn;
    }
    
    inline int getMapColumn()
    {
        return m_iMapColumn;
    }
    
    inline void setMapRow(int iMapRow)
    {
        m_iMapRow = iMapRow;
    }
    
    inline int getMapRow()
    {
        return m_iMapRow;
    }

private:
    
    //区域id
    int m_zoneId;
    
    //地图id
    int m_mapId;
    
	int m_iMapColumn;
	int m_iMapRow;
    
	
//	CCLayer* m_pBackground;//背景层，加载地形资源
//	CCLayer* m_pIntermediate;//中间层，显示角色，怪物，等可变元素
//	CCLayer* m_pForeground;//前景层,背景层某些物体的遮挡元素。通常为空。

	//寻路
//	CCAstar* m_pAstar;
	//处理遮挡
//	CCZIndex* m_pZIndex;
    yhge::ISOCamera* m_pGameCamera;

    yhge::ISOTileMap* m_isoMap;
//	Player* m_pPlayer;

	//touch
	CCPoint m_startTouchLocation;
	CCPoint m_lastTouchLocation;
	bool m_bIsTouchMoved;

	CCPoint m_startPoint;

	//units
	CCArray* m_pUnits;
	/*CCArray* m_pBuildings;
	CCArray* m_pMonsters;
	CCArray* m_pResources;*/

};

NS_CC_GE_END

#endif // CCGE_CONTROLLERS_GAMEWORLDCONTROLLER_H_
