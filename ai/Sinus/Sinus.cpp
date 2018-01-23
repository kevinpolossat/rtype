#include "Sinus.h"

Sinus::Sinus(const uint32_t myX, const uint32_t myY, const uint32_t width, const uint32_t height)
{
	_angle = 0;
	_rayon = height / 10.f;
	AIPosition p;
	p.X = myX;
	p.Y = myY;

	_stockY = myY;

	this->setName("Sinus");
	this->setLife(1);
	this->setPosition(p);
	this->setWidth(width);
	this->setHeight(height);
	this->setShoot(false);
	this->setTurn(0);
}

std::shared_ptr<IArtificialIntelligence> Sinus::NewIA(const uint32_t myX, const uint32_t myY, const uint32_t width, const uint32_t height)
{
	return std::make_shared<Sinus>(Sinus(myX, myY, width, height));
}

bool Sinus::setDamages(uint32_t dmg)
{
		uint32_t l = this->getLife();

		this->setLife(l - dmg);
		return (this->getLife() > 0);
}

// SETTER | GETTER
const AIPosition& Sinus::getPosition() const { return _pos; }
void Sinus::setPosition(const AIPosition& p) { _pos = p; }

const std::string &Sinus::getName() const { return _name; }
const void Sinus::setName(const std::string &n) { _name = n; }

const uint32_t Sinus::getLife() const { return _life; }
void Sinus::setLife(const uint32_t l) { _life = l; }

const uint32_t Sinus::getWidth() const { return _width; }
void Sinus::setWidth(const uint32_t l) { _width = l; }

const uint32_t Sinus::getHeight() const { return _height; }
void Sinus::setHeight(const uint32_t l) { _height = l; }

const bool Sinus::getShoot() const { return _shoot; }
void Sinus::setShoot(const bool x) { _shoot = x; }

const uint32_t Sinus::getTurn() const { return _turn; }
void Sinus::setTurn(const uint32_t t) { _turn = t; }

void Sinus::setShootVector(const vec2D& x) {_shootVector = x;}
const vec2D& Sinus::getShootVector() const {return _shootVector;}

AIPosition& Sinus::getNearPlayer(std::vector<AIPosition>& players) const
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



Action Sinus::actualize(std::vector<AIPosition>& players, std::vector<AIPosition>&, AIPosition)
{
	AIPosition p;
	p.X = this->getPosition().X;
	p.Y = this->getPosition().Y;

	float radian = _angle * 3.14 / 180;

	p.Y = _stockY + sin(radian) * _rayon;
	p.X -= 3;
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
	_angle = static_cast<int>(_angle + 5) % 365;

	if (this->getLife() == 0)
		return (Action::DEAD);
	if (this->getShoot() == true)
		return (Action::SHOOT);
	return (Action::DEFAULT);
}

#if defined (_WIN32) || defined (_WIN64)
extern "C" __declspec(dllexport) std::shared_ptr<IArtificialIntelligence> createLib(const int a, const int b, const int c, const int d)
{
	return (std::make_shared<Sinus>(Sinus(a, b, c, d)));
}
#elif defined (__linux__) || defined (__APPLE__)
extern "C" std::shared_ptr<IArtificialIntelligence> createLib(const int a, const int b, const int c, const int d)
{
	return (std::make_shared<Sinus>(Sinus(a, b, c, d)));
}
#endif
