//
//  Monster.h
//  unctouchable
//
//  Created by Vinova on 8/15/15.
//
//

#pragma once
#include "Monster.h"

USING_NS_CC;

namespace unt {
    class Monster : public Node
    {
    public:
        static int TAG;
    private:
        Vec2 velocity;
        
    public:
        bool init(const Color4F &color, Vec2 dir);
        void update(float dt);
        
        static Monster* create(const Color4F &color, Vec2 dir);
    };
}