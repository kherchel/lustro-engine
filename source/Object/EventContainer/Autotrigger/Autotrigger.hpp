#include "../../EventContainer/EventContainer.hpp"

#ifndef AUTOTRIGGER_HPP
#define AUTOTRIGGER_HPP

namespace lustro
{

	class Autotrigger : public EventContainer
	{
		public:
			Autotrigger(std::string name, bool);
			void update(double x, double y) override;
			Sprite2D* getSprite2D() override;
	};
	
}

#endif
