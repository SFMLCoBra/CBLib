#include "TextDocument.hpp"

#include <sys/stat.h>
#include <boost/filesystem.hpp>

#include "Data.hpp"

namespace cb
{

TextDocument::TextDocument()
	: lines(0), sect(0), writetosection(false)
{

}

TextDocument::TextDocument(const std::string& currentFilePath)
	: currentFilePath(currentFilePath), lines(0), sect(0), writetosection(false)
{

}

TextDocument::~TextDocument()
{
}

bool TextDocument::dirExists(const std::string& path)
{

	boost::filesystem::path temppath(path);

	if (boost::filesystem::exists(temppath))
	{
		// can normal io apply to the file?
		if (boost::filesystem::is_directory(temppath))
		{
			return true;
		}
		else
		{
			CB_DEFAULT_ERROR_MSG("file " + path + " is no directory.");
			return false;
		}
	}

	CB_DEFAULT_ERROR_MSG("file " + path + " doesn't exist.");
	// else: directory does not exist
	return false;

	// native c++ | <sys/stat>
	/*
	if (access(path.c_str(), 0) != -1)
	{
	return true;
	}
	*/
}

bool TextDocument::fileExists(const std::string & path)
{
	boost::filesystem::path temppath(path);

	if (boost::filesystem::exists(temppath))
	{
		// can normal io apply to the file?
		if (boost::filesystem::is_regular_file(temppath))
		{
			return true;
		}
		else
		{
			CB_DEFAULT_ERROR_MSG("file " + path + " is not a regular file.");
			return false;
		}
	}

	CB_DEFAULT_ERROR_MSG("file " + path + " doesn't exist.");
	// else: directory does not exist
	return false;
}

bool TextDocument::createDirectory(const std::string& path)
{
	boost::filesystem::path dir(path);

	if (boost::filesystem::create_directory(dir))
	{
		return true;
	}
	CB_DEFAULT_ERROR_MSG("couldn't create file: " + path);
	return false;
}

void TextDocument::write(const std::string& var, const std::string& content)
{
	if (writetosection)
	{
		section += "<" + var + ":" + content + ">\n";

		linesbtw++;
	}
	else
	{
		this->content += "<" + var + ":" + content + ">\n";
	}
	lines++;
}

void TextDocument::writeLineToContent(const std::string& content)
{
	this->content += content;
}

void TextDocument::writeToContent(const std::string& content, bool lineBreak)
{
	this->content += content;
	if (lineBreak)
		this->content += "\n";
}

void TextDocument::writeTruncToContent(const std::string& content)
{
	this->content = content;
}


bool TextDocument::writeContentToFile(const std::string &currentFilePath)
{
	if (currentFilePath == "")
	{
		if (this->currentFilePath == "")
		{
			CB_DEFAULT_ERROR_MSG("this->currentFilePath is not a file");
			return false;
		}
		open.open(this->currentFilePath, std::ofstream::out | std::ofstream::app);
	}
	else
	{
		open.open(currentFilePath, std::ofstream::out | std::ofstream::app);
	}
	open << content;
	open.close();
	return true;
}

void TextDocument::writeContentTruncToFile(const std::string &currentFilePath)
{
	if (currentFilePath == "")
	{
		if (this->currentFilePath == "")
		{
			CB_DEFAULT_ERROR_MSG("this->currentFilePath is not a file");
			return;
		}
		open.open(this->currentFilePath, std::ofstream::out | std::ofstream::trunc);
	}
	else
	{
		open.open(currentFilePath, std::ofstream::out | std::ofstream::trunc);
	}
	open << content;
	open.close();
}

void TextDocument::writeSectionToFile()
{
	open.open(currentFilePath, std::ofstream::out | std::ofstream::app);
	open << section;
	open.close();
}

void TextDocument::clearContent()
{
	section.clear();
	content.clear();
	lines = 0;
	sect = 0;
}

void TextDocument::clearSection()
{
	section.clear();
	sect = 0;
	linesbtw = 0;
}

void TextDocument::clearToUseNewFile(const std::string& filename)
{
	clearContent();
	sect = 0;

	if (!filename.empty())
	{
		setFileName(filename);
	}
}

bool TextDocument::deleteFile(const std::string& filename)
{
	try
	{
		boost::filesystem::remove_all(filename.c_str());
	}
	catch (boost::filesystem::filesystem_error e)
	{
		CB_DEFAULT_ERROR_MSG("couldn't clear file: " + filename);
	}

	return true;
}

void TextDocument::addSectionToContent()
{
	content += section;
}

bool TextDocument::loadFile(const std::string& filename, bool var)
{
	if (!(fileExists(filename)))
	{
		CB_DEFAULT_ERROR_MSG("Couldn't open file: " + filename);
		return false;
	}

	clearContent();

	read.open(filename);

	if (var)
	{
		std::pair<std::string, std::string> p;
		std::vector<std::pair<std::string, std::string>> vp;
		std::string temp;

		while (!read.eof())
		{
			getline(read, temp);
			content += temp;
			lines++;

			fir = temp.find("<");
			sec = temp.find(":");
			p.first = temp.substr(fir + 1, sec - fir - 1);

			fir = temp.find(":");
			sec = temp.find(">");
			p.second = temp.substr(fir + 1, sec - fir - 1);
			addVar(p.first, p.second);
		}
	}
	else
	{
		content.assign((std::istreambuf_iterator<char>(read)),
			(std::istreambuf_iterator<char>()));
	}

	read.close();
	return true;
}

bool TextDocument::loadSection(int section)
{
	std::string temp;

	fir = content.find("|b" + std::to_string(section) + "b|");

	// if the position is the end of the file (std::string::npos = -1)
	// return false because it couldn't find the beginning of the section.
	if (fir == std::string::npos)
	{
		CB_DEFAULT_ERROR_MSG(
			"Couldn't load section " +
			std::to_string(section) + " in " + currentFilePath);
		return false;
	}
	sec = content.find("|e" + std::to_string(section) + "e|");
	temp = content.substr(fir + 1, sec - fir - 1);

	fir = content.find(section + "e|");
	std::string s = content.substr(sec + 1, fir - sec - 1);

	std::pair<std::string, std::string> pair;

	int l = stoi(s);

	for (int i = 0; i < l; i++)
	{
		fir = temp.find("<");
		sec = temp.find(":");
		pair.first = temp.substr(fir + 1, sec - fir - 1);

		fir = temp.find(":");
		sec = temp.find(">");
		pair.second = temp.substr(fir + 1, sec - fir - 1);

		addVar(pair.first, pair.second);
	}

	return true;
}

void TextDocument::beginSection()
{
	section.clear();
	writetosection = true;
	linesbtw = 0;
	section += "|b" + std::to_string(sect) + "b|\n";
	lines++;
}

void TextDocument::endSection()
{
	section += "|e" + std::to_string(linesbtw) + "e|\n";
	content += section;
	writetosection = false;
	lines++;
	sect++;
}


void TextDocument::addVar(const std::string& var, const std::string& content)
{
	bool addnew = true;
	int id = -1;

	// checks if variable container already exists
	for (std::size_t i = 0; i < vvar.size(); i++)
	{
		if (vvar[i].begin()->first == var)
		{
			id = i;
			if (addnew != false)
				addnew = false;
		}
	}

	// add new container for the new variable
	if (addnew)
	{
		vpair.clear();
		vpair.push_back(std::make_pair(var, content));
		vvar.push_back(vpair);
	}
	else
	{
		if (id >= 0)
		{
			vvar[id].push_back(std::make_pair(var, content));
		}
	}
}

// SETTER

void TextDocument::setFileName(const std::string& currentFilePath)
{
	this->currentFilePath = currentFilePath;
}

// GETTER

std::string TextDocument::getContent(const std::string& var, unsigned int count)
{
	for (std::size_t i = 0; i < vvar.size(); i++)
	{
		if (vvar[i].begin()->first == var)
		{
			if (vvar[i].size() > count)
			{
				return vvar[i].at(count).second;
			}
		}
	}
	CB_DEFAULT_ERROR_MSG("probably couldn't find variable name.");
	return "";
}

int TextDocument::getContentAsInt(const std::string& var, unsigned int count)
{
	for (std::size_t i = 0; i < vvar.size(); i++)
	{
		if (vvar[i].begin()->first == var)
		{
			if (vvar[i].size() > count)
			{
				return stoi(vvar[i].at(count).second);
			}
		}
	}

	return -666;
}



std::string TextDocument::getCurrentDirectory() const
{
	std::wstring s = boost::filesystem::current_path().c_str();
	return std::string(s.begin(), s.end());
}

int	TextDocument::getLinesFromFile(const std::string& currentFilePath)
{
	read.open(currentFilePath);
	std::string s;
	while (!read.eof())
	{
		std::getline(read, s);
		lines++;
	}
	read.close();
	return lines;
}

int TextDocument::getLinesFromActualFile() const
{
	return lines;
}

const std::string& TextDocument::getFileContent() const
{
	//std::ifstream ifs(currentFilePath);
	//std::string content((std::istreambuf_iterator<char>(ifs)),
	//	(std::istreambuf_iterator<char>()));
	return content;
}

std::vector<std::string> TextDocument::getFilenamesInDir(const std::string& path)
{
	std::vector<std::string> vfiles;

	if (!dirExists(path))
	{
		CB_DEFAULT_ERROR_MSG("Path " + path + " is not a directory");
		return std::vector<std::string>{};
	}

	auto files = boost::make_iterator_range(boost::filesystem::directory_iterator(path), {});

	for (auto& i : files)
	{
		vfiles.push_back(i.path().filename().string());
	}

	return vfiles;
}

std::vector<std::string> TextDocument::getFilenamesInDirWithExt(const std::string& path, const std::string& ext)
{
	std::vector<std::string> vfiles;

	if (!dirExists(path))
	{
		CB_DEFAULT_ERROR_MSG("Path " + path + " is not a directory");
		return std::vector<std::string>{};
	}

	auto files = boost::make_iterator_range(boost::filesystem::directory_iterator(path), {});

	for (auto& i : files)
	{
		if (i.path().extension() == ext)
		{
			vfiles.push_back(i.path().filename().string());
		}
	}
	return vfiles;
}

std::vector<std::string> TextDocument::getFilenamesInDirWithoutExt(const std::string& path)
{
	std::vector<std::string> vfiles;

	if (!dirExists(path))
	{
		CB_DEFAULT_ERROR_MSG("Path " + path + " is not a directory");
		return std::vector<std::string>{};
	}

	auto files = boost::make_iterator_range(boost::filesystem::directory_iterator(path), {});

	for (auto& i : files)
	{
		if (i.status().type() == boost::filesystem::file_type::regular_file)
		{
			if (i.path().has_extension())
			{
				vfiles.push_back(i.path().stem().string());
			}
			else
			{
				vfiles.push_back(i.path().filename().string());
			}
		}
	}

	return vfiles;
}

void TextDocument::lowerString(std::string& data)
{
	std::locale loc;
	std::transform(data.begin(), data.end(), data.begin(), ::tolower);
}

std::string TextDocument::getStringBetween(const std::string & text, const std::string & first, const std::string & second, std::size_t offset)
{
	std::size_t f = text.find(first, offset);
	std::size_t s;

	if (second == first)
		s = text.find(second, f + 1);
	else
		s = text.find(second, offset);

	if (first == "") return text.substr(0, s);
	if (second == "") return text.substr(f + first.size(), text.size() - f - first.size());

	return text.substr(f + first.size(), s - f - first.size());
}

int TextDocument::removeAllOccurencesAndInsert(std::string & str, const std::string & deleteThis, const std::string & insert, bool deleteBorder)
{
	// 1. find substring to delete
	// 2. delete substring from string 
	// 3. insert replacement

	int amount = 0;
	std::size_t pos;
	while ((pos = str.find(deleteThis)) != std::string::npos)
	{
		if (deleteBorder)
		{
			str.erase(pos - 1, deleteThis.size() + 2);
			str.insert(pos - 1, insert);
		}
		else
		{
			str.erase(pos, deleteThis.size());
			str.insert(pos, insert);
		}
		amount++;
	}
	return amount;
}

std::size_t TextDocument::removeOccurenceAndInsert(std::string & str, const std::string & deleteThis, const std::string & insert, std::size_t offset, bool deleteBorder)
{
	std::size_t pos;
	if ((pos = str.find(deleteThis, offset)) != std::string::npos)
	{
		if (deleteBorder)
		{
			str.erase(pos - 1, deleteThis.size() + 2);
			str.insert(pos - 1, insert);
		}
		else
		{
			str.erase(pos, deleteThis.size());
			str.insert(pos, insert);
		}
	}
	return pos;
}

std::vector<std::string> TextDocument::getAllStringsBetween(const std::string& content, const std::string & first, const std::string & second)
{
	std::vector<std::string> occurrence;
	std::size_t start, end = 0;

	while ((start = content.find(first, end)) != std::string::npos)
	{
		end = content.find(second, start + 1);
		if (end == std::string::npos)
		{
			break;
		}
		occurrence.push_back(getStringBetween(content, first, second));
	}
	return occurrence;
}

std::vector<std::string> TextDocument::splitInLines(const std::string & text, bool deleteEmpty)
{
	std::size_t p = 0;
	std::size_t cur = 0;

	std::vector<std::string> lines;

	while (true)
	{
		cur = p;
		if ((p = text.find('\n', p + 1)) == std::string::npos)
			break;

		std::string str = text.substr(cur, text.find('\n', cur + 1) - cur);

		str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());

		if (!str.empty())
			lines.push_back(str);
	}

	if (cur < text.size())
	{
		std::string str = text.substr(cur, text.size() - cur);

		str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());

		if (!str.empty())
			lines.push_back(str);
	}

	return lines;
}


}