#ifndef __TREESEARCH_HPP__
#define __TREESEARCH_HPP__

#include <vector>
#include <random>
#include "Boss.h"

namespace MCTS
{

  enum Direction
  {
    TOP,
    LEFT,
    RIGHT,
    BOTTOM,
    NONE
  };

  class Node
  {
    public:
      explicit Node(Node *parent, AIPosition position, Direction d, int prof) {_parent = parent; _pos = position; _score = _visit = 0; _d = d; _prof = prof;}
      ~Node() = default;

      Node                        *getParent() const {return _parent;}
      const std::vector<Node *>&  getChilds() const {return _childs;}
      Node                        *getChildIndex(const int index) const {return _childs.at(index);}
      const int                   getVisits() const {return _visit;}
      const int                   getScore() const {return _score;}
      const AIPosition            getPosition() const {return _pos;}
      const Direction             getDirection() const {return _d;}

      void addChild(Node *x) {_childs.push_back(x);}
      void addVisit() {_visit++;}
      void addScore(const int w) {_score+= w;}

      void clearChildsVector() {_childs.clear();}

      const double calculUCB() const;

      const int getProf() const {return _prof;}

    private:
      Direction             _d;
      Node                  *_parent;
      std::vector<Node *>   _childs;
      int                   _visit;
      int                   _score;
      AIPosition            _pos;
      int                   _prof;
  };

  class TreeSearch
  {
    public:
      explicit TreeSearch(const std::vector<AIShoot *> s, AIPosition p, int w, int h);
      ~TreeSearch() = default;

      Node        *selectNode();
      Node        *expandNode(Node *);
      const int   simulateNode(Node *);
      void        backpropagationNode(const int , Node *);
      AIPosition  loopTree(const int);

      const bool  isInMap(const AIPosition x) const {return (x.X < _width - 80 && x.X > 40 && x.Y < _height - 80 && x.Y > 40);}
      Node        *selectRec(Node *x, const double v, int prof);

      Node        *getRoot() const {return _root;}

      void        clearTree(Node *);

    private:
      Node                    *_root;
      int                     _height;
      int                     _width;
      std::vector<AIShoot *>  _shoots;
      AIPosition              _pos;
      int                     _simuDepth;
      int                     _treeDepth;
  };

};

#endif
