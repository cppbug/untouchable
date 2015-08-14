//
//  EndGameScene.h
//  unctouchable
//
//  Created by Vinova on 8/15/15.
//
//

#pragma once
#include "cocos2d.h"

USING_NS_CC;

namespace unt {
    class EndGameScene : public Node
    {
    public:
        static Scene* createScene();
        
    public:
        bool init();
        
        CREATE_FUNC(EndGameScene);
    };
}