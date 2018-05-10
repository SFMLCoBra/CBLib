#include "AnimationSprite.hpp"


namespace cb
{


AnimationSprite::AnimationSprite()
	: playing(false), looped(true), currentFrame(0), 
	animation(nullptr), frameTime(sf::seconds(1.0)), time(sf::Time::Zero)
{
}

AnimationSprite::AnimationSprite(const Animation & animation)
	: AnimationSprite()
{
	this->animation = &animation;
}

AnimationSprite::~AnimationSprite()
{
	animation = nullptr;
}


void AnimationSprite::updateAnimation(sf::Time frameTime)
{
	if (isPlaying())
	{
		// add the frame time to the total time
		time += frameTime;

		if (time >= this->frameTime)
		{
			time = time % frameTime;

			setNextFrame();
		}
	}
}

void AnimationSprite::startAnimation()
{
	playing = true;
}

void AnimationSprite::playAnimation(const Animation & animation)
{
	this->animation = &animation;
	currentFrame = 0;
	frameTime = sf::Time::Zero;

	startAnimation();
}

void AnimationSprite::pauseAnimation()
{
	playing = false;
}

void AnimationSprite::resetAnimation(bool stillPlaying)
{
	currentFrame = 0;
	time = sf::Time::Zero;

	if (stillPlaying)
	{
		playing = true;
	}
	else
	{
		playing = false;
	}
}


void AnimationSprite::setAnimation(const Animation & animation, sf::Time frameTime)
{
	this->animation = &animation;
	currentFrame = 0;
	this->frameTime = frameTime;
	time = sf::Time::Zero;
}

void AnimationSprite::setLooped(bool animation)
{
	looped = animation;
}

void AnimationSprite::setFrameTime(sf::Time time)
{
	this->frameTime = time;
}

void AnimationSprite::setNextFrame()
{
	if (animation != nullptr)
	{
		// is the end reached
		if ((++currentFrame) >= animation->getSize())
		{
			// don't start the animation again if 
			// it's not looped
			if (!looped)
			{
				playing = false;
			}
			currentFrame = 0;
		}

		setTextureRect(animation->getFrame(currentFrame));
	}
}

bool AnimationSprite::isLooped() const
{
	return looped;
}

bool AnimationSprite::isPlaying() const
{
	return playing;
}

const sf::Vector2f& AnimationSprite::getSize() const
{
	if (animation != nullptr)
		return sf::Vector2f((float)animation->getFrame(currentFrame).width, (float)animation->getFrame(currentFrame).height);
}

const sf::Time &AnimationSprite::getFrameTime() const
{
	return frameTime;
}

}