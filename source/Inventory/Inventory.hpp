#include <map>
#include <string>
#include <vector>

#ifndef INVENTORY_HPP_INCLUDED
#define INVENTORY_HPP_INCLUDED

namespace lustro
{
	class Inventory
	{
		public:
			Inventory();
			static void addItem(std::string, std::string);
			static void removeItem(std::string);
			static void selectItem(unsigned int);
			static void selectNextItem();
			static void selectPreviousItem();
			static bool checkForItem(std::string);
			static std::string getItemDescription(std::string);
			static std::vector<std::pair<std::string, std::string> >& getItems();
			static unsigned int getCurrentItemID();
			static std::pair<std::string, std::string> getCurrentItem();
			
		private:
			static std::vector<std::pair<std::string, std::string> > items;
			static int currentItem;
	};
}

#endif
