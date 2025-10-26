#pragma once
#include "raw/weapon.h"
#include "screen/hud_skill.h"

class WeaponThunder : public Weapon
{
protected:
    HUDSkill* hud_skill_ = nullptr;

public:
    static WeaponThunder* addWeaponThunderChild(Actor* parent, float cool_down, float mana_cost);

    virtual void init() override;
    virtual bool handleEvents(SDL_Event& event) override;
    virtual void update(float dt) override;
};