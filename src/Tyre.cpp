#include "../include/Tyre.h"
#include "../include/Game.h"
Tyre::Tyre()
{
	//Sets the tyre defualt position
	CurrentSprite.setPosition(sf::Vector2f(0, 0));

	//Sets the texture to the first sprite
	CurrentSprite.setTextureRect(sf::IntRect(0, 0, 60, 60));
	m_fRadius = 30.0f;
}

Tyre::Tyre(const float k_fX, const float k_fY)
{
	//Sets the tyre position to the parameters given.
	CurrentSprite.setPosition( sf::Vector2f(k_fX, k_fY));
	
	//Sets the texture to the first sprite
	CurrentSprite.setTextureRect(sf::IntRect(0, 0, 60, 60));
	m_fRadius = 30.0f;
}

float Tyre::getRadius()
{
	return m_fRadius; //Returns the radius
}

void Tyre::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(CurrentSprite); //draws the tyre.
};

void Tyre::setTexture(std::vector<sf::Texture>::iterator Iter)
{
	//Sets the texture for the tyre
	CurrentTexture = (*Iter);
	CurrentSprite.setTexture(CurrentTexture);
}

void Tyre::setPosition(const float &k_fX, const float &k_fY)
{
	//Sets the position to the parameters given
	CurrentSprite.setPosition(sf::Vector2f(k_fX, k_fY));
};

void Tyre::Collision(Tyre& Collidable2)
{
	//TYRE TYRE COLLISION
}
void Tyre::Collision(Collidable &Collidable2)
{
	//Redirects the collision to the appropriate subroutine.
	Collidable2.Collision(*this);
}

void Tyre::Collision(PlayerCar &Collidable2)
{
	//Performs collision between the tyre and a car.
	Game::OBBCircle(Collidable2, *this);
}

sf::Vector2f Tyre::getPosition()
{
	//Returns the cars position.
	return CurrentSprite.getPosition();
};