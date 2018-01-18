#include "Circle.h"

Circle::Circle(const uint32_t myX, const uint32_t myY, const uint32_t width, const uint32_t height)
{
	AIPosition p;
	p.X = myX;
	p.Y = myY;

	this->setName("Circle");
	this->setLife(1);
	this->setPosition(p);
	this->setWidth(width);
	this->setHeight(height);
	this->setShoot(false);
	this->setTurn(0);

	_angle = 0;
	_rayon = static_cast<float>(height) / 10.f;
	_center.X = myX;
	_center.Y = myY;
}

Action Circle::actualize(const uint32_t enX, const uint32_t enY)
{
	AIPosition p{this->getPosition().X, this->getPosition().Y};

	if (_angle <= 360)
	{
		float radian = _angle * 3.14 / 180;

		p.X = _center.X + static_cast<int>(cos(radian) * _rayon);
		p.Y = _center.Y + static_cast<int>(sin(radian) * _rayon);
	}
	else if (_angle <= 400)
	{
		p.X = this->getPosition().X - 10;
	}
	else
	{
		p.X = this->getPosition().X - 10;
		_angle = 0;
		_center.X = p.X;
		_center.Y = p.Y;
	}

	if (p.X >= 0)
		this->setPosition(p);
	else
		this->setLife(0);

	uint32_t randshoot = this->getTurn() % 20 + 1;
	if (this->getTurn() % randshoot == 0)
	{
		vec2D toShoot;
		float dX = static_cast<float>(enX - p.X);
		float dY = static_cast<float>(enY - p.Y);

		if (dX == 0 && dY == 0)
			dX += 1;
		toShoot.X = -(dX / (dX * dX + dY * dY));
		toShoot.Y = -(dY / (dX * dX + dY * dY));
		this->setShootVector(toShoot);
		this->setShoot(true);
	}
	else
		this->setShoot(false);

	_angle += 10;
	this->setTurn(this->getTurn() + 1);
	if (this->getLife() == 0)
		return (Action::DEAD);
	if (this->getShoot() == true)
		return (Action::SHOOT);
	return (Action::DEFAULT);
}

#if defined (_WIN32) || defined (_WIN64)
extern "C" __declspec(dllexport) IArtificialIntelligence *createLib(const int a, const int b, const int c, const int d)
{
	return (new Circle(a, b, c, d));
}
#elif defined (__linux__) || defined (__APPLE__)
extern "C" IArtificialIntelligence *createLib(const int a, const int b, const int c, const int d)
{
	return (new Circle(a, b, c, d));
}
#endif
