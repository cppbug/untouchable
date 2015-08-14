//
//  EndGameScene.cpp
//  unctouchable
//
//  Created by Vinova on 8/15/15.
//
//

#include "EndGameScene.h"
#include "CocosGUI.h"
#include "GamePlayScene.h"

namespace unt {
    Scene* EndGameScene::createScene()
    {
        Scene *scene = Scene::create();
        auto *layer = EndGameScene::create();
        scene->addChild(layer);
        
        return scene;
    }
    
    bool EndGameScene::init()
    {
        if (!Node::init())
            return false;
        
        auto winSize = Director::getInstance()->getOpenGLView()->getDesignResolutionSize();
        setContentSize(winSize);
        
        Label *label = Label::create();
        label->setSystemFontSize(80);
        label->setString("YOU LOSE!!");
        label->setAlignment(TextHAlignment::CENTER);
        label->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        label->setPosition(Vec2(winSize.width / 2, winSize.height / 2 + 100));
        addChild(label);
        
        ui::Button *button = ui::Button::create();
        button->setTitleFontSize(40);
        button->setTitleText("[PRESS TO REPLAY]");
        button->setPosition(winSize / 2);
        button->setZoomScale(-0.05);
        button->addClickEventListener([](Ref *r) {
            Director::getInstance()->replaceScene(GamePlayScene::createScene());
        });
        addChild(button);
        
        return true;
    }
}