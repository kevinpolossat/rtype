#include "Random.h"

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

std::shared_ptr<IArtificialIntelligence> Random::NewIA(const uint32_t myX, const uint32_t myY, const uint32_t width, const uint32_t height)
{
	return std::make_shared<Random>(Random(myX, myY, width, height));
}


bool Random::setDamages(uint32_t dmg)
{
		uint32_t l = this->getLife();

		this->setLife(l - dmg);
		return (this->getLife() > 0);
}

// SETTER | GETTER
const AIPosition& Random::getPosition() const { return _pos; }
void Random::setPosition(const AIPosition& p) { _pos = p; }

const std::string &Random::getName() const { return _name; }
const void Random::setName(const std::string &n) { _name = n; }

const uint32_t Random::getLife() const { return _life; }
void Random::setLife(const uint32_t l) { _life = l; }

const uint32_t Random::getWidth() const { return _width; }
void Random::setWidth(const uint32_t l) { _width = l; }

const uint32_t Random::getHeight() const { return _height; }
void Random::setHeight(const uint32_t l) { _height = l; }

const bool Random::getShoot() const { return _shoot; }
void Random::setShoot(const bool x) { _shoot = x; }

const uint32_t Random::getTurn() const { return _turn; }
void Random::setTurn(const uint32_t t) { _turn = t; }

void Random::setShootVector(const vec2D& x) {_shootVector = x;}
const vec2D& Random::getShootVector() const {return _shootVector;}

AIPosition& Random::getNearPlayer(std::vector<AIPosition>& players) const
{
	double min = static_cast<double>(_height) * static_cast<double>(_width);
	int minIndex = 0;
	for (int i = 0; i < players.size(); i++)
	{
		double stock = sqrt((this->getPosition().X - players.at(i).X) * (this->getPosition().X - players.at(i).X)
												+ (this->getPosition().Y - players.at(i).Y) * (this->getPosition().Y - players.at(i). Y));
		if (stock < min)
		{
			min = stock;
			minIndex = i;
		}
	}
	return players.at(minIndex);
}



Action Random::actualize(std::vector<AIPosition>& players, std::vector<AIPosition>&, AIPosition)
{
	AIPosition p{this->getPosition().X, this->getPosition().Y};

  int dY = std::rand() % 3;

  p.X -= 5;
  p.Y += ((dY == 0) ? (0) : ((dY == 1) ? (5) : (-5)));

	if (p.X >= 0)
		this->setPosition(p);
	else
		this->setLife(0);

	if (this->getTurn() % 20 == 0)
	{
		AIPosition en = this->getNearPlayer(players);
		vec2D toShoot;

		float dX = static_cast<float>(en.X - p.X);
		float dY = static_cast<float>(en.Y - p.Y);

		if (dX == 0 && dY == 0)
			dX += 1;
		toShoot.X = -(dX / sqrt(dX * dX + dY * dY));
		toShoot.Y = -(dY / sqrt(dX * dX + dY * dY));
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
extern "C" __declspec(dllexport) std::shared_ptr<IArtificialIntelligence> createLib(const int a, const int b, const int c, const int d)
{
	return (std::make_shared<Random>(Random(a, b, c, d)));
}
#elif defined (__linux__) || defined (__APPLE__)
extern "C" std::shared_ptr<IArtificialIntelligence> createLib(const int a, const int b, const int c, const int d)
{
	return (std::make_shared<Random>(Random(a, b, c, d)));
}
#endif
