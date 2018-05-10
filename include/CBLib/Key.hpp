#ifndef CB_KEY_HPP
#define CB_KEY_HPP

#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>

namespace cb
{


/*
Important: set a value for event!
1) update after calling ispressedonce/releaseonce.
*/

class Key
{
public:
	Key(sf::Keyboard::Key K) : key(K) {}
	Key() {}
	~Key() {}

	inline bool IsKeyPressedOnce()
	{
		return oncepressed;
	}

	inline bool IsKeyReleasedOnce()
	{
		return oncereleased;
	}

	void update();
	void handleReleasedEvents(const sf::Event& event);
	void handlePressedEvents(const sf::Event& event);

	void setKey(sf::Keyboard::Key K) { key = K; }

	inline sf::Keyboard::Key getKey() const 
	{
		return key;
	}

private:
	sf::Keyboard::Key key;

	// Those two are needed...
	bool onetime{ false };
	bool once{ false };

	bool clicked{ false };

	bool oncepressed{ false };
	bool oncereleased{ false };
};


}

#endif