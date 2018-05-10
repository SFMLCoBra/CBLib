#ifndef CB_TEXTDOCUMENT_HPP
#define CB_TEXTDOCUMENT_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <utility>

#include <io.h>
#include <sys/types.h>


#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>


namespace cb
{

/*
// Comes in handy when working with plain-text files. :D
// - create Files
// -> plain text
// - delete Files
// - write to files
// - create directory
// - get file names of directory
// - can create sections for reducing time traversing
//   the content
*/
class TextDocument
{
public:
	TextDocument();
	/*
	// Sets the path to the current file. (!= folder)
	*/
	TextDocument(const std::string& currentFilePath);
	virtual ~TextDocument();


	// METHODS


	// ------------------- File Operations ------------------------------------------

	/*
	// Returns true if directory exists.
	// example: "c:\\temp\\file"
	// (full path)
	*/
	static bool dirExists(const std::string &directoryName);

	/*
	// Checks if a path exists.
	*/
	static bool fileExists(const std::string &currentFilePath);

	/*
	// Creates a directory.
	// example: "c:\\temp\\file"
	// (full path or relative to project)
	*/
	bool createDirectory(const std::string &directoryName);

	/*
	// Writes the Content to the end of the file.
	// When no string given, then it's writing to the 'currentFilePath' attribute.
	// This won't overwrite the 'currentFilePath' attribute.
	*/
	bool writeContentToFile(const std::string &currentFilePath = "");

	/*
	// Over writes the Content of the file.
	// When no string given, then it's writing to the 'currentFilePath' attribute.
	// This won't overwrite the 'currentFilePath' attribute.
	*/
	void writeContentTruncToFile(const std::string &currentFilePath = "");

	/*
	// Writes the sections' content to the end of the file.
	*/
	void writeSectionToFile();

	/*
	// Will be saved as: <x:123>.
	// Writes plain text.
	// To write content to file call 'writeContentToFile()'.
	// Also: automaticly writes to section if 'beginSection()' was called
	// (ends with 'endSection()')
	*/
	void write(const std::string &variableName, const std::string &content);

	/*
	// Per default this loads all variables of a file.
	// If the addVar parameter is false, this loads the whole
	// file content to the 'content' attribute.
	*/
	bool loadFile(const std::string &filename, bool addVar = true);

	/*
	// Deletes file or directory (and its content/files).
	*/
	bool deleteFile(const std::string &currentFilePath);

	/*
	// Path to file
	// e.g.:
	// 1: "C:\\" or "C:/"
	// lists all files in C
	*/
	static std::vector<std::string> getFilenamesInDir(const std::string& path);

	/*
	// First argument is the path, the second is the extension.
	// e.g.:
	// 1: "C:\\" or "C:/"
	// 2: ".txt"
	// lists all files in C with extion
	*/
	static std::vector<std::string> getFilenamesInDirWithExt(const std::string& path, const std::string& ext);

	/*
	// First argument is the path, the second is the extension.
	// e.g.:
	// 1: "C:\\" or "C:/"
	// 2: ".txt"
	// lists all files in C without their extensions.
	// Doesn't list folder.
	*/
	static std::vector<std::string> getFilenamesInDirWithoutExt(const std::string& path);

	/*
	// Lowers the input string.
	*/
	static void lowerString(std::string& lowerThis);

	/*
	// Returns the string between first and second.
	// if first  == "" -> returns string from text beginning.
	// if second == "" -> returns string until end.
	*/
	static std::string getStringBetween(const std::string& text, const std::string& first, const std::string& second, std::size_t offset = 0);

	/*
	// Removes every occurence in the string and
	// replaces it with the replacement.
	// If deleteBorder == true 
	// -> removes the character infront and behind of the occurences.
	// Returns the amount of occurences.
	*/
	static int removeAllOccurencesAndInsert(std::string& str, const std::string& deleteThis, const std::string& insert, bool deleteBorder = false);

	/*
	// Removes the first occurence in the string and
	// replaces it with the replacement.
	// If deleteBorder == true
	// -> removes the character infront and behind of the occurence.
	// Returns the position of the occurence.
	*/
	static std::size_t removeOccurenceAndInsert(std::string& str, const std::string& deleteThis, const std::string& insert, std::size_t offset = 0, bool deleteBorder = false);

	/*
	// Find every occurence between the first and second
	// in the string.
	// Returns every text between first and second as a vector.
	*/
	static std::vector<std::string> getAllStringsBetween(const std::string& content, const std::string& first, const std::string& second);

	/*
	// Splits the text in lines.
	// if deleteEmpty == true -> deletes every line that's empty.
	// (empty: only contains '\n')
	// Returns the lines of the text in a vector.
	*/
	static std::vector<std::string> splitInLines(const std::string& text, bool deleteEmpty = false);



	// ------------------- File Content ------------------------------------------

	/*
	// Writes directly to the content string.
	// To write content to file call 'writeContentToFile()'.
	*/
	void writeToContent(const std::string &line, bool lineBreak = true);

	/*
	// Writes directly to the content string with a line at the end.
	// To write content to file call 'writeContentToFile()'.
	*/
	void writeLineToContent(const std::string &line);

	/*
	// Writes directly to the content.
	// To write content to file call 'writeContentToFile()'.
	*/
	void writeTruncToContent(const std::string &line);

	/*
	// Clears line count, saved content/section.
	*/
	void clearContent();

	/*
	// Clears actual content and sets the filename for further use.
	*/
	void clearToUseNewFile(const std::string &filename = "");




	// ------------------- Sections ------------------------------------------

	/*
	// Prepares to write a new section.
	// Marks new section in 'section' attribute (std::string).
	*/
	void beginSection();

	/*
	// Saves the lines of a section.
	// Marks the end of a section.
	*/
	void endSection();

	/*
	// Clears sections' std::string content and resets.
	*/
	void clearSection();

	/*
	// Appends the section to the 'content' attribute.
	*/
	void addSectionToContent();

	/*
	// When the whole file content is loaded into the string variable
	// and the file was created using sections this file can load
	// only a section to your variable(name) container.
	// Returns false if section couldn't be found.
	*/
	bool loadSection(int section);


	// SETTER

	/*
	// Sets only the currentFilePath.
	*/
	void setFileName(const std::string& currentFilePath);


	// GETTER

	/*
	// !You have to load the file before (load(std::string))!
	// returns content as std::string.
	// para 1: variable container name
	// para 2: index
	*/
	std::string getContent(const std::string& variableContainer, unsigned int index);

	/*
	// Uses the stoi function to cast the string to an integer.
	// Returns the casted content.
	*/
	int getContentAsInt(const std::string& var, unsigned int index);

	/*
	// Uses the getline function to read each line of file.
	// Returns number of lines.
	*/
	int	getLinesFromFile(const std::string& currentFilePath);

	/*
	// Returns number of lines.
	*/
	int getLinesFromActualFile() const;

	/*
	// Returns the current content.
	*/
	const std::string& getFileContent() const;

	/*
	// Returns the current Directory.
	// ( "../abc")
	*/
	std::string getCurrentDirectory() const;



private:
	/*
	// Adds a content to the container.
	// Example: ("xpos", "10")
	*/
	void addVar(const std::string& containerName, const std::string& content);


	std::string					currentFilePath;
	std::ofstream				open;
	std::ifstream				read;
	std::stringstream			stream;
	std::string					output;
	std::string					content;
	int							lines;
	unsigned					fir, sec;

	// sections
	int			sect;
	int			linesbtw;
	bool		writetosection;
	std::string section;

	std::vector<std::pair<std::string, std::string>> vpair;
	std::vector<std::vector<std::pair<std::string, std::string>>> vvar;
};


}

#endif