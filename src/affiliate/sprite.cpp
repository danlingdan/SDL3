#include "sprite.h"

Texture::Texture(const std::string& file_path)
{
    texture = Game::GetInstance().getAssetStore()->getImage(file_path);
    SDL_GetTextureSize(texture, &src_rect.w, &src_rect.h);
}


Sprite* Sprite::addSpriteChild(ObjectScreen* parrent, const std::string& file_path, float scale)
{
    auto sprite = new Sprite();
    sprite->init();
    sprite->setTexture(Texture(file_path));
    sprite->setScale(scale);
    sprite->setParrent(parrent);
    parrent->addChild(sprite);
    return sprite;
}

void Sprite::render()
{
    if (!texture_.texture || !parrent_ || is_finish_) return;
    auto pos = parrent_->getRenderPosition() + offset_;
    game_.renderTexture(texture_, pos, size_);   //解耦
}

void Sprite::setTexture(const Texture& texture)
{
    texture_ = texture;
    size_ = glm::vec2(texture.src_rect.w, texture.src_rect.h);
}
