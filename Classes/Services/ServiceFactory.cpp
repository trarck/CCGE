#include "ServiceFactory.h"

USING_NS_CC;

NS_CC_GE_BEGIN


static ServiceFactory* s_dataFactoryInstance=NULL;

ServiceFactory::ServiceFactory()
:m_pveBattleService(NULL)
,m_missionService(NULL)
{

}

ServiceFactory::~ServiceFactory()
{
    CC_SAFE_RELEASE_NULL(m_pveBattleService);
    CC_SAFE_RELEASE_NULL(m_missionService);
}

bool ServiceFactory::init()
{
    setup();
    return true;
}

ServiceFactory* ServiceFactory::getInstance()
{
    if (!s_dataFactoryInstance)
    {
        s_dataFactoryInstance=new ServiceFactory();
        s_dataFactoryInstance->init();
    }
    return s_dataFactoryInstance;
}

void ServiceFactory::destroyInstance()
{
    if (s_dataFactoryInstance){
        s_dataFactoryInstance->release();
    }
}

void ServiceFactory::setup()
{
    m_pveBattleService=new PveBattleService();
    m_pveBattleService->init();
    
    m_missionService=new MissionService();
    m_missionService->init();
}

NS_CC_GE_END
