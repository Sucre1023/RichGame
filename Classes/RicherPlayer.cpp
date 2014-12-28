//
//  RicherPlayer.cpp
//  RichGame
//
//  Created by Sucre on 14/12/25.
//
//

#include "RicherPlayer.h"
#include "PlayerController.h"
#include "GameBaseScene.h"
PlayerController *plController;
RicherPlayer ::RicherPlayer()
{
    _comefromhang =-1;
    _comefromlie =-1;
}
RicherPlayer::~RicherPlayer()
{
}

RicherPlayer *RicherPlayer::create(char* name,int tag,bool enemy,int money,int strength)
{
    RicherPlayer *player =new RicherPlayer();
    player->init(name,tag, enemy, money, strength);
    player->autorelease();
    return player;
}
bool RicherPlayer::init(char *name, int tag, bool enemy, int money, int strength)
{
    this->setTag(tag);
    addSpriteFrameCache();
    SpriteFrame *spf;
    //根据tag从精灵缓存帧中取出第一张图片
    switch (tag) {
        case 1:
            spf =player_spriteframecache->getSpriteFrameByName("player1_anim_01.png");
            break;
        case 2:
            spf =player_spriteframecache->getSpriteFrameByName("player2_anim_01.png");
            break;
    }
    addPlayerAnimate();
    Sprite::initWithSpriteFrame(spf);
    _name = name;
    _enemy = enemy;
    _money = money;
    _strength = strength;
    plController =PlayerController::create();
    plController->retain();
    return true;

}


void RicherPlayer::addSpriteFrameCache()
{
    //根据tag加入完整的精灵缓存帧
    player_spriteframecache =SpriteFrameCache::getInstance();
    int tag =getTag();
    switch (tag) {
        case 1:
            player_spriteframecache->addSpriteFramesWithFile("player1_anim.plist", "player1_anim.png");
            break;
            
        case 2:
            player_spriteframecache->addSpriteFramesWithFile("player2_anim.plist", "player2_anim.png");
            break;
    }
    //按方向不同存入相应方向的容器
    char name[20];
    memset(name, 0, 20);//清零；前20个字节写入0
    for(int i=1;i<=4;i++)
    {
        sprintf(name, "player%d_anim_%02d.png",tag,i);//把1-4张图片写入name中
        player_left_direction.pushBack(player_spriteframecache->getSpriteFrameByName(name));
        
    }
    for(int i=5;i<=8;i++)
    {
        sprintf(name, "player%d_anim_%02d.png",tag,i);//把1-4张图片写入name中
        player_right_direction.pushBack(player_spriteframecache->getSpriteFrameByName(name));
        
    }
    for(int i=9;i<=12;i++)
    {
        sprintf(name, "player%d_anim_%02d.png",tag,i);//把1-4张图片写入name中
        player_down_direction.pushBack(player_spriteframecache->getSpriteFrameByName(name));
        
    }
    for(int i=13;i<=16;i++)
    {
        sprintf(name, "player%d_anim_%02d.png",tag,i);//把1-4张图片写入name中
        player_up_direction.pushBack(player_spriteframecache->getSpriteFrameByName(name));
        
    }
}
void RicherPlayer::addPlayerAnimate()
{
    int tag =getTag();
    //根据tag创建animation
    char player_left_animation[20];
    memset(player_left_animation, 0, 20);
    sprintf(player_left_animation, "player%d_left_animation",tag);

    char player_right_animation[20];
    memset(player_right_animation, 0, 20);
    sprintf(player_right_animation, "player%d_right_animation",tag);
    
    char player_down_animation[20];
    memset(player_down_animation, 0, 20);
    sprintf(player_down_animation, "player%d_down_animation",tag);
    
    char player_up_animation[20];
    memset(player_up_animation, 0, 20);
    sprintf(player_up_animation, "player%d_up_animation",tag);
    
    if (!AnimationCache::getInstance()->getAnimation(player_left_animation)) {
        AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(player_left_direction,0.07f), player_left_animation);
    }
    if (!AnimationCache::getInstance()->getAnimation(player_right_animation)) {
        AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(player_right_direction,0.07f), player_right_animation);
    }
    if (!AnimationCache::getInstance()->getAnimation(player_up_animation)) {
        AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(player_up_direction,0.07f), player_up_animation);
    }
    if (!AnimationCache::getInstance()->getAnimation(player_down_animation)) {
        AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(player_down_direction,0.07f), player_down_animation);
    }
    //创建animate动画
    player_left_animate =Animate::create(AnimationCache::getInstance()->getAnimation(player_left_animation));
    player_right_animate =Animate::create(AnimationCache::getInstance()->getAnimation(player_right_animation));
    player_up_animate =Animate::create(AnimationCache::getInstance()->getAnimation(player_up_animation));
    player_down_animate =Animate::create(AnimationCache::getInstance()->getAnimation(player_down_animation));
    //引用计数加一，防止被清除
    player_left_animate->retain();
    player_right_animate->retain();
    player_up_animate->retain();
    player_down_animate->retain();

}
void RicherPlayer::startgo(std::vector<int> hangvector, std::vector<int> lievector)
{
    PlayerController *instance =PlayerController::getInstance();
    instance->startwalk(hangvector, lievector, this);
    
}
