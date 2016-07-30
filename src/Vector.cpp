#include "../include/Vector.h"

util::Vector::Vector()
{
	//Sets all the values in the vector to 0
	m_afItems.at(0) = 0;
	m_afItems.at(1) = 0;
	m_afItems.at(2) = 0;
}

util::Vector::Vector(float fValues)
{
	//Sets all the values in the vector to the parameter value
	m_afItems.at(0) = fValues;
	m_afItems.at(1) = fValues;
	m_afItems.at(2) = 0;
}

util::Vector::Vector(sf::Vector2f fValues)
{
	//Sets all the values in the vector to the parameter value
	m_afItems.at(0) = fValues.x;
	m_afItems.at(1) = fValues.y;
	m_afItems.at(2) = 0;
}

util::Vector::Vector(float fX, float fY)
{
	//Sets all the values in the vector to the values given
	set(fX,fY);
}

util::Vector::Vector(float fX, float fY, int fH)
{
	//Sets all the values in the vector to the values given
	set(fX,fY,fH);
}

void util::Vector::set(float fX, float fY)
{
	//Sets all the values in the vector to the values given
	m_afItems.at(0) = fX;
	m_afItems.at(1) = fY;
	m_afItems.at(2) = 0;
}

void util::Vector::set(float fX, float fY, int fH)
{
	//Sets all the values in the vector to the values given
	m_afItems.at(0) = fX;
	m_afItems.at(1) = fY;
	m_afItems.at(2) = fH;
}

void util::Vector::set(util::Vector Vect2)
{
	//Sets all the values in the vector to the values given
	m_afItems.at(0) = Vect2.x();
	m_afItems.at(1) = Vect2.y();
	m_afItems.at(2) = Vect2.h();
}

void util::Vector::set(sf::Vector2f fValues)
{
	//Sets all the values in the vector to the parameter value
	m_afItems.at(0) = fValues.x;
	m_afItems.at(1) = fValues.y;
	m_afItems.at(2) = 0;
};

float util::Vector::angle(const util::Vector Vect2) const
{
	//Returns the angle between this vector and another vector.
	return acos(dotProduct(Vect2) / (Magnitude() * Vect2.Magnitude())) *(180/3.1415 );
}

float util::Vector::dotProduct(const util::Vector Vect2) const
{
	//Returns the scalar value of the 2 vectors
	return (x() * Vect2.x()) + (y() * Vect2.y()) +(h() * Vect2.h());
}

float util::Vector::crossProduct(const util::Vector Vect2) const
{
	//Returns the vector perpendicular to the vectors
	return ((x()*Vect2.y()) - (Vect2.x()*y()));
}

util::Vector util::Vector::unitVector() const
{
	//returns the unit vector
	return util::Vector(x() / Magnitude(), y() / Magnitude());
}

float util::Vector::x() const
{
	//returns the vectors x value
	return m_afItems.at(0);
}

float util::Vector::y() const
{
	//returns the vectors y value
	return m_afItems.at(1);
}

int util::Vector::h() const
{
	//returns the vectors hermogenous value
	return m_afItems.at(2);
}

float util::Vector::Magnitude() const
{
	//returns the distance between the 2 vectors ends.
	return sqrtf(pow(x(), 2) + pow(y(), 2));
}


util::Vector util::Vector::operator - (const util::Vector Vect2)
{
	//negates Vector 2 from the vector
	return util::Vector(x() - Vect2.x(), y() - Vect2.y());
}

util::Vector util::Vector::operator + (const util::Vector Vect2)
{
	//Adds Vector 2 to the vector
	return util::Vector(x() + Vect2.x(), y() + Vect2.y());
}

util::Vector util::Vector::operator * (const util::Vector Vect2)
{
	//Multiplies Vector 2 by the vector
	return util::Vector(x() * Vect2.x(), y() * Vect2.y());
}

util::Vector util::Vector::operator * (const float fValue)
{
	//Multiplies Vector 2 by the vector
	return util::Vector(x() * fValue, y() * fValue);
}

util::Vector util::Vector::operator / (const float fValue)
{
	//divides Vector 2 by the value given if the value does not equal 0
	if (fValue != 0)
	{
		return util::Vector(x() / fValue, y() / fValue);
	}
	//Else an error is output
	else
	{
		sf::err() << "ERROR(VECTOR DIVISION): DIVISION BY 0" << "\n";
		return 0;
	}
}

bool util::Vector::operator == (const util::Vector Vect2)
{
	// If both vector values match return true
	if (Vect2.x() == x() && Vect2.y() == y())
	{
		return true;
	}
	//else return false.
	else
	{
		return false;
	}
}

util::Vector util::Vector::scale(const float fScalar)
{
	//Scales the vector by the scalar
	util::Vector vScaled((fScalar * m_afItems.at(0)) + (0 * m_afItems.at(1))    + (0 * m_afItems.at(2)),
						 (0 * m_afItems.at(0))	   + (fScalar*m_afItems.at(1)) + (0 * m_afItems.at(2)),
						 (0 * m_afItems.at(0))	   + (0 * m_afItems.at(1))    + (1 * m_afItems.at(2)));

	//Returns the scaled vector.
	return vScaled;
}

util::Vector util::Vector::rotate(float angle)
{
	//Converts the angle into radians
	angle = angle * (3.1415 / 180);

	//Rotates the vector by the rotation matrix
	util::Vector vRotated((cos(angle) * m_afItems.at(0)) + (-sin(angle) * m_afItems.at(1)) + (0 * m_afItems.at(2)),
						  (sin(angle) * m_afItems.at(0)) + (cos(angle) * m_afItems.at(1))  + (0 * m_afItems.at(2)),
						  (0 * m_afItems.at(0))			+ (0 * m_afItems.at(1))		     + (1 * m_afItems.at(2)));

	//Returns the rotated vector.
	return vRotated;
}

util::Vector util::Vector::translate(const float fX, const float fY)
{
	//translates the vector by the x and y values
	util::Vector vTranslated((1 * m_afItems.at(0)) + (0 * m_afItems.at(1)) + (1* fX ),
						 (0 * m_afItems.at(0)) + (1 * m_afItems.at(1)) + (1 * fY ),
						 (0 * m_afItems.at(0)) + (0 * m_afItems.at(1)) + (1 * m_afItems.at(2)));

	//Returns the translated vector.
	return vTranslated;
}

sf::Vector2f util::Vector::to2f()
{
	//Returns the Vector2f version of the vector.
	return(sf::Vector2f(m_afItems.at(0), m_afItems.at(1)));
};

