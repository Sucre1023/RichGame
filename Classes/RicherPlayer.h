//
//  RicherPlayer.h
//  RichGame
//
//  Created by Sucre on 14/12/25.
//
//

#ifndef __RichGame__RicherPlayer__
#define __RichGame__RicherPlayer__

#include <stdio.h>
#include"cocos2d.h"
#include "extensions/cocos-ext.h"
USING_NS_CC_EXT;
USING_NS_CC;
class RicherPlayer:public Sprite
{
    RicherPlayer();
    ~RicherPlayer();
public:
    static RicherPlayer* create(char* name,int tag,bool enemy,int money=50000,int strength=100);
    bool init(char* name,int tag,bool enemy,int money,int strength);
    void startgo(std::vector<int> hangvector,std::vector<int>lievector);
    void addSpriteFrameCache();
    void addPlayerAnimate();
    SpriteFrameCache *player_spriteframecache;
        //存放精灵缓存帧中同一个方向的四张图片
       CC_SYNTHESIZE(Vector<SpriteFrame*>, player_left_direction, player_left_direction);
       CC_SYNTHESIZE(Vector<SpriteFrame*>, player_right_direction, player_right_direction);
       CC_SYNTHESIZE(Vector<SpriteFrame*>, player_up_direction, player_up_direction);
       CC_SYNTHESIZE(Vector<SpriteFrame*>, player_down_direction, player_down_direction);
        //
    CC_SYNTHESIZE(Animate*, player_left_animate, left_animate);
    CC_SYNTHESIZE(Animate*, player_right_animate, right_animate);
    CC_SYNTHESIZE(Animate*, player_up_animate, up_animate);
    CC_SYNTHESIZE(Animate*, player_down_animate, down_animate);
  
private:
    CC_SYNTHESIZE(std::string, _name, Name);
    CC_SYNTHESIZE(int, _money, Money);
    CC_SYNTHESIZE(int, _strength, Strength);
    CC_SYNTHESIZE(bool, _enemy, Enemy);
    //
    CC_SYNTHESIZE(int, _comefromhang, ComeFromHang);
    CC_SYNTHESIZE(int, _comefromlie, ComeFromLie);
    
};
#endif /* defined(__RichGame__RicherPlayer__) */

