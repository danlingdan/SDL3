#pragma once
#include "sprite.h"

class SpriteAnim : public Sprite
{
    int current_frame_ = 0;
    int total_frames_ = 0;
    int fps_ = 10;
    float frame_timer_ = 0.0f;

public:
    static SpriteAnim* addSpriteAnimChild(ObjectScreen* parrent, const std::string& file_path, float scale = 1.0f);
    virtual void update(float dt) override;

    // getters and setters
    virtual void setTexture(const Texture& texture) override;

    int getCurrentFrame() const { return current_frame_; }
    void setCurrentFrame(int current_frame) { current_frame_ = current_frame; }
    int getTotalFrames() const { return total_frames_; }
    void setTotalFrames(int total_frames) { total_frames_ = total_frames; }
    int getFps() const { return fps_; }
    void setFps(int fps) { fps_ = fps; }

};