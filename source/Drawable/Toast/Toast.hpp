#include "../Drawable.hpp"
#include "../../Timer/Timer.hpp"
#ifndef TOAST_HPP
#define TOAST_HPP

namespace lustro
{
	class Toast : public Drawable
	{
		public:
			Toast();
			Toast(PixelData color, double inAnimationTime, double onScreenTime, double outAnimationTime);
			bool showsSomething();
			void start(std::string text);
			void update();
			void render();
			void showText(int);
		
		private:
			std::string text;
			PixelData color;
			double inAnimationTime, onScreenTime, outAnimationTime;
	};
}

#endif
