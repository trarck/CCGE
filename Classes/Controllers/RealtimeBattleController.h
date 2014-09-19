#ifndef CCGE_CONTROLLERS_RealtimeBattleController_H_
#define CCGE_CONTROLLERS_RealtimeBattleController_H_

#include <yhge/yhge.h>
#include <yhmvc/yhmvc.h>
#include <yhge/isometric.h>
#include "CCGEMacros.h"
#include "BaseController.h"
#include "Consts/GameDefine.h"
#include "EntityComponent/GameEntity.h"
#include "EntityComponent/Managers/BattleManager.h"

NS_CC_GE_BEGIN

class TimelineNode :public CCObject
{
public:
    
    TimelineNode()
    :m_duration(0.0f)
    ,m_elapsed(0.0f)
    ,m_gameEntity(NULL)
    ,m_renderer(NULL)
    {
        
    }
    
    ~TimelineNode()
    {
        CC_SAFE_RELEASE_NULL(m_gameEntity);
        CC_SAFE_RELEASE_NULL(m_renderer);
    }
    
    inline bool isTurn(){
        return m_elapsed>=m_duration;
    }
    
    inline void fixTurn(){
        
        int loop=int (m_elapsed/m_duration);
        
        m_elapsed-=loop*m_duration;
    }
    
    inline void addElapsed(float delta)
    {
        m_elapsed += delta;
    }
    
    inline void setElapsed(float elapsed)
    {
        m_elapsed = elapsed;
    }
    
    inline float getElapsed()
    {
        return m_elapsed;
    }
    
    inline void setDuration(float duration)
    {
        m_duration = duration;
    }
    
    inline float getDuration()
    {
        return m_duration;
    }
    
    inline void setGameEntity(GameEntity* gameEntity)
    {
        CC_SAFE_RETAIN(gameEntity);
        CC_SAFE_RELEASE(m_gameEntity);
        m_gameEntity = gameEntity;
    }
    
    inline GameEntity* getGameEntity()
    {
        return m_gameEntity;
    }
    
    inline void setRenderer(CCSprite* renderer)
    {
        CC_SAFE_RETAIN(renderer);
        CC_SAFE_RELEASE(m_renderer);
        m_renderer = renderer;
    }
    
    inline CCSprite* getRenderer()
    {
        return m_renderer;
    }
    
protected:
    float m_elapsed;
    float m_duration;
    GameEntity* m_gameEntity;
    CCSprite* m_renderer;
};

/**
 * 战斗直接使用直角坐标系
 * 显示可以使用斜视角
 */
class RealtimeBattleController:public BaseController,public CCTouchDelegate
{
public:
	
    RealtimeBattleController(void);
    
	~RealtimeBattleController(void);
    
    bool init();

	void viewDidLoad();
    
    void onViewEnter();
    
    void onViewExit();
    
    /**
     * @brief 加载背景
     */
    void loadBattleGround();
    
    void loadBattleWorld();
    
    /**
     * @brief 显示坐标
     */
    void showCoordinate();

    /**
     * @brief 加载战斗单元
     */
    void loadEntities();
    
    /**
     * @brief 卸载战斗单元
     */
    void unloadEntities();
    
    /**
     * @brief 加载自己
     */
    void loadSelfEntities();

    /**
     * @brief 加载对方
     */
    void loadOppEntities();
    
    /**
     * @brief 战斗结束操作
     *
     * @param win 是否胜利
     */
    void doBattleEnd(bool win);
    
    void onEndTipCallback();
    
    void onSkill1(CCObject* sender);
    
    void onSkill2(CCObject* sender);
    
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
    yhge::Vector<GameEntity*> m_selfTroops;
    
    //对手的队伍.3x3
    yhge::Vector<GameEntity*> m_oppTroops;
    
    bool m_battleEnd;
    
    bool m_win;
    
    CCLayer* m_battleWorld;

    CCArray* m_timelineNodes;
    
    CCLayer* m_timelineLayer;
    
    CCLayer* m_tipLayer;
    
    //weak refrence;
    BattleManager* m_battleManager;
    
};
NS_CC_GE_END

#endif //CCGE_CONTROLLERS_RealtimeBattleController_H_
