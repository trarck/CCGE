#ifndef CCGE_DATAS_DATAFACTORY_H_
#define CCGE_DATAS_DATAFACTORY_H_

#include "cocos2d.h"
#include "CCGEMacros.h"
#include <yhge/yhge.h>
#include "BaseData.h"
#include "AnimationData.h"
#include "MapData.h"
#include "UnitData.h"

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
    
    void setupDao();
    
    void setupData();

public:
    
    inline yhge::JSONDAO* getGameDao()
    {
        return m_gameDao;
    }
    
    inline AnimationData* getAnimationData()
    {
        return m_animationData;
    }
    
    inline MapData* getMapData()
    {
        return m_mapData;
    }
    
    inline BaseData* getZoneData()
    {
        return m_zoneData;
    }
    
    inline UnitData* getUnitData()
    {
        return m_unitData;
    }
    
protected:

    /**
     *@brief 取得数据的路径 
     *@param file 文件名。
     *@return 返回完整的配置文件路径。将来支持多语言。
     */
    std::string getDataFilePath(const std::string& file);

protected:
    
    yhge::JSONDAO* m_gameDao;
    
    //动画数据
    AnimationData* m_animationData;
    
    //地图数据
    MapData* m_mapData;
    
    BaseData* m_zoneData;
    
    UnitData* m_unitData;
    
};

NS_CC_GE_END
#endif //CCGE_DATAS_DATAFACTORY_H_
