#include "CharacterDAO.h"
#include <yhge/yhge.h>

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

CharacterDAO::CharacterDAO()
{

}

CharacterDAO::~CharacterDAO()
{

}

int CharacterDAO::getUnitId(int playerId)
{
    std::string sql="SELECT unit_id FROM "+m_table+" WHERE "+m_key+" = ?";
    return fetchNumber(sql);
}

NS_CC_GE_END