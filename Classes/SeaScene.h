//
//  SeaScene.h
//  RichGame
//
//  Created by Sucre on 14/12/23.
//
//

#ifndef __RichGame__SeaScene__
#define __RichGame__SeaScene__

#include <stdio.h>
#include "cocos2d.h"
#include "GameBaseScene.h"
#include "extensions/cocos-ext.h"
USING_NS_CC_EXT;
USING_NS_CC;
class SeaScene:public GameBaseScene
{
public:
    virtual bool init();
    static Scene*createScene();
    CREATE_FUNC(SeaScene);
    

};
#endif /* defined(__RichGame__SeaScene__) */
