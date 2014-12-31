//
//  MenuScene.h
//  RichGame
//
//  Created by Sucre on 14/12/22.
//
//

#ifndef __RichGame__MenuScene__
#define __RichGame__MenuScene__

#include <stdio.h>
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "PopupLayer.h"
USING_NS_CC_EXT;
USING_NS_CC;

class MenuScene:public LayerColor
{
public:
    virtual bool init();
    static Scene *createScene();
    CREATE_FUNC(MenuScene);
private:
    Size visibleSize;
    void addMenuSprites();
    void menuTouchDown (Ref* pSender,Control::EventType event);// Menu点击回调方法
    Label *setmusic;
    void popuplayer();
    void quitbtncallfunc(Node *p);
};
#endif /* defined(__RichGame__MenuScene__) */
