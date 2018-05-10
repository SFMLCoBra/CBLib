#include "TimeData.hpp"

#include <chrono>


namespace cb
{

TimeData::TimeData()
{
	timeSpeed = 1.f;
	bef = sf::Time::Zero;
	aft = sf::Time::Zero;
	totalTime = 0;

	totalClock.restart();
	frameTimeClock.restart();
}


TimeData::~TimeData()
{
}

void TimeData::update()
{
	aft = Clock.getElapsedTime();
	totalTime += ( (aft - bef).asSeconds() * timeSpeed);
	bef = aft;
}

void TimeData::setSpeed(float TimeSpeed)
{
	timeSpeed = TimeSpeed;
}

/*void TimeData::setTotalTime(float Time)
{
	totalTime = Time;
}*/

void TimeData::calcFrametime() 
{
	frameTime = frameTimeClock.restart();
}

float TimeData::getFrameTime()
{
	return frameTime.asSeconds();
}

float TimeData::getFrameTimeActual()
{
	return frameTimeClock.getElapsedTime().asSeconds();
}

long long TimeData::getSystemTime()
{
	auto ms =
		std::chrono::duration_cast<std::chrono::milliseconds>
		(std::chrono::system_clock::now().time_since_epoch()).count();
	return ms;
}

void TimeData::restart()
{
	frameTimeClock.restart();
}

float TimeData::getRealTotalTime()
{
	return totalClock.getElapsedTime().asSeconds();
}

float TimeData::getTotalTime()
{
	return totalTime;
}

const float& TimeData::getSpeed()
{
	return timeSpeed;
}

}