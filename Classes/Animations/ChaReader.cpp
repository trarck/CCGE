#include "ChaReader.h"
#include <yhge/yhge.h>

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN


std::string readString(InputStream* is)
{
    int strLen=is->readInt32();

    unsigned char* strBytes=new unsigned char[strLen];
    
    is->readBytes(strBytes, strLen);
    
    std::string str=std::string((const char*)strBytes,strLen);
    
    CC_SAFE_DELETE_ARRAY(strBytes);
    
    return str;
}

CCAffineTransform readMatrix(InputStream* is)
{
    CCAffineTransform matrix;
    
    matrix.a=is->readFloat();
    matrix.b=is->readFloat();
    matrix.c=is->readFloat();
    matrix.d=is->readFloat();
    matrix.tx=is->readFloat();
    matrix.ty=is->readFloat();
    
    return matrix;
}


void readElement(FcaInfo* fcaInfo,InputStream* is,FcaElement& element)
{
    element.name=readString(is);
    element.textureKey=readString(is);
    element.index=is->readInt32();
    
    CCSpriteFrame* spriteFrame=fcaInfo->getSpriteFrame(element.textureKey);
    if (spriteFrame) {
        element.size=spriteFrame->getOriginalSize();
    }
    
}

void readElements(FcaInfo* fcaInfo,InputStream* is)
{
    int elementCount=is->readInt32();
    
    FcaElement emptyElement={"","",0};
    
    for (int i=0; i<elementCount; ++i) {
        
        fcaInfo->getElements().push_back(emptyElement);
        
        readElement(fcaInfo,is, fcaInfo->getElements().back());
    }
}

void readFrameEvent(InputStream* is,FcaFrameEvent& frameEvent)
{
    
    frameEvent.type=is->readInt32();
    frameEvent.arg=readString(is);
    
    frameEvent.anchor.x=is->readFloat();
    frameEvent.anchor.y=is->readFloat();
    
    frameEvent.matrix=readMatrix(is);
    
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

void readFrameElement(FcaInfo* fcaInfo,InputStream* is,FcaFrameElement& frameElement)
{
    frameElement.index=is->readInt16();
    frameElement.alpha=is->readUInt8();
    frameElement.matrix=readMatrix(is);
    
}

void readFrameElements(FcaInfo* fcaInfo,InputStream* is,FcaFrame& frame)
{
    int frameCount=is->readInt32();
    
    FcaFrameElement emptyElement;
    
    for (int i=0; i<frameCount; ++i) {
        
        frame.elements.push_back(emptyElement);
        
        readFrameElement(fcaInfo, is, frame.elements.back());
    }

}

void readActionFrame(FcaInfo* fcaInfo,InputStream* is,FcaFrame& frame)
{
    readActionFrameEvents(fcaInfo, is, frame);
    
    readFrameElements(fcaInfo, is, frame);
}

void readActionFrames(FcaInfo* fcaInfo,InputStream* is,FcaAction& action)
{
    int frameCount=is->readInt32();
    
    CCLOG("%s,%d",action.name.c_str(),frameCount);
    
    FcaFrame emptyFrame;
    
    for (int i=0; i<frameCount; ++i) {
        
        action.frames.push_back(emptyFrame);
        
        readActionFrame(fcaInfo, is, action.frames.back());
    }
}

void readAction(FcaInfo* fcaInfo,InputStream* is,FcaAction& action)
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
       
        readAction(fcaInfo, is,fcaInfo->getActions().back());
    }
}

void readCha(FcaInfo* fcaInfo,unsigned char* data,size_t size)
{
    Buffer* buffer=new Buffer(data,size,false);
    
    InputStream* is=new InputStream();
    is->init(buffer);
    is->setEndianness(kLittleEndian);
    
    fcaInfo->setName(readString(is));
    
    readElements(fcaInfo, is);
    
    readActions(fcaInfo, is);
    
    buffer->release();
    is->release();
}

NS_CC_GE_END