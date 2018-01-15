#include "../../EventContainer/EventContainer.hpp"

#ifndef TRIGGER_HPP
#define TRIGGER_HPP

namespace lustro
{

	class Trigger : public EventContainer
	{
		public:
			Trigger(std::string name, double x1, double y1, double x2, double y2);
			void update(double x, double y) override;
			Sprite2D* getSprite2D();
		
		private:
			bool isInside(double x, double y);
			std::string triggerMode; //possible modes: "onLeave", "onEntry"
			double x1, y1, x2, y2;
			bool triggerValue;
	};
	
}

#endif
