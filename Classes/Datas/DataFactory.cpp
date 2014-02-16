#include "DataFactory.h"

USING_NS_CC;

NS_CC_GE_BEGIN

static const char* kDataDir="datas/";

static DataFactory* s_dataFactoryInstance=NULL;

DataFactory::DataFactory()
{

}

DataFactory::~DataFactory()
{

}

bool DataFactory::init()
{
    setup();
    return true;
}

DataFactory* DataFactory::getInstance()
{
    if (!s_dataFactoryInstance)
    {
        s_dataFactoryInstance=new DataFactory();
        s_dataFactoryInstance->init();
    }
    return s_dataFactoryInstance;
}

void DataFactory::setup()
{
    m_animationData=new AnimationData();
    m_animationData->init();
    m_animationData->loadFromFile(getDataFilePath("animation.json"));
}

std::string DataFactory::getDataFilePath(const std::string& file)
{
    std::string filePath=file;

    //����Ǿ���·������ֱ��ʹ��
    if (file.substr(0,1)!="/")
    {
        //���������dataĿ¼������ӵ�dataĿ¼
        if (file.find_first_of(kDataDir)!=0)
        {
            filePath=kDataDir+file;
        }

        //ת������Ŀ¼
        filePath=CCFileUtils::sharedFileUtils()->fullPathForFilename(filePath.c_str());
    }

    return filePath;
}

NS_CC_GE_END
