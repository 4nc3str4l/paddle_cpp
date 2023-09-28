#pragma once

#include "Entity.h"
#include "ParticleEmitter.h"

#include <SFML/Audio.hpp>


class Player;

inline const float EMISSION_RATE = 0.01f;

class Ball : public Entity
{
public:
    Ball();
    void Update(float dt, sf::RenderWindow &window) override;
    void Render(sf::RenderWindow &window) override;
    void ChooseInitialVelocity();
    void ResetPosition();
    void CheckBoundaries();
    void CheckCollision(Player& player);
    void EmitRandomParticles(int num);
    void UpdateParticles(float dt);

public:
    float Radius{0.0f};

private:
    sf::Vector2f m_Velocity{0.0f, 0.0f};
    float m_NextParticleEmit {0.0f};
    ParticleEmitter m_ParticleEmitter;



};