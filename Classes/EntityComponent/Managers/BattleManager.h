
#ifndef CCGE_ENTITYCOMPONENT_MANAGERS_BATTLEMANAGER_H_
#define CCGE_ENTITYCOMPONENT_MANAGERS_BATTLEMANAGER_H_

#include "cocos2d.h"
#include <yhge/yhge.h>
#include "CCGEMacros.h"
#include "../GameEntity.h"
#include "BattleUpdateManager.h"

NS_CC_GE_BEGIN

typedef yhge::Vector<GameEntity*> GameEntityVector;

typedef std::vector<yhge::Json::Value> HeroVector;

struct ManualOpration
{
    int wave;
    int tick;
    int unitIndex;
};

typedef std::vector<ManualOpration> ManualOprationList;

/**
 * 战斗管理器
 */
class BattleManager : public yhge::ECManager
{
public:
    
    BattleManager();
    
    virtual ~BattleManager();
    
    bool init();
    
    void reset();
    
    void resetUnits();
    
    void resetAliveUnits();
    
    void resetStage();
    
    void addUnit(GameEntity* entity);
    
    /**
     * @brief 进入关卡
     */
    void enterStage(yhge::Json::Value& stageInfo,HeroVector& heroList,bool isBot,int startWaveId=1);
    
    /**
     * @brief 进入竞技场
     */
    void enterArena(HeroVector& heroList,HeroVector& enemyList,bool heroIsBot,bool enemyIsBot);
    
    /**
     * @brief 进入远程
     */
    void enterCrusade(HeroVector& heroList,HeroVector& enemyList,bool enemyisBot,yhge::Json::Value& selfCrusade,yhge::Json::Value& enemyCrusade,int stageId);
    
    /**
     * @brief 进入矿场
     */
    void enterExcavate(HeroVector& heroList,HeroVector& enemyList,bool enemyisBot,yhge::Json::Value& selfDynaList,yhge::Json::Value& enemyDynaList,int stageId);
    
    /**
     * @brief 初始化己方战斗单位
     */
    void setupSelfEntities(HeroVector& heroList,bool isBot);
    
    /**
     * @brief 初始化敌方战斗单位
     */
    void setupEnemyEntities(HeroVector& heroList,bool isBot);
    
    /**
     * @brief 初始化英雄
     */
    void setupHeros();
    
    void onUnitDie(GameEntity* unit,GameEntity* killer);
    
    /**
     * @brief 构建英雄属性
     * 基础+装备+被动技能+buff
     */
    void rebuildEntity(GameEntity* entity);
    
protected:
    
    HeroVector sortEntity(const HeroVector& entityList);
    
    GameEntity* createEntity(yhge::Json::Value& hero);
    
public:
    
    inline void setEnabled(bool enabled)
    {
        m_enabled = enabled;
    }
    
    inline bool isEnabled()
    {
        return m_enabled;
    }
    
    inline void setAliveAllianceCount( int aliveAllianceCount)
    {
        m_aliveAllianceCount = aliveAllianceCount;
    }
    
    inline  int getAliveAllianceCount()
    {
        return m_aliveAllianceCount;
    }
    
    inline void setAliveEnemyCount( int aliveEnemyCount)
    {
        m_aliveEnemyCount = aliveEnemyCount;
    }
    
    inline  int getAliveEnemyCount()
    {
        return m_aliveEnemyCount;
    }
    
    inline void setDeadAllianceCount( int deadAllianceCount)
    {
        m_deadAllianceCount = deadAllianceCount;
    }
    
    inline  int getDeadAllianceCount()
    {
        return m_deadAllianceCount;
    }
    
    inline void setDeadEnemyCount( int deadEnemyCount)
    {
        m_deadEnemyCount = deadEnemyCount;
    }
    
    inline  int getDeadEnemyCount()
    {
        return m_deadEnemyCount;
    }
    
    inline void setArenaMode(bool arenaMode)
    {
        m_arenaMode = arenaMode;
    }
    
    inline bool isArenaMode()
    {
        return m_arenaMode;
    }
    
    inline void setCrusadeMode(bool crusadeMode)
    {
        m_crusadeMode = crusadeMode;
    }
    
    inline bool isCrusadeMode()
    {
        return m_crusadeMode;
    }
    
    inline void setExcavateMode(bool excavateMode)
    {
        m_excavateMode = excavateMode;
    }
    
    inline bool isExcavateMode()
    {
        return m_excavateMode;
    }
    
    inline void setReplayMode(bool replayMode)
    {
        m_replayMode = replayMode;
    }
    
    inline bool isReplayMode()
    {
        return m_replayMode;
    }
    
    inline void setGuildInstanceMode(bool guildInstanceMode)
    {
        m_guildInstanceMode = guildInstanceMode;
    }
    
    inline bool isGuildInstanceMode()
    {
        return m_guildInstanceMode;
    }
    
    inline void setStageRect(const CCRect& stageRect)
    {
        m_stageRect = stageRect;
    }
    
    inline const CCRect& getStageRect()
    {
        return m_stageRect;
    }
    
    inline void setOprationList(const ManualOprationList& oprationList)
    {
        m_oprationList = oprationList;
    }
    
    inline const ManualOprationList& getOprationList()
    {
        return m_oprationList;
    }
    
    inline GameEntityVector& getUnits()
    {
        return m_units;
    }
    
    inline std::map<int, GameEntityVector >& getAliveUnits()
    {
        return m_aliveUnits;
    }
    
    inline GameEntityVector& getAliveUnitsOfCamp(int camp)
    {
        return m_aliveUnits[camp];
    }
    
    inline void setManaBonus(float manaBonus)
    {
        m_manaBonus = manaBonus;
    }
    
    inline float getManaBonus()
    {
        return m_manaBonus;
    }
    
protected:
    
    bool m_enabled;
    
    GameEntityVector m_units;
    
    //camp:unit list
    std::map<int, GameEntityVector > m_aliveUnits;
    
    //己方存活的单位数量
    int m_aliveAllianceCount;
    //敌方存活的单位数量
    int m_aliveEnemyCount;
    //己方死亡的单位数量
    int m_deadAllianceCount;
    //敌方死亡的单位数量
    int m_deadEnemyCount;
    
    
    //战斗模式
    bool m_arenaMode;
    bool m_crusadeMode;
    bool m_excavateMode;
    bool m_replayMode;
    bool m_guildInstanceMode;
    
    //战斗场景大小
    CCRect m_stageRect;
    
    //操作列表
    ManualOprationList m_oprationList;
    //战斗过程的mp回复参数
    float m_manaBonus;
    
};


NS_CC_GE_END



#endif // CCGE_ENTITYCOMPONENT_MANAGERS_BATTLEMANAGER_H_
