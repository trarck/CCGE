#include "FcaInfo.h"
#include <yhge/yhge.h>

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

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
    m_spriteFrameCache=CCSpriteFrameCache::sharedSpriteFrameCache();
    m_spriteFrameCache->retain();
    
    return true;
}

FcaInfo* FcaInfo::create(const std::string& fcaFile)
{
    
    FcaInfo* fcaInfo=new FcaInfo();
    fcaInfo->init();
    
   
    std::string plistFile=fcaFile+"/plist";
    std::string chaFile=fcaFile+"/cha";

    fcaInfo->getSpriteFrameCache()->addSpriteFramesWithFile(plistFile.c_str());
    
    size_t size=0;
    unsigned char* data=CCFileUtils::sharedFileUtils()->getFileData(chaFile.c_str(), "rb", &size);
    
    fcaInfo->readCha(data, size);
    
    CC_SAFE_DELETE_ARRAY(data);
    
    fcaInfo->autorelease();
    
    return fcaInfo;
}

void FcaInfo::readCha(unsigned char* data,size_t size)
{
    Buffer* buffer=new Buffer(data,size,false);
    
    InputStream* is=new InputStream();
    is->init(buffer);
    
    
    buffer->release();
    is->release();
    
}

std::string readString(InputStream* is)
{
    int strLen=is->readInt32();

    unsigned char* strBytes=new unsigned char(strLen);
    
    is->readBytes(strBytes, strLen);
    
    std::string str=std::string((const char*)strBytes,strLen);
    
    CC_SAFE_DELETE_ARRAY(strBytes);
    
    return str;
}

void readElement(InputStream* is,FcaElement& element)
{
    element.name=readString(is);
    element.textureKey=readString(is);
    element.index=is->readInt32();
}

void readElements(FcaInfo* fcaInfo,InputStream* is)
{
    int elementCount=is->readInt32();
    
    FcaElement emptyElement={"","",0};
    
    for (int i=0; i<elementCount; ++i) {
        
        fcaInfo->getElements().push_back(emptyElement);
        
        readElement(is, fcaInfo->getElements().back());
    }
}

void readFrameEvent(InputStream* is,FcaFrameEvent& frameEvent)
{
    
    frameEvent.type=is->readInt32();
    frameEvent.arg=readString(is);
    
    frameEvent.anchor.x=is->readFloat();
    frameEvent.anchor.y=is->readFloat();
    
    frameEvent.matrix.a=is->readFloat();
    frameEvent.matrix.b=is->readFloat();
    frameEvent.matrix.c=is->readFloat();
    frameEvent.matrix.d=is->readFloat();
    frameEvent.matrix.tx=is->readFloat();
    frameEvent.matrix.ty=is->readFloat();
    
    frameEvent.index=is->readInt32();
}


void readActionFrameEvents(FcaInfo* fcaInfo,InputStream* is,FcaFrame& frame)
{
    int eventCount=is->readInt32();
    
    if (eventCount) {
        
        FcaFrameEvent emptyEvent;
        
        for (int i=0; i<eventCount; ++i) {
            frame.events.push_back(emptyEvent);
            readFrameEvent(is, frame.events.back());
        }
    }
}

void readFrameElements(FcaInfo* fcaInfo,InputStream* is,FcaFrame& frame)
{
    
}

void readActionFrame(FcaInfo* fcaInfo,InputStream* is,FcaFrame& frame)
{
    readActionFrameEvents(fcaInfo, is, frame);
    
    readFrameElements(fcaInfo, is, frame);
}

void readActionFrames(FcaInfo* fcaInfo,InputStream* is,FcaAction& action)
{
    int frameCount=is->readInt32();
    
    FcaFrame emptyFrame;
    
    for (int i=0; i<frameCount; ++i) {
        
        action.frames.push_back(emptyFrame);
        
        readActionFrame(fcaInfo, is, action.frames.back());
    }
}

void readAction(FcaInfo* fcaInfo,InputStream* is,FcaAction action)
{
    
    action.name=readString(is);
    action.fps=is->readFloat();
    
    readActionFrames(fcaInfo, is,action);

}

void readActions(FcaInfo* fcaInfo,InputStream* is)
{
    int actionCount=is->readInt32();
    
    FcaAction emptyAction;
    
    for (int i=0; i<actionCount; ++i) {
        
        fcaInfo->getActions().push_back(emptyAction);
        
        fcaInfo->getActions().back().name=readString(is);
        fcaInfo->getActions().back().fps=is->readFloat();
        
        readActionFrames(fcaInfo, is);
        
    }
}

void readCha(FcaInfo* fcaInfo,unsigned char* data,size_t size)
{
    Buffer* buffer=new Buffer(data,size,false);
    
    InputStream* is=new InputStream();
    is->init(buffer);
    is->setEndianness(kLittleEndian);
    
    fcaInfo->setName(readString(is));
    
    readElement(fcaInfo, is);
    
    readAction(fcaInfo, is);
    
    buffer->release();
    is->release();
    
}

NS_CC_GE_END