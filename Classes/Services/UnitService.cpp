#include "UnitService.h"
#include "Consts/DataDefine.h"
#include "Formula/AttackSpeedFormula.h"

USING_NS_CC;

NS_CC_GE_BEGIN


UnitService::UnitService()
{
    
}

UnitService::~UnitService()
{

}

UnitProperty* UnitService::createUnitPropertyFromLevel(int level,const yhge::Json::Value& unitProto)
{
    
    //根据属生成长计算某个等级的元素属性
    int growType=unitProto[CCGE_UNIT_GROW_TYPE].asInt();
    
    float finalValue=0.0f;
    
    UnitProperty* unitProperty=new UnitProperty();
    
    //id
    unitProperty->setUnitId(unitProto[CCGE_UNIT_ID].asInt());
    
    //level
    unitProperty->setLevel(level);
        
    unitProperty->autorelease();
    
    return unitProperty;
}

NS_CC_GE_END
