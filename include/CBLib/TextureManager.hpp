#ifndef CB_TEXTUREMANAGER_HPP
#define CB_TEXTUREMANAGER_HPP

#include <iostream>
#include <map>

#include <SFML/Graphics.hpp>


namespace cb
{

/*
// This class should contain all used textures used.
// Saved as map<std::string, sf::Texture>.
// This can load all Textures within a certain folder
// with file extensions bmp, png, tga, jpg, gif, psd, hdr and pic.
*/
	class TextureManager
	{
	public:
		TextureManager();
		TextureManager(const TextureManager&) = delete;
		virtual ~TextureManager();

		TextureManager& operator=(const TextureManager&) = delete;


		// METHODS

		/*
		// This clears the map.
		*/
		void clearContainer();

		/*
		// Loads all textures within the path and names the key after the file name(!=path) without.
		// Without file ending.
		*/
		bool loadTexturesWithinFile(const std::string& path);

		/*
		// Loads all textures within the path and names the key after the file name.
		*/
		bool loadTexture(const std::string& fileName, const std::string & path);

		// SETTER


		// GETTER

		/*
		// returns nullptr if no texture found.
		*/
		const std::map<std::string, sf::Texture>::iterator& getTexture(const std::string& texturename);

private:
	std::map<std::string, sf::Texture> textures;
};


}

#endif