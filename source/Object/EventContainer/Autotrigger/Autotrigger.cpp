#include "Autotrigger.hpp"

namespace lustro
{
	Autotrigger::Autotrigger(std::string name, bool isActive)
	{
		this->name = name;

		this->isActive = isActive;
	}

	void Autotrigger::update(double x, double y)
	{
		if(!isActive) return;
		runEvents("auto");
	}
	
	Sprite2D* Autotrigger::getSprite2D()
	{
		return nullptr;
	}


}
