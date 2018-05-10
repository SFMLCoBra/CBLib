#include "Mouse.hpp"


namespace cb
{

bool  Mouse::leftonceclicked{ false };
bool  Mouse::leftpressedonce{ false };
bool Mouse::rightonceclicked{ false };
bool Mouse::rightpressedonce{ false };

sf::Clock Mouse::clock;
sf::Vector2i Mouse::lastmouse;
float Mouse::notMovedDuration{ 0.0f };


Mouse::Mouse()
{
}

Mouse::~Mouse()
{
}

bool Mouse::isLeftOnceClicked()
{
	return leftonceclicked;
}

bool Mouse::isRightOnceClicked()
{
	return rightonceclicked;
}

bool Mouse::isLeftPressedOnce()
{
	return leftpressedonce;
}

bool Mouse::isRightPressedOnce()
{
	return rightpressedonce;
}

void Mouse::handleEvents(const sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
	{
		leftonceclicked = true;
	}
	else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	{
		leftpressedonce = true;
	}

	if (event.type == sf::Event::MouseButtonReleased&& event.mouseButton.button == sf::Mouse::Right)
	{
		rightonceclicked = true;
	}
	else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
	{
		rightpressedonce = true;
	}
}

void Mouse::reset()
{
	leftonceclicked = false;
	leftpressedonce = false;
	rightonceclicked = false;
	rightpressedonce = false;
}

void Mouse::update()
{
	// check mouse
	if (lastmouse == sf::Mouse::getPosition())
	{
		notMovedDuration = clock.getElapsedTime().asSeconds();
	}
	else
	{
		clock.restart();
		notMovedDuration = 0.0f;
	}

	lastmouse = sf::Mouse::getPosition();
}

bool Mouse::mouseWaitsForSecs(float time)
{
	if (time < notMovedDuration)
	{
		return true;
	}
	return false;
}


}
