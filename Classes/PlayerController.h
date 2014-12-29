//
//  PlayerController.h
//  RichGame
//
//  Created by Sucre on 14/12/27.
//
//

#ifndef __RichGame__PlayerController__
#define __RichGame__PlayerController__

#include <stdio.h>
#include "cocos2d.h"
#include "RicherPlayer.h"
USING_NS_CC;
class PlayerController:public Layer
{
public:
    static PlayerController *instance;
    static PlayerController *getInstance();
    ~PlayerController();
    void startwalk(std::vector<int> hangvector,std::vector<int> lievector,RicherPlayer *player);
    void endwalk();
    virtual bool init();
    CREATE_FUNC(PlayerController);
    void pickonetogo();
private:
    Action *Walk;
    int currenthang,currentlie,nexthang,nextlie;
    int stepshasgone;//已走的步数
    int stepscount;//需要走得步数
    MoveBy *moveby;
    Repeat *repeat;
    CallFunc *callend;
    
    std::vector<int> _hangvector;
    std::vector<int>_lievector;
    RicherPlayer *_player;
    bool isAnimFinished;
    void walkonestep(RicherPlayer *player);//走一步的函数
    
};
#endif /* defined(__RichGame__PlayerController__) */
