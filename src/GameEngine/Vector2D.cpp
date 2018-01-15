#include "Vector2D.h"

Vector2D::Vector2D(double x, double y)
{
  this->x = x;
  this->y = y;
}

Vector2D::~Vector2D()
{
}

Vector2D Vector2D::operator+(const Vector2D& rhs) const
{
  Vector2D tmp{this->x + rhs.x, this->y + rhs.y};
  return (tmp);
}

Vector2D Vector2D::operator=(const Vector2D& rhs)
{
  this->x = rhs.x;
  this->y = rhs.y;
  return (*this);
}

Vector2D Vector2D::operator-(const Vector2D& rhs) const
{
  Vector2D tmp{this->x - rhs.x, this->y - rhs.y};
  return (tmp);
}

Vector2D Vector2D::operator*(const Vector2D& rhs) const
{
  Vector2D tmp{this->x * rhs.x, this->y * rhs.y};
  return (tmp);
}

Vector2D Vector2D::operator*(const float& rhs) const
{
  Vector2D tmp(this->x * rhs, this->y * rhs);
  return (tmp);
}

Vector2D Vector2D::operator/(const Vector2D& rhs) const
{
  Vector2D tmp{this->x / rhs.x, this->y / rhs.y};
  return (tmp);
}

double Vector2D::lenght() const
{
  return (sqrt((this->x * this->x) + (this->y * this->y)));
}

double Vector2D::dotProduct(const Vector2D& rhs) const
{
  return ((this->x * rhs.x) + (this->y * rhs.y));
}

bool operator==(const Vector2D& lhs, const Vector2D& rhs)
{
  if (lhs.x == rhs.x && lhs.y == rhs.y)
    return (true);
  return (false);
}

Vector2D Vector2D::normalize()
{
  this->x /= this->lenght();
  this->y /= this->lenght();
  return (*this);
}
