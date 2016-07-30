#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/graphics.hpp>
#include "iostream"
#include "Collidable.h"
#include "PlayerCar.h"

////////////////////////////////////////////////////////////
/// \brief Tyres which are used to border the track for the player to collide into.
////////////////////////////////////////////////////////////
class Tyre : public Collidable
{
	private:
		float m_fRadius;//!< Holds the distance between the centre and the edge of the tyre.

		////////////////////////////////////////////////////////////
		/// \brief Draws all of the drawable tyre entities to the screen
		///
		/// \param target Holds where to draw the entities to.
		///					   
		///	\param states 
		///
		/// \see CurrentSprite
		////////////////////////////////////////////////////////////
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		////////////////////////////////////////////////////////////
		/// \brief Checks the collision between the tyre and a tyre.
		///
		/// \param Collidable2 Holds the Tyre data to check against the tyre.
		///
		/// \see Collision(), CurrentSprite
		////////////////////////////////////////////////////////////
		void Collision(Tyre &Collidable2);

		////////////////////////////////////////////////////////////
		/// \brief Checks the collision between the tyre and a car.
		///
		/// \param Collidable2 Holds the car data to check against the tyre.
		///
		/// \see Collision(), CurrentSprite
		////////////////////////////////////////////////////////////
		void Collision(PlayerCar &Collidable2);

	public:
		////////////////////////////////////////////////////////////
		/// \brief Default constructor
		////////////////////////////////////////////////////////////
		Tyre();

		////////////////////////////////////////////////////////////
		/// \brief Constructor
		///
		/// \param k_fX Holds the X coordinate of the tyres position
		///
		/// \param k_fY Holds the Y coordinate of the tyres position
		////////////////////////////////////////////////////////////
		Tyre(const float k_fX, const float k_fY);

		////////////////////////////////////////////////////////////
		/// \brief Reroutes the collision to the correct collision Subroutine.
		///
		/// \param Collidable2 Holds the collidable to check the collision on which can be either a
		///					   Tyre for Tyre - Tyre Collision or a
		///					   Car for Tyre - Car Collision.
		////////////////////////////////////////////////////////////
		void Collision(Collidable &Collidable2);

		////////////////////////////////////////////////////////////
		/// \brief Returns the radius of the tyre
		///
		/// \return Returns the radius of the tyre
		///
		/// \see m_fRadius
		////////////////////////////////////////////////////////////
		float getRadius();

		////////////////////////////////////////////////////////////
		/// \brief Sets the texture of the Tyre to the texture given.
		///
		/// \param Iter Holds the pointer to the texture that is going to be used.
		///
		/// \see CurrentTexture, CurrentSprite
		////////////////////////////////////////////////////////////
		void setTexture(std::vector<sf::Texture>::iterator Iter);

		////////////////////////////////////////////////////////////
		/// \brief Sets the position of the Tyre to the coordinates given
		///
		/// \param k_fX Holds the X coordinate of the position
		///
		/// \param k_fY Holds the Y coordinate of the position
		///
		/// \see CurrentSprite, getPosition()
		////////////////////////////////////////////////////////////
		void setPosition(const float &k_fX, const float &k_fY);

		////////////////////////////////////////////////////////////
		/// \brief Returns the position coordinates of the tyre sprite
		///
		/// \return Returns the position coordinates of the tyre sprite
		///
		/// \see CurrentSprite, setPosition()
		////////////////////////////////////////////////////////////
		sf::Vector2f getPosition();
};

////////////////////////////////////////////////////////////
/// \class Tyre
///
/// Tyres are used for borders of the track and are static, these can be positioned
/// anywhere on the track to be obstacles.
///
/// The cars can collide with tyres to stop them from moving.
///
/// The different properties of the car are accessible by using the get() and set() functions
/// such as getPosition(), setPosition(), getRadius() etc.
///
/// \see Collidable
////////////////////////////////////////////////////////////
