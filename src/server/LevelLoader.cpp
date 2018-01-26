#include "LevelLoader.hpp"

LevelLoader::LevelLoader()
{
	this->m_CurrentLevel = -1;

	std::string path = std::experimental::filesystem::current_path().generic_string() + "/Levels";
	unsigned int size = path.length() + 1;
	for (auto & p : std::experimental::filesystem::directory_iterator(path))
	{
		LevelData *ld = new LevelData();

		ld->m_LevelName =  p.path().generic_string().substr(size);
		ld->m_LevelName = ld->m_LevelName.substr(0, ld->m_LevelName.length() - 5);
		
		std::ifstream t(p);
		std::string str((std::istreambuf_iterator<char>(t)),
			std::istreambuf_iterator<char>());
		ld->m_Data.Parse(str.c_str());
		if (ld->m_Data.IsObject())
		{
			if (ld->m_Data.HasMember("LevelName"))
				ld->m_LevelName = ld->m_Data["LevelName"].GetString();
		}
		this->m_Levels.push_back(ld);
	}
}

LevelLoader::~LevelLoader()
{

}

void LevelLoader::LoadObjects()
{
	if (this->m_Levels[this->m_CurrentLevel]->m_Data.HasMember("LevelData"))
	{
		const rapidjson::Value& a = this->m_Levels[this->m_CurrentLevel]->m_Data["LevelData"];
		for (auto & it : a.GetArray())
		{
			LevelObjects *lo = new LevelObjects();

			lo->m_Done = false;
			if (it.HasMember("TimeStamp"))
				lo->m_TimeStamp = it["TimeStamp"].GetInt();
			if (it.HasMember("Objects"))
			{
				for (auto & obj : it["Objects"].GetArray())
					lo->m_ObjectsNames.push_back(obj.GetString());
			}
			this->m_Objects.push_back(lo);
		}
	}
}

bool LevelLoader::SelectCurrentLevel(const std::string& t_LevelName)
{
	int idx = 0;

	for (auto & it : this->m_Levels)
	{
		if (t_LevelName == it->m_LevelName)
		{
			this->m_CurrentLevel = idx;
			this->LoadObjects();
			return (true);
		}
		idx++;
	}
	return (false);
}

std::vector<std::string> LevelLoader::GetObjects(const long long & t_TimeStamp)
{
	if (this->m_CurrentLevel == -1)
		std::cout << "[ERROR] You didn't select any level" << std::endl;
	else
	{
		for (auto it : this->m_Objects)
		{
			if (it->m_TimeStamp == t_TimeStamp && it->m_Done == false)
			{
				it->m_Done = true;
				return (it->m_ObjectsNames);
			}
		}
	}
	return (std::vector<std::string>());
}