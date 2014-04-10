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
    troops.push_back(1);
    troops.push_back(1);
    troops.push_back(0);
    troops.push_back(1);
    troops.push_back(1);
    troops.push_back(1);
    troops.push_back(1);
    troops.push_back(1);
    troops.push_back(1);
    return troops;
}

std::vector<int> BattleService::getOppTroops()
{
    std::vector<int> troops;
    troops.push_back(3);
    troops.push_back(3);
    troops.push_back(3);
    troops.push_back(3);
    troops.push_back(3);
    troops.push_back(3);
    troops.push_back(3);
    troops.push_back(3);
    troops.push_back(3);
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
