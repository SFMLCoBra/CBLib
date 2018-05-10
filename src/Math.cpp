#include "Math.hpp"

#include "Data.hpp"

namespace cb
{

Math::Math()
{
}


Math::~Math()
{
}

void Math::normalize(sf::Vector2f& v)
{
	float length = std::sqrt(v.x*v.x + v.y*v.y);

	v.x /= length;
	v.y /= length;
}

float Math::getLength(sf::Vector2f v1, sf::Vector2f v2)
{
	return std::sqrt((v2.x - v1.x)*(v2.x - v1.x) + (v2.y - v1.y)*(v2.y - v1.y));
}

float Math::getLength(sf::Vector2f v)
{
	return std::sqrt((v.x * v.x) + (v.y * v.y));
}

sf::Vector2f Math::getVectorBetweenPoints(sf::Vector2f p1, sf::Vector2f p2)
{
	return sf::Vector2f(p1 - p2);
}

std::vector<sf::Vector2f> Math::getPixelPositionsBetween(sf::Vector2f v1, sf::Vector2f v2)
{
	std::vector<sf::Vector2f> v;
	bool steep = (std::fabs(v2.y - v1.y) > fabs(v2.x - v1.x));

	if (steep)
	{
		std::swap(v1.x, v1.y);
		std::swap(v2.x, v2.y);
	}

	if (v1.x > v2.x)
	{
		std::swap(v1.x, v2.x);
		std::swap(v1.y, v2.y);
	}

	float dx = v2.x - v1.x;
	float dy = std::fabs(v2.y - v1.y);

	float error = dx / 2.0f;
	int ystep = (v1.y < v2.y) ? 1 : -1;
	int y = static_cast<int>(v1.y);

	int maxX = static_cast<int>(v2.x);

	for (int x = v1.x; x < maxX; x++)
	{
		if (steep)
		{
			v.push_back(sf::Vector2f(y, x));
		}
		else
		{
			v.push_back(sf::Vector2f(x, y));
		}

		error -= dy;
		if (error < 0)
		{
			y += ystep;
			error += dx;
		}
	}

	return v;
}

sf::Vector2f Math::getDirection(sf::Vector2f start, sf::Vector2f t)
{
	t -= start;
	float x = std::abs(t.x);
	float y = std::abs(t.y);
	float length = std::sqrt(x*x + y*y);

	if (length > 0)
	{
		t.x /= length;
		t.y /= length;
	}
	else
	{
		t.x /= 1.f;
		t.y /= 1.f;
	}

	return t;
}

float Math::getAngle(sf::Vector2f start, sf::Vector2f t)
{
	t -= start;

	return (atan2(t.y, t.x ) * 180.f / PI);
}

sf::Vector2f Math::calculateNormal(sf::Vector2f s, sf::Vector2f n, bool clockwise)
{
	n -= s;
	if (clockwise)
	{
		return { n.y,-n.x };
	}
	return {-n.y, n.x};
}

sf::Vector2f Math::calculateNormal(sf::Vector2f v, bool clockwise)
{
	if (clockwise)
	{
		return{ v.y,-v.x };
	}
	return{ -v.y, v.x };
}

bool Math::isNormalPointingOutwards(sf::Vector2f a, sf::Vector2f b)
{
	if (calculateCrossProduct(a, b) > 0)
	{
		return true;
	}
	return false;
}

float Math::calculateScalarProduct(sf::Vector2f a, sf::Vector2f b)
{
	return	{ (a.x*b.x) + (a.y * b.y) };
}

float Math::calculateCrossProduct(const sf::Vector2f& a, const sf::Vector2f& b)
{
	return (a.x*b.y - a.y * b.x);
}

bool Math::isVectorOrthogonal(const sf::Vector2f& a, const sf::Vector2f& b)
{
	float f = std::abs(calculateScalarProduct(a, b) / (getLength(a) * getLength(b)));

	if (f > 1 - 0.000001f)
	{
		return true;
	}
	else if (f < -1 + 0.000001f)
	{
		return true;
	}

	return false;
}


}


