#include "ServiceFactory.h"

USING_NS_CC;

NS_CC_GE_BEGIN


static ServiceFactory* s_dataFactoryInstance=NULL;

ServiceFactory::ServiceFactory()
:m_pveBattleService(NULL)
{

}

ServiceFactory::~ServiceFactory()
{
    CC_SAFE_RELEASE_NULL(m_pveBattleService);
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

void ServiceFactory::setup()
{
    m_pveBattleService=new PveBattleService();
    m_pveBattleService->init();
}

NS_CC_GE_END
