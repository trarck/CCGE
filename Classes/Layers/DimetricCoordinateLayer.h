#ifndef CCGE_LAYERS_DIMETRICCOORDINATELAYER_H_
#define CCGE_LAYERS_DIMETRICCOORDINATELAYER_H_

#include "cocos2d.h"
#include "CCGEMacros.h"

NS_CC_GE_BEGIN

class DimetricCoordinateLayer: public CCLayer
{
public:
	DimetricCoordinateLayer();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // implement the "static node()" method manually
    CREATE_FUNC(DimetricCoordinateLayer);
	
	virtual void draw();

	void showCoordinate(bool isShow);

	virtual void setMapWidth(int iMapWidth);
	virtual int getMapWidth();
	virtual void setMapHeight(int iMapHeight);
	virtual int getMapHeight();
private:
	int m_iMapWidth;
	int m_iMapHeight;
	bool m_bIsShow;
};

NS_CC_GE_END

#endif // CCGE_LAYERS_DIMETRICCOORDINATELAYER_H_
