#include "SkillDAO.h"
#include <yhge/yhge.h>
#include "Consts/DataDefine.h"

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

SkillDAO::SkillDAO()
{

}

SkillDAO::~SkillDAO()
{

}

yhge::Json::Value SkillDAO::getDataById(int aId)
{
    Json::Value data=loadData(aId);
    
    data[CCGE_SKILL_ACTIONS]=getSkillActions(aId);
    return data;
}

yhge::Json::Value SkillDAO::getSkillActions(int skillId)
{
    std::string sql="SELECT * FROM ";
    sql+=CCGE_TABLE_SKILL_ACTIONS;
    sql+=" WHERE action_id = ?";
    
    Json::Value params;
    params.append(skillId);
    return fetchAll(sql, params);
}

NS_CC_GE_END
