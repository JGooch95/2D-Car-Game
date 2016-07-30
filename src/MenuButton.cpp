#include "../include/MenuButton.h"

MenuButton::MenuButton()
{
	//Sets the font for the menu button text
	FontArial.loadFromFile("Assets/Fonts/Arial.ttf");

	//Sets up the text for the button
	TextHolder.setColor(sf::Color::Blue);
	TextHolder.setFont(FontArial);
	TextHolder.setPosition(CurrentSprite.getPosition().x + 35, CurrentSprite.getPosition().x + 5);
	TextHolder.setString("DEFAULT");
	TextHolder.setCharacterSize(CurrentSprite.getScale().y * 60);
}

void MenuButton::setSize(const float &k_fWidth, const float &k_fHeight)
{
	//REsizes the button and text to fit in the dimensions given.
	CurrentSprite.setScale(k_fWidth/200, k_fHeight/100);
	TextHolder.setCharacterSize(CurrentSprite.getScale().y * 60);
}

void MenuButton::setPosition(const float &k_fX, const float &k_fY)
{
	//Sets the position of the button to the values given
	CurrentSprite.setPosition(k_fX, k_fY);
	TextHolder.setPosition(CurrentSprite.getPosition().x + 35, CurrentSprite.getPosition().y + 5);
}

void MenuButton::setString(const std::string &k_strText)
{
	//Changes the text on the button
	TextHolder.setFont(FontArial);
	TextHolder.setString(k_strText);
}

void MenuButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//Draws the button then the text over it.
	target.draw(CurrentSprite);
	target.draw(TextHolder);
}

void MenuButton::setTexture(std::vector<sf::Texture>::iterator Iter)
{
	//Sets the button texture.
	CurrentTexture = (*Iter);
	CurrentSprite.setTexture(CurrentTexture);
}