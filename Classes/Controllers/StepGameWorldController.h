#ifndef CCGE_CONTROLLERS_STEPGAMEWORLDCONTROLLER_H_
#define CCGE_CONTROLLERS_STEPGAMEWORLDCONTROLLER_H_

#include "cocos2d.h"
#include <yhge/yhge.h>
#include <yhmvc/yhmvc.h>
#include "CCGEMacros.h"
#include "GameWorldController.h"
#include "EntityComponent/GameEntity.h"

NS_CC_GE_BEGIN

class GameActiveSortLayer;

class StepGameWorldController: public GameWorldController
{
public:
	
    StepGameWorldController();
    
	~StepGameWorldController();

//    virtual bool init();  
//    
//    virtual bool init(int zoneId,int mapId);
    
    virtual void setup();
    
    /**
     * 创建游戏地图
     */
    virtual yhge::isometric::ISOMapInfo* createGameMap();
    
    /**
     * @brief 移动到下一步
     */
    void nextStep(int step=1);
    
    /**
     * @brief 检查当前结点是否是终点
     */
    bool isEndStep();
    
    /**
     * @brief 取得玩家的当前点
     */
    const CCPoint& getCurrentPosition();

protected:
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
    

public:
    
    inline void setWalkPaths(CCArray* walkPaths)
    {
        CC_SAFE_RETAIN(walkPaths);
        CC_SAFE_RELEASE(m_walkPaths);
        m_walkPaths = walkPaths;
    }
    
    inline CCArray* getWalkPaths()
    {
        return m_walkPaths;
    }
    
    inline void setStepIndex(int stepIndex)
    {
        m_stepIndex = stepIndex;
    }
    
    inline int getStepIndex()
    {
        return m_stepIndex;
    }
    
private:

    //行走路径
    CCArray* m_walkPaths;
    
    //路径结点索引值.0-表示起始
    int m_stepIndex;

};

NS_CC_GE_END

#endif // CCGE_CONTROLLERS_STEPGAMEWORLDCONTROLLER_H_
