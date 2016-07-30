#include "../include/Collidable.h"
#include "../include/Game.h"
#include "../include/PlayerCar.h"

Collidable::Collidable()
{}

sf::Vector2f Collidable::getSize()
{
	return sf::Vector2f(CurrentSprite.getLocalBounds().width, CurrentSprite.getLocalBounds().height);
}


void Collidable::setPosition(const float &k_fX, const float &k_fY)
{
	CurrentSprite.setPosition(k_fX, k_fY);
}
sf::Vector2f Collidable::getPosition()
{
	return CurrentSprite.getPosition();
};

void Collidable::setTexture(std::vector<sf::Texture>::iterator Iter)
{
	CurrentTexture = (*Iter);
	CurrentSprite.setTexture(CurrentTexture);
}