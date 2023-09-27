#pragma once

#include <SFML/Graphics.hpp>

struct Particle
{
    sf::Vector2f Position {0.f, 0.f};
    sf::Vector2f Velocity {0.f, 0.f};
    sf::Color Color {sf::Color::White};
    float Lifetime {0.f};

};

class ParticleEmitter
{
public:
    ParticleEmitter() = default;
    ~ParticleEmitter() = default;

    void Update(float dt);
    void Render(sf::RenderWindow &window);

    void Emit(const sf::Vector2f &position, const sf::Vector2f &velocity, float lifetime, sf::Color color);
private:
    std::vector<Particle> m_Particles {100};
    sf::CircleShape m_Shape {8.f};
};