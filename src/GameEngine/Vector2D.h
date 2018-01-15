/*
** IObject.hpp for 2D_Game_Engine in /home/isidor_m/tek2/tmp/2D_Game_Engine/includes
**
** Made by isidor_m
** Login   <isidor_m@epitech.net>
**
** Started on  Wed May 10 11:29:50 2017 isidor_m
** Last update Tue May 30 18:18:31 2017 Enzo WALTER
*/

#ifndef VEC2D_HPP
#define VEC2D_HPP

#include <iostream>
#include <ostream>
#include <math.h>

class Vector2D
{
  public:
    explicit Vector2D(double x = 0, double y = 0);
    ~Vector2D();
    Vector2D operator+(const Vector2D& rhs) const;
    Vector2D operator=(const Vector2D&);
    Vector2D operator-(const Vector2D&) const;
    Vector2D operator*(const Vector2D&) const;
    Vector2D operator*(const float&) const;
    Vector2D operator/(const Vector2D&) const;
    Vector2D normalize();
	double lenght() const;
	double dotProduct(const Vector2D&) const;
    double x;
    double y;
};
bool operator==(const Vector2D&, const Vector2D&);

#endif
