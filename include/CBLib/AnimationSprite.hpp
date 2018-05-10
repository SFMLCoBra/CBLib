#ifndef CB_ANIMATEDSPRITE_HPP
#define CB_ANIMATEDSPRITE_HPP

#include "Animation.hpp"

namespace cb
{

/*
// A sprite with a Texture/Sprite sheet
// which has an 'animation const pointer to 
// an animation' which can be used as:
// \n
// Animation anim; 
// \n ...
// AnimSprite spr(&anim);
*/
class AnimationSprite : public sf::Sprite
{
public:
	AnimationSprite();
	AnimationSprite(const Animation& animation);
	virtual ~AnimationSprite();

	// METHODS

	/*
	// Takes time between 2 frames as argument.
	// This updates the sprite to change
	// its frame. After 'frame time' it
	// changes the frame to the next one
	// (ordered by setFrame(...) in the 
	// animation class).
	// If 'looped' is set, it restarts
	// the animation.
	*/
	void updateAnimation(sf::Time frameTime);

	/*
	// Simply sets animating true.
	*/
	void startAnimation();

	/*
	// Resets and sets the new animation 
	// and calls playAnimation().
	*/
	void playAnimation(const Animation& animation);

	/*
	// Simply stops the animation at the current frame.
	*/
	void pauseAnimation();

	/*
	// Resets the animation to the first frame
	*/
	void resetAnimation(bool playing = true);
	

	// SETTER

	/*
	// Sets the Animation and the time between frames.
	// Default 1.0 seconds.
	*/
	void setAnimation(const Animation& animation, sf::Time frameTime = sf::seconds(1.0));

	/*
	// Should the animation start anew 
	// or simply stop animating after 
	// the last frame.
	// default: true (looping)
	*/
	void setLooped(bool animation);

	/*
	// Time step between frames.
	*/
	void setFrameTime(sf::Time time);

	/*
	// this will automaticly called in 
	// the update method.
	*/
	void setNextFrame();


	// GETTER

	bool isLooped() const;
	bool isPlaying() const;
	/*
	// returns the size of the actual frame
	*/
	sf::Vector2f getSize() const;
	const sf::Time& getFrameTime() const;


private:
	const Animation* animation;

	std::size_t currentFrame;
	bool looped;
	bool playing;

	/*
	// Time between 2 frames
	*/
	sf::Time frameTime;
	sf::Time time;
};


}

#endif

