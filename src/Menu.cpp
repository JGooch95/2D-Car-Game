#include "../include/Menu.h"

Menu::Menu()
{
	//Sets up the texture loader.
	Textures1.setBaseDirectory("Assets/Sprites/");
	Textures1.LoadTextures(std::vector<std::string>{
		"/MenuFade.png",
		"/MenuTile.png",
		"/Logo.png",
		"/Button.png",
		"/ButtonPushed.png"
	});

	//Sets up the moving background sprites
	for (int i = 0; i < m_aBackgroundSprite.size(); i++)
	{
		m_aBackgroundTextures.at(i) = *Textures1.getTextureIterator(1);
		m_aBackgroundSprite.at(i).setTextureRect(sf::IntRect(0, 0, 800, 600));
		m_aBackgroundSprite.at(0).setPosition(-800, 0);
		m_aBackgroundSprite.at(1).setPosition(0, 0);
		m_aBackgroundSprite.at(i).setTexture(m_aBackgroundTextures.at(i));
		m_aBackgroundTextures.at(i).setRepeated(true);
	}

	//Puts the blue fade on the bottom of the menu
	BottomTexture = *Textures1.getTextureIterator(0);
	BottomSprite.setTextureRect(sf::IntRect(0, 0, 800, 100));
	BottomSprite.setPosition(0, 500);
	BottomTexture.setRepeated(true);
	BottomSprite.setTexture(BottomTexture);

	//Sets up the logo
	LogoTexture = *Textures1.getTextureIterator(2);
	LogoSprite.setPosition(100, 100);
	LogoSprite.setTexture(LogoTexture);
	
	//Sets the menu to be the first menu
	setMenu(0);

	//Sets the  player count to be 1 player default
	m_iPlayerCount = 1;

	//Sets the font for the instructions page
	FontArial.loadFromFile("Assets/Fonts/Arial.ttf");

	//Sets up the instructions text
	Instructions.setColor(sf::Color::White);
	Instructions.setFont(FontArial);
	Instructions.setPosition(200, 250);
	Instructions.setString("Drive around the track with up to four players!\nYour laps will be timed so be quick!and try to\n"
						   "beat your score"
						   "\n"
						   "\n"
						   "Controls:\n"
						   "Player 1:LEFT RIGHT UP AND DOWN\n"
						   "Player 2:WASD\n"
						   "Player 3:TFGH\n"
						   "Player 4:IJKL");

	Instructions.setCharacterSize(20);
	InstructionsBorder.setFillColor(sf::Color(50,50,255,255));
	InstructionsBorder.setSize(sf::Vector2f(440,230));
	InstructionsBorder.setPosition(sf::Vector2f(190, 240));

}

int Menu::Inputs(sf::Event event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		//If the up key is pressed
		if (event.key.code == sf::Keyboard::Up)
		{
			//The button above the current button is set to be active and the previous button is deactivated.
			Button.at(m_iButtonSelected).setTexture(Textures1.getTextureIterator(3));
			m_iButtonSelected--;

			//Stops the button selection being less than 0
			if (m_iButtonSelected < 0)
			{
				m_iButtonSelected = 0;
			}
			
			Button.at(m_iButtonSelected).setTexture(Textures1.getTextureIterator(4));
		}

		//If the down key is pressed
		if (event.key.code == sf::Keyboard::Down)
		{
			//The button below the current button is set to be active and the previous button is deactivated.
			Button.at(m_iButtonSelected).setTexture(Textures1.getTextureIterator(3));
			m_iButtonSelected++;

			//Stops the button selection being more than the max amount of buttons
			if (m_iButtonSelected >= Button.size() - 1)
			{
				m_iButtonSelected = Button.size() - 1;
			}

			Button.at(m_iButtonSelected).setTexture(Textures1.getTextureIterator(4));
		}

		//if the enter key is pressed
		if (event.key.code == sf::Keyboard::Return)
		{
			//If the menu is the first menu
			if (m_iCurrentMenu == 0)
			{
				if (m_iButtonSelected == 0) //If its the last button
				{
					setMenu(1); //Opens the player select menu
				}

				else if (m_iButtonSelected == 1)
				{
					setMenu(2); //Opens the instructions menu
				}

				else if (m_iButtonSelected == 2)
				{
					return(3); //Return to close the game
				}

			}
			//If the menu is the player selection menu
			else if (m_iCurrentMenu == 1)
			{
				if (m_iButtonSelected == Button.size()-1) //If its the last button
				{
					setMenu(0); //Go to the previous menu
				}
				else
				{
					//Sets the player count to the button value.
					m_iPlayerCount = m_iButtonSelected + 1;
					return 1; //Return that the game should start
				}
			}
			//If the menu is the instructions screen
			else if (m_iCurrentMenu == 2)
			{
				if (m_iButtonSelected == 0) //If its the last button
				{
					setMenu(0);//Go to the previous menu
				}
			}
		}
	}

	return 0;

}
int Menu::getNumOfPlayers()
{
	//returns the number of players.
	return m_iPlayerCount;
}

void Menu::AnimateBG()
{
	//For both background pieces
	for (int i = 0; i < m_aBackgroundSprite.size(); i++)
	{
		//Move one pixel across
		m_aBackgroundSprite.at(i).setPosition(m_aBackgroundSprite.at(i).getPosition().x + 1, m_aBackgroundSprite.at(i).getPosition().y);

		//If the image moves off the screen
		if (m_aBackgroundSprite.at(i).getPosition().x >= 800)
		{
			//Put the background off the edge of the other side of the screen.
			m_aBackgroundSprite.at(i).setPosition(-800, m_aBackgroundSprite.at(i).getPosition().y);
		}
	}
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//Draws the blue fade
	target.draw(BottomSprite);

	//Draws the scrolling background
	for (int i = 0; i < m_aBackgroundSprite.size(); i++)
	{
		target.draw(m_aBackgroundSprite.at(i));
	}
	
	//Draws the logo
	target.draw(LogoSprite);
	
	//Draws all of the buttons
	for (int i = 0; i < Button.size(); i++)
	{
		target.draw(Button.at(i));
	}

	//Draws the instructions if the instructions screen is open
	if (m_iCurrentMenu == 2)
	{
		target.draw(InstructionsBorder);
		target.draw(Instructions);
	}
}

void Menu::setMenu(const int &k_iMenu)
{
	//Sets the button to the first button
	m_iButtonSelected = 0;

	//Sets the menu to the number given
	m_iCurrentMenu = k_iMenu;

	//If the menu is the start menu the amount of buttons is set to 3 and the text is changed
	if (k_iMenu == 0)
	{
		Button.resize(3);

		Button.at(0).setString("Play");
		Button.at(1).setString("Instructions");
		Button.at(2).setString("Exit Game");
	}

	//If the menu is the player select menu the amount of buttons is set to 4 and the text is changed
	else if (k_iMenu == 1)
	{
		Button.resize(5);

		Button.at(0).setString("1 Player");
		Button.at(1).setString("2 Player");
		Button.at(2).setString("3 Player");
		Button.at(3).setString("4 Player");
	}

	//If the menu is the instructions menu 1 button is created
	else if (k_iMenu == 2)
	{
		Button.resize(1);
	}

	//Every menus last button is a back button except the start menu.
	if (k_iMenu != 0)
	{
		Button.at(Button.size() - 1).setString("Back");
	}

	//Set up every button
	for (int i = 0; i < Button.size(); i++)
	{
		Button.at(i).setTexture(Textures1.getTextureIterator(3));
		Button.at(i).setSize(200, 50);
		Button.at(i).setPosition(300, 250 + (70 * i));
	}

	//If the menu is the instructions menu move the back button downwards
	if (k_iMenu == 2)
	{
		Button.at(Button.size()-1).setPosition(300, 500);
	}

	//Sets the button thats selected's texture to the pushed down texture.
	Button.at(m_iButtonSelected).setTexture(Textures1.getTextureIterator(4));
}