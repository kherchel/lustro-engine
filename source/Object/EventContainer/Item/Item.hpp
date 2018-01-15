#include "../EventContainer.hpp"
#include <cmath>

#ifndef ITEM_HPP
#define ITEM_HPP

namespace lustro
{
	class Item : public EventContainer
	{
		public: 
			Item(std::string name, double x, double y, bool isActive, Animation animation);
			void checkInteractivity(double, double, double) override;
	};
}
#endif
