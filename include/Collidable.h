#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/graphics.hpp>
#include "../include/vector.h"

class PlayerCar;
class Tyre;

////////////////////////////////////////////////////////////
/// \brief A collidable type which can collide with other collidable types.
////////////////////////////////////////////////////////////
class Collidable : public sf::Drawable
{	
	public:
		sf::Texture CurrentTexture; //!< Holds the texture data to be applied to the sprite.
		sf::Sprite CurrentSprite; //!< Holds the data to be drawn to the screen for the collidable.

		////////////////////////////////////////////////////////////
		/// \brief A virtual constructor for the collision between Collidables and tyres to be overwridden when derived from by objects.
		///
		/// \param Collidable2 Holds the Tyre data to check the collisions.
		////////////////////////////////////////////////////////////
		virtual void Collision(Tyre& Collidable2)=0;

		////////////////////////////////////////////////////////////
		/// \brief A virtual constructor for the collision between Collidables and Cars to be overwridden when derived from by objects.
		///
		/// \param Collidable2 Holds the Car data to check the collisions.
		////////////////////////////////////////////////////////////
		virtual void Collision(PlayerCar& Collidable2)=0;

		////////////////////////////////////////////////////////////
		/// \brief A virtual constructor for the collision between Collidables to be overwridden when derived from by objects.
		///
		/// \param Collidable2 Holds the Collidable data to check the collisions.
		////////////////////////////////////////////////////////////
		virtual void Collision(Collidable& Collidable2)=0;
};

////////////////////////////////////////////////////////////
/// \class Collidable
///
/// A collidable type which can collide with other collidable types. There are 2 types of collidable Cars and tyres.
/// These can collide with eachother using the functions within this class, these are pure virtual functions therefore 
/// they must be overwridden to determine how to perform the algorithm.
/// 
/// \see PlayerCar, Tyre
////////////////////////////////////////////////////////////