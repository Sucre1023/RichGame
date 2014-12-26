//
//  RicherPlayer.cpp
//  RichGame
//
//  Created by Sucre on 14/12/25.
//
//

#include "RicherPlayer.h"
RicherPlayer *RicherPlayer::create(char* name,SpriteFrame* spriteFrame,bool enemy,int money,int strength)
{
    RicherPlayer *player =new RicherPlayer;
    player->init(name,spriteFrame, enemy, money, strength);
    player->autorelease();
    return player;
}
bool RicherPlayer::init(char *name, cocos2d::SpriteFrame *spriteFrame, bool enemy, int money, int strength)
{

    Sprite::initWithSpriteFrame(spriteFrame);
    _name = name;
    _enemy = enemy;
    _money = money;
    _strength = strength;
    return true;

}