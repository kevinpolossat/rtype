#include "Linear.h"

Linear::Linear(const uint32_t myX, const uint32_t myY, const uint32_t width, const uint32_t height)
{
	AIPosition p;
	p.X = myX;
	p.Y = myY;

	_x = 0;
	this->setName("Linear");
	this->setLife(1);
	this->setPosition(p);
	this->setWidth(width);
	this->setHeight(height);
	this->setShoot(false);
	this->setTurn(0);
}

std::shared_ptr<IArtificialIntelligence> Linear::NewIA(const uint32_t myX, const uint32_t myY, const uint32_t width, const uint32_t height)
{
	return std::make_shared<Linear>(Linear(myX, myY, width, height));
}


bool Linear::setDamages(uint32_t dmg)
{
		uint32_t l = this->getLife();

		this->setLife(l - dmg);
		return (this->getLife() > 0);
}

// SETTER | GETTER
const AIPosition& Linear::getPosition() const { return _pos; }
void Linear::setPosition(const AIPosition& p) { _pos = p; }

const std::string &Linear::getName() const { return _name; }
const void Linear::setName(const std::string &n) { _name = n; }

const uint32_t Linear::getLife() const { return _life; }
void Linear::setLife(const uint32_t l) { _life = l; }

const uint32_t Linear::getWidth() const { return _width; }
void Linear::setWidth(const uint32_t l) { _width = l; }

const uint32_t Linear::getHeight() const { return _height; }
void Linear::setHeight(const uint32_t l) { _height = l; }

const bool Linear::getShoot() const { return _shoot; }
void Linear::setShoot(const bool x) { _shoot = x; }

const uint32_t Linear::getTurn() const { return _turn; }
void Linear::setTurn(const uint32_t t) { _turn = t; }

void Linear::setShootVector(const vec2D& x) {_shootVector = x;}
const vec2D& Linear::getShootVector() const {return _shootVector;}

AIPosition& Linear::getNearPlayer(std::vector<AIPosition>& players) const
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


Action Linear::actualize(std::vector<AIPosition>& players, std::vector<AIPosition>&, AIPosition)
{
	AIPosition p;
	p.X = this->getPosition().X;
	p.Y = this->getPosition().Y;

	if (p.Y <= 5 || p.Y > this->getHeight() - 51)
		_x = (_x + 1) % 2;

	if (_x == 0)
		p.Y -= 5;
	else
		p.Y += 5;

		p.X -= 5;
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
extern "C" __declspec(dllexport) IArtificialIntelligence *createLib(const int a, const int b, const int c, const int d)
{
	return new Linear(a, b, c, d);
}
extern "C" __declspec(dllexport) void deleteLib(Linear *b)
{
	delete b;
}
#elif defined (__linux__) || defined (__APPLE__)
extern "C" IArtificialIntelligence *createLib(const int a, const int b, const int c, const int d)
{
	return new Linear(a, b, c, d);
}
extern "C" void deleteLib(Linear *b)
{
	delete b;
}
#endif
