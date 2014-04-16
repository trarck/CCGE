#include "DimetricCoordinateLayer.h"
#include <yhge/yhge.h>

USING_NS_CC;

USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

DimetricCoordinateLayer::DimetricCoordinateLayer()
:m_iMapWidth(0)
,m_iMapHeight(0)
,m_bIsShow(true)
{

}

// on "init" you need to initialize your instance
bool DimetricCoordinateLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    return true;
}

void DimetricCoordinateLayer::draw()
{
	if(m_bIsShow){
		int i,j;
		CCPoint to;
		CCPoint from;

		ccDrawColor4B(255,0,0,255);
		//draw yias
		for(i=0;i<=m_iMapWidth;i++){
//			from=dimetric::StaticSideViewCoordinateFormulae::gameToView2F(i,0);
//			to=dimetric::StaticSideViewCoordinateFormulae::gameToView2F(i,m_iMapHeight);
            
            from=dimetric::StaticTopViewCoordinateFormulae::gameToView2F(i,0);
			to=dimetric::StaticTopViewCoordinateFormulae::gameToView2F(i,m_iMapHeight);
			
			ccDrawLine( from, to );
		}
		//draw xias
		for(j=0;j<=m_iMapHeight;j++){
//			from=dimetric::StaticSideViewCoordinateFormulae::gameToView2F(0,j);
//			to=dimetric::StaticSideViewCoordinateFormulae::gameToView2F(m_iMapWidth,j);

            from=dimetric::StaticTopViewCoordinateFormulae::gameToView2F(0,j);
			to=dimetric::StaticTopViewCoordinateFormulae::gameToView2F(m_iMapWidth,j);
            
			ccDrawLine( from, to );
		}
	}
}

void DimetricCoordinateLayer::showCoordinate(bool isShow)
{
	m_bIsShow=isShow;
}


void DimetricCoordinateLayer::setMapWidth(int iMapWidth)
{
    m_iMapWidth = iMapWidth;
}

int DimetricCoordinateLayer::getMapWidth()
{
    return m_iMapWidth;
}

void DimetricCoordinateLayer::setMapHeight(int iMapHeight)
{
    m_iMapHeight = iMapHeight;
}

int DimetricCoordinateLayer::getMapHeight()
{
    return m_iMapHeight;
}

NS_CC_GE_END