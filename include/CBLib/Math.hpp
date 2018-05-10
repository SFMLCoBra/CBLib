#ifndef MMATH_H
#define MMATH_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdarg>

#ifndef PI
#define PI (3.14159265358979323846)
#endif

#ifndef RAD_TO_DEGREE 
#define RAD_TO_DEGREE 57.295779513082320876
#endif

#ifndef DEGREE_TO_RAD 
#define DEGREE_TO_RAD 0.0174532925199432957
#endif


namespace cb
{

class Math
{
public:
	Math();
	~Math();

	/*
	// Normalizes a vector.
	*/
	static void normalize(sf::Vector2f& v);
	template <typename T>
	static void normalize(T& t...);

	static float getLength									(sf::Vector2f v1, sf::Vector2f v2);
	static float getLength									(sf::Vector2f v);

	static std::vector<sf::Vector2f> getPixelPositionsBetween	(sf::Vector2f, sf::Vector2f);

	static sf::Vector2f getVectorBetweenPoints					(sf::Vector2f p1, sf::Vector2f p2);
	
	static sf::Vector2f getDirection							(sf::Vector2f start, sf::Vector2f target);
		
	static float getAngle									(sf::Vector2f start, sf::Vector2f target);

	static sf::Vector2f calculateNormal							(sf::Vector2f s, sf::Vector2f n, bool clockwise = true);
	static sf::Vector2f calculateNormal							(sf::Vector2f v, bool clockwise = true);
	static bool isNormalPointingOutwards					(sf::Vector2f v, sf::Vector2f n);

	static bool isVectorOrthogonal							(const sf::Vector2f& a, const sf::Vector2f& b);

	static float calculateScalarProduct						(sf::Vector2f a, sf::Vector2f b);

	static float calculateCrossProduct						(const sf::Vector2f& a, const sf::Vector2f& b);

private:

};


template<typename T>
inline void Math::normalize(T& t...)
{
	va_list args;
	va_start(args, fmt);

	T length{ T(0) };

	T* temp[sizeof...(t)];

	for (int i = 0; i < sizeof...(t); i++)
	{
		temp[i] = &va_arg(args, T);
		length += (temp*temp);
	}
	temp[i] /= length;


	va_end(args);
}

}

#endif
