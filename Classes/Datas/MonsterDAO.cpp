#include "MonsterDAO.h"
#include <yhge/yhge.h>

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

MonsterDAO::MonsterDAO()
{

}

MonsterDAO::~MonsterDAO()
{

}

int MonsterDAO::getUnitId(int monsterId)
{
    std::string sql="SELECT unit_id FROM "+m_table+" WHERE "+m_key+" = ?";
    return fetchNumber(sql);
}

NS_CC_GE_END
