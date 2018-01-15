#include "Sprite2D.hpp"

namespace lustro
{
	Sprite2D::Sprite2D() : x(0), y(0), isActive(true), texture(nullptr) {}
	Sprite2D::Sprite2D(Texture* texture) : x(0), y(0), texture(texture), isActive(true) {}
	Sprite2D::Sprite2D(Texture* texture, double x, double y) : texture(texture), x(x), y(y), isActive(true) {}
	
	void Sprite2D::setPosition(double x, double y)
	{
		this->x = x;
		this->y = y;
	}
	
	void Sprite2D::setTexture(Texture* texture)
	{
		this->texture = texture;
	}
	
	void Sprite2D::setActivityState(bool state)
	{
		isActive = state;
	}
	
	bool Sprite2D::getActivityState() const
	{
		return isActive;
	}
	
	const Texture& Sprite2D::getTexture() const
	{
		return *texture;
	}
	
	double Sprite2D::getX() const
	{
		return x;
	}
	
	double Sprite2D::getY() const
	{
		return y;
	}
	
	PixelData Sprite2D::getPixel(double x, double y) const
	{
		if(isActive == false || texture == nullptr) return PixelData();
		return texture->getPixelData(x*texture->getWidth(), y*texture->getHeight());
	}
}
