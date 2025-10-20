#pragma once
#include "object_screen.h"

class ObjectAffiliate : public Object
{
protected:
    ObjectScreen* parrent_ = nullptr; // 父节点
    glm::vec2 offset_ = glm::vec2(0, 0); // 相对父节点的偏移
    glm::vec2 size_ = glm::vec2(0, 0); // 大小

public:
    // getters and setters
    ObjectScreen* getParrent() const { return parrent_; }
    void setParrent(ObjectScreen* parrent) { parrent_ = parrent; }
    glm::vec2 getOffset() const { return offset_; }
    void setOffset(const glm::vec2& offset) { offset_ = offset; }
    glm::vec2 getSize() const { return size_; }
    void setSize(const glm::vec2& size) { size_ = size; }
};