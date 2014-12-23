//
//  MapChooseScene.h
//  RichGame
//
//  Created by Sucre on 14/12/22.
//
//

#ifndef __RichGame__MapChooseScene__
#define __RichGame__MapChooseScene__

#include <stdio.h>
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
USING_NS_CC_EXT;
USING_NS_CC;
const int MAP_COUNT =3;
const int TOUCH_INSTANCE =50;
class MapChooseScene:public Layer,public ScrollViewDelegate
{
public:
    virtual bool init();
    static Scene *createScene();
    CREATE_FUNC(MapChooseScene);
private:
    int currentpage;
    Size visibleSize;
    ScrollView *scrollview;
    Point beginingpoint;
    Layer *mapcontainer;//存放3张地图
    void addscrollview();
    void adjustscrollview(float t);
    void onTouchEnded(Touch*touch,Event *event);
    bool onTouchBegan(Touch * touch,Event *event);

};
#endif /* defined(__RichGame__MapChooseScene__) */
