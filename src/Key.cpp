#include "Key.hpp"


namespace cb
{


void Key::handleReleasedEvents(const sf::Event& event)
{
	if (oncereleased)
	{
		//if (event.type == sf::Event::KeyPressed && event.key.code == key)
		if (sf::Keyboard::isKeyPressed(key))
		{
			once = true;
		}
		else
		{
			if (once)
			{
				once = false;
				oncereleased = true;
			}
		}
	}
}

void Key::handlePressedEvents(const sf::Event& event)
{
	if (!oncepressed)
	{
		if (onetime)
		{
			if (event.type == sf::Event::KeyReleased && event.key.code == key)
			{
				onetime = false;
			}
		}
		else if (sf::Keyboard::isKeyPressed(key))
		{
			onetime = true;
			oncepressed = true;
		}
		else
		{
			onetime = false;
		}
	}
}


void Key::update()
{
	if (oncepressed)
	{
		oncepressed = false;
	}

	if (oncereleased)
	{
		oncereleased = false;
	}
}


}
