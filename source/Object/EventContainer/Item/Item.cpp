#include "Item.hpp"

namespace lustro
{
	Item::Item(std::string name, double x, double y, bool isActive, Animation animation) 
		: EventContainer(name, x, y, isActive, animation) {}
	
	
	void Item::checkInteractivity(double x, double y, double rot)
	{
		if(!isActive)return;
		
		if((x-this->x)*(x-this->x)+(y-this->y)*(y-this->y) > 1.5) return;
	
		double angle = fabs(atan2(this->y-y, this->x-x) - rot/180.*M_PI);
		while(angle >= M_PI*2) angle -= M_PI*2;
		if(angle > M_PI) angle = M_PI*2-angle;
		
		if(angle > 15*M_PI/180) return;
		
		runEvents("onUse");
	}
}
