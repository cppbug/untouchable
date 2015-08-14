//
//  Bullet.h
//  unctouchable
//
//  Created by Vinova on 8/15/15.
//
//

#pragma once
#include "cocos2d.h"

USING_NS_CC;

namespace unt {
    class Bullet : public Node
    {
    public:
        static int TAG;
    private:
        Vec2 velocity;
        float ttl;
        
    public:
        bool initWithDirection(Vec2 dir);
        void update(float dt);
        
        static Bullet* createWithDirection(Vec2 dir);
    };
}