//
//  GetWalkPath.h
//  RichGame
//
//  Created by Sucre on 14/12/26.
//
//

#ifndef __RichGame__GetWalkPath__
#define __RichGame__GetWalkPath__

#include <stdio.h>
#include "cocos2d.h"
#include "RicherPlayer.h"
USING_NS_CC;
//
const int Up =0;
const int Down =1;
const int Left =2;
const int Right =3;
class GetWalkPath
{
public:
    static GetWalkPath *instance;//该类的静态对象
    static GetWalkPath *getInstance();//获取静态对象的方法
    
    void getpath(RicherPlayer *player,int stepsCount,bool**canpassgrid,int HangInGrid,int LieInGrid );//stepscount:要走的步数 canpassgrid:地图能否走动的二维数组  HangInGrid:canpassgird数组的行数  LieInGrid:数组的列数
    bool iscanwalk_direction_4(int hang,int lie,int direction,bool** canpassgrid);//判断四个方向的位置是否可以走的方法
private:
    CC_SYNTHESIZE(std::vector<int>, pathhang_vector, Pathhang_vector);
    CC_SYNTHESIZE(std::vector<int>, pathlie_vector, Pathlie_vector);
protected:
    GetWalkPath(void);
    ~GetWalkPath(void);

};
#endif /* defined(__RichGame__GetWalkPath__) */
