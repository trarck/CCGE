#include "DataFactory.h"

USING_NS_CC;

NS_CC_GE_BEGIN

static const char* kDataDir="datas/";

static DataFactory* s_dataFactoryInstance=NULL;

DataFactory::DataFactory()
:m_animationData(NULL)
,m_mapData(NULL)
,m_zoneData(NULL)
{

}

DataFactory::~DataFactory()
{
    CC_SAFE_RELEASE_NULL(m_animationData);
    CC_SAFE_RELEASE_NULL(m_mapData);
    CC_SAFE_RELEASE_NULL(m_zoneData);
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
    
    m_mapData=new MapData();
    m_mapData->init();
    m_mapData->loadFromFile(getDataFilePath("map.json"));
    
    m_zoneData=new BaseData();
    m_zoneData->init();
    m_zoneData->loadFromFile(getDataFilePath("zone.json"));
}

std::string DataFactory::getDataFilePath(const std::string& file)
{
    std::string filePath=file;

    //如果是绝对路径，则直接使用
    if (filePath[0]!='/')
    {
        //如果不是在data目录，则添加到data目录
        if (file.substr(0,strlen(kDataDir))!=kDataDir)
        {
            filePath=kDataDir+file;
        }

        //转到绝对目录
        filePath=CCFileUtils::sharedFileUtils()->fullPathForFilename(filePath.c_str());
    }
    
    return filePath;
}

NS_CC_GE_END
