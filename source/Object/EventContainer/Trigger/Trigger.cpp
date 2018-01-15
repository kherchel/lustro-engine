#include "Trigger.hpp"

namespace lustro
{
	Trigger::Trigger(std::string name, double x1, double y1, double x2, double y2)
	{
		this->name = name;
		
		this->x1 = std::min(x1, x2);
		this->y1 = std::min(y1, y2);
		
		this->x2 = std::max(x1, x2);
		this->y2 = std::max(y1, y2);
		
		triggerValue = false;
		isActive = true;
	}


	void Trigger::update(double x, double y)
	{
		if(!isActive) return;
		bool nowIs = isInside(x, y);

		if(nowIs && !triggerValue)
		    runEvents("onEntry");
		if(!nowIs && triggerValue)
			runEvents("onLeave");
		
		triggerValue = nowIs;
	}
	
	Sprite2D* Trigger::getSprite2D()
	{
		return nullptr;
	}
	
	bool Trigger::isInside(double x, double y)
	{
		return (x1 <= x && x2 >= x && y1 <= y && y2 >= y);
	}

}
