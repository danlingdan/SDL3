#pragma once
#include "../core/object_affiliate.h"
#include <string>

struct Texture
{
    SDL_Texture* texture = nullptr;
    SDL_FRect src_rect = { 0, 0, 0, 0 };
    float angle = 0;
    bool is_flip = false;
    Texture() = default;
    Texture(const std::string& file_path);
};

class Sprite : public ObjectAffiliate
{
protected:
    Texture texture_;

public:
    static Sprite* addSpriteChild(ObjectScreen* parrent, const std::string& file_path, float scale = 1.0f);

    virtual void render() override;

    // getters and setters
    Texture getTexture() const { return texture_; }
    virtual void setTexture(const Texture& texture);
    void setScale(float scale) { size_ *= scale; }

};