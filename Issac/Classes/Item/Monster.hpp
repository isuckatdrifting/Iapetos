#ifndef Monster_hpp
#define Monster_hpp

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class Monster : public Sprite {
public:
    static Monster *createMonster();
    static Sprite *createSprite();
    bool init() override;
    
    CREATE_FUNC(Monster)
    
    CC_SYNTHESIZE_RETAIN(Animate*, idleAnimate, IdleAnimate)
    CC_SYNTHESIZE_RETAIN(Animate*, moveAnimate, MoveAnimate)
    
    CC_SYNTHESIZE(bool, moving, Moving)
    CC_SYNTHESIZE(int, prev_walk_orientation, PrevWalkOrientation)
    CC_SYNTHESIZE(int, prev_head_orientation, PrevHeadOrientation)
    
    void move(int walk_direction, int tear_direction);
    
private:
    void build_sprite_frame_cache(Texture2D *texture_) const;//必要时需要重载
    static void build_animation_cache();
};
#endif /* Monster_hpp */