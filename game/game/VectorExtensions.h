#pragma once

#include <SFML\System.hpp>
#include "Angle.h"

namespace jck
{
	namespace vector
	{

		template <class T>
		T mag(const sf::Vector2<T>& rhs)
		{
			return sqrt(pow(rhs.x, 2) + pow(rhs.y, 2));
		}
		template <class T>
		sf::Vector2<T> normalize(const sf::Vector2<T>& rhs)
		{
			return sf::Vector2<T>(rhs.x / mag(rhs), rhs.y / mag(rhs));
		} 
		template <class T>
		Angle<T> atan(const sf::Vector2<T>& rhs)
		{
			return Angle<T>(atan2(rhs.y, rhs.x));
		}
		
		template <class T>
		T dot(const sf::Vector2<T>& lhs, const sf::Vector2<T>& rhs)
		{
			return lhs.x * rhs.x + lhs.y * rhs.y;
		}

		template <class T>
		T cross(const sf::Vector2<T>& lhs, const sf::Vector2<T>& rhs)
		{
			return lhs.x * rhs.y - lhs.y * rhs.x;
		}
		template <class T>
		sf::Vector2<T> rotate(const sf::Vector2<T>& rhs, const Angle<T>& angle)
		{
			sf::Vector2<T> ret;
			ret.x = rhs.x * cos(angle.radians()) - rhs.y * sin(angle.radians());
			ret.y = rhs.x * sin(angle.radians()) + rhs.y * cos(angle.radians());
			return ret;
		}
		
		template <class T>
		void createBounds(const sf::Vector2<T>& base, const sf::Vector2<T>& modifier, sf::Vector2<T>* lowerBound, sf::Vector2<T>* upperBound)
		{
			lowerBound->x = std::min(base.x - modifier.x, base.x + modifier.x);
			lowerBound->y = std::min(base.y - modifier.y, base.y + modifier.y);

			upperBound->x = std::max(base.x - modifier.x, base.x + modifier.x);
			upperBound->y = std::max(base.y - modifier.y, base.y + modifier.y);
		}
		template <class T>
		sf::Vector2<T> max(const sf::Vector2<T>& lhs, const sf::Vector2<T>& rhs)
		{
			sf::Vector2<T> ret;
			
			ret.x = std::max(lhs.x, rhs.x);
			ret.y = std::max(lhs.y, rhs.y);

			return ret;
		}
		template <class T>
		sf::Vector2<T> min(const sf::Vector2<T>& lhs, const sf::Vector2<T>& rhs)
		{
			sf::Vector2<T> ret;
			
			ret.x = std::min(lhs.x, rhs.x);
			ret.y = std::min(lhs.y, rhs.y);

			return ret;
		}
	}
}