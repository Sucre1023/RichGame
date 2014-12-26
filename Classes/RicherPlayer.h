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
public:
    static RicherPlayer* create(char* name,SpriteFrame* spriteFrame,bool enemy,int money=50000,int strength=100);
    bool init(char* name,SpriteFrame* spriteFrame,bool enemy,int money,int strength);
private:
    CC_SYNTHESIZE(std::string, _name, Name);
    CC_SYNTHESIZE(int, _money, Money);
    CC_SYNTHESIZE(int, _strength, Strength);
    CC_SYNTHESIZE(bool, _enemy, Enemy);
    
};
#endif /* defined(__RichGame__RicherPlayer__) */

