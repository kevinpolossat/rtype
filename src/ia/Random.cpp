#include "Random.h"

Random & Random::operator=(Random *c)
{
	this->setName(c->getName());
	this->setLife(c->getLife());
	this->setPosition(c->getPosition());
	this->setWidth(c->getWidth());
	this->setHeight(c->getHeight());
	this->setShoot(c->getShoot());
	this->setShootVector(c->getShootVector());
	this->setTurn(c->getTurn());
	return *this;
}

Random::Random(Random *c)
{
	this->setName(c->getName());
	this->setLife(c->getLife());
	this->setPosition(c->getPosition());
	this->setWidth(c->getWidth());
	this->setHeight(c->getHeight());
	this->setShoot(c->getShoot());
	this->setShootVector(c->getShootVector());
	this->setTurn(c->getTurn());
}

Random::Random(const uint32_t myX, const uint32_t myY, const uint32_t width, const uint32_t height)
{
	AIPosition p;
	p.X = myX;
	p.Y = myY;

	this->setName("Random");
	this->setLife(1);
	this->setPosition(p);
	this->setWidth(width);
	this->setHeight(height);
	this->setShoot(false);
	this->setTurn(0);
}

Action Random::actualize(std::vector<AIPosition>& players)
{
	AIPosition p{this->getPosition().X, this->getPosition().Y};

  int dY = std::rand() % 3;

  p.X -= 10;
  p.Y += ((dY == 0) ? (0) : ((dY == 1) ? (10) : (-10)));

	if (p.X >= 0)
		this->setPosition(p);
	else
		this->setLife(0);

	uint32_t randshoot = this->getTurn() % 20 + 1;
	if (this->getTurn() % randshoot == 0)
	{
		AIPosition en = this->getNearPlayer(players);
		vec2D toShoot;

		float dX = static_cast<float>(en.X - p.X);
		float dY = static_cast<float>(en.Y - p.Y);

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
	return (new Random(a, b, c, d));
}
#elif defined (__linux__) || defined (__APPLE__)
extern "C" IArtificialIntelligence *createLib(const int a, const int b, const int c, const int d)
{
	return (new Random(a, b, c, d));
}
#endif
