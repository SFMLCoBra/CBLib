#include "Animation.hpp"
#include "Data.hpp"
/*
// for the frame time
*/
#include "TimeData.hpp"


namespace cb
{

Animation::Animation()
	: tex(nullptr)
{
}
Animation::Animation(const sf::Texture &texture)
{
	tex = &texture;
}

Animation::~Animation()
{
	tex = nullptr;
}

void Animation::addFrame(const sf::IntRect& frameSize)
{
	vframes.push_back(frameSize);
}

void Animation::setSpriteSheet(const sf::Texture & tex)
{
	this->tex = &tex;
}

const sf::IntRect& Animation::getFrame(const std::size_t& index) const
{
	if (index > vframes.size())
	{
		try
		{
			return vframes[index];
		}
		catch (const std::exception& e)
		{
			CB_DEFAULT_ERROR_MSG("index: " + std::to_string(index) + " doesn't exist, because  \
						    vframes is too small: " + std::to_string(vframes.size()));

			std::cerr << e.what() << std::endl:
		}
	}

	

	return sf::IntRect{};
}

const sf::Texture * Animation::getSpriteSheet() const
{
	return tex;
}

std::size_t Animation::getSize() const
{
	return vframes.size();
}

}