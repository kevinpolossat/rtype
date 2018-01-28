#include "TreeSearch.hpp"

const double MCTS::Node::calculUCB() const
{
  if (_parent == nullptr)
    return (0);
  if (_visit == 0)
    return (42);
  double k = 0;//static_cast<double>(_score) / static_cast<double>(_visit);
  k += sqrt(2) * log(static_cast<double>(_parent->getVisits() * 10000) / static_cast<double>(_visit));
  return k;
}

MCTS::TreeSearch::TreeSearch(const std::vector<AIShoot *> s, AIPosition p, int w, int h)
{
  _shoots = s;
  _pos = p;
  _width = w;
  _height = h;
  _treeDepth = 25;
  _simuDepth = 50;
  _root = new MCTS::Node(nullptr, p, MCTS::Direction::NONE, 0);
}

AIPosition MCTS::TreeSearch::loopTree(const int simu)
{
  AIPosition p = _root->getPosition();

  for (int i = 0; i < simu; i++)
  {
      MCTS::Node *x = selectNode();
      x = expandNode(x);
      backpropagationNode(simulateNode(x), x);
  }
  int min = 0;
  for (auto x : _root->getChilds())
  {
    if (x->getScore() > min)
    {
      min = x->getScore();
      p = x->getPosition();
    }
  }
  return p;
}

MCTS::Node *MCTS::TreeSearch::selectRec(MCTS::Node *x, const double v, int prof)
{
  if (prof >= _treeDepth)
    return x;
  if (x->getChilds().size() == 0)
    return x;

  double min = 0;
  int minIndex = 0;
  for (int i = 0; i < x->getChilds().size(); i++)
  {
    if (x->getChildIndex(i)->calculUCB() > min)
    {
      min = x->getChildIndex(i)->calculUCB();
      minIndex = i;
    }
  }
  if (min > v)
    return (selectRec(x->getChildIndex(minIndex), min, prof + 1));
  return (x);
}

MCTS::Node *MCTS::TreeSearch::selectNode()
{
  return (selectRec(_root, -1, 1));
}

MCTS::Node *MCTS::TreeSearch::expandNode(MCTS::Node *x)
{
  if (x->getChilds().size() > 0 || x->getVisits() == 0)
    return x;

  AIPosition p;

  for (auto s : _shoots)
  {
    s->resetTheoryPosition();
    for (int i = 0; i < x->getProf(); i++)
      s->increaseShoot();
  }


  p = x->getPosition();
  if (isInMap(p))
  {
    bool shot = false;
    for (auto s : _shoots)
    {
      if (s->collisionNoAutoIncrease(p, 60, 60))
      {
        shot = true;
      }
    }
    if (!shot)
    {
      x->addChild(new MCTS::Node(x, p, MCTS::Direction::NONE, x->getProf() + 1));
    }
  }

  p = x->getPosition();
  p.X -= 8;
  if (isInMap(p))
  {
    bool shot = false;
    for (auto s : _shoots)
      if (s->collisionNoAutoIncrease(p, 60, 60))
        shot = true;
    if (!shot)
      x->addChild(new MCTS::Node(x, p, MCTS::Direction::TOP, x->getProf() + 1));
  }

  p = x->getPosition();
  p.X += 8;
  if (isInMap(p))
  {
    bool shot = false;
    for (auto s : _shoots)
      if (s->collisionNoAutoIncrease(p, 60, 60))
        shot = true;
    if (!shot)
      x->addChild(new MCTS::Node(x, p, MCTS::Direction::BOTTOM, x->getProf() + 1));
  }

  p = x->getPosition();
  p.Y -= 8;
  if (isInMap(p))
  {
    bool shot = false;
    for (auto s : _shoots)
      if (s->collisionNoAutoIncrease(p, 60, 60))
        shot = true;
    if (!shot)
      x->addChild(new MCTS::Node(x, p, MCTS::Direction::LEFT, x->getProf() + 1));
  }

  p = x->getPosition();
  p.Y += 8;
  if (isInMap(p))
  {
    bool shot = false;
    for (auto s : _shoots)
      if (s->collisionNoAutoIncrease(p, 60, 60))
        shot = true;
    if (!shot)
      x->addChild(new MCTS::Node(x, p, MCTS::Direction::RIGHT, x->getProf() + 1));
  }

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0, x->getChilds().size());
  int k = dis(gen);

  if (x->getChilds().size() == 0)
    return x;
  return (x->getChildIndex(k));
}

const int MCTS::TreeSearch::simulateNode(MCTS::Node *x)
{
  int dead = 0;

  if (!isInMap(x->getPosition()))
    return (dead);

  for (auto s : _shoots)
    s->resetTheoryPosition();

  for (auto s : _shoots)
    for (int i = 0; i < x->getProf() && s->increaseShoot(); i++);

  AIPosition testPosition = x->getPosition();

  for (int i = 0; i < _simuDepth; i++)
  {
    for (auto s : _shoots)
    {
      if (s->collisionNoAutoIncrease(testPosition, 60, 60) || !s->increaseShoot())
        return dead;
    }
    dead++;
  }
return dead;
}

void       MCTS::TreeSearch::backpropagationNode(const int w, MCTS::Node *x)
{
  MCTS::Node *l = x;
  do
  {
    l->addVisit();
    l->addScore(w);
    l = l->getParent();
  } while (l != nullptr);
}

void      MCTS::TreeSearch::clearTree(Node *x)
{
  if (x->getChilds().size() == 0)
    delete x;
  else
  {
    for (auto z : x->getChilds())
      clearTree(z);
    x->clearChildsVector();
    delete x;
  }
}
