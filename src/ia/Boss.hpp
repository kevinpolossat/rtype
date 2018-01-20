#ifndef __BOSS_HPP__
#define __BOSS_HPP__

#include <iostream>
#include <vector>
#include "IArtificialIntelligence.hpp"

class AIShoot
{
public:
  explicit AIShoot(AIPosition p, vec2D v, int hitbox);
  ~AIShoot();

  const AIPosition getTheoryPosition() const { return _theoryPos; }
  const AIPosition getStartPosition() const { return _startPos; }

  void resetTheoryPosition() {_theoryPos = _startPos;}

  const bool increaseShoot();

  const bool collision(AIPosition check, int Xbox, int Ybox);
  const bool collisionNoAutoIncrease(AIPosition check, int Xbox, int Ybox);

private:
  int         _hitbox;
  AIPosition  _startPos;
  AIPosition  _theoryPos;
  vec2D       _direction;
};

class Boss : public IArtificialIntelligence
{
public:
  	Boss(const int myX, const int myY, const int width, const int height);
    Boss(Boss *);
  	~Boss() {}

    Boss & operator=(Boss *);

  	virtual Action actualize(std::vector<AIPosition>& shoots, std::vector<AIPosition>& enemies, AIPosition myPos);

private:

  void        _selectMove(std::vector<AIPosition>&);
  void        _selectShoot(std::vector<AIPosition>&);

  int    _XBox;
  int    _YBox;
};

#endif
