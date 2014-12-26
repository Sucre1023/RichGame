//
//  GetWalkPath.cpp
//  RichGame
//
//  Created by Sucre on 14/12/26.
//
//

#include "GetWalkPath.h"
//单列模式定义该类
GetWalkPath *GetWalkPath::instance =NULL;
GetWalkPath::GetWalkPath(void)
{
    struct timeval now;
    gettimeofday(&now, NULL);
    unsigned rand_seed =(unsigned)(now.tv_sec*1000 + now.tv_usec/1000);
    srand(rand_seed);
}
GetWalkPath::~GetWalkPath(void)
{
    instance =NULL;
    pathhang_vector.clear();
    pathlie_vector.clear();
    std::vector<int>(pathhang_vector).swap(pathhang_vector);
    std::vector<int>(pathlie_vector).swap(pathlie_vector);

}
GetWalkPath *GetWalkPath::getInstance()
{
    if (!instance) {
        instance =new GetWalkPath();
    }
    return instance;
}

void GetWalkPath::getpath(cocos2d::Sprite *playerSprite, int stepsCount, bool **canpassgrid, int HangInGrid, int LieInGrid)
{
    pathhang_vector.clear();
    pathlie_vector.clear();
    //定义当前位置行列、下一步位置行列
    int currentHang,currentLie;
    int nextHang,nextLie;
    //获取人物所在位置坐标
    float x =playerSprite->getPositionX();
    float y =playerSprite->getPositionY();
    //转换为行列
    currentLie =x/32;
    currentHang =(y-34)/34;
    
    std::vector<bool> direction_4;//当前位置的4个方向的位置是否可以走
    std::vector<int>  canwalk_direction;//4个方向可以走的位置
    //赋值canpassgrid
    bool** canpassgrid_copy =new bool *[HangInGrid];
    for (int hang; hang<HangInGrid; hang++) {
        for (int lie; lie <LieInGrid; lie++) {
            canpassgrid_copy[hang][lie] =canpassgrid[hang][lie];
        }
    }
    
    
    int n =0;
    while (n<stepsCount)
    {
        //初始化数组为false
        direction_4.clear();
        canwalk_direction.clear();
        for(int i=0;i<4;i++)
        {
            direction_4.push_back(false);
        
        }
        //分别判断四个方向
        direction_4[Up] =iscanwalk_direction_4(currentHang, currentLie, Up, canpassgrid);
        direction_4[Down] =iscanwalk_direction_4(currentHang, currentLie, Down, canpassgrid);
        direction_4[Left] =iscanwalk_direction_4(currentHang, currentLie, Left, canpassgrid);
        direction_4[Right] =iscanwalk_direction_4(currentHang, currentLie, Right, canpassgrid);
        //存入可以行走的方向
        for (int i=0; i<4; i++) {
            if (direction_4[i]) {
                canwalk_direction.push_back(i);
            }
        }
        //在可以行走的方向随机选一个,赋值下一步的行列数
        int rand_direction =rand()%canwalk_direction.size();
        switch (rand_direction) {
            case Up:
                nextHang =currentHang -1;
                nextLie =currentLie;
                break;
            case Down:
                nextHang =currentHang +1;
                nextLie =currentLie;
                break;
            case Left:
                nextHang =currentHang;
                nextLie =currentLie -1;
                break;
            case Right:
                nextHang =currentHang;
                nextLie =currentLie +1;
                break;
                
            default:
                break;
        }
        //储存行列到容器
        pathhang_vector.push_back(nextHang);
        pathlie_vector.push_back(nextLie);
        //前一步置为false
        canpassgrid[currentHang][currentLie] =false;
        //
        currentHang =nextHang;
        currentLie =nextLie;
        //
        n++;
        
    }
    //释放内存
    CC_SAFE_DELETE(canpassgrid_copy);
    direction_4.clear();
    canwalk_direction.clear();
    std::vector<bool>(direction_4).swap(direction_4);
    std::vector<int>(canwalk_direction).swap(canwalk_direction);
    
    

}
bool GetWalkPath::iscanwalk_direction_4(int hang, int lie, int direction, bool **canpassgrid)
{

    switch (direction)
    {
        case Up:{
            return canpassgrid[hang-1][lie];
            break;}
        case Down:{
            return canpassgrid[hang+1][lie];
            break;}
        case Left:{
            return canpassgrid[hang][lie-1];
            break;}
        case Right:{
            return canpassgrid[hang][lie+1];
            break;}
     
    }
    return false;
    
}