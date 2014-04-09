#ifndef CCGE_SERVICES_ENTITYSERVICE_H_
#define CCGE_SERVICES_ENTITYSERVICE_H_

#include "BaseService.h"
#include "EntityComponent/Properties/UnitProperty.h"

NS_CC_GE_BEGIN

/**
 * @brief 实体逻辑
 */
class EntityService:public BaseService
{
public:
    
	EntityService();
    
	~EntityService();
    
    /**
     * @brief 计算实体的总的属性值
     * 基础属性+装备的加成属性+其它加成(星座，公会等长时间加成)
     * 不包含buffer，buffer由战斗逻辑控制。
     * 其它加成由unit的属性决定
     */
    UnitProperty* calcTotalUnitProperty(int unitId);
    
    /**
     * @brief 加入装备的属性
     */
    UnitProperty* addEquipUnitProperty(UnitProperty* baseProperty,const yhge::Json::Value& equipData);
    
    /**
     * @brief 根据配置和等级取得实体的数据
     */
    UnitProperty* calcLevelUnitProperty(int level,const yhge::Json::Value& entityConfig);
    
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
#endif //CCGE_SERVICES_ENTITYSERVICE_H_
