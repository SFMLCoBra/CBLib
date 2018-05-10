#include "FontLoader.hpp"

#include "TextDocument.hpp"
#include "Data.hpp"


namespace cb
{

FontLoader::FontLoader()
{
}

FontLoader::~FontLoader()
{
}

const sf::Font& FontLoader::getFont(const std::string& fontName)
{
	if (fonts.empty())
	{
		CB_DEFAULT_ERROR_MSG("No fonts loaded.");
	}

	auto s = fonts.find(fontName);
	if (s != fonts.end())
	{
		return s->second;
	}

	CB_DEFAULT_ERROR_MSG("Couldn't find font: " + fontName);
}

void FontLoader::getFontNames(std::vector<std::string>& container) const
{
	if (!container.empty())
		container.clear();

	for (auto&& i : fonts)
	{
		container.push_back(i.first);
	}
}

const std::vector<std::string>& FontLoader::getFontNames() const
{
	std::vector<std::string> container;

	for (auto&& i : fonts)
	{
		container.push_back(i.first);
	}
	return container;
}

bool FontLoader::loadFont(const std::string& path, const std::string& fontName)
{
	std::pair<std::string, sf::Font> v;
	sf::Font& font = v.second;

	if (!(font.loadFromFile(path)))
	{
		CB_DEFAULT_ERROR_MSG("Couldn't load font: " + fontName + " from: " + path);
		return false;
	}

	v.first = fontName;
	fonts.insert(v);

	return true;
}


} 