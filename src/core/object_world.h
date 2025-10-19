#pragma once
#include "object_screen.h"

class ObjectWorld : public ObjectScreen
{
protected:
    glm::vec2 position_ = glm::vec2(0, 0); // 世界位置
    virtual void init() override { type_ = ObjectType::OBJECT_WORLD; }

public:

    virtual void update(float dt) override;

    // getters and stters
    glm::vec2 getPosition() const { return position_; }
    void setPosition(const glm::vec2& position);
    virtual void setRenderPosition(const glm::vec2& render_position) override;
};