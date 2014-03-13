#ifndef CCGE_CONTROLLERS_BATTLECONTROLLER_H_
#define CCGE_CONTROLLERS_BATTLECONTROLLER_H_

#include <yhge/yhge.h>
#include <yhmvc/yhmvc.h>
#include <yhge/isometric.h>
#include "CCGEMacros.h"
#include "BaseController.h"
#include "Consts/GameDefine.h"
#include "EntityComponent/GameEntity.h"

NS_CC_GE_BEGIN

/**
 * 战斗直接使用直角坐标系
 * 显示可以使用斜视角
 */
class BattleController:public BaseController,public CCTouchDelegate
{
public:
	
    BattleController(void);
    
	~BattleController(void);
    
    bool init();

	void viewDidLoad();
    
    void onViewExit();
    
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
     * @brief 初始化战斗双方的队伍
     */
    void initTroops();
    
    /**
     * @brief 消除战斗双方的队伍
     */
    void cleanTroops();
    
    /**
     * @brief 添加到自己队伍
     */
    void addEntityToSelfTroops(GameEntity* entity,int col,int row);
    
    /**
     * @brief 消除自己队伍里的成员
     */
    void removeEntityFromSelfTroops(GameEntity* entity);
    
    /**
     * @brief 消除自己队伍里的成员
     */
    void removeEntityFromSelfTroops(int col,int row);
    
    /**
     * @brief 取得自己队伍里的成员
     */
    GameEntity* getEntityFromSelfTroops(int col,int row);
    
    /**
     * @brief 添加到对方队伍
     */
    void addEntityToOppTroops(GameEntity* entity,int col,int row);
    
    /**
     * @brief 消除对方队伍里的成员
     */
    void removeEntityFromOppTroops(GameEntity* entity);
    
    /**
     * @brief 消除对方队伍里的成员
     */
    void removeEntityFromOppTroops(int col,int row);

    /**
     * @brief 取得对方队伍里的成员
     */
    GameEntity* getEntityFromOppTroops(int col,int row);
    
    /**
     * @brief 取得队伍里的成员
     *
     * @param col 战斗列号
     * @param col 战斗行号
     * @param side 战斗一方
     */
    GameEntity* getEntityFromTroops(int col,int row,int side);
    
    /**
     * @brief 添加到队伍
     */
    void addEntityToTroops(GameEntity* entity,int col,int row,int side);
    
    /**
     * @brief 消除对方队伍里的成员
     */
    void removeEntityFromTroops(GameEntity* entity,int side);
    
    /**
     * @brief 消除对方队伍里的成员
     */
    void removeEntityFromTroops(int col,int row,int side);
    
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
     * @brief 处理一回合
     */
    void parseRound();
    
    void battleUpdate(float delta);
    
    /**
     * @brief 执行战斗步骤
     */
    void parseNextStep();
    
    /**
     * @brief 执行我方战斗步骤
     */
    bool trunSelfStep();
    
    /**
     * @brief 执行对方战斗步骤
     */
    bool trunOppStep();
    
    /**
     * @brief 战斗结束操作
     *
     * @param win 是否胜利
     */
    void doBattleEnd(bool win);
    
    /**
     * @brief 一个实体攻击完成
     */
    void onEntityAttackComplete(yhge::Message* message);
    
    void onEntityDie(yhge::Message* message);
    
    void onSkip(CCObject* pSender);
    
    void onStart(CCObject* pSender);

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
protected:
    
    /**
     * @brief 检查一轮是否完成
     */
    bool isRoundComplete();
    
    /**
     * @brief 一个步骤结点
     */
    void doStepEnd();
    
    /**
     * @brief 把一维转成二维
     *
     * @param index 序列号
     * @param col 逻辑列值
     * @param row 逻辑行值
     */
    void convertIndexToCell(int index,int* col,int* row);
    
    /**
     * @brief 把一维转成二维
     *
     * @param index 序列号
     * @param col 逻辑列值
     * @param row 逻辑行值
     * @param x   地图x坐标
     * @param y   地图y坐标
     */
    void convertCoord(int index,int* col,int* row,int* x,int* y);
    
    /**
     * @brief 把一维转成二维
     *
     * @param index 序列号
     * @param col 逻辑列值
     * @param row 逻辑行值
     * @param x   地图x坐标
     * @param y   地图y坐标
     */
    void convertOppCoord(int index,int* col,int* row,int* x,int* y);
    
    /**
     * @brief 取得一个存在的队员
     *
     * @param index 从某个位置开始
     * @param side 战斗一方
     * @param entity 取得的物体
     * @return 当前物体的索引
     */
    int getExistEntityBySide(int index,int side,GameEntity** entity);
    
    /**
     * @brief 取得一个存在的队员
     *
     * @param index 从某个位置开始
     * @param entity 取得的物体
     * @return 当前物体的索引
     */
    int getSelfExistEntity(int index,GameEntity** entity);
    
    /**
     * @brief 取得一个存在的队员
     *
     * @param index 从某个位置开始
     * @param entity 取得的物体
     * @return 当前物体的索引
     */
    int getOppExistEntity(int index,GameEntity** entity);
    
    /**
     * @brief 队员攻击
     *
     * @param entity 战场上的一个entity
     * @param col 逻辑列值
     * @param row 逻辑行值
     * @param side 攻击方
     */
    void entityAttack(GameEntity* entity,int col,int row,int side);
    
    /**
     * @brief 取得攻击目标
     *
     * @param col 逻辑列值
     * @param row 逻辑行值
     * @param side 被攻击方
     * @return 取得的目标
     */
    GameEntity* getAttackTarget(int col,int row,int side);
    
    inline int getOtherSide(int side)
    {
        switch (side) {
            case kSelfSide:
                return kOppSide;
                break;
            case kOppSide:
                return kSelfSide;
            default:
                return -1;
                break;
        }
    }
    
    /**
     * @brief 处理entity相的消息
     *
     * @param entity 战场上的一个entity
     */
    void registerEntityMessage(GameEntity* entity);
    
    /**
     * @brief 注销ntity相的消息
     *
     * @param entity 战场上的一个entity
     */
    void removeEntityMessage(GameEntity* entity);
    
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
    
    inline void setRound(int round)
    {
        m_round = round;
    }
    
    inline int getRound()
    {
        return m_round;
    }
    
    inline void setSelfStepIndex(int selfStepIndex)
    {
        m_selfStepIndex = selfStepIndex;
    }
    
    inline int getSelfStepIndex()
    {
        return m_selfStepIndex;
    }
    
    inline void setOppStepIndex(int oppStepIndex)
    {
        m_oppStepIndex = oppStepIndex;
    }
    
    inline int getOppStepIndex()
    {
        return m_oppStepIndex;
    }
    
    inline void setStepSide(int stepSide)
    {
        m_stepSide = stepSide;
    }
    
    inline int getStepSide()
    {
        return m_stepSide;
    }
    
    inline void setBattleEnd(bool battleEnd)
    {
        m_battleEnd = battleEnd;
    }
    
    inline bool isBattleEnd()
    {
        return m_battleEnd;
    }
    
    inline void setWin(bool win)
    {
        m_win = win;
    }
    
    inline bool isWin()
    {
        return m_win;
    }
    
private:

    //区域id
    int m_zoneId;
    
    //地图id
    int m_mapId;
    
    //战斗回合数
    int m_round;
    
    //步骤中的战斗一方
    int m_stepSide;
    
    int m_selfStepIndex;
    
    int m_oppStepIndex;
    
    //自己的队伍.3x3.这里直接使用固定大小的数组。也可以使用动态的一维数组。
    GameEntity* m_selfTroops[kBattleCellRow][kBattleCellCol];
    
    //对手的队伍.3x3
    GameEntity* m_oppTroops[kBattleCellRow][kBattleCellCol];
    
    bool m_battleEnd;
    
    bool m_win;

    
};
NS_CC_GE_END

#endif //CCGE_CONTROLLERS_BATTLECONTROLLER_H_
