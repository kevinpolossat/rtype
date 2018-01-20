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

Action Boss::actualize(std::vector<AIPosition>& shoots, std::vector<AIPosition>& enemies, AIPosition myPos)
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
