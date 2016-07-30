#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/graphics.hpp>
#include <iostream>
#include <Array>
#include "../include/vector.h"
#include "../include/Tyre.h"
#include "../include/Collidable.h"

////////////////////////////////////////////////////////////
/// \brief A car which the player can control
////////////////////////////////////////////////////////////
class PlayerCar : public Collidable
{
	private:
		util::Vector m_vAcceleration; //!< Holds the acceleration rate.
		util::Vector m_vVelocity; //!< Holds the velocity in x and y.
		float m_fSteeringAngle; //!< Holds the angle the front wheel is turned towards relative to the car.
		float m_fCarAngle; //!< Holds the angle the car is turned towards.
		float m_iTurnDirection; //!< States which direction the car is rotating.
		float m_iDriveDirection;//!< States which direction the car is moving.
		std::array<sf::RectangleShape, 4> m_aWheels; //!< Holds data for displayed wheels
		int m_iLapsCompleted; //!< States how many laps have been completed by the player
		float m_fBestLapTime; //!< Holds the best lap time the player has achieved
		std::vector<bool> m_vbCheckpointsReached; //!< Holds whether each checkpoint on the track has been reached.
		sf::Clock LapTime; //!< Holds the current time its taken for the player to perform a lap.

		////////////////////////////////////////////////////////////
		/// \brief Checks the collision between the car and a tyre.
		///
		/// \param Collidable2 Holds the Tyre data to check against the car.
		///
		/// \see Collision(), CurrentSprite
		////////////////////////////////////////////////////////////
		void Collision(Tyre &Collidable2);

		////////////////////////////////////////////////////////////
		/// \brief Checks the collision between the car and a car.
		///
		/// \param Collidable2 Holds the car data to check against the car.
		///
		/// \see Collision(), CurrentSprite
		////////////////////////////////////////////////////////////
		void Collision(PlayerCar &Collidable2);

		////////////////////////////////////////////////////////////
		/// \brief Draws all of the drawable car entities to the screen
		///
		/// \param target Holds where to draw the entities to.
		///					   
		///	\param states 
		///
		/// \see Wheels, CurrentSprite
		////////////////////////////////////////////////////////////
		void draw(sf::RenderTarget& target, sf::RenderStates states) const; // Used to draw the car.

	public:

		////////////////////////////////////////////////////////////
		/// \brief Default constructor
		////////////////////////////////////////////////////////////
		PlayerCar();

		////////////////////////////////////////////////////////////
		/// \brief Constructor
		///
		/// \param k_fX Holds the X coordinate of the cars position
		///
		/// \param k_fY Holds the Y coordinate of the cars position
		////////////////////////////////////////////////////////////
		PlayerCar(const float k_fX, const float k_fY);

		////////////////////////////////////////////////////////////
		/// \brief Sets the direction in which the front wheels of the car will turn every frame
		///
		/// \param k_iValue This holds the scalar in which the cars wheels will turn
		///		   0 < Will turn the wheels right
		///		   0 Will stop the wheels from turning
		///        0 > Will turn the wheels left
		///
		/// \see TurnWheels(), PositionWheels()
		////////////////////////////////////////////////////////////
		void setTurnDirection(const int &k_iValue);

		////////////////////////////////////////////////////////////
		/// \brief Performs all of the movement for the car using the bicycle steering model
		///
		/// \param k_fFriction Holds the frictional coefficient which is used to calculate 
		///                    how fast the car accelerates / decelerates
		///					   1 Will cause the car to move very slowly
		///					   0 Will cause the car to not decelerate
		///
		/// \param k_fTimeStep Holds the amount of time which has passed since the last frame.
		///
		/// \see m_vVelocity, m_vAcceleration, m_fSteeringAngle, m_fCarAngle, TurnWheels(), PositionWheels()
		////////////////////////////////////////////////////////////
		void Move(const float &k_fFriction, const float &k_fTimeStep);

		////////////////////////////////////////////////////////////
		/// \brief Performs the turning of the front wheels using the turn direction
		///
		/// \see setTurnDirection(), PositionWheels(), Wheels
		////////////////////////////////////////////////////////////
		void TurnWheels();

		////////////////////////////////////////////////////////////
		/// \brief Reroutes the collision to the correct collision Subroutine.
		///
		/// \param Collidable2 Holds the collidable to check the collision on which can be either a
		///					   Car for Car - Car Collision or a
		///					   Tyre for Car - Tyre Collision.
		////////////////////////////////////////////////////////////
		void Collision(Collidable &Collidable2);

		////////////////////////////////////////////////////////////
		/// \brief Sets the direction in which the car will move every frame
		///
		/// \param k_iValue This holds the scalar in which the car will move
		///		   0 < Will move the car forwards
		///		   0 Will stop the car from moving
		///        0 > Will move the car backwards
		///
		/// \see m_iDriveDirection
		////////////////////////////////////////////////////////////
		void setDriveDirection(const int &k_iValue);

		////////////////////////////////////////////////////////////
		/// \brief Positions the wheels to line up with the car.
		///
		/// \see CurrentSprite, Wheels
		////////////////////////////////////////////////////////////
		void PositionWheels();

		////////////////////////////////////////////////////////////
		/// \brief Returns the angle the car is pointed towards
		///
		/// \return Returns the angle the car is pointed towards
		///
		/// \see m_fCarAngle
		////////////////////////////////////////////////////////////
		float getRotation();

		////////////////////////////////////////////////////////////
		/// \brief Returns the velocity of the car
		///
		/// \return Returns the velocity of the car
		///
		/// \see m_vVelocity, setVelocity()
		////////////////////////////////////////////////////////////
		util::Vector getVelocity();

		////////////////////////////////////////////////////////////
		/// \brief Sets the velocity to the value given
		///
		/// \param k_Vect1 Holds the Velocity x and y values you want to set the velocity to.
		///
		/// \see m_vVelocity, getVelocity()
		////////////////////////////////////////////////////////////
		void setVelocity(const util::Vector &k_Vect1);

		////////////////////////////////////////////////////////////
		/// \brief Returns the amount of laps completed by the player.
		///
		/// \return Returns the amount of laps completed by the player.
		///
		/// \see m_iLapsCompleted, LapComplete()
		////////////////////////////////////////////////////////////
		int getLapsCompleted();

		////////////////////////////////////////////////////////////
		/// \brief Returns the lap time of the current lap
		///
		/// \return Returns the lap time of the current lap
		///
		/// \see LapTime, LapComplete()
		////////////////////////////////////////////////////////////
		float getLapTime();

		////////////////////////////////////////////////////////////
		/// \brief Returns the best lap time the player has achieved
		///
		/// \return Returns the best lap time the player has achieved
		///
		/// \see m_fBestLapTime, LapComplete()
		////////////////////////////////////////////////////////////
		float getBestLapTime();

		////////////////////////////////////////////////////////////
		/// \brief Sets the Checkpoint State to the value given
		///
		/// \param k_iIndex Holds the position of the checkpoint in the vector of checkpoints.
		///
		/// \param k_bState States whether the checkpoint has been passed.
		///
		/// \see m_vbCheckpointsReached, getCheckpointState()
		////////////////////////////////////////////////////////////
		void setCheckpointState(const int &k_iIndex, const bool &k_bState);

		////////////////////////////////////////////////////////////
		/// \brief Returns whether the checkpoint stated has been passed.
		///
		/// \param k_iIndex Holds the position of the checkpoint in the vector of checkpoints.
		///
		/// \return Returns whether the checkpoint stated has been passed.
		///
		/// \see m_vbCheckpointsReached, setCheckpointState()
		////////////////////////////////////////////////////////////
		bool getCheckpointState(const int &k_iIndex);

		////////////////////////////////////////////////////////////
		/// \brief Sets the amount of checkpoints that are being checked against
		///
		/// \param k_iValue Holds the number of checkpoints that are to be created.
		///
		/// \see m_vbCheckpointsReached
		////////////////////////////////////////////////////////////
		void setCheckpointAmount(const int &k_iValue);

		////////////////////////////////////////////////////////////
		/// \brief Completes the lap, checks to see if the best lap has been beaten and starts a new one
		///
		/// \see m_vbCheckpointsReached,m_iLapsCompleted, m_fBestLapTime, LapTime
		////////////////////////////////////////////////////////////
		void LapComplete();

		////////////////////////////////////////////////////////////
		/// \brief Sets the texture of the car to the texture given.
		///
		/// \param Iter Holds the pointer to the texture that is going to be used.
		///
		/// \see CurrentTexture, CurrentSprite
		////////////////////////////////////////////////////////////
		void setTexture(std::vector<sf::Texture>::iterator Iter);

		////////////////////////////////////////////////////////////
		/// \brief Returns the dimensions of the car sprite
		///
		/// \return Returns the dimensions of the car sprite
		///
		/// \see CurrentSprite
		////////////////////////////////////////////////////////////
		sf::Vector2f getSize();

		////////////////////////////////////////////////////////////
		/// \brief Sets the position of the Car to the coordinates given
		///
		/// \param k_fX Holds the X coordinate of the position
		///
		/// \param k_fY Holds the Y coordinate of the position
		///
		/// \see CurrentSprite, getPosition()
		////////////////////////////////////////////////////////////
		void setPosition(const float &k_fX, const float &k_fY);

		////////////////////////////////////////////////////////////
		/// \brief Returns the position coordinates of the car sprite
		///
		/// \return Returns the position coordinates of the car sprite
		///
		/// \see CurrentSprite, setPosition()
		////////////////////////////////////////////////////////////
		sf::Vector2f getPosition();
};

////////////////////////////////////////////////////////////
/// \class PlayerCar
///
/// PlayerCar is a car which the player can control to play the car game,
/// the car can drive forwards, backwards, turn left and right using the bicycle model of steering.
/// The car is effected by frictional force so the car will slow down over time if there is no throttle
/// and will also come to a terminal velocity after a period of time.
///
/// The car has collision algorithms which allow it to collide with tyres and other cars in the game.
///
/// The car keeps track of its own data such as the amount of laps it has performed, its current lap time and its best lap time.
///
/// The different properties of the car are accessible by using the get() and set() functions
/// such as getPosition(), setPosition(), getSize() etc.
///
/// \see Collidable
////////////////////////////////////////////////////////////