#ifndef CB_FONTLOADER_HPP
#define CB_FONTLOADER_HPP

#include <map>
#include <memory>


#include <SFML/Graphics.hpp>


namespace cb
{


class FontLoader
{
public:
	FontLoader();
	virtual ~FontLoader();


	/*
	// Loads font from file.
	*/
	bool loadFont(const std::string& path, const std::string& fontName);


	const sf::Font& getFont(const std::string& fontName);

	/*
	// Empties the container and pushs the key values/names from the loaded fonts.
	*/
	void getFontNames(std::vector<std::string>& container) const;
	
	/*
	// returns the font names.
	*/
	const std::vector<std::string>& getFontNames() const;

private:

	std::map<std::string, sf::Font> fonts;
};


}

#endif