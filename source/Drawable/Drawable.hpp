#include <vector>
#include <limits>
#include "../PixelData/PixelData.hpp"

#ifndef DRAWABLE_HPP_INCLUDED
#define DRAWABLE_HPP_INCLUDED

namespace lustro
{
	class Drawable
	{
		public:
			Drawable();
			virtual void setPosition(int, int);
			virtual void setDepth(int);
			virtual void setSize(int, int);
			void setPixel(int, int, PixelData);
			
			int getX() const;
			int getY() const;
			int getDepth() const;
			const std::vector<double>& getZBuffer() const;
			const std::vector<PixelData>& getBuffer() const;
			int getWidth() const;
			int getHeight() const;			
			PixelData getPixel(int, int) const;
			double getZ(int x, int y) const;

			void clear(PixelData pixel = PixelData(), int x1 = 0, int y1 = 0, int x2 = -1, int y2 = -1);
			virtual void update() = 0;
			virtual void render() = 0;
			
		protected:
			int x, y;
			int width, height;
			int depth;
			std::vector<PixelData> buffer;
			std::vector<double> zBuffer;
			
	};
}

#endif
