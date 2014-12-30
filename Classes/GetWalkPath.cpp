//
//  GetWalkPath.cpp
//  RichGame
//
//  Created by Sucre on 14/12/26.
//
//

#include "GetWalkPath.h"
#include "GameBaseScene.h"
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

void GetWalkPath::getpath(RicherPlayer *player, int stepsCount, bool **canpassgrid, int HangInGrid, int LieInGrid)
{
    pathhang_vector.clear();
    pathlie_vector.clear();
    //定义当前位置行列、下一步位置行列
    int currentHang,currentLie;
    int nextHang,nextLie;
    //获取人物所在位置坐标
    float x =player->getPositionX();
    float y =player->getPositionY();
    //转换为行列
    currentLie =x/34;
    currentHang =(y-32)/32;
    pathhang_vector.push_back(currentHang);
    pathlie_vector.push_back(currentLie);
  
    //复制canpassgrid
    bool** canpassgrid_copy =new bool *[HangInGrid];
    for (int i=0; i<HangInGrid; i++)
       canpassgrid_copy[i] =new bool[LieInGrid];
    
    for (int hang =0; hang<HangInGrid; hang++) {
        for (int lie =0; lie<LieInGrid; lie++) {
            canpassgrid_copy[hang][lie] =canpassgrid[hang][lie];
        }
    }
    //角色从哪来
    int hangtem =player->getComeFromHang();
    int lietemp =player->getComeFromLie();
    if (hangtem <=-1||lietemp <=-1) {
        player->setComeFromHang(currentHang);
        player->setComeFromLie(currentLie);
    }
    canpassgrid_copy[player->getComeFromHang()][player->getComeFromLie()]=false;
    
    std::vector<bool> direction_4;//当前位置的4个方向的位置是否可以走
    std::vector<int>  canwalk_direction;//4个方向可以走的位置
    int n =0;
    while (n<stepsCount)
    {
        //初始化数组为false
        direction_4.clear();
        for(int i=0;i<4;i++)
        {
            direction_4.push_back(false);
        
        }
        canwalk_direction.clear();
        //分别判断四个方向
        direction_4[Up] =iscanwalk_direction_4(currentHang, currentLie, Up, canpassgrid_copy);
        direction_4[Down] =iscanwalk_direction_4(currentHang, currentLie, Down, canpassgrid_copy);
        direction_4[Left] =iscanwalk_direction_4(currentHang, currentLie, Left, canpassgrid_copy);
        direction_4[Right] =iscanwalk_direction_4(currentHang, currentLie, Right, canpassgrid_copy);
        //存入可以行走的方向
        for (int i=0; i<4; i++)
        {
            if (direction_4[i])
            {
                canwalk_direction.push_back(i);
            }
        }

//        if (canwalk_direction.size()==0)
//        {
//            canpassgrid_copy[player->getComeFromHang()][player->getComeFromLie()]=true;
//            for (int i=0; i<4; i++)
//            {
//                if (direction_4[i])
//                {
//                    canwalk_direction.push_back(i);
//                }
//            }
//            rand_direction =rand()%canwalk_direction.size();
//
//            
//        }
//        
//        else
//        {
//        rand_direction =rand()%canwalk_direction.size();
//            
//        }
        //在可以行走的方向随机选一个,赋值下一步的行列数
        int rand_direction =rand()%canwalk_direction.size();
        switch (canwalk_direction[rand_direction])
        {
            case Up:
                nextHang =currentHang +1;
                nextLie =currentLie;
                break;
            case Down:
                nextHang =currentHang -1;
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
        canpassgrid_copy[currentHang][currentLie] =false;
        //
        currentHang =nextHang;
        currentLie =nextLie;
        //
        n=n+1;
        
    }
  //pathhang_vector里包含了当前位置
    if (pathhang_vector.size() ==2)
    {
        player->setComeFromHang(pathhang_vector[pathhang_vector.size()-1]);
        player->setComeFromLie(pathlie_vector[pathlie_vector.size()-1]);
    }else
    {
    player->setComeFromHang(pathhang_vector[pathhang_vector.size()-2]);
        player->setComeFromLie(pathlie_vector[pathlie_vector.size()-2]);
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
            return canpassgrid[hang +1][lie];
            }
        case Down:{
            return canpassgrid[hang -1][lie];
            }
        case Left:{
            return canpassgrid[hang][lie-1];
           }
        case Right:{
            return canpassgrid[hang][lie+1];
           }
     
    }
    return false;
    
}