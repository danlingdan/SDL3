#pragma once
#include "../core/object.h"

class BgStar : public Object {
protected:
    std::vector<glm::vec2> star_far_;
    std::vector<glm::vec2> star_mid_;
    std::vector<glm::vec2> star_near_;
    float scale_far_ = 0.2;
    float scale_mid_ = 0.5;
    float scale_near_ = 0.7;
    SDL_FColor color_far_ = { 0, 0, 0, 1 };
    SDL_FColor color_mid_ = { 0, 0, 0, 1 };
    SDL_FColor color_near_ = { 0, 0, 0, 1 };
    float timer_ = 0;
    int num_ = 2000;        // 每一层的星星数量

public:
    static BgStar* addBgStarChild(Object* parent, int num, float scale_far, float scale_mid, float scale_near);
    virtual void update(float dt) override;
    virtual void render() override;

    // getters and setters
    float getScaleFar() const { return scale_far_; }
    void setScaleFar(float scale_far) { scale_far_ = scale_far; }
    float getScaleMid() const { return scale_mid_; }
    void setScaleMid(float scale_mid) { scale_mid_ = scale_mid; }
    float getScaleNear() const { return scale_near_; }
    void setScaleNear(float scale_near) { scale_near_ = scale_near; }

};