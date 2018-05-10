#ifndef CB_TIMEDATA_HPP
#define CB_TIMEDATA_HPP


#include <SFML/Graphics.hpp>


namespace cb
{

/*
//  use:
//  - gives you a total time since the creating
//  - can give you the actual total time and even
//    chane the time elapse
//  - multiplier for the time
//  - can calculate the frame time
//  - can give you the system Time
*/
class TimeData
{
public:
	TimeData();
	virtual ~TimeData();

	// METHODS

	/*
	// This updates the total time:
	// time between the updates x speed.
	*/
	void update();

	/*
	// Restarts the frameClock by
	*/
	void restart();

	/*
	// Returns the time since the last call of this
	// method
	*/
	void calcFrametime();

	// SETTER

	/*
	// Sets the how fast the time should elapse.
	// Default 1.0f.
	*/
	void setSpeed(float timeSpeed);

	// GETTER

	/*
	// Returns the total time since
	// the last update.
	*/
	float getTotalTime();

	/*
	// This returns the multiplyer for the time
	// default: 1.0f (normal).
	*/
	const float& getSpeed();

	/*
	// This returns the total time without any multiplyer
	// since the constructor was called!
	*/
	float getRealTotalTime();

	/*
	// This returns the time since the last
	// call of this function (or constructor).
	*/
	float getFrameTime();

	/*
	// Returns the actual elapsed time.
	*/
	float getFrameTimeActual();

	/*
	// Returns the system time in milliseconds.
	// see: c++ <chrono> at http://de.cppreference.com/w/cpp/chrono
	*/
	static long long getSystemTime();

private:
	sf::Time frameTime;
	sf::Clock frameTimeClock;

	sf::Time bef, aft;

	sf::Clock	Clock;
	sf::Clock	totalClock;

	float totalTime;

	float timeSpeed;
};

}

#endif