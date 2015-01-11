//
//  PopupLayer.cpp
//  RichGame
//
//  Created by Sucre on 14/12/30.
//
//

#include "PopupLayer.h"
PopupLayer::PopupLayer():_menubutton(NULL),m_contentPadding(0),m_contentPaddingTop(0),m_callbackListener(NULL),m_callback(NULL),
_backgroundsp(NULL),_backgrounds9sp(NULL),_titlelabel(NULL),_contentlabel(NULL){}

PopupLayer::~PopupLayer()
{
    CC_SAFE_RELEASE(_menubutton);
    CC_SAFE_RELEASE(_backgroundsp);
    CC_SAFE_RELEASE(_backgrounds9sp);
    CC_SAFE_RELEASE(_titlelabel);
    CC_SAFE_RELEASE(_contentlabel);

}
void PopupLayer::setcallbackfunc(Ref*target, SEL_CallFuncN callfun)
{
    //menuitem根据传入的对象，会进行方法的回调
    m_callback =callfun;
    m_callbackListener =target;
    
    
}

bool PopupLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    winSize =Director::getInstance()->getWinSize();
    this->setContentSize(Size::ZERO);
   //初始化 Menu
    Menu *menu =Menu::create();
    menu->setPosition(Point::ZERO);
    setMenubutton(menu);
    //添加监听
    setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
    auto listner =EventListenerTouchOneByOne::create();
    listner->setSwallowTouches(true);//消息不往下传递
    listner->onTouchBegan=[](Touch *touch,Event *event){
        log("PopupLayer touch");
        return true;
    };
   _eventDispatcher->addEventListenerWithSceneGraphPriority(listner, this);

    return true;
}

PopupLayer *PopupLayer::create(const char *backgroundImage)
{
    PopupLayer *Im =PopupLayer::create();
    Im->setBackgroundsp(Sprite::create(backgroundImage));
    Im->setBackgrounds9sp(Scale9Sprite::create(backgroundImage));
    return Im;
}
//
void PopupLayer::setTitle(const char *title,int fontsize)
{
    Label *titlelabel =Label::create(title,"",20);
    setTitlelabel(titlelabel);
}
void PopupLayer::setContentText(const char *text,int fontsize,int padding,int paddingTop)
{
    LabelTTF *content =LabelTTF::create(text, "", 20);
    setContentlabel(content);
    m_contentPadding =padding;
    m_contentPaddingTop =paddingTop;
    
}

//创建button
bool PopupLayer::addButton(const char *normalImage, const char *selectedImage, const char *title,int tag)
{
    MenuItemImage *menuitemimage =MenuItemImage::create(normalImage, selectedImage, this,menu_selector(PopupLayer::buttonCallback));
    menuitemimage->setTag(tag);
    menuitemimage->setPosition(winSize.width/2,winSize.height/2);
    
    //按钮上的文字
    Size menuItemSize = menuitemimage->getContentSize();
    Label *text =Label::create(title,"",20);
    text->setColor(Color3B::BLACK);
    text->setPosition(menuItemSize.width/2, menuItemSize.height/2);
    menuitemimage->addChild(text);
    
    getMenubutton()->addChild(menuitemimage);
    return true;
    
}
void PopupLayer::buttonCallback(cocos2d::Ref *p)
{
    Node *node =dynamic_cast<Node*>(p);
    log("touch tag: %d",node->getTag());
    
    if (m_callback && m_callbackListener) {
        (m_callbackListener->*m_callback)(node);
    }
    this->removeFromParent();

}
//对话框弹出前调用进行界面初始化工作
void PopupLayer::onEnter()
{
    Layer::onEnter();
    Size contentSize;
    Point center =Point(winSize.width/2,winSize.height/2);
    //对话框背景
    if (getContentSize().equals(Size::ZERO))
    {
        getBackgroundsp()->setPosition(winSize.width/2,winSize.height/2);
        this->addChild(getBackgroundsp(),0,0);
        contentSize =getBackgroundsp()->getTexture()->getContentSize();
    }else{
        Scale9Sprite *background =getBackgrounds9sp();
        background->setContentSize(getContentSize());
        background->setPosition(winSize.width/2,winSize.height/2);
        this->addChild(background,0,0);
        contentSize =getContentSize();
    
    }
    //添加按钮
    this->addChild(getMenubutton());
    float btnWidth =contentSize.width/(getMenubutton()->getChildrenCount() +1);
    Vector<Node*>button_vector =getMenubutton()->getChildren();
    int j=0;
    for (auto it =button_vector.begin(); it!=button_vector.end(); it++) {
        Node *node =dynamic_cast<Node*>(*it);
        node->setPosition(winSize.width/2 -contentSize.width/2+btnWidth*(j+1),winSize.height/2-contentSize.height/3);
        j++;
    }
    
    //显示对话框标题
    if (getTitlelabel())
    {
        getTitlelabel()->setPosition(winSize.width/2,winSize.height/2+contentSize.height/2 -20);
        getTitlelabel()->setColor(Color3B::BLACK);
        this->addChild(getTitlelabel());
    }
    if (getContentlabel()) {
        LabelTTF *ct =getContentlabel();
        ct->setPosition(winSize.width/2,winSize.height/2);
        ct->setDimensions(CCSizeMake(contentSize.width -m_contentPadding*2, contentSize.height -m_contentPaddingTop));
        ct->setColor(Color3B::BLACK);
        this->addChild(ct);
        
    }
    
    //添加对话框出现动画
   // Action *popuplayer_disappear =Sequence::create(ScaleTo::create(0.1, 1.0), NULL);
    //this->runAction(popuplayer_disappear);
}
void PopupLayer::onExit(){
    
    Layer::onExit();
    
}
