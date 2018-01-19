#include "Linear.h"

Linear::Linear(const uint32_t myX, const uint32_t myY, const uint32_t width, const uint32_t height)
{
	AIPosition p;
	p.X = myX;
	p.Y = myY;

	this->setName("Linear");
	this->setLife(1);
	this->setPosition(p);
	this->setWidth(width);
	this->setHeight(height);
	this->setShoot(false);
	this->setTurn(0);
}

Action Linear::actualize(const uint32_t enX, const uint32_t enY)
{
	AIPosition p;
	p.X = this->getPosition().X;
	p.Y = this->getPosition().Y;

	if (_x == 0)
		p.Y -= 1;
	else
		p.Y += 1;

	if (p.Y <= 1 || p.Y >= this->getHeight() - 1)
		_x = (_x + 1) % 2;

		p.X -= 1;
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
	return (new Linear(a, b, c, d));
}
#elif defined (__linux__) || defined (__APPLE__)
extern "C" IArtificialIntelligence *createLib(const int a, const int b, const int c, const int d)
{
	return (new Linear(a, b, c, d));
}
#endif
