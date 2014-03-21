#ifndef CCGE_DATAS_MAPDATA_H_
#define CCGE_DATAS_MAPDATA_H_

#include "cocos2d.h"
#include "CCGEMacros.h"
#include <yhge/Jsoncpp/json.h>
#include <yhge/Datas/CocosData.h>
#include <yhge/Datas/JSONData.h>

NS_CC_GE_BEGIN

/**
 * 地图数据
 * id.key
 */
class MapData:public yhge::JSONData
{
public:
    
	MapData();
    
	~MapData();
    
    inline const yhge::Json::Value& getDataById(int mapId)
    {
        char idKey[10];
        sprintf(idKey, "%u",mapId);
        return m_data[idKey];
    }
    
protected:
    
    
};

NS_CC_GE_END
#endif //CCGE_DATAS_MAPDATA_H_
