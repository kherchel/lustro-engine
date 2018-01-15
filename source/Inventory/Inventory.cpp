#include "Inventory.hpp"

namespace lustro
{
	std::vector<std::pair<std::string, std::string> > Inventory::items;
	int Inventory::currentItem = 0;

	Inventory::Inventory() {}
	
	void Inventory::addItem(std::string name, std::string description)
	{
		items.push_back(std::pair<std::string, std::string>(name, description));
	}
	
	void Inventory::removeItem(std::string name)
	{
		for(unsigned int i = 0; i < items.size(); i++)
			if(items[i].first == name) items.erase(items.begin()+i);
	}
	
	void Inventory::selectItem(unsigned int number)
	{
		if(number > items.size()) return;
		currentItem = number;
	}
	
	void Inventory::selectNextItem()
	{
		currentItem++;
		if(currentItem >= items.size()) currentItem = 0;
	}
	
	void Inventory::selectPreviousItem()
	{
		currentItem--;
		if(currentItem < 0) currentItem = items.size()-1;
	}
	
	bool Inventory::checkForItem(std::string name)
	{
		for(auto& i : items)
			if(i.first == name) return true;
			
		return false;
	}
	
	std::string Inventory::getItemDescription(std::string name)
	{
		for(auto& i : items)
			if(i.first == name) return i.second;
		
		return "";
	}
	
	unsigned int Inventory::getCurrentItemID()
	{
		if(currentItem >= items.size()) currentItem = 0;
		return currentItem;
	}
	
	std::pair<std::string, std::string> Inventory::getCurrentItem()
	{
		if(currentItem >= items.size()) return std::pair<std::string, std::string>("", "");
		return items[currentItem];
	}
	
	std::vector<std::pair<std::string, std::string> >& Inventory::getItems()
	{
		return items;
	}
	
}
