#include "Object.hpp"

namespace lustro
{

	Object::Object() : x(0), y(0), isActive(true) {}
	
	Object::Object(std::string name, double x, double y, bool isActive, Animation animation) : name(name), x(x), y(y), isActive(isActive), animation(animation), sprite(nullptr, x, y) {}
	
	void Object::setPosition(double x, double y)
	{
		this->x = x;
		this->y = y;
		sprite.setPosition(x, y);
	}
	
	Sprite2D* Object::getSprite2D()
	{
		if(!isActive) return nullptr;
		return &sprite;
	}
	
	void Object::setAnimation(Animation animation)
	{
		this->animation = animation;
	}
	
	void Object::setActivityState(bool state)
	{
		isActive = state;
		sprite.setActivityState(isActive);
	}
	
	void Object::checkInteractivity(double x, double y, double rot) {}
	
	void Object::update(double x, double y)
	{
		animation.update();
		sprite.setTexture(animation.getCurrentTexture());
	}
	
	void Object::setName(std::string name)
	{
		this->name = name;
	}
	
	std::string Object::getName() const
	{
		return name;
	}

}
