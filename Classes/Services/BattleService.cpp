#include "BattleService.h"

USING_NS_CC;

NS_CC_GE_BEGIN

BattleService::BattleService()
{

}

BattleService::~BattleService()
{

}

void BattleService::prepareBattle(int oppId)
{
    
}

CCDictionary* BattleService::getSelfBattleData()
{
    return NULL;
}

CCDictionary* BattleService::getOppBattleData()
{
    return NULL;
}

CCDictionary* BattleService::getOppBattleData(int oppId)
{
    return NULL;
}

std::vector<int> BattleService::getSelfTroops()
{
    std::vector<int> troops;
    troops[0]=2;
    troops[1]=2;
    troops[2]=2;
    troops[3]=2;
    troops[4]=2;
    troops[5]=2;
    troops[6]=2;
    troops[7]=2;
    troops[8]=2;
    return troops;
}

std::vector<int> BattleService::getOppTroops()
{
    std::vector<int> troops;
    troops[0]=3;
    troops[1]=3;
    troops[2]=3;
    troops[3]=3;
    troops[4]=3;
    troops[5]=3;
    troops[6]=3;
    troops[7]=3;
    troops[8]=3;
    return troops;
}

int BattleService::getSelfFormationFormula()
{
    return 0;
}

int BattleService::getOppFormationFormula()
{
    return 0;
}

NS_CC_GE_END
