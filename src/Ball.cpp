#include "Ball.h"
#include "constants.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include "Maths.h"

Ball::Ball() : Entity(new sf::CircleShape())
{
    auto* circle = dynamic_cast<sf::CircleShape*>(m_shape);
    circle->setRadius(10.0f);
    circle->setFillColor(sf::Color::White);
    circle->setOrigin(circle->getRadius(), circle->getRadius());
    Radius = circle->getRadius();
}

void Ball::Update(float dt, sf::RenderWindow& window)
{
    m_shape->move(m_Velocity * dt);
    if((m_Velocity.x != 0 || m_Velocity.y != 0) && m_NextParticleEmit <= 0)
    {
        m_ParticleEmitter.Emit(GetPosition(),
                               -m_Velocity * 0.1f,
                               0.5f,
                               sf::Color{150, 150, 150},
                               Radius);
        m_NextParticleEmit =  EMISSION_RATE;
    }
    m_NextParticleEmit -= dt;

    UpdateParticles(dt);
    UpdateShake(dt);
}

void Ball::UpdateParticles(float dt)
{
    m_ParticleEmitter.Update(dt);
}

void Ball::ResetPosition()
{
    m_shape->setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
}

void Ball::ChooseInitialVelocity()
{
    float angleDeg = std::rand() % 91 - 45;
    float angleRad = angleDeg * 3.14f / 180.f;
    int direction = (std::rand() % 2 == 0) ? 1 : -1;
    m_Velocity = sf::Vector2f(std::cos(angleRad) * direction,
                              std::sin(angleRad)) * 400.f;
}


void Ball::Render(sf::RenderWindow& window)
{
    m_ParticleEmitter.Render(window);
    window.draw(*m_shape);
}

void Ball::CheckBoundaries()
{
	if (GetPosition().y < 0)
	{
		m_Velocity.y = -m_Velocity.y;
        EmitRandomParticles(5);
    }

	if (GetPosition().y + Radius * 2 > WINDOW_HEIGHT)
	{
		m_Velocity.y = -m_Velocity.y;
        EmitRandomParticles(5);
	}
}

void Ball::CheckCollision(Player& player)
{
	sf::FloatRect playerBounds = player.GetBounds();
	sf::FloatRect ballBounds = GetBounds();

	if (playerBounds.intersects(ballBounds))
	{
		m_Velocity.x = -m_Velocity.x;

		float relativeY = (player.GetPosition().y + player.Size.y / 2) - (GetPosition().y + Radius);

		float maxSpeedChange = 200.f;
		m_Velocity.y += -maxSpeedChange * (relativeY / (player.Size.y / 2));

        EmitRandomParticles(10);

        player.Shake();
    }
}

void Ball::EmitRandomParticles(int num)
{
    Shake();
    for(int i = 0; i < num; ++i)
    {
        auto direction = randomDirection2D() * 400.f;
        m_ParticleEmitter.Emit(GetPosition(),
                               direction,
                               0.2f,
                               sf::Color{150, 150, 150},
                               Radius * 0.5f);
    }
}
