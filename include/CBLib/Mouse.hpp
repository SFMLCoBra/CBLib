#ifndef CB_MOUSE_HPP
#define CB_MOUSE_HPP

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Data.hpp"


namespace cb
{

/*
// Run the 'handleEvents' in sf::RenderWindow::pollEvents().
*/
class Mouse
{
public:
	Mouse();
	~Mouse();

	static bool isLeftOnceClicked();
	static bool isRightOnceClicked();

	static bool isLeftPressedOnce();
	static bool isRightPressedOnce();

	/*
	// update once per each frame/event 
	*/
	static void update();
	static void reset();

	static void handleEvents(const sf::Event& event);

	/*
	// Checks if the mouse wasn't moving for 'sec' time.
	*/
	bool mouseWaitsForSecs(float sec);

private:
	static sf::Clock clock;
	static sf::Vector2i lastmouse;
	/*
	// Mouse is not moving for this duration.
	*/
	static float notMovedDuration;

	static bool leftonceclicked;
	static bool leftpressedonce;
	static bool rightonceclicked;
	static bool rightpressedonce;
};


}

#endif