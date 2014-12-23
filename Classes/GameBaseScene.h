//
//  GameBaseScene.h
//  RichGame
//
//  Created by Sucre on 14/12/23.
//
//

#ifndef __RichGame__GameBaseScene__
#define __RichGame__GameBaseScene__

#include <stdio.h>
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
USING_NS_CC_EXT;
USING_NS_CC;
class GameBaseScene:public Layer
{
public:
    Size visibleSie;
    virtual bool init();
    static Scene*createScene();
    CREATE_FUNC(GameBaseScene);
    TMXTiledMap *_map;
    virtual void addMap();
private:
    //void drawTable(int playnumber);//根据人数绘画右边信息栏的表格
    void addPlayer();//添加人物
    Sprite *rightbanner;

};
#endif /* defined(__RichGame__GameBaseScene__) */
