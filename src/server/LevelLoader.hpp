#pragma once
#ifndef LEVELLOADER_HPP
#define LEVELLOADER_HPP

#include <string>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <streambuf>
#include <chrono>
#include <thread>
#include "cereal\external\rapidjson\document.h"

class LevelData
{
public:
	LevelData() {}
	~LevelData() {}
	std::string			m_LevelName;
	rapidjson::Document	m_Data;
};

class LevelObjects
{
public:
	LevelObjects() {}
	~LevelObjects() {}
	int							m_TimeStamp;
	bool						m_Done = false;
	std::vector<std::string>	m_ObjectsNames;
};

class LevelLoader
{
	public:
		LevelLoader();
		~LevelLoader();
		bool SelectCurrentLevel(const std::string& t_LevelName);
		std::vector<std::string> GetObjects(const long long & t_TimeStamp);
	private:
		int							m_CurrentLevel;
		std::vector<LevelData*>		m_Levels;
		std::vector<LevelObjects*>	m_Objects;

		void LoadObjects();
};


#endif // !LEVELLOADER_HPP


