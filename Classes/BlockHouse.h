//
//  BlockHouse.h
//  unctouchable
//
//  Created by Vinova on 8/15/15.
//
//

#pragma once
#include "cocos2d.h"

USING_NS_CC;

namespace unt {
    class BlockHouse : public cocos2d::Node
    {
    private:
        float fireTime;
        Vec2 firePoint;
        Vec2 target;
        
        void fireBullet();
        
    public:
        bool init();
        void update(float dt) override;
        
        CC_SYNTHESIZE(bool, fireable, Fireable);
        void setTarget(Vec2 target);
        
        CREATE_FUNC(BlockHouse);
    };
}