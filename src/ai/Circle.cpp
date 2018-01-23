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
	_rayon = 90.f;
	_center.X = myX;
	_center.Y = myY;
}

std::shared_ptr<IArtificialIntelligence> Circle::NewIA(const uint32_t myX, const uint32_t myY, const uint32_t width, const uint32_t height)
{
	return std::make_shared<Circle>(Circle(myX, myY, width, height));
}


bool Circle::setDamages(uint32_t dmg)
{
		uint32_t l = this->getLife();

		this->setLife(l - dmg);
		return (this->getLife() > 0);
}

const AIPosition& Circle::getPosition() const { return _pos; }
void Circle::setPosition(const AIPosition& p) { _pos = p; }

const std::string &Circle::getName() const { return _name; }
const void Circle::setName(const std::string &n) { _name = n; }

const uint32_t Circle::getLife() const { return _life; }
void Circle::setLife(const uint32_t l) { _life = l; }

const uint32_t Circle::getWidth() const { return _width; }
void Circle::setWidth(const uint32_t l) { _width = l; }

const uint32_t Circle::getHeight() const { return _height; }
void Circle::setHeight(const uint32_t l) { _height = l; }

const bool Circle::getShoot() const { return _shoot; }
void Circle::setShoot(const bool x) { _shoot = x; }

const uint32_t Circle::getTurn() const { return _turn; }
void Circle::setTurn(const uint32_t t) { _turn = t; }

void Circle::setShootVector(const vec2D& x) {_shootVector = x;}
const vec2D& Circle::getShootVector() const {return _shootVector;}

AIPosition& Circle::getNearPlayer(std::vector<AIPosition>& players) const
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


Action Circle::actualize(std::vector<AIPosition>& players, std::vector<AIPosition>&, AIPosition)
{
	AIPosition p{this->getPosition().X, this->getPosition().Y};

	if (_angle <= 360)
	{
		float radian = _angle * 3.14 / 180;

		p.X = _center.X + static_cast<int>(cos(radian) * _rayon);
		p.Y = _center.Y + static_cast<int>(sin(radian) * _rayon);
	}
	else if (_angle <= 500)
	{
		p.X = this->getPosition().X - 5;
	}
	else
	{
		p.X = this->getPosition().X - 5;
		_angle = -5;
		_center.X = p.X - _rayon;
		_center.Y = p.Y;
	}

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

	_angle += 5;
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
	return (std::make_shared<Circle>(Circle(a, b, c, d)));
}
#elif defined (__linux__) || defined (__APPLE__)
extern "C" std::shared_ptr<IArtificialIntelligence> createLib(const int a, const int b, const int c, const int d)
{
	return (std::make_shared<Circle>(Circle(a, b, c, d)));
}
#endif
