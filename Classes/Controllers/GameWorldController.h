#ifndef CCGE_CONTROLLERS_GAMEWORLDCONTROLLER_H_
#define CCGE_CONTROLLERS_GAMEWORLDCONTROLLER_H_

#include "cocos2d.h"
#include <yhge/yhge.h>
#include <yhmvc/yhmvc.h>
#include "CCGEMacros.h"
#include "BaseController.h"
#include "EntityComponent/GameEntity.h"

NS_CC_GE_BEGIN

class GameActiveSortLayer;

class GameWorldController: public BaseController,
    public yhge::isometric::ISOCameraDelegate,
    public CCTouchDelegate
{
public:
	
    GameWorldController();
    
	~GameWorldController();

    virtual bool init();  

	virtual bool init(int zoneId,int mapId);

    void viewDidLoad();

    void onViewExit();

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
    yhge::isometric::ISOMapInfo* loadMapData();
    
    /**
     * 设置相机的可视
     */
    void setCameraMoveRange();

    /**
     * 创建测试按钮
     */
    void createTestMenu();
    
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
     * 更新地图位置
     * 这里的位置和相机的移动方向一致
     */
    void updateMapPosition(const CCPoint& position);
    void updateMapPosition(float x,float y);
    
    //touch事件
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
    /**
     * 相机移动
     * 参数为相机所在的地图位置
     */
    void onCameraMove(const CCPoint& worldPosition);
    
    /**
     * 相机缩放
     */
    void onCameraScale(float scaleX,float scaleY);
    
	 // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    void menuRunCallback(CCObject* pSender);
    void menuStopCallback(CCObject* pSender);
    void menuMoveToCallback(CCObject* pSender);
    
    void menuBigCallback(CCObject* pSender);
    void menuSmallCallback(CCObject* pSender);
	   
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
    
    inline void setAstar(yhge::CallbackAstar* astar)
    {
        CC_SAFE_RETAIN(astar);
        CC_SAFE_RELEASE(m_astar);
        m_astar = astar;
    }
    
    inline yhge::CallbackAstar* getAstar()
    {
        return m_astar;
    }
    
    inline void setOcclusion(yhge::isometric::SortZIndex* occlusion)
    {
        CC_SAFE_RETAIN(occlusion);
        CC_SAFE_RELEASE(m_occlusion);
        m_occlusion = occlusion;
    }
    
    inline yhge::isometric::SortZIndex* getOcclusion()
    {
        return m_occlusion;
    }
    
    inline void setPlayer(GameEntity* player)
    {
        CC_SAFE_RETAIN(player);
        CC_SAFE_RELEASE(m_player);
        m_player = player;
    }
    
    inline GameEntity* getPlayer()
    {
        return m_player;
    }

protected:
    
    /*
     * 创建活动层
     */
    void createActiveLayer(yhge::isometric::ISOActiveLayerInfo* activeLayerInfo);
    
    
    /*
     * 取得路径tile的id
     */
    int getStepTileId(yhge::isometric::ISOMapInfo* mapInfo);
    
    /*
     * 构建行走路径所在的层
     */
    yhge::isometric::ISOLayerInfo* getStepLayer(yhge::isometric::ISOMapInfo* mapInfo);
    
    /*
     * 构建行走路径
     */
    CCArray* buildWalkPaths(yhge::isometric::ISOMapInfo* mapInfo,int startX,int startY);
    
    /*
     * 创建行走路径
     */
    CCArray* createWalkPaths(yhge::isometric::ISOLayerInfo* layerInfo,int stepTileId,int startX,int startY);
    
    /*
     * 创建行走路径
     */
    CCArray* createWalkPathsFromCell(unsigned int* tiles,int col,int row,int stepTileId,int startX,int startY,int stepX,int stepY);
    
    /**
     * @brief 取得当前格子的下一个格子
     *
     * @param nextX 下一个格子横坐标
     * @param nextY 下一个格子纵坐标
     * @param outStepX 找到下个格子的步进x
     * @param outStepY 找到下个格子的步进y
     * @param tiles 层包含的格子信息
     * @param col 层的行数
     * @param row 层的列数
     * @param cellX 当前搜索格子X
     * @param cellY 当前搜索格子Y
     * @param stepX 进入当前格子的步进X
     * @param stepY 进入当前格子的步进Y
     * @param stepTileId 需要检查的tile的id
     *
     * @return 是否查找成功
     */
    bool getNextStepPoint(int* nextX,int* nextY,int* outStepX,int* outStepY,unsigned int* tiles,int col,int row,int cellX,int cellY,int stepX,int stepY,int stepTileId);
    
    /*
     * 构建行走路径
     * 从任意点开始创建
     */
    CCArray* buildWalkPaths(yhge::isometric::ISOMapInfo* mapInfo);
    
    /*
     * 创建行走路径
     *  从任意点开始创建
     */
    CCArray* createWalkPaths(yhge::isometric::ISOLayerInfo* layerInfo,int stepTileId);
    
private:
    
    //区域id
    int m_zoneId;
    
    //地图id
    int m_mapId;
    
	int m_iMapColumn;
	int m_iMapRow;
    
//    GameActiveSortLayer* m_activeLayer;
    
    yhge::isometric::ISOActiveLayer* m_activeLayer;
    
//	CCLayer* m_pBackground;//背景层，加载地形资源
//	CCLayer* m_pIntermediate;//中间层，显示角色，怪物，等可变元素
//	CCLayer* m_pForeground;//前景层,背景层某些物体的遮挡元素。通常为空。

	//寻路
    yhge::CallbackAstar* m_astar;
	//处理遮挡
    yhge::isometric::SortZIndex* m_occlusion;
    
    yhge::isometric::ISOCamera* m_pGameCamera;

    yhge::isometric::ISOTileMap* m_isoMap;
    
	GameEntity* m_player;

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
    
    //行走路径
    CCArray* m_walkPaths;

};

NS_CC_GE_END

#endif // CCGE_CONTROLLERS_GAMEWORLDCONTROLLER_H_
