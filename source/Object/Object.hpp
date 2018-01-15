#include <vector>
#include "../Sprite2D/Sprite2D.hpp"
#include "../Animation/Animation.hpp"

#ifndef OBJECT_HPP
#define OBJECT_HPP

namespace lustro
{
	class Object
	{
		public:
			Object();
			Object(std::string name, double x, double y, bool isActive, Animation animation);
			void setPosition(double x, double y);
			void setAnimation(Animation);
			virtual Sprite2D* getSprite2D();
			virtual void update(double x, double y);
			virtual void checkInteractivity(double x, double y, double rot);
			void setName(std::string name);
			void setActivityState(bool state);
			std::string getName() const;
		protected:
			double x, y;
			std::string name;
			bool isActive;
			Sprite2D sprite;
		 	Animation animation;
	};
}

#endif
