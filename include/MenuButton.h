#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "SFML/graphics.hpp"
#include <array>

////////////////////////////////////////////////////////////
/// \brief A Menu button which is displayed to the player on the menu to give them options on what to do next.
////////////////////////////////////////////////////////////
class MenuButton : public sf::Drawable
{
private:
	////////////////////////////////////////////////////////////
	/// \brief Draws all of the menu button entities to the screen.
	///
	/// \param target Holds where to draw the entities to.
	///					   
	///	\param states 
	///
	/// \see TextHolder, CurrentSprite
	////////////////////////////////////////////////////////////
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Font FontArial; //!< Holds the font to be used for the Button's text.
	sf::Text TextHolder; //!< Holds the text to be drawn on top of the button.

public:
	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	////////////////////////////////////////////////////////////
	MenuButton();

	////////////////////////////////////////////////////////////
	/// \brief Sets the texture of the button to the texture given.
	///
	/// \param Iter Holds the pointer to the texture that is going to be used.
	///
	/// \see CurrentTexture, CurrentSprite
	////////////////////////////////////////////////////////////
	void setTexture(std::vector<sf::Texture>::iterator Iter);

	////////////////////////////////////////////////////////////
	/// \brief Resizes the buttons to the sizes given to the function
	///
	/// \param k_fWidth Holds the Size in the X axis
	///
	/// \param k_fWidth Holds the Size in the Y axis
	///
	/// \see CurrentSprite
	////////////////////////////////////////////////////////////
	void setSize(const float &k_fWidth, const float &k_fHeight);

	////////////////////////////////////////////////////////////
	/// \brief Repostiions the buttons to the coordinates given to the function
	///
	/// \param k_fX Holds the coordinate in the X axis
	///
	/// \param k_fY Holds the coordinate in the Y axis
	///
	/// \see CurrentSprite
	////////////////////////////////////////////////////////////
	void setPosition(const float &k_fX, const float &k_fY);

	////////////////////////////////////////////////////////////
	/// \brief Sets the string for the button to the string given
	///
	/// \param k_strText Holds the text to change the buttons text to.
	///
	/// \see TextHolder
	////////////////////////////////////////////////////////////
	void setString(const std::string &k_strText);

	sf::Sprite CurrentSprite;  //!< Holds the data to be drawn to the screen for the button.
	sf::Texture CurrentTexture; //!< Holds the texture data to be applied to the sprite.
};

////////////////////////////////////////////////////////////
/// \class MenuButton
///
/// This is the menu button class which contains the drawn information for the options that are
/// given to the player in the main menu. These are chosen and perform different tasks depending on
/// which is chosen.
///
/// \see Menu
////////////////////////////////////////////////////////////