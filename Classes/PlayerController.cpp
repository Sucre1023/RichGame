//
//  PlayerController.cpp
//  RichGame
//
//  Created by Sucre on 14/12/27.
//
//

#include "PlayerController.h"
#include "GameBaseScene.h"
PlayerController *PlayerController::instance =NULL;
bool PlayerController::init()
{
    if (!Layer::init()) {
        return false;
    }
    callend =CallFunc::create(CC_CALLBACK_0(PlayerController::endwalk, this));
    return  true;

}
PlayerController *PlayerController::getInstance()
{
    if (!instance) {
        instance =PlayerController::create();
        
    }
    instance->retain();
    return instance;

}
PlayerController::~PlayerController()
{
    Walk->release();

}

void PlayerController::startwalk(std::vector<int> hangvector, std::vector<int> lievector, RicherPlayer *player)
{
    //初始化行列
    currenthang =hangvector[0];
    currentlie =lievector[0];
    nexthang =0;nextlie=0;
    
    _hangvector =hangvector;
    _lievector =lievector;
    _player =player;
    isAnimFinished =false;
    stepshasgone =0;
    stepscount =(int) _hangvector.size()-1;//减去当前的位置
    walkonestep(player);
}
void PlayerController::walkonestep(RicherPlayer *player)
{
//获取下一步的位置
    nexthang =_hangvector[stepshasgone +1];
    nextlie =_lievector[stepshasgone +1];
    //两步之间的 行和列 的差，用来判断方向
    int hangDistance =nexthang -currenthang;
    int lieDistance =nextlie -currentlie;
    if (hangDistance > 0)//向上
    {
        moveby =MoveBy::create(0.1f, Point(0,32));
        repeat =Repeat::create(player->getup_animate(), 1);
    }
    if (hangDistance < 0)//向下
    {
        moveby =MoveBy::create(0.1f, Point(0,-32));
        repeat =Repeat::create(player->getdown_animate(), 1);
    }
    if (lieDistance > 0)//向右
    {
        moveby =MoveBy::create(0.1f, Point(34,0));
        repeat =Repeat::create(player->getright_animate(), 1);
    }
    if (lieDistance < 0)//向下
    {
        moveby =MoveBy::create(0.1f, Point(-34,0));
        repeat =Repeat::create(player->getdown_animate(), 1);
    }
    //
    Walk =Sequence::create(Spawn::create(moveby,repeat, NULL),callend ,NULL);//spawn:让多个动作调试执行
    Walk->retain();
    player->runAction(Walk);
}
void PlayerController::endwalk()
{
    stepshasgone++;
    if (stepshasgone>=stepscount) {
        return;
    }
    currenthang =nexthang;
    currentlie =nextlie;
    walkonestep(_player);
    
    
}