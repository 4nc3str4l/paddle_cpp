#include "UI.h"
#include <iostream>
#include <string>

#include "Game.h"
#include "Utils.h"
#include "constants.h"

UI::UI(Game* game) : m_Game(game)
{
}

bool UI::Init()
{
    auto f = FindInResources("./", "ARCADECLASSIC.TTF");
    if (!font.loadFromFile(f))
	{
		std::cout << "Error loading font" << std::endl;
        return false;
	}

    leftScore.setFont(font);
	leftScore.setString(std::to_string(0));
	leftScore.setCharacterSize(50);
	leftScore.setFillColor(sf::Color::White);
	leftScore.setPosition(250, 10);

	rightScore.setFont(font);
	rightScore.setString(std::to_string(0));
	rightScore.setCharacterSize(50);
	rightScore.setFillColor(sf::Color::White);
	rightScore.setPosition(450, 10);

	winner.setFont(font);
	winner.setString("");
	winner.setCharacterSize(50);
	winner.setFillColor(sf::Color::White);
	winner.setPosition(150, 200);

	// Put the instruction just bellow the winner text
	instructions.setFont(font);
	instructions.setCharacterSize(50);
	instructions.setFillColor(sf::Color::White);
	instructions.setPosition(100, 300);

    SetInstruction("Press   Space   to   start");

    return true;
}

void UI::Render(sf::RenderTexture& window)
{
    window.draw(leftScore);
    window.draw(rightScore);

	if (m_Game->GetGameState() == GameState::Over)
	{
		window.draw(winner);
		window.draw(instructions);
	}
	if(m_Game->GetGameState() == GameState::Starting)
	{
		window.draw(instructions);
	}
	if(m_Game->GetGameState() == GameState::Paused)
	{
		window.draw(instructions);
	}
}

void UI::SetLeftScore(uint8_t score)
{
    leftScore.setString(std::to_string(score));
}

void UI::SetRightScore(uint8_t score)
{
    rightScore.setString(std::to_string(score));
}

void UI::Update(float dt, sf::RenderWindow& window)
{
    // Do nothing for now
}


void UI::SetWinner(bool isLeftPlayer)
{
	if (isLeftPlayer)
	{
		winner.setString("Left Player Wins!");
		CenterTextX(winner, {WINDOW_WIDTH, WINDOW_HEIGHT});
		SetInstruction("Press   R   to   restart");
	}
	else
	{
		winner.setString("Right Player Wins!");
		CenterTextX(winner, { WINDOW_WIDTH, WINDOW_HEIGHT });
		SetInstruction("Press   R   to   restart");
	}
}

void UI::SetInstruction(const std::string& instruction)
{
	instructions.setString(instruction);
    CenterTextX(instructions, { WINDOW_WIDTH, WINDOW_HEIGHT });
}