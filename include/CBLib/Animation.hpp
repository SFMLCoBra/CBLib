#ifndef CB_ANIMATION_HPP
#define CB_ANIMATION_HPP

#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

namespace cb
{

/*
// - contains a reference(!) to the Texture.
//	 the texture musn't be deleted until this instance is destroyed.
// - the order of the add Frame calls
//   determines the animation order
*/
class Animation
{
public:
	Animation();
	Animation(const sf::Texture& spriteSheet);
	virtual ~Animation();


	// METHODS

	/*
	// Define the frame which should be displayed first.
	// The order of the add Frame calls
	// determines the animation order.
	// e.g.:
	// addFrame( { 0, 0 , 32, 32 } );
	// defines a clip on x=0 | y=0 | w=32 | h=32
	// as the first frame..
	*/
	void addFrame(const sf::IntRect& frameSize);

	
	// SETTER
	/*
	// 
	*/
	void setSpriteSheet(const sf::Texture& tex);


	// GETTER
	
	/*
	// Returns Rectangle.
	// Returns default contructor copy of sf::IntRect if index => size of vector.
	*/
	const sf::IntRect& getFrame(const std::size_t& index) const;
	/*
	// Returns nullptr if no texture given.
	*/
	const sf::Texture* getSpriteSheet() const;
	std::size_t getSize() const;

private:
	const sf::Texture* tex;
	std::vector<sf::IntRect> vframes;
};

}

#endif