#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Array>
#include <SFML/graphics.hpp>
#include <SFML/graphics.hpp>

namespace util{
	////////////////////////////////////////////////////////////
	/// \brief A vector which holds an x and y displacement and functions to manipulate them.
	////////////////////////////////////////////////////////////
	class Vector
	{
		private:
			std::array<float, 3> m_afItems; //!< Holds the x,y and h values in the vector.

		public:
			////////////////////////////////////////////////////////////
			/// \brief Default constructor
			////////////////////////////////////////////////////////////
			Vector();

			////////////////////////////////////////////////////////////
			/// \brief Constructor
			///
			/// \param fValues holds a single value which the x and y will be set to.
			///
			/// \see x(),y(),h(), m_afItems
			////////////////////////////////////////////////////////////
			Vector(float fValues);

			////////////////////////////////////////////////////////////
			/// \brief Constructor
			///
			/// \param fX Holds the X coordinate which x will be set to.
			///
			/// \param fY Holds the Y coordinate which y will be set to.
			///
			/// \see x(),y(),h(), m_afItems
			////////////////////////////////////////////////////////////
			Vector(float fX, float fY);

			////////////////////////////////////////////////////////////
			/// \brief Constructor
			///
			/// \param fX Holds the X coordinate which x will be set to.
			///
			/// \param fY Holds the Y coordinate which y will be set to.
			///
			/// \param fH Holds the H hymogenous coordinate which h will be set to.
			///
			/// \see x(),y(),h(), m_afItems
			////////////////////////////////////////////////////////////
			Vector(float fX, float fY, int fH);

			////////////////////////////////////////////////////////////
			/// \brief Constructor
			///
			/// \param fValues Holds the coordinates which x and y will be set to.
			///
			/// \see x(),y(),h(), m_afItems
			////////////////////////////////////////////////////////////
			Vector(sf::Vector2f fValues);

			////////////////////////////////////////////////////////////
			/// \brief Sets the x y and h values of the vector.
			///
			/// \param fX Holds the X coordinate which x will be set to.
			///
			/// \param fY Holds the Y coordinate which y will be set to.
			///
			/// \see x(),y(),h(), m_afItems
			////////////////////////////////////////////////////////////
			void set(float fX, float fY);

			////////////////////////////////////////////////////////////
			/// \brief Sets the x y and h values of the vector.
			///
			/// \param fX Holds the X coordinate which x will be set to.
			///
			/// \param fY Holds the Y coordinate which y will be set to.
			///
			/// \param fH Holds the H hymogenous coordinate which h will be set to.
			///
			/// \see x(),y(),h(), m_afItems
			////////////////////////////////////////////////////////////
			void set(float fX, float fY, int fH);

			////////////////////////////////////////////////////////////
			/// \brief Sets the Vector values to the same values of the vector given
			///
			/// \param Vect2 Holds the vector data to be copied
			///
			/// \see x(),y(),h(), m_afItems
			////////////////////////////////////////////////////////////
			void set(util::Vector Vect2);

			////////////////////////////////////////////////////////////
			/// \brief Sets the Vector values to the same values of the sf::vector2f given
			///
			/// \param fValues Holds the x and y data to be copied
			///
			/// \see x(),y(),h(), m_afItems
			////////////////////////////////////////////////////////////
			void set(sf::Vector2f fValues);

			////////////////////////////////////////////////////////////
			/// \brief Returns the angle between this vector and another vector.
			///
			/// \param Vect2 Holds the second vector to check against.
			///
			/// \return Returns the angle between this vector and another vector.
			///
			/// \see x(),y(),h(), m_afItems
			////////////////////////////////////////////////////////////
			float angle(const util::Vector Vect2) const;

			////////////////////////////////////////////////////////////
			/// \brief Returns the dot product of this vector against a second vector
			///
			/// \param Vect2 Holds the second vector to check against.
			///
			/// \return Returns dot product of this vector against another vector.
			///
			/// \see x(),y(),h(), m_afItems
			////////////////////////////////////////////////////////////
			float dotProduct(const util::Vector Vect2) const;

			////////////////////////////////////////////////////////////
			/// \brief Returns the cross product of this vector against a second vector
			///
			/// \param Vect2 Holds the second vector to check against.
			///
			/// \return Returns cross product of this vector against another vector.
			///
			/// \see x(),y(),h(), m_afItems
			////////////////////////////////////////////////////////////
			float crossProduct(const util::Vector Vect2) const;

			////////////////////////////////////////////////////////////
			/// \brief Returns the unit vector of this vector.
			///
			/// \return Returns the unit vector of this vector.
			///
			/// \see x(),y(),h(), m_afItems
			////////////////////////////////////////////////////////////
			util::Vector unitVector() const;

			////////////////////////////////////////////////////////////
			/// \brief Returns the x value of this vector.
			///
			/// \return Returns the x value of this vector.
			///
			/// \see x(), m_afItems
			////////////////////////////////////////////////////////////
			float x() const;

			////////////////////////////////////////////////////////////
			/// \brief Returns the y value of this vector.
			///
			/// \return Returns the y value of this vector.
			///
			/// \see y(), m_afItems
			////////////////////////////////////////////////////////////
			float y() const;

			////////////////////////////////////////////////////////////
			/// \brief Returns the h value of this vector.
			///
			/// \return Returns the h value of this vector.
			///
			/// \see h(), m_afItems
			////////////////////////////////////////////////////////////
			int h() const;

			////////////////////////////////////////////////////////////
			/// \brief Returns the magnitude of this vector.
			///
			/// \return Returns the magnitude of this vector.
			///
			/// \see x(), y(), m_afItems
			////////////////////////////////////////////////////////////
			float Magnitude() const;
			
			////////////////////////////////////////////////////////////
			/// \brief - Overrider which allows vectors to be subtracted from the vector.
			///
			/// \param Vect2 Holds the second vector to be used.
			///
			/// \return Returns this vector subtract the second vector.
			///
			/// \see x(), y(), m_afItems
			////////////////////////////////////////////////////////////
			util::Vector operator - (const util::Vector Vect2);

			////////////////////////////////////////////////////////////
			/// \brief + Overrider which allows vectors to be added to the vector.
			///
			/// \param Vect2 Holds the second vector to be used.
			///
			/// \return Returns this vector added to the second vector.
			///
			/// \see x(), y(), m_afItems
			////////////////////////////////////////////////////////////
			util::Vector operator + (const util::Vector Vect2);

			////////////////////////////////////////////////////////////
			/// \brief * Overrider which allows vectors to be multiplied with the vector.
			///
			/// \param Vect2 Holds the second vector to be used.
			///
			/// \return Returns this vector multiplied with the second vector.
			///
			/// \see x(), y(), m_afItems
			////////////////////////////////////////////////////////////
			util::Vector operator * (const util::Vector Vect2);

			////////////////////////////////////////////////////////////
			/// \brief * Overrider which allows vectors to be multiplied with a scalar.
			///
			/// \param fValue Holds the scalar to be used.
			///
			/// \return Returns this vector multiplied with the second vector.
			///
			/// \see x(), y(), m_afItems
			////////////////////////////////////////////////////////////
			util::Vector operator * (const float fValue);

			////////////////////////////////////////////////////////////
			/// \brief / Overrider which allows vectors to be divided by a scalar.
			///
			/// \param fValue Holds the scalar to be used.
			///
			/// \return Returns this vector divided by the scalar.
			///
			/// \see x(), y(), m_afItems
			////////////////////////////////////////////////////////////
			util::Vector operator / (const float fValue);

			////////////////////////////////////////////////////////////
			/// \brief == Overrider which allows vectors to be checked against eachother to see if they match
			///
			/// \param Vect2 Holds the second vector to check against.
			///
			/// \return Returns whether the vectors match
			///
			/// \see x(), y(), m_afItems
			////////////////////////////////////////////////////////////
			bool operator == (const util::Vector Vect2);
			
			////////////////////////////////////////////////////////////
			/// \brief Scales the vector by the scalar given.
			///
			/// \param fScalar Holds the value for how much the vector will be scaled
			///
			/// \return Returns the scaled vector
			///
			/// \see x(), y(), m_afItems
			////////////////////////////////////////////////////////////
			util::Vector scale(const float fScalar);

			////////////////////////////////////////////////////////////
			/// \brief Rotates the vector by the angle given.
			///
			/// \param fAngle Holds the angle to rotate the vector by.
			///
			/// \return Returns the rotated vector
			///
			/// \see x(), y(), m_afItems
			////////////////////////////////////////////////////////////
			util::Vector rotate(float fAngle);

			////////////////////////////////////////////////////////////
			/// \brief Translates the vector by the coordinates given.
			///
			/// \param fX Holds the X coordinate which x will be translated by.
			///
			/// \param fY Holds the Y coordinate which y will be translated by.
			///
			/// \return Returns the translated vector
			///
			/// \see x(), y(), m_afItems
			////////////////////////////////////////////////////////////
			util::Vector translate(const float fX, const float fY);

			////////////////////////////////////////////////////////////
			/// \brief Returns a vector2f type of the vector.
			///
			/// \return Returns a vector2f type of the vector.
			///
			/// \see x(), y(), m_afItems
			////////////////////////////////////////////////////////////
			sf::Vector2f to2f();
	};
};

////////////////////////////////////////////////////////////
/// \class Vector
///
/// The vector class holds x and y values which can represent many different values such as
/// displacement and velocity. These values can be manipulated using the functions scale,
/// rotate and translate.
///
/// \see Collidable
////////////////////////////////////////////////////////////

