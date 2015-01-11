//
//  Util.h
//  RichGame
//
//  Created by Sucre on 14/12/31.
//
//

#ifndef RichGame_Util_h
#define RichGame_Util_h

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
USING_NS_CC_EXT;
USING_NS_CC;
struct Util
{
 //把layer层上的坐标转换为GL坐标
    static Point maptoGl(const Point &ptmap,TMXTiledMap *map)
    {
        Point  ptUI;
        ptUI.x =ptmap.x *map->getTileSize().width;
        ptUI.y =(ptmap.y +1) *map->getTileSize().height;
        
        Point ptGL =ptUI;
        ptGL.y =map->getContentSize().height -ptUI.y;
        return ptGL;
    }
    //把GL坐标转换为layer上的坐标，这样layer层根据坐标就可以判断当前位置的title ID
    static Point GLtomap(const Point &ptGL,TMXTiledMap *map)
    {
        Point ptUI =ptGL;
        ptUI.y =map->getContentSize().height -ptGL.y;
        int x =ptUI.x /map->getTileSize().width;
        int y =ptUI.y /map->getTileSize().height;
        return Point(x,y);
    }
    //截取字符
    static Vector<String*> splitString(const char *srcStr,const char *sSep)
    {
        Vector<String*> stringList;
        int size =strlen(srcStr);
        String *str =String::create(srcStr);
        
        int startIndex =0;
        int endIndex =0;
        endIndex =str->_string.find(sSep);
        String *spliStr =NULL;
        
        while(endIndex >0)
        {
            spliStr =CCString::create("");
            spliStr->_string =str->_string.substr(startIndex,endIndex);
            stringList.pushBack(spliStr);
            endIndex =str->_string.find(sSep);
        }
        if(str->_string.compare("") !=0)
        {
            stringList.pushBack(String::create(str->_string));
        }
        return stringList;
        
    }

};

#endif
