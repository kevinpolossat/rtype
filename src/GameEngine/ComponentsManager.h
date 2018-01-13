#ifndef COMPONENTSMANAGER_H
#define COMPONENTSMANAGER_H

#include <unordered_map>
#include <vector>
#include <iostream>

#include "Settings.h"

namespace ge {
	class ComponentsManager {
	public:
		ComponentsManager() = default;
		ComponentsManager(ComponentsManager const & other) = delete;
		ComponentsManager(ComponentsManager && other) = delete;
		~ComponentsManager() = default;

		ComponentsManager & operator=(ComponentsManager const & other) = delete;
		ComponentsManager & operator=(ComponentsManager && other) = delete;

		bool AddComponent(std::string const & name);
		bool AddComponents(std::vector<std::string> const & names);
		bool AddComposedComponents(std::string const & name, std::vector<std::string> const & composition);

		Component const & operator[](std::string const & name) const;

	private:
		void ErrorAddExistingComponent_(std::string const & name) const;
		void ErrorUnknownComponent_(std::string const & name) const;
		void ErrorToManyComponents_() const;

		static uint32_t count_;

		std::unordered_map<std::string, Component> components_;
	};
}


#endif /*COMPONENTSMANAGER_H*/
