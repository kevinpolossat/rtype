#include "Boss.hpp"
#include "TreeSearch.hpp"

AIShoot::AIShoot(AIPosition p, vec2D v, int hitbox)
{
  _startPos = p;
  _theoryPos = p;
  _hitbox = hitbox;
  _direction = v;
}

const bool AIShoot::increaseShoot()
{
   _theoryPos.Y += static_cast<int>(_direction.X);
   _theoryPos.X += static_cast<int>(_direction.Y);

   return (_theoryPos.X >= 1);
}

const bool AIShoot::collision(AIPosition check, int XBox, int YBox)
{
  bool end = true;
  bool hit = false;

  while (end)
  {
    for (int i = check.X - XBox; i <= check.X + XBox; i++)
      for (int j = check.Y - YBox; j <= check.Y + YBox; j++)
        for (int m = this->_theoryPos.X - this->_hitbox; m <= this->_theoryPos.X + this->_hitbox; m++)
          for (int n = this->_theoryPos.Y - this->_hitbox; n <= this->_theoryPos.Y + this->_hitbox; n++)
            if (i == m && j == n)
              return true;
    end = this->increaseShoot();
  }
  this->resetTheoryPosition();
  return hit;
}

const bool AIShoot::collisionNoAutoIncrease(AIPosition check, int XBox, int YBox)
{
  bool hit = false;

  for (int i = check.X - XBox; i <= check.X + XBox; i++)
    for (int j = check.Y - YBox; j <= check.Y + YBox; j++)
      for (int m = this->_theoryPos.X - this->_hitbox; m <= this->_theoryPos.X + this->_hitbox; m++)
        for (int n = this->_theoryPos.Y - this->_hitbox; n <= this->_theoryPos.Y + this->_hitbox; n++)
          if (i == m && j == n)
            return true;
  return hit;
}

Boss & Boss::operator=(Boss *c)
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

Boss::Boss(Boss *c)
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

IArtificialIntelligence *Boss::NewIA(const uint32_t myX, const uint32_t myY, const uint32_t width, const uint32_t height)
{
	return new Boss(myX, myY, width, height);
}

bool Boss::setDamages(uint32_t dmg)
{
		uint32_t l = this->getLife();

		this->setLife(l - dmg);
		return (this->getLife() > 0);
}

// SETTER | GETTER
const AIPosition Boss::getPosition() const { return _pos; }
void Boss::setPosition(const AIPosition p) { _pos = p; }

const std::string &Boss::getName() const { return _name; }
const void Boss::setName(const std::string &n) { _name = n; }

const uint32_t Boss::getLife() const { return _life; }
void Boss::setLife(const uint32_t l) { _life = l; }

const uint32_t Boss::getWidth() const { return _width; }
void Boss::setWidth(const uint32_t l) { _width = l; }

const uint32_t Boss::getHeight() const { return _height; }
void Boss::setHeight(const uint32_t l) { _height = l; }

const bool Boss::getShoot() const { return _shoot; }
void Boss::setShoot(const bool x) { _shoot = x; }

const uint32_t Boss::getTurn() const { return _turn; }
void Boss::setTurn(const uint32_t t) { _turn = t; }

void Boss::setShootVector(const vec2D x) {_shootVector = x;}
const vec2D Boss::getShootVector() const {return _shootVector;}

AIPosition Boss::getNearPlayer(std::vector<AIPosition>& players) const
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

Boss::Boss(const int myX, const int myY, const int width, const int height)
{
  AIPosition p;
	p.X = myX;
	p.Y = myY;

	this->setName("Boss");
	this->setLife(10);
	this->setPosition(p);
	this->setWidth(width);
	this->setHeight(height);
	this->setShoot(false);
	this->setTurn(0);
  _XBox = 1;
  _YBox = 3;
}

Action Boss::actualize(std::vector<AIPosition>& enemies, std::vector<AIPosition>& shoots, AIPosition myPos)
{
  this->setTurn(this->getTurn() + 1);
  this->setPosition(myPos);
  this->_selectMove(shoots);
  if (this->getTurn() % 3 == 0)
  {
      this->_selectShoot(enemies);
      return (Action::SHOOT);
  }
  else
    this->setShoot(false);
  return (Action::DEFAULT);
}

void        Boss::_selectMove(std::vector<AIPosition>& shoots)
{
    std::vector<AIShoot *> Cshoots;
    for (auto x : shoots)
      Cshoots.push_back(new AIShoot(x, {0, -1}, 0));

    AIPosition p;
    MCTS::TreeSearch *tree = new MCTS::TreeSearch(Cshoots, this->getPosition(), this->getWidth(), this->getHeight());

    p = tree->loopTree(500);
    tree->clearTree(tree->getRoot());
    this->setPosition(p);
}

void        Boss::_selectShoot(std::vector<AIPosition>& enemies)
{
  AIPosition en = this->getNearPlayer(enemies);
  vec2D toShoot;

  float dX = static_cast<float>(en.X - this->getPosition().X);
  float dY = static_cast<float>(en.Y - this->getPosition().Y);

  if (dX == 0 && dY == 0)
    dX += 1;
  toShoot.X = -(dX / (dX * dX + dY * dY));
  toShoot.Y = -(dY / (dX * dX + dY * dY));
  this->setShootVector(toShoot);
  this->setShoot(true);
}
