#ifndef CCGE_DATAS_ANIMATIONDATA_H_
#define CCGE_DATAS_ANIMATIONDATA_H_

#include "cocos2d.h"
#include "CCGEMacros.h"
#include <yhge/Jsoncpp/json.h>
#include <yhge/Datas/CocosData.h>
#include <yhge/Datas/JSONData.h>

NS_CC_GE_BEGIN

/**
 * 动画数据
 * id.key
 */
class AnimationData:public yhge::JSONData
{
public:
    
	AnimationData();
    
	~AnimationData();
    
    inline const yhge::Json::Value& getEntityAnimateData(int entityId)
    {
        char idKey[10];
        sprintf(idKey, "%u",entityId);
        return m_data[idKey];
    }

    inline const yhge::Json::Value& getEntityAnimateData(int entityId,const std::string& key)
    {
        char idKey[10];
        sprintf(idKey, "%u",entityId);
        return m_data[idKey][key];
    }
    
protected:
    
    
};

NS_CC_GE_END
#endif //CCGE_DATAS_ANIMATIONDATA_H_
