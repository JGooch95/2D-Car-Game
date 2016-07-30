#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <iostream>
#include <array>
#include <SFML/Graphics.hpp>
#include "TextureLoader.h"
#include "MenuButton.h"


////////////////////////////////////////////////////////////
/// \brief A Menu which gives the player choices on what they want to do when they start the game.
////////////////////////////////////////////////////////////
class Menu : public sf::Drawable
{
	private:
		TextureLoader Textures1; //!< A texture loader to manage the amount of textures loaded into the menu.
		int m_iButtonSelected; //!< Holds the index for the current button which is active.
		std::array<sf::Texture, 2> m_aBackgroundTextures; //!< Holds the texture data to be applied to the sprite for the moving background.
		std::array<sf::Sprite, 2> m_aBackgroundSprite; //!< Holds the data to be drawn to the screen for the moving background.
		sf::Texture LogoTexture; //!< Holds the texture data to be applied to the sprite for the game logo.
		sf::Sprite LogoSprite; //!< Holds the data to be drawn to the screen for the game logo.
		sf::Texture BottomTexture; //!< Holds the texture data to be applied to the sprite for the bottom fade effect.
		sf::Sprite BottomSprite; //!< Holds the data to be drawn to the screen for the bottom fade effect.

		std::vector<MenuButton> Button; //!< Holds the data for all of the buttons to be drawn.
		int m_iPlayerCount; //!< Holds the number of players that should be made when the game runs.
		int m_iCurrentMenu; //!< Holds the index of the current menu tab that is open.
		sf::Font FontArial; //!< Holds the font to be used for the Instructions text.
		sf::Text Instructions; //!< Holds the text to be used for the Instructions text.
		sf::RectangleShape InstructionsBorder; //!< A Rectangle which is placed behind the instructions to make them more readable.
		

	public:
		////////////////////////////////////////////////////////////
		/// \brief Default constructor
		////////////////////////////////////////////////////////////
		Menu();

		////////////////////////////////////////////////////////////
		/// \brief Draws all of the drawable entities in menu to the screen
		///
		/// \param target Holds where to draw the entities to.
		///					   
		///	\param states 
		///
		/// \see BackgroundSprite, LogoSprite, BottomSprite, Instructions, InstructionsBorder, Button
		////////////////////////////////////////////////////////////
		void draw(sf::RenderTarget &target, sf::RenderStates states) const;

		////////////////////////////////////////////////////////////
		/// \brief Takes all of the inputs to traverse the menu
		///
		/// \param event Holds the sf::event which is used for the key inputs for the menu
		///
		/// \return returns a number which represents whether to leave the menu and run the game.
		///
		/// \see C_iCurrentMenu, m_iButtonSelected
		////////////////////////////////////////////////////////////
		int Inputs(sf::Event event);

		////////////////////////////////////////////////////////////
		/// \brief Returns the number of players that the game will have
		///
		/// \return Returns the number of players that the game will have
		///
		/// \see m_iPlayerCount
		////////////////////////////////////////////////////////////
		int getNumOfPlayers();

		////////////////////////////////////////////////////////////
		/// \brief Moves the background an extra step to animate the backgorund
		///
		/// \see BackgroundSprite
		////////////////////////////////////////////////////////////
		void AnimateBG();

		////////////////////////////////////////////////////////////
		/// \brief Sets the menu to the menu given to the function and displays new data
		///
		/// \param k_iMenu Holds the index for which menu to change to.
		///
		/// \see C_iCurrentMenu
		////////////////////////////////////////////////////////////
		void setMenu(const int &k_iMenu);
};

////////////////////////////////////////////////////////////
/// \class Menu
///
/// This is the menu class which has all of the main menu processing within it before the game is run.
/// The menu takes care of the players inputs and allows them to decide how many players will be playing
/// the game and it also allows the player to see how to play the game by using the inststructions routine.
///
/// \see MenuButton, Inputs()
////////////////////////////////////////////////////////////