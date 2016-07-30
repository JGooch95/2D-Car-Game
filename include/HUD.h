#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/graphics.hpp>
#include <Array>
#include <iostream>

////////////////////////////////////////////////////////////
/// \brief HUD to display player information while they're playing the game.
////////////////////////////////////////////////////////////
class HUD : public sf::Drawable
{
	private:
		sf::Font FontArial; //!< Holds the font to be used for the HUD's text.
		std::array<sf::Text, 5> TextHolder; //!< Holds every peice of text used for the HUD.

		////////////////////////////////////////////////////////////
		/// \brief Draws all of the drawable entities in the HUD to the screen
		///
		/// \param target Holds where to draw the entities to.
		///					   
		///	\param states 
		///
		/// \see TextHolder
		////////////////////////////////////////////////////////////
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	public:
		////////////////////////////////////////////////////////////
		/// \brief Default constructor
		////////////////////////////////////////////////////////////
		HUD();

		////////////////////////////////////////////////////////////
		/// \brief Updates all of the text for the HUDto display the latest values.
		///
		/// \param k_fVel Holds the Velocity of the car
		///
		/// \param k_iLap Holds the amount of laps the player has done
		///
		/// \param k_fLapTime Holds the Current lap time of the player
		///
		/// \param k_fBestLapTime Holds the best lap time the player has achieved.
		////////////////////////////////////////////////////////////
		void Update(const float &k_fVel, const int &k_iLap, const float &k_fLapTime, const float &k_fBestLapTime);
};

////////////////////////////////////////////////////////////
/// \class HUD
///
/// The HUD is a display which shows the player their crucial information such as their miles per
/// hour, the amount of laps theyve performed, their fastest lap and their position. This is updated
/// every frame to have the latest response.
///
/// \see Menu
////////////////////////////////////////////////////////////