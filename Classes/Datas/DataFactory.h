#ifndef CCGE_DATAS_DATAFACTORY_H_
#define CCGE_DATAS_DATAFACTORY_H_

#include "cocos2d.h"
#include "CCGEMacros.h"
#include <yhge/yhge.h>
#include "BaseDAO.h"
#include "BaseSqlDAO.h"
#include "AnimationDAO.h"
#include "MapDAO.h"
#include "UnitDAO.h"
#include "MonsterDAO.h"
#include "CharacterDAO.h"
#include "SkillDAO.h"

NS_CC_GE_BEGIN

/**
 * 数据工场
 */
class DataFactory:public CCObject
{
public:
    
	DataFactory();
    
	~DataFactory();

    bool init();

    static DataFactory* getInstance();
    
    void setup();
    
    void setupDriver();
    
    void setupDAO();

public:
    
    inline yhge::data::CocosSqliteDriver* getDriver()
    {
        return m_driver;
    }
    
    inline AnimationDAO* getAnimationDAO()
    {
        return m_animationDAO;
    }
    
    inline MapDAO* getMapDAO()
    {
        return m_mapDAO;
    }
    
    inline BaseDAO* getZoneDAO()
    {
        return m_zoneDAO;
    }
    
    inline UnitDAO* getUnitDAO()
    {
        return m_unitDAO;
    }
    
    inline MonsterDAO* getMonsterDAO()
    {
        return m_monsterDAO;
    }

    inline CharacterDAO* getCharacterDAO()
    {
        return m_characterDAO;
    }
    
    inline SkillDAO* getSkillDAO()
    {
        return m_skillDAO;
    }
    
    inline BaseSqlDAO* getSkillGroupDAO()
    {
        return m_skillGroupDAO;
    }
    
protected:

    /**
     *@brief 取得数据的路径 
     *@param file 文件名。
     *@return 返回完整的配置文件路径。将来支持多语言。
     */
    std::string getDataFilePath(const std::string& file);

protected:
    
    yhge::data::CocosSqliteDriver* m_driver;
    
    //动画数据
    AnimationDAO* m_animationDAO;
    
    //地图数据
    MapDAO* m_mapDAO;
    
    BaseDAO* m_zoneDAO;
    
    UnitDAO* m_unitDAO;
    
    MonsterDAO* m_monsterDAO;
    
    CharacterDAO* m_characterDAO;
    
    SkillDAO* m_skillDAO;
    
    BaseSqlDAO* m_skillGroupDAO;
    
};

NS_CC_GE_END
#endif //CCGE_DATAS_DATAFACTORY_H_
