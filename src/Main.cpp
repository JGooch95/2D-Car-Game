#include <iostream>
#include "../include/Game.h"
#include "../include/Vector.h"
#include "../include/HUD.h"
#include "../include/Menu.h"



int main()
{	
	//Creates the window for items to be drawn onto.
	sf::RenderWindow window(sf::VideoMode(800, 600), "2D Car Game");
	int iPlayerCount = 1; //The amount of players for the game
	int iScreenState = 0; //States which screen is currently being displayed.

	//Constructs a menu
	Menu Menu1;

	//Creates an event to check for quit events.
	sf::Event event;

	//Constructs a game. 
	Game Game1;

	//Clock used to handle the amount of loops perfromed a second.
	sf::Clock Timer;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				Game1.~Game();
				window.close();
				return 0;
			}
			if (iScreenState == 0) //If the screen is the menu.
			{
				int i = Menu1.Inputs(event);
				if (i == 1) //If a player option has been entered
				{
					iScreenState = 1;//Set the screen state to the game screen.

					//States the amount of player to set the game up for.
					iPlayerCount = Menu1.getNumOfPlayers();
					
					//Sets up the players and screen layouts for the game.
					Game1.Setup(iPlayerCount, window.getSize());
					//Menu1.~Menu(); //Deconstruct the menu.
				}
				else if (i == 3) //If the exit menu has been chosen
				{
					window.close();
					return 0;
				}
			}
		}

		if (Timer.getElapsedTime().asSeconds() > 1.0 / 60.0) //Limits the amount of frames performed per second.
		{
			if (iScreenState == 0) //Menu screen
			{ 
				//Update
				Menu1.AnimateBG(); //Animates the background

				//draw
				window.clear(sf::Color(22, 165, 212, 0)); //Background color
				window.draw(Menu1); //Draws the contents
			}

			if (iScreenState == 1) //Game screen
			{
				//Update
				Game1.Inputs(); //Takes all of the games inputs
				Game1.Update(Timer.getElapsedTime().asSeconds()); //Updates all of the games data.

				//draw
				window.clear(sf::Color::Black);//Background color

				// For every player
				for (int i = 0; i < iPlayerCount; i++)
				{
					//Draw the Players view
					window.setView(Game1.GameViews.at(i));
					Game1.GameViews.at(i).setCenter(Game1.getPlayerPos(i));
					window.draw(Game1);

					//Draw the players HUD
					window.setView(Game1.HUDViews.at(i));
					window.draw(Game1.HUD1.at(i));
				}

				//Draws the Borders for splitscreen.
				if (iPlayerCount > 1)
				{
					window.setView(Game1.BorderView);
					window.draw(Game1.Borders);
				}

				//Draws the minimap to the map.
				window.setView(Game1.MiniMap);
				window.draw(Game1);
			}

			//Draws everything to the window.
			window.display();

			//Restarts the timer to allow another frame to be run.
			Timer.restart();
		}
	}
}