#include "ModelFactory.h"

USING_NS_CC;

NS_CC_GE_BEGIN


static ModelFactory* s_dataFactoryInstance=NULL;

ModelFactory::ModelFactory()
{

}

ModelFactory::~ModelFactory()
{

}

bool ModelFactory::init()
{
    setup();
    return true;
}

ModelFactory* ModelFactory::getInstance()
{
    if (!s_dataFactoryInstance)
    {
        s_dataFactoryInstance=new ModelFactory();
        s_dataFactoryInstance->init();
    }
    return s_dataFactoryInstance;
}

void ModelFactory::setup()
{

}

NS_CC_GE_END
