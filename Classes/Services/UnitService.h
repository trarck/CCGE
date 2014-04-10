#ifndef CCGE_SERVICES_UNITSERVICE_H_
#define CCGE_SERVICES_UNITSERVICE_H_

#include "BaseService.h"
#include "EntityComponent/Properties/UnitProperty.h"

NS_CC_GE_BEGIN

/**
 * @brief 实体逻辑
 */
class UnitService:public BaseService
{
public:
    
	UnitService();
    
	~UnitService();
    
    /**
     * @brief 根据配置和等级取得实体的数据
     * 这里只计算unit的基础属性，不算其它。比如装备，长时间加成。
     * 其它属性由具体的server处理。
     */
    UnitProperty* createUnitPropertyFromLevel(int level,const yhge::Json::Value& entityConfig);
    
    inline static float calcGrow(float baseValue,float growValue,int level,int type)
    {
        //TODO 根据type选择公式
        return calcNormalGrow(baseValue,growValue,level);
    }
    
    inline static float calcNormalGrow(float baseValue,float growValue,int level)
    {
        return baseValue+growValue*level;
    }
    
};

NS_CC_GE_END

#endif //CCGE_SERVICES_UNITSERVICE_H_
