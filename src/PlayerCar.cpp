#include "../include/PlayerCar.h"

#include "../include/Game.h"
PlayerCar::PlayerCar()
{
	//Sets the default values.
	m_vAcceleration = util::Vector(0, 0);
	m_fSteeringAngle = 0;
	m_iTurnDirection = 0;
	m_vVelocity = util::Vector(0, 0);
	m_iDriveDirection = 0;
	m_fCarAngle = 0;

	//Sets up the Car Sprite.
	CurrentSprite.setPosition(sf::Vector2f(1000, 250));
	CurrentSprite.setOrigin(CurrentSprite.getLocalBounds().width / 2, CurrentSprite.getLocalBounds().height / 2);

	//Sets up the wheels
	for (int i = 0; i < m_aWheels.size(); i++)
	{
		m_aWheels.at(i).setSize(sf::Vector2f(20, 10));
		m_aWheels.at(i).setFillColor(sf::Color::Black);
		m_aWheels.at(i).setOrigin(m_aWheels.at(i).getSize().x / 2, m_aWheels.at(i).getSize().y / 2);
	}

	//Front wheels
	for (int i = 0; i < 2; i++)
	{
		m_aWheels.at(i).setPosition(CurrentSprite.getPosition().x, CurrentSprite.getPosition().y + (CurrentSprite.getLocalBounds().height / 2));
	}

	//Back wheels
	for (int i = 2; i < 4; i++)
	{
		m_aWheels.at(i).setPosition(40, CurrentSprite.getPosition().y + (CurrentSprite.getLocalBounds().height / 2));
	}

	m_iLapsCompleted = 1;
	m_fBestLapTime = 0.0f;
}

PlayerCar::PlayerCar(const float k_fX, const float k_fY)
{
	//Sets the default values.
	m_vAcceleration = util::Vector(0, 0);
	m_fSteeringAngle = 0;
	m_iTurnDirection = 0;
	m_vVelocity = util::Vector(0, 0);
	m_iDriveDirection = 0;
	m_fCarAngle = 0;

	//Sets the lap data for the car
	m_iLapsCompleted = 1;
	m_fBestLapTime = 0.0f;

	//Sets up the Car Sprite.
	CurrentSprite.setPosition(sf::Vector2f(k_fX, k_fY));
	CurrentSprite.setOrigin(CurrentSprite.getLocalBounds().width / 2, CurrentSprite.getLocalBounds().height / 2);

	//Sets up the wheels
	for (int i = 0; i < m_aWheels.size(); i++)
	{
		m_aWheels.at(i).setSize(sf::Vector2f(20, 10));
		m_aWheels.at(i).setFillColor(sf::Color::Black);
		m_aWheels.at(i).setOrigin(m_aWheels.at(i).getSize().x / 2, m_aWheels.at(i).getSize().y / 2);
	}

	//Repositioning of the wheels
	//Front wheels
	for (int i = 0; i < 2; i++)
	{
		m_aWheels.at(i).setPosition(CurrentSprite.getPosition().x, CurrentSprite.getPosition().y + (CurrentSprite.getLocalBounds().height / 2));
	}
	//Back wheels
	for (int i = 2; i < 4; i++)
	{
		m_aWheels.at(i).setPosition(40, CurrentSprite.getPosition().y + (CurrentSprite.getLocalBounds().height / 2));
	}
}

void PlayerCar::setTurnDirection(const int &k_iValue)
{
	//Sets the Rotating variable to the parameter value.
	m_iTurnDirection = k_iValue;
}

void PlayerCar::setDriveDirection(const int &k_iValue)
{
	//Sets the Rotating variable to the parameter value.
	m_iDriveDirection = k_iValue;
}

void PlayerCar::Move(const float &k_fFrictionCoefficient, const float &k_fTimeStep)
{
	//const values.
	const float k_fPi = 3.14159265359; //Holds the value of PI.
	const float k_fTopSpeed = 1000; //Holds the value of the top velocity the car can reach.
	
	//Variable values.
	util::Vector Wheelf; //Holds data for the front wheel
	util::Vector Wheelr; // Holds data for the rear wheel

	float Displacement; //Holds the distance moved in the timestep
	float WheelBase = CurrentSprite.getLocalBounds().width * 0.8; // Holds the distance between the front and rear wheels

	util::Vector vFriction(m_vVelocity * k_fFrictionCoefficient); //Defines the friction of the car.
	util::Vector CarOrientation(1, 0); //Holds the unit vector of the direction the car is going.
	util::Vector SteerOrientation(1,0); //Holds the unit vector of the direction the front wheel is facing.

	//Rotates the front wheel by the rotation speed and direction.
	TurnWheels();

	//Sets the car orientation and steering orientation as unit vectors
	CarOrientation = CarOrientation.rotate(m_fCarAngle);
	SteerOrientation = SteerOrientation.rotate(m_fCarAngle + m_fSteeringAngle);

	//Acceleration = 5000 * Direction - Friction
	m_vAcceleration.set((CarOrientation * k_fTopSpeed * m_iDriveDirection) - vFriction);

	//Sets the new Velocity (v = u + at)
	m_vVelocity.set(m_vVelocity + (m_vAcceleration * k_fTimeStep));

	//Sets the Displacement (d = v * h)
	Displacement = m_vVelocity.Magnitude() * k_fTimeStep;;

	//If velocity is going to the left reverse displacement.
	if (m_vVelocity.dotProduct(CarOrientation) < 0)
	{
		Displacement = -Displacement;
		m_vVelocity = CarOrientation * -m_vVelocity.Magnitude();
	}
	else
	{
		m_vVelocity = CarOrientation * m_vVelocity.Magnitude();
	}
	
	//Calculate the current position of the front and rear wheels
	Wheelf.set(util::Vector(CurrentSprite.getPosition().x, CurrentSprite.getPosition().y) + CarOrientation * (WheelBase / 2));
	Wheelr.set(util::Vector(CurrentSprite.getPosition().x, CurrentSprite.getPosition().y) - CarOrientation * (WheelBase / 2));

	//Integrate the front and rear wheels movement over the timestep
	Wheelf.set(Wheelf + SteerOrientation * Displacement);
	Wheelr.set(Wheelr + CarOrientation * Displacement);

	//The cars new position is the average of the front and back wheels positions
	CurrentSprite.setPosition(((Wheelf + Wheelr) / 2).to2f());

	//The Current angle is then calculated back into degrees.
	m_fCarAngle = atan2(Wheelf.y() - Wheelr.y(), Wheelf.x() - Wheelr.x()) * (180/k_fPi);
	
	//Rotates the Car and wheel rects by their respecitve angles.
	CurrentSprite.setRotation(m_fCarAngle);
	PositionWheels();	

	//Sets the sprite settings 
	CurrentSprite.setPosition(CurrentSprite.getPosition().x , CurrentSprite.getPosition().y);
	CurrentSprite.setOrigin(CurrentSprite.getLocalBounds().width / 2, CurrentSprite.getLocalBounds().height / 2);
	CurrentSprite.setRotation(m_fCarAngle);
	CurrentSprite.setScale((CurrentSprite.getLocalBounds().width / CurrentTexture.getSize().x), (CurrentSprite.getLocalBounds().height / CurrentTexture.getSize().y) + 0.2);
}

void PlayerCar::PositionWheels()
{
	//Holds the positions for the top left and bottom right wheel after rotation
	util::Vector WheelPositions = util::Vector(((CurrentSprite.getLocalBounds().width / 2)*0.8) - (m_aWheels.at(0).getSize().x / 2), (CurrentSprite.getLocalBounds().height / 2) - 3).rotate(m_fCarAngle);
	//Holds the positions for the bottom left and top right wheel after rotation
	util::Vector WheelPositions2 = util::Vector(((CurrentSprite.getLocalBounds().width / 2)*0.8) - (m_aWheels.at(0).getSize().x / 2), -(CurrentSprite.getLocalBounds().height / 2) + 3).rotate(m_fCarAngle); //Holds the positions for the bottom left and top right wheel after rotation

	//for the front wheels 
	for (int i = 0; i < 2; i++)
	{
		m_aWheels.at(i).setOrigin(m_aWheels.at(i).getSize().x / 2, m_aWheels.at(i).getSize().y / 2);
		m_aWheels.at(i).setRotation(m_fCarAngle + m_fSteeringAngle);
	}

	//Sets the new positions for the front wheels
	m_aWheels.at(0).setPosition(CurrentSprite.getPosition().x + WheelPositions2.x(), CurrentSprite.getPosition().y + WheelPositions2.y());
	m_aWheels.at(1).setPosition(CurrentSprite.getPosition().x + WheelPositions.x(), CurrentSprite.getPosition().y + WheelPositions.y());

	//for the back wheels
	for (int i = 2; i < m_aWheels.size(); i++)
	{
		m_aWheels.at(i).setRotation(m_fCarAngle);
	}
	
	//Sets the new positions for the back Wheels
	m_aWheels.at(2).setPosition(CurrentSprite.getPosition().x - WheelPositions.x(), CurrentSprite.getPosition().y - WheelPositions.y());
	m_aWheels.at(3).setPosition(CurrentSprite.getPosition().x - WheelPositions2.x(), CurrentSprite.getPosition().y - WheelPositions2.y());
}

void PlayerCar::TurnWheels()
{
	const float k_fTopSteeringAngle = 45; //Holds the maximum angle the front wheel can turn
	const float k_fTurningSpeed = 1; //Holds the speed the wheel turns.

	//Alters the steering angle by the angle passed by the parameters;
	m_fSteeringAngle += k_fTurningSpeed * m_iTurnDirection;

	//Stops the wheeel from being turned further than the limit.
	if ( m_fSteeringAngle >   k_fTopSteeringAngle)
	{
		m_fSteeringAngle = k_fTopSteeringAngle;
	}
	if ( m_fSteeringAngle <  - k_fTopSteeringAngle)
	{
		m_fSteeringAngle = -k_fTopSteeringAngle;
	}

	//If the wheel isnt set to rotate the wheel rotates back.
	if (m_iTurnDirection == 0)
	{
		if (m_fSteeringAngle > 0)
		{
			m_fSteeringAngle -= k_fTurningSpeed;
		}
		if (m_fSteeringAngle < 0)
		{
			m_fSteeringAngle += k_fTurningSpeed;
		}
	}
}
float PlayerCar::getRotation()
{
	//Gets the angle the car is pointed towards.
	return m_fCarAngle;
}
void PlayerCar::Collision(Tyre &Collidable2)
{
	//Reroutes the collision depending on the collidable
	Game::OBBCircle(*this, Collidable2);
}

void PlayerCar::Collision(PlayerCar &Collidable2)
{
	//Performs collision between the car and another car.
	Game::OBBOBB(*this, Collidable2);
}

util::Vector PlayerCar::getVelocity()
{
	//returns the cars velocity
	return m_vVelocity;
}

void PlayerCar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//Draws the wheels
	for (int i = 0; i < 4; i++)
	{
		target.draw(m_aWheels.at(i));
	}
	//Draws the rest of the car
	target.draw(CurrentSprite);
	
};

int PlayerCar::getLapsCompleted()
{
	//Returns the amount of laps the car has performed
	return m_iLapsCompleted;
}

float PlayerCar::getLapTime()
{
	//Returns the lap time hte car is currently on.
	return LapTime.getElapsedTime().asSeconds();
}

float PlayerCar::getBestLapTime()
{
	//Returns the best lap time the car has reached so far.
	return m_fBestLapTime;
}

void PlayerCar::LapComplete()
{
	//Gets the latest lap time
	float fCurrentLapTime = LapTime.getElapsedTime().asSeconds();

	//If the lap time is less than the best then its overwritten
	if (fCurrentLapTime < m_fBestLapTime || m_fBestLapTime == 0.0f)
	{
		m_fBestLapTime = fCurrentLapTime;
	}

	//The laps are incremented by one and the lap timer restarts
	m_iLapsCompleted += 1;
	LapTime.restart();
}

void PlayerCar::setCheckpointState(const int &k_iIndex, const bool &k_bState)
{
	//Sets the checkpoint to be active or not active
	m_vbCheckpointsReached.at(k_iIndex) = k_bState;
}

bool PlayerCar::getCheckpointState(const int &k_iIndex)
{
	//returns whether the checkpoint has been activated
	return m_vbCheckpointsReached.at(k_iIndex);
}

void PlayerCar::setCheckpointAmount(const int &k_iValue)
{
	//Sets the amount of checkpoints so the state vector can be resized
	m_vbCheckpointsReached.resize(k_iValue);
}

void PlayerCar::Collision(Collidable &Collidable2)
{
	//Reroutes the collision depending on the collidable type.
	Collidable2.Collision(*this);
}

void PlayerCar::setVelocity(const util::Vector &k_Vect1)
{
	//Sets the velocity to hte values given
	m_vVelocity.set(k_Vect1);
}

sf::Vector2f PlayerCar::getSize()
{
	//Returns the dimensions of the cars sprite. 
	return sf::Vector2f(CurrentSprite.getLocalBounds().width, CurrentSprite.getLocalBounds().height);
}

void PlayerCar::setPosition(const float &k_fX, const float &k_fY)
{
	//Sets the position of the car to the values given
	CurrentSprite.setPosition(k_fX, k_fY);
}

sf::Vector2f PlayerCar::getPosition()
{
	//Returns the position of the car.
	return CurrentSprite.getPosition();
};

void PlayerCar::setTexture(std::vector<sf::Texture>::iterator Iter)
{
	//Sets the texture of the cars sprite.
	CurrentTexture = (*Iter);
	CurrentSprite.setTexture(CurrentTexture);
}