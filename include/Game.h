#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <iostream>
#include <SFML/Graphics.hpp>
#include "PlayerCar.h"
#include "Tyre.h"
#include "HUD.h"
#include "TextureLoader.h"

////////////////////////////////////////////////////////////
/// \mainpage This is the documentation for my car game coursework
/// Use the menu on the left to browse the header files and understand
/// the solution.
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
/// \brief A Game which runs all of the functions to run the gameplay.
////////////////////////////////////////////////////////////
class Game : public sf::Drawable
{
	private:
		std::vector<sf::FloatRect> Checkpoints;//!< Holds the positional and structural data for every checkpoint
		TextureLoader Textures1;//!< A texture loader to manage the amount of textures loaded into the game.

		sf::Sprite StartPointSprite;//!< Holds the data to be drawn to the screen for the StartPoint.
		sf::Texture StartPointTexture;//!< Holds the texture data to be applied to the sprite for the start point.
		sf::Sprite GrassSprite; //!< Holds the data to be drawn to the screen for the Grass.
		sf::Texture GrassTexture;//!< Holds the texture data to be applied to the sprite for the Grass.
		sf::Sprite TrackSprite; //!< Holds the data to be drawn to the screen for the Track.
		sf::Texture TrackTexture;//!< Holds the texture data to be applied to the sprite for the Track.

		std::vector <PlayerCar*> Cars;//!< Holds the pointers to the data of every car in the game.
		std::vector <Collidable*> Collidables;//!< Holds the pointers to the data of every collidable in the game(Cars and Tyres).

	public:
		////////////////////////////////////////////////////////////
		/// \brief Default constructor
		////////////////////////////////////////////////////////////
		Game(); 

		std::vector<HUD> HUD1; //!< Holds every players HUD object to display their data.
		std::vector<sf::View> GameViews; //!< Holds every players GameView to display the game from the players perspective
		std::vector<sf::View> HUDViews; //!< Holds every players HUD view to display their data.
		sf::View MiniMap; //!< Holds the minimaps view data
		sf::View BorderView; //!< Holds the borders view data to be placed over the game views.
		sf::VertexArray Borders; //!< Holds the border lines to be drawn to the border views.

		////////////////////////////////////////////////////////////
		/// \brief Creates all of the players and sets up the views for each player dependant on the amount of players there are.
		///
		/// \param k_iPlayerCount States the number of players to make.
		///
		/// \param WindowSize States the dimensions of the game window
		///
		/// \see Cars, Collidables
		////////////////////////////////////////////////////////////
		void Setup(const int &k_iPlayerCount, const sf::Vector2u &WindowSize); 

		////////////////////////////////////////////////////////////
		/// \brief Draws all of the drawable entities in game to the screen
		///
		/// \param target Holds where to draw the entities to.
		///					   
		///	\param states 
		///
		/// \see StartPointSprite, GrassSprite, TrackSprite, Collidables
		////////////////////////////////////////////////////////////
		void draw(sf::RenderTarget &target, sf::RenderStates states) const; 
		 
		////////////////////////////////////////////////////////////
		/// \brief Performs all of the movement, collisions and main processing of the game.
		///
		/// \param k_fTimeStep Holds the amount of time which has passed since the last frame.
		///
		/// \see Cars, Collidables
		////////////////////////////////////////////////////////////
		void Update(const float &k_fTimeStep); 

		////////////////////////////////////////////////////////////
		/// \brief Takes all of the players inputs when playing the game and mainpulates the car accordingly.
		///
		/// \see Cars
		////////////////////////////////////////////////////////////
		void Inputs(); 

		////////////////////////////////////////////////////////////
		/// \brief returns the player position to main so the views can be repositioned.
		///
		/// \param k_iIndex states which car in the data structure to view.
		///
		/// \return returns the player position of the car at the index given.
		///
		/// \see Cars, Collidables
		////////////////////////////////////////////////////////////
		sf::Vector2f getPlayerPos(const int &k_iIndex); 
		
		////////////////////////////////////////////////////////////
		/// \brief Holds the code for collision between Cars and tyres
		///
		/// \param Collidable1 Holds the data for the car which is colliding with the tyre.
		///
		/// \param Collidable2 Holds the data for the tyre which is being colliding with the car.
		///
		/// \see Cars, Collidables
		////////////////////////////////////////////////////////////
		static void OBBCircle(PlayerCar &Collidable1, Tyre &Collidable2); 

		////////////////////////////////////////////////////////////
		/// \brief Holds the code for collision between Cars.
		///
		/// \param Collidable1 Holds the data for the first car.
		///
		/// \param Collidable2 Holds the data for the second car.
		///
		/// \see Cars, Collidables
		////////////////////////////////////////////////////////////
		static void OBBOBB(PlayerCar &Collidable1, PlayerCar &Collidable2);

		////////////////////////////////////////////////////////////
		/// \brief Deconstructor for game which deletes the pointers to the collidables in game.
		///
		/// \see Collidables
		////////////////////////////////////////////////////////////
		~Game();

};

////////////////////////////////////////////////////////////
/// \class Game
///
/// This is the game class which has all of the gameplay processing within it.
/// The game holds the OBBOBB and OBBCircle collision for collision handling so collisions are checked 
/// in an organised manor. This class holds all of the objects required for the game including
/// cars, tyres and views.
///
/// The game has an inputs,update and draw function for the main parts of the games processing then
/// all the game processing is within it.
///
/// \see Menu
////////////////////////////////////////////////////////////