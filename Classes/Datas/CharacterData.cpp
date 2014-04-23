#include "CharacterData.h"
#include <yhge/yhge.h>

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

CharacterData::CharacterData()
{

}

CharacterData::~CharacterData()
{

}

int CharacterData::getUnitId(int playerId)
{
    std::string sql="SELECT unit_id FROM "+m_table+" WHERE "+m_key+" = ?";
    return m_dao->fetchNumber(sql);
}

NS_CC_GE_END
