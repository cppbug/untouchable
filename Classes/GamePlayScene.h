//
//  GamePlayScene.h
//  unctouchable
//
//  Created by Vinova on 8/15/15.
//
//

#pragma once
#include "cocos2d.h"
#include "BlockHouse.h"
#include "Bullet.h"
#include "Monster.h"

USING_NS_CC;

namespace unt {
    class GamePlayScene : public Node
    {
    public:
        static Scene* createScene();
        
    private:
        float genMonsterTimer;
        
        BlockHouse *blockHouse;
        
        Vector<Bullet *> bullets;
        Vector<Monster *> monsters;
        
        bool onTouchBegan(Touch *t, Event *e);
        void onTouchMoved(Touch *t, Event *e);
        void onTouchEnded(Touch *t, Event *e);
        void onTouchCancelled(Touch *t, Event *e);
        
        void generateMonster();
        void checkCollision();
        bool handleCollision(Node *a, Node *b);
        
    public:
        bool init();
        void update(float dt);
        
        void addBullet(Bullet *bullet);
        
        CREATE_FUNC(GamePlayScene);
    };
}