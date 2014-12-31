//
//  PopupLayer.h
//  RichGame
//
//  Created by Sucre on 14/12/30.
//
//

#ifndef __RichGame__PopupLayer__
#define __RichGame__PopupLayer__

#include <stdio.h>
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
USING_NS_CC_EXT;
USING_NS_CC;
class PopupLayer:public Layer
{
public:
    PopupLayer();
    ~PopupLayer();
    virtual bool init();
    CREATE_FUNC(PopupLayer);
    
    static PopupLayer *create(const char *backgroundImage);//根据图片创建窗口
    void setTitle(const char*title,int fontsize =20);//设置对话框标题
    void setContentText(const char *text,int fontsize=20,int padding =50,int paddingTop =100 );//对话框文本
    void setcallbackfunc(Ref*target,SEL_CallFuncN callfun);
    bool addButton(const char *normalImage,const char *selectedImage,const char*title,int tag=0);//添加按钮
    
    virtual void onEnter();
    virtual void onExit();
private:
    void buttonCallback(Ref *p);//按钮回调
    int m_contentPadding;//文字内容的两边空白区距离
    int m_contentPaddingTop;//文字上边空白区距离
    Size winSize;
    
    Ref *m_callbackListener;
    SEL_CallFuncN m_callback;
    
    CC_SYNTHESIZE_RETAIN(Menu*, _menubutton, Menubutton);
    CC_SYNTHESIZE_RETAIN(Sprite*, _backgroundsp, Backgroundsp);
    CC_SYNTHESIZE_RETAIN(Scale9Sprite*, _backgrounds9sp, Backgrounds9sp);
    CC_SYNTHESIZE_RETAIN(Label*, _titlelabel, Titlelabel);
    CC_SYNTHESIZE_RETAIN(LabelTTF*, _contentlabel, Contentlabel);
    
};

#endif /* defined(__RichGame__PopupLayer__) */
