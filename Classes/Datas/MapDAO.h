#ifndef CCGE_DATAS_MAPDAO_H_
#define CCGE_DATAS_MAPDAO_H_

#include "cocos2d.h"
#include "CCGEMacros.h"
#include <yhge/yhge.h>

NS_CC_GE_BEGIN

/**
 * 地图数据
 * id.key
 */
class MapDAO:public yhge::data::JSONDataDAO
{
public:
    
	MapDAO();
    
	~MapDAO();
    
    inline const yhge::Json::Value& getDataById(int mapId)
    {
        char idKey[10];
        sprintf(idKey, "%u",mapId);
        return m_data[idKey];
    }
    
protected:
    
    
};

NS_CC_GE_END
#endif //CCGE_DATAS_MAPDAO_H_
