#include "TextureManager.hpp"

#include <locale> 
#include <algorithm>
#include <string>

#include "Data.hpp"
#include "TextDocument.hpp"


namespace cb
{


TextureManager::TextureManager()
{
}


TextureManager::~TextureManager()
{
	std::cout << textures.empty() << std::endl;
}

void TextureManager::clearContainer()
{
	textures.clear();
}

bool TextureManager::loadTexturesWithinFile(const std::string& path)
{
	if (!cb::TextDocument::dirExists(path))
	{
		CB_DEFAULT_ERROR_MSG("File doesn't exist: " + path);
		return false;
	}

	std::vector<std::string> fileNames = TextDocument::getFilenamesInDir(path);
	std::vector<std::string> vtextures;
	std::string fileEnding;
	// last point
	size_t last;

	for (auto& fileName : fileNames)
	{
		if ((last = fileName.find_last_of('.')) == std::string::npos)
			continue;

		fileEnding = fileName.substr(last, fileName.size() - last);
		
		// bmp, png, tga, jpg, gif, psd, hdr and pic
		if (fileEnding == ".png" || fileEnding == ".bmp" || fileEnding == ".tga" || fileEnding == ".jpg" ||
			fileEnding == ".hdr" || fileEnding == ".gif" || fileEnding == ".psd" || fileEnding == ".pic")
		{
			vtextures.push_back(fileName);
		}
	}

	std::locale loc;
	for (auto& textureString : vtextures)
	{
		for (size_t key = 0; key < textureString.size(); key++)
		{
			textureString[key] = std::tolower(textureString[key], loc);
		}
	}

	sf::Texture texture;
	for (auto&& textureString : vtextures)
	{		
		texture.loadFromFile(path + "//" + textureString);
		textures.insert(std::pair<std::string, sf::Texture>(textureString, texture));
	}
	return true;
}

bool TextureManager::loadTexture(const std::string& fN, const std::string & path)
{
	// load the texture
	sf::Texture texture;
	if (!texture.loadFromFile(path))
		return false;

	// is the file type supported
	size_t last;
	std::string fileName = fN;
	if ((last = fileName.find_last_of('.')) == std::string::npos)
		return false;

	// lower File names character
	std::string textureName = fN;
	std::transform(textureName.begin(), textureName.end(), textureName.begin(), ::tolower);

	std::string fileEnding = fileName.substr(last, fileName.size() - last);

	// bmp, png, tga, jpg, gif, psd, hdr and pic
	if (fileEnding == ".png" || fileEnding == ".bmp" || fileEnding == ".tga" || fileEnding == ".jpg" ||
		fileEnding == ".hdr" || fileEnding == ".gif" || fileEnding == ".psd" || fileEnding == ".pic")
	{
		textures.insert(std::pair<std::string, sf::Texture>(fileName, texture));
	}

	return true;
}

const std::map<std::string, sf::Texture>::iterator& TextureManager::getTexture(const std::string& tN)
{
	std::locale loc;

	std::string textureName = tN;

	for (auto& character : textureName)
	{
		character = std::tolower(character, loc);
	}

	const std::map<std::string, sf::Texture>::iterator& it = textures.find(textureName.c_str());

	if (it == textures.end())
	{
		CB_DEFAULT_ERROR_MSG("couldn't load texture: " + textureName);
	}

	return it;
}




}