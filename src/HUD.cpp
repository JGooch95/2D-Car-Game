#include "../include/HUD.h"

HUD::HUD()
{
	//Sets the font
	FontArial.loadFromFile("Assets/Fonts/Arial.ttf");

	//Sets the default text values
	for (int i = 0; i < TextHolder.size(); i++)
	{
		TextHolder.at(i).setColor(sf::Color::Blue);
		TextHolder.at(i).setCharacterSize(10);
		TextHolder.at(i).setFont(FontArial);
	}

	//Sets the mph counter text settings.
	TextHolder.at(0).setPosition(800 * 0.8, 600 * 0.9);
	TextHolder.at(0).setString("0 MPH");
	TextHolder.at(0).setCharacterSize(30);

	//Sets the lap counter text settings.
	TextHolder.at(1).setPosition(800 * 0.7, 600 * 0.32);
	TextHolder.at(1).setString("Lap: ");

	//Sets the lap time text settings.
	TextHolder.at(2).setPosition(800 * 0.75, 600 * 0.32);
	TextHolder.at(2).setString("Lap Time: " + std::to_string(0.0f));

	//Sets the Position text settings.
	TextHolder.at(3).setPosition(800 * 0.05, 600 * 0.83);
	TextHolder.at(3).setString("1st");
	TextHolder.at(3).setCharacterSize(60);

	//Sets the mph Best lap time text settings.
	TextHolder.at(4).setPosition(800 * 0.75, 600 * 0.34);
	TextHolder.at(4).setString("Best Lap Time: " + std::to_string(0.0f));
}

void HUD::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//Draws the hud text to the screen
	for (int i = 0; i < TextHolder.size(); i++)
	{
		target.draw(TextHolder.at(i));
	}
}

void HUD::Update(const float &k_fVel, const int &k_iLap, const float &k_fLapTime, const float &k_fBestLapTime)
{	
	//Updates all of the text values.
	TextHolder.at(0).setString(std::to_string(int(k_fVel) / 10) + " MPH");
	TextHolder.at(1).setString("Lap: " + std::to_string(k_iLap));
	TextHolder.at(2).setString("Lap Time: " + std::to_string(k_fLapTime));
	TextHolder.at(3).setString("1st");
	TextHolder.at(4).setString("Best Lap Time: " + std::to_string(k_fBestLapTime));
}