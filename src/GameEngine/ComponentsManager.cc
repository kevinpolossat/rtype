#include "ComponentsManager.h"

uint32_t ge::ComponentsManager::count_ = 0;

bool ge::ComponentsManager::AddComponents(std::vector<std::string> const & names) {
	bool ret = true;
	for (auto & name : names) {
		ret = ret && AddComponent(name);
	}
	return ret;
}

bool ge::ComponentsManager::AddComponent(std::string const & name) {
	if (count_ < ge::Settings::ComponentsCount) {
		if (!components_.count(name)) {
			components_.insert(std::pair<std::string, Component>(name, Component(static_cast<unsigned long long int>(1 << count_))));
			++count_;
			return true;
		}
		ErrorAddExistingComponent_(name);
		return false;
	}
	ErrorToManyComponents_();
	return false;
}

bool ge::ComponentsManager::AddComposedComponents(std::string const & name, std::vector<std::string> const & composition) {
	if (!components_.count(name)) {
		Component b(0);
		for (auto & c : composition) {
			if (components_.count(c)) {
				b |= components_[c];
			} else {
				ErrorUnknownComponent_(c);
				return false;
			}
		}
		components_.insert(std::pair<std::string, Component>(name, b));
		return true;
	}
	ErrorAddExistingComponent_(name);
	return false;
}

bool ge::ComponentsManager::Match(const ge::Entity & entity, const ge::Component & component) const {
	return (entity & component) == component;
}

bool ge::ComponentsManager::Match(const ge::Entity & entity, std::string const & name) const {
	return Match(entity, (*this)[name]);
}

bool ge::ComponentsManager::Match(std::string const & name1, std::string const & name2) const {
	return Match((*this)[name1], (*this)[name2]);
}

ge::Component const & ge::ComponentsManager::operator[](std::string const & name) const {
	if (components_.count(name)) {
		return components_.at(name);
	}
	ErrorUnknownComponent_(name);
	return ge::Components::None;
}

void ge::ComponentsManager::ErrorAddExistingComponent_(std::string const &name) const {
	std::cerr << "ComponentManager : Component " << name << " already exist" <<std::endl;
}

void ge::ComponentsManager::ErrorUnknownComponent_(std::string const &name) const {
	std::cerr << "ComponentManager : Component " << name << " doesn't exist" <<std::endl;
}

void ge::ComponentsManager::ErrorToManyComponents_() const {
	std::cerr << "ComponentManager : To many basic components" <<std::endl;
}
