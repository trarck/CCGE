#include "FcaInfo.h"
#include <yhge/yhge.h>
#include "ChaReader.h"

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

MySpriteFrameCache::MySpriteFrameCache()
{
    
}

MySpriteFrameCache::~MySpriteFrameCache()
{
    
}

FcaInfo::FcaInfo(void)
:m_name("")
,m_spriteFrameCache(NULL)
{
    
}


FcaInfo::~FcaInfo(void)
{
    CCLOG("FcaInfo destroy");
    CC_SAFE_RELEASE_NULL(m_spriteFrameCache);
}

bool FcaInfo::init()
{
    m_spriteFrameCache=new MySpriteFrameCache();
    m_spriteFrameCache->init();
    
    return true;
}

CCSpriteFrame* FcaInfo::getSpriteFrame(const std::string& spriteName)
{
    std::string newname=spriteName;
    
    if (spriteName.find(".png")==std::string::npos) {
        newname=spriteName+".png";
    }
    
    return m_spriteFrameCache->spriteFrameByName(newname.c_str());
}

FcaInfo* FcaInfo::create(const std::string& fcaFile)
{
    
    FcaInfo* fcaInfo=new FcaInfo();
    fcaInfo->init();
    
   
    std::string plistFile=fcaFile+"/plist";
    std::string chaFile=fcaFile+"/cha";

    fcaInfo->getSpriteFrameCache()->addSpriteFramesWithFile(plistFile.c_str());
    
    unsigned long size=0;
    unsigned char* data=CCFileUtils::sharedFileUtils()->getFileData(chaFile.c_str(), "rb", &size);
    
    readCha(fcaInfo,data, size);
    
    CC_SAFE_DELETE_ARRAY(data);
    
    fcaInfo->autorelease();
    
    return fcaInfo;
}

NS_CC_GE_END