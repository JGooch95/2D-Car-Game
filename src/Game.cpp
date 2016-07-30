#include "../include/Game.h"
#include <memory>
Game::Game()
{
	//Sets up the texture loader and loads the textures.
	Textures1.setBaseDirectory("Assets/Sprites/");
	Textures1.LoadTextures(std::vector<std::string>{
	"/Car.png",		   //0
	"/Car2.png",	   //1
	"/Car3.png",	   //2
	"/Car4.png",	   //3
	"/Tyre.png",	   //4
	"/Grass.png",	   //5
	"/Track.png",	   //6
	"/StartTile.png"});//7

	//Sets up the grass background.
	GrassTexture = *Textures1.getTextureIterator(5);
	GrassSprite.setTextureRect(sf::IntRect(0, 0, 4000, 4000));
	GrassSprite.setPosition(-1000.0f, -1000.0f);
	GrassSprite.setTexture(GrassTexture);
	GrassTexture.setRepeated(true);

	//Sets up the track background.
	TrackTexture = *Textures1.getTextureIterator(6);
	TrackSprite.setTexture(TrackTexture);
	TrackSprite.setPosition(0.0f, 0.0f);

	//Temporary objects and variables used for track generation.
	Tyre* Tyre1;
	sf::FloatRect Checkpoint1;
	int angle = 0;
	util::Vector pos(0.0f,0.0f);

	//Generates a track by spinning in a circle and placing items at different angles around the circle.
	while (angle < 360)
	{
		//outer layer of tyres
		if (angle % 3 == 0.0f)
		{
			pos = util::Vector(0.0f, -1000.0f).rotate(angle); //Finds the location to place the tyre
			Collidables.push_back(new Tyre()); //Creates a new tyre and pushes the pointer to the vector of collidables.

			Tyre1 = (Tyre*)Collidables.back(); //Sets the tyre1 value so the tyre can be easily changed.

			//Moves the tyre to the centre of the track and displaces it by the position.
			Tyre1->setPosition(TrackSprite.getPosition().x + (TrackSprite.getLocalBounds().width / 2) + pos.x() - Tyre1->getRadius(),
				TrackSprite.getPosition().y + (TrackSprite.getLocalBounds().height / 2) + pos.y() - Tyre1->getRadius());

			Tyre1->setTexture(Textures1.getTextureIterator(4)); //Sets the texture to the tyre texture
		}

		//Inner layer of tyres
		if (angle % 5 == 0.0f)
		{
			pos = util::Vector(0.0f, -600.0f).rotate(angle); //Finds the location to place the tyre
			Collidables.push_back(new Tyre()); //Creates a new tyre and pushes the pointer to the vector of collidables.

			Tyre1 = (Tyre*)Collidables.back(); //Sets the tyre1 value so the tyre can be easily changed.

			//Moves the tyre to the centre of the track and displaces it by the position.
			Tyre1->setPosition(TrackSprite.getPosition().x + (TrackSprite.getLocalBounds().width / 2) + pos.x() - Tyre1->getRadius(),
				TrackSprite.getPosition().y + (TrackSprite.getLocalBounds().height / 2) + pos.y() - Tyre1->getRadius());

			Tyre1->setTexture(Textures1.getTextureIterator(4)); //Sets the texture to the tyre texture
		}

		//Checkpoints
		if (angle % 180 == 0.0f)
		{
			pos = util::Vector(0.0f, -800.0f).rotate(angle); //Finds the location to place the checkpoint

			//Sets the checkpoint dimensions
			Checkpoint1.width = 100;
			Checkpoint1.height = 400;

			//Moves the checkpoint to the centre of the track and displaces it by the position.
			Checkpoint1.left = TrackSprite.getPosition().x + (TrackSprite.getLocalBounds().width / 2) + pos.x() - (Checkpoint1.width / 2);
			Checkpoint1.top = TrackSprite.getPosition().y + (TrackSprite.getLocalBounds().height / 2) + pos.y() - (Checkpoint1.height / 2);

			Checkpoints.push_back(Checkpoint1); //Pushes the checkpoint onto the checkpoints vector
		}

		angle += 1; //Increments the angle.
	};

	//Sets the start point texture and places it onto the first checkpoint.
	StartPointTexture = *Textures1.getTextureIterator(7);
	StartPointTexture.setRepeated(true);
	StartPointSprite.setTexture(StartPointTexture);
	StartPointSprite.setTextureRect(sf::IntRect(Checkpoints.at(0).left, Checkpoints.at(0).top, Checkpoints.at(0).width, Checkpoints.at(0).height));
	StartPointSprite.setPosition(Checkpoints.at(0).left, Checkpoints.at(0).top);
	Points.setPrimitiveType(sf::Lines);
	Points.resize(3);
}

void Game::Setup(const int &k_iPlayerCount, const sf::Vector2u &WindowSize)
{
	//Adds all the cars to the vector of cars
	//For every car setup the car.
	for (int i = 0; i < k_iPlayerCount; i++)
	{
		Cars.push_back(new PlayerCar(1000, 100 + (60*i))); //Creates a new car and pushes the pointer onto the car vector
		Cars.back()->setTexture(Textures1.getTextureIterator(i)); //Sets the cars texture to the car texture
		Cars.back()->setCheckpointAmount(Checkpoints.size()); //Sets the amount of checkpoints in the map for the car so the vector can be resized.

		//For every checkpoint set the state vector value to false.
		for (int j = 0; j < Checkpoints.size(); j++)
		{
			Cars.at(i)->setCheckpointState(j, false);
		}

		Collidables.push_back(Cars.at(i)); //Push back the car pointer to the collidables vector.
	}

	//Sets up the HUD and Laptime for every player.
	HUD1.resize(Cars.size());

	// Resizes the View vectors so each player gets their own.
	GameViews.resize(k_iPlayerCount);
	HUDViews.resize(k_iPlayerCount);

	//Borders are set up for the multiplayer.
	Borders.resize(4);
	Borders.setPrimitiveType(sf::Lines);

	if (k_iPlayerCount > 1) //If there is more than one player
	{
		//Set the borders to be black
		for (int i = 0; i < Borders.getVertexCount(); i++)
		{
			Borders[i].color = sf::Color::Black;
		}

		//Adds the vertical line between screens
		Borders[0].position = sf::Vector2f(WindowSize.x / 2, 0);
		Borders[1].position = sf::Vector2f(WindowSize.x / 2, WindowSize.y);

		//If there are more than two players add the horizontal line
		if (k_iPlayerCount > 2)
		{
			Borders[2].position = sf::Vector2f(0, WindowSize.y / 2);
			Borders[3].position = sf::Vector2f(WindowSize.x, WindowSize.y / 2);
		}
	}

	//Sets up the view to place the borders.
	BorderView.setCenter(sf::Vector2f(WindowSize.x / 2, WindowSize.y / 2));
	BorderView.setSize(sf::Vector2f(WindowSize.x, WindowSize.y));
	BorderView.setViewport(sf::FloatRect(0, 0, 1, 1));

	//Sets up the minimap.
	MiniMap.setSize(sf::Vector2f(WindowSize.x, WindowSize.y));
	MiniMap.zoom(4);
	MiniMap.setCenter(1000, 1000);


	//Sets up the view settings that are the same for every player
	for (int i = 0; i < k_iPlayerCount; i++)
	{
		//Sets the view to be centered in the center of the game
		GameViews.at(i).setCenter(WindowSize.x / 2, WindowSize.y / 2);

		//Sets the HUD view to be centered at the center of the game and sets the size to fit the window.
		HUDViews.at(i).setSize(sf::Vector2f(WindowSize.x, WindowSize.y));
		HUDViews.at(i).setCenter(WindowSize.x / 2, WindowSize.y / 2);

		//2 Player
		if (k_iPlayerCount == 2)
		{
			GameViews.at(i).setSize(sf::Vector2f(WindowSize.x / 2, WindowSize.y)); //Both players get a half screen window
		}
		//More than 2 players
		if (k_iPlayerCount > 2)
		{
			GameViews.at(i).setSize(sf::Vector2f(WindowSize.x / 2, WindowSize.y / 2)); //Four players get a quarter screen window size
		}
	}

	//Player Specific view settings(1 Player)
	if (k_iPlayerCount == 1)
	{
		//The players window is set to take the whole screen
		GameViews.at(0).setSize(sf::Vector2f(WindowSize.x, WindowSize.y));
		GameViews.at(0).setViewport(sf::FloatRect(0, 0, 1, 1));

		//Positions the minimap in the top left
		MiniMap.setViewport(sf::FloatRect(0.70f, 0.05f, 0.25f, 0.25f));

		//HUD is set to take the whole screen.
		HUDViews.at(0).setViewport(sf::FloatRect(0, 0, 1, 1));
	}

	//Player Specific view settings(2 Player)
	else if (k_iPlayerCount == 2)
	{
		//The players window is set to take half of the screen
		GameViews.at(0).setViewport(sf::FloatRect(0, 0, 0.5, 1));
		GameViews.at(1).setViewport(sf::FloatRect(0.5, 0, 0.5, 1));

		//Sets the minimapp to be the top center of the window.
		MiniMap.setViewport(sf::FloatRect(0.25f + (0.25f / 2), 0.05f, 0.25f, 0.25f));

		//Resizes the hud to take half of the screen
		HUDViews.at(0).setViewport(sf::FloatRect(0, 0, 0.5, 1));
		HUDViews.at(1).setViewport(sf::FloatRect(0.5, 0, 0.5, 1));
	}

	//Sets up the view settings that are the same for every player for 4 player
	else if (k_iPlayerCount > 2)
	{
		//Sets the game view to be quarter of the screen
		GameViews.at(0).setViewport(sf::FloatRect(0, 0, 0.5, 0.5));

		//Sets the hud to take quarter of the screen
		HUDViews.at(0).setViewport(sf::FloatRect(0, 0, 0.5, 0.5));
		HUDViews.at(1).setViewport(sf::FloatRect(0.5, 0, 0.5, 0.5));

		//Player Specific view settings(3 Player)
		if (k_iPlayerCount == 3)
		{
			//Repositions the 2nd and 3rd views to go to the corners of the window.
			GameViews.at(1).setViewport(sf::FloatRect(0, 0.5, 0.5, 0.5));
			GameViews.at(2).setViewport(sf::FloatRect(0.5, 0.5, 0.5, 0.5));

			//The HUD is set to be a quarter of the window and is repositioned over the players.
			HUDViews.at(1).setViewport(sf::FloatRect(0, 0.5, 0.5, 0.5));
			HUDViews.at(2).setViewport(sf::FloatRect(0.5, 0.5, 0.5, 0.5));

			//The minimap is set to be the top right corner of the window
			MiniMap.setViewport(sf::FloatRect(0.5f, 0, 0.5f, 0.5f));
		}
		//Player Specific view settings(4 Player)
		if (k_iPlayerCount == 4)
		{
			//Repositions the 2nd and 3rd and 4th views to go to the corners of the window.
			GameViews.at(1).setViewport(sf::FloatRect(0.5, 0, 0.5, 0.5));
			GameViews.at(2).setViewport(sf::FloatRect(0, 0.5, 0.5, 0.5));
			GameViews.at(3).setViewport(sf::FloatRect(0.5, 0.5, 0.5, 0.5));

			//The HUD is set to be a quarter of the window and is repositioned over the players.
			HUDViews.at(1).setViewport(sf::FloatRect(0.5, 0, 0.5, 0.5));
			HUDViews.at(2).setViewport(sf::FloatRect(0, 0.5, 0.5, 0.5));
			HUDViews.at(3).setViewport(sf::FloatRect(0.5, 0.5, 0.5, 0.5));

			//The minimap is set to be the center of the window
			MiniMap.setViewport(sf::FloatRect(0.25f + (0.25f / 2), 0.5f - (0.25f / 2), 0.25f, 0.25f));
		}
	}
}

void Game::Inputs()
{
	//Player 1 Controls
	//Moves the car forwards
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		Cars.at(0)->setDriveDirection(1);
	}
	//Moves the car backwards
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		Cars.at(0)->setDriveDirection(-1);
	}
	//Stops accelerating the Car
	else
	{
		Cars.at(0)->setDriveDirection(0);
	}

	//Turns the car left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		Cars.at(0)->setTurnDirection(-1);
	}
	//Turns the car right
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		Cars.at(0)->setTurnDirection(1);
	}
	//Stops turning the car
	else
	{
		Cars.at(0)->setTurnDirection(0);
	}

	//Player 2 Controls
	if (Cars.size() > 1)
	{
		//-----------------------------------------------------------------------
		//Moves the car forwards
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		{
			Cars.at(1)->setDriveDirection(1);
		}
		//Moves the car backwards
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		{
			Cars.at(1)->setDriveDirection(-1);
		}
		//Stops accelerating the Car
		else
		{
			Cars.at(1)->setDriveDirection(0);
		}

		//Turns the car left
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			Cars.at(1)->setTurnDirection(-1);
		}
		//Turns the car right
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			Cars.at(1)->setTurnDirection(1);
		}
		//Stops turning the car
		else
		{
			Cars.at(1)->setTurnDirection(0);
		}
	}

	//Player 3 Controls
	if (Cars.size() > 2)
	{
		//-----------------------------------------------------------------------
		//Moves the car forwards
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::T))
		{
			Cars.at(2)->setDriveDirection(1);
		}
		//Moves the car backwards
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::G))
		{
			Cars.at(2)->setDriveDirection(-1);
		}
		//Stops accelerating the Car
		else
		{
			Cars.at(2)->setDriveDirection(0);
		}

		//Turns the car left
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F))
		{
			Cars.at(2)->setTurnDirection(-1);
		}
		//Turns the car right
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H))
		{
			Cars.at(2)->setTurnDirection(1);
		}
		//Stops turning the car
		else
		{
			Cars.at(2)->setTurnDirection(0);
		}
	}

	//Player 4 Controls
	if (Cars.size() > 3)
	{
		//-----------------------------------------------------------------------
		//Moves the car forwards
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::I))
		{
			Cars.at(3)->setDriveDirection(1);
		}
		//Moves the car backwards
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K))
		{
			Cars.at(3)->setDriveDirection(-1);
		}
		//Stops accelerating the Car
		else
		{
			Cars.at(3)->setDriveDirection(0);
		}

		//Turns the car left
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J))
		{
			Cars.at(3)->setTurnDirection(-1);
		}
		//Turns the car right
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L))
		{
			Cars.at(3)->setTurnDirection(1);
		}
		//Stops turning the car
		else
		{
			Cars.at(3)->setTurnDirection(0);
		}
	}
}

void Game::Update(const float &k_fTimeStep)
{
	Points.clear();
	//Moves the car. 
	for (int i = 0; i < Cars.size(); i++)
	{
		Cars.at(i)->Move(0.8, k_fTimeStep);
	}

	//Checks collision of every collidable
	for (int i = 0; i < Collidables.size(); i++)
	{
		//With every collidable
		for (int j = 0; j < Collidables.size(); j++)
		{
			//If the collidable is not itself
			if (!(j == i))
			{
				//If their bounding boxes overlap
				if (Collidables.at(j)->CurrentSprite.getGlobalBounds().intersects(Collidables.at(i)->CurrentSprite.getGlobalBounds()));
				{
					//The collision is checked further
					Collidables.at(j)->Collision(*Collidables.at(i));
				}
			}
		}
	}

	//For every checkpoint
	for (int i = 0; i < Checkpoints.size(); i++)
	{
		//For every car
		for (int j = 0; j < Cars.size(); j++)
		{
			//if the checkpoint before the current one has been reached check the collision.
			if (i == 0 || Cars.at(j)->getCheckpointState(i - 1) == true)
			{
				if (Cars.at(j)->CurrentSprite.getGlobalBounds().intersects(Checkpoints.at(i)))
				{
					Cars.at(j)->setCheckpointState(i, true); //Sets the checkpoint to be true
				}
			}

			//if the checkpoint before the last has been reached and the car has reached the beginning again reset the checkpoints
			if (Cars.at(j)->getCheckpointState(Checkpoints.size() - 1) == true && Cars.at(j)->CurrentSprite.getGlobalBounds().intersects(Checkpoints.at(0)))
			{
				//Reset every checkpoint
				for (int k = 0; k < Checkpoints.size(); k++)
				{
					Cars.at(j)->setCheckpointState(k, false);
				}

				//Completes the lap.
				Cars.at(j)->LapComplete();
			}
		}
	}

	for (int i = 0; i < Cars.size(); i++)
	{
		//Updates the HUD to show the data
		HUD1.at(i).Update(Cars.at(i)->getVelocity().Magnitude(), Cars.at(i)->getLapsCompleted(), Cars.at(i)->getLapTime(), Cars.at(i)->getBestLapTime());
	}
}

sf::Vector2f Game::getPlayerPos(const int &k_iIndex)
{
	// if the index is in scope Gets the player position
	if (k_iIndex < Cars.size() && k_iIndex >= 0)
	{
		return(Cars.at(k_iIndex)->getPosition());
	}
	//else return the last players position
	else
	{
		return(Cars.at(Cars.size() - 1)->getPosition());
	}
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//Draws the track details
	target.draw(GrassSprite);
	target.draw(TrackSprite);
	target.draw(StartPointSprite);

	//draws the tyres
	for (int i = 0; i < Collidables.size(); i++)
	{
		target.draw(*Collidables.at(i));
	}
	target.draw(Points);
}

void Game::OBBCircle(PlayerCar &Collidable1, Tyre &Collidable2)
{
	util::Vector Distance(Collidable2.getPosition() - Collidable1.getPosition() + sf::Vector2f(Collidable2.getRadius(), Collidable2.getRadius()));//Holds the distance between the centre of the car and the centre of the tyre
	util::Vector clamp;			 //Holds the coordinate of the closest point to the tyre on the car.
	util::Vector Difference;	 //Holds the difference between the edge and the centre of the tyre.
	float Dist;					 //Holds the Distance between the car edge and the tyre edge.

	//Sets the distance and rotates it by however many degrees the car has been turned.
	Distance = Distance.rotate(-Collidable1.getRotation());

	//If the distance in the x component is more than 0 (Tyre on the right side of the car).
	if (Distance.x() >= 0)
	{
		clamp.set(fmin(Distance.x(), Collidable1.getSize().x / 2), clamp.y());
	}
	//If the distance in the x component is less than 0 (Tyre on the left side of the car).
	else if (Distance.x() < 0)
	{
		clamp.set(fmax(Distance.x(), -(Collidable1.getSize().x / 2)), clamp.y());
	}

	//If the distance in the y component is more than 0 (Tyre on the bottom side of the car).
	if (Distance.y() >= 0)
	{
		clamp.set(clamp.x(), fmin(Distance.y(), Collidable1.getSize().y / 2));
	}
	//If the distance in the y component is less than 0 (Tyre on the top side of the car).
	else if (Distance.y() < 0)
	{
		clamp.set(clamp.x(), fmax(Distance.y(), -(Collidable1.getSize().y / 2)));
	}

	//The difference between the edge and the centre of the tyre.
	Difference = Distance - clamp;

	//The Distance between the edge of the tyre and the closest edge of the car.
	Dist = Difference.Magnitude() - Collidable2.getRadius();

	//If the car is colliding with the tyre then bounce off.
	if (Dist <= 0)
	{
		//Rotates the clamp back to the cars angle and uses it to find the direction
		clamp = clamp.rotate(Collidable1.getRotation());
		util::Vector CollisionNormal = clamp.unitVector();

		//Rotates the distance to move out by and then moves the car out by the vector.
		util::Vector PositionCorrection = CollisionNormal * (Dist-0.25);
		Collidable1.setPosition(Collidable1.getPosition().x + PositionCorrection.x(), Collidable1.getPosition().y + PositionCorrection.y());

		//The cars wheels are then repositioned.
		Collidable1.PositionWheels();

		//Sets the velocity using the restitution force.
		Collidable1.setVelocity(Collidable1.getVelocity() + (CollisionNormal * -(1 + 0.3) * Collidable1.getVelocity().dotProduct(CollisionNormal)));
	}
};

void Game::OBBOBB(PlayerCar &Collidable1, PlayerCar &Collidable2)
{

	sf::FloatRect Car1_BB = Collidable1.CurrentSprite.getLocalBounds();
	util::Vector aBC = util::Vector(Car1_BB.width, 0).rotate(Collidable1.getRotation());
	util::Vector aBC1 = util::Vector(0, Car1_BB.height).rotate(Collidable1.getRotation());
	std::vector<util::Vector> Box1Coords;
	Box1Coords.push_back(util::Vector(sf::Vector2f(Collidable1.getPosition().x - (aBC.x() / 2) - (aBC1.x() / 2), Collidable1.getPosition().y - (aBC.y() / 2) - (aBC1.y() / 2)))); //Top left
	Box1Coords.push_back(util::Vector(sf::Vector2f(Collidable1.getPosition().x + (aBC.x() / 2) - (aBC1.x() / 2), Collidable1.getPosition().y + (aBC.y() / 2) - (aBC1.y() / 2)))); // Top right
	Box1Coords.push_back(util::Vector(sf::Vector2f(Collidable1.getPosition().x + (aBC.x() / 2) + (aBC1.x() / 2), Collidable1.getPosition().y + (aBC.y() / 2) + (aBC1.y() / 2)))); //Bottom right
	Box1Coords.push_back(util::Vector(sf::Vector2f(Collidable1.getPosition().x + (aBC1.x() / 2) - (aBC.x() / 2), Collidable1.getPosition().y + (aBC1.y() / 2) - (aBC.y() / 2)))); // Bottom left

	sf::FloatRect Car2_BB = Collidable2.CurrentSprite.getLocalBounds();
	aBC = util::Vector(Car2_BB.width, 0).rotate(Collidable2.getRotation());
	aBC1 = util::Vector(0, Car2_BB.height).rotate(Collidable2.getRotation());
	std::vector<util::Vector> Box2Coords;
	Box2Coords.push_back(util::Vector(sf::Vector2f(Collidable2.getPosition().x - (aBC.x() / 2) - (aBC1.x() / 2), Collidable2.getPosition().y - (aBC.y() / 2) - (aBC1.y() / 2)))); //Top left
	Box2Coords.push_back(util::Vector(sf::Vector2f(Collidable2.getPosition().x + (aBC.x() / 2) - (aBC1.x() / 2), Collidable2.getPosition().y + (aBC.y() / 2) - (aBC1.y() / 2)))); // Top right
	Box2Coords.push_back(util::Vector(sf::Vector2f(Collidable2.getPosition().x + (aBC.x() / 2) + (aBC1.x() / 2), Collidable2.getPosition().y + (aBC.y() / 2) + (aBC1.y() / 2)))); //Bottom right
	Box2Coords.push_back(util::Vector(sf::Vector2f(Collidable2.getPosition().x + (aBC1.x() / 2) - (aBC.x() / 2), Collidable2.getPosition().y + (aBC1.y() / 2) - (aBC.y() / 2)))); // Bottom left

	util::Vector Axis1(Box1Coords.at(1) - Box1Coords.at(0)); // Box1 UR - Box1 UL
	util::Vector Axis2(Box1Coords.at(1) - Box1Coords.at(2)); // Box1 UR - Box1 LR
	util::Vector Axis3(Box2Coords.at(0) - Box2Coords.at(3)); // Box2 UL - Box2 LL
	util::Vector Axis4(Box2Coords.at(0) - Box2Coords.at(1)); // Box2 UL - Box2 UR

	util::Vector BoxProjection;
	std::vector<float> Box1ScalarsA1;
	for (int i = 0; i < 4; i++)
	{
		BoxProjection = (Axis1 * ((Box1Coords.at(i).dotProduct(Axis1)) / (Axis1.Magnitude() * Axis1.Magnitude())));
		Box1ScalarsA1.push_back(BoxProjection.dotProduct(Axis1));
	}
	std::vector<float> Box1ScalarsA2;
	for (int i = 0; i < 4; i++)
	{
		BoxProjection = (Axis2 *((Box1Coords.at(i).dotProduct(Axis2)) / (Axis2.Magnitude() * Axis2.Magnitude())));
		Box1ScalarsA2.push_back(BoxProjection.dotProduct(Axis2));
	}
	std::vector<float> Box1ScalarsA3;
	for (int i = 0; i < 4; i++)
	{
		BoxProjection = (Axis3 *((Box1Coords.at(i).dotProduct(Axis3)) / (Axis3.Magnitude() * Axis3.Magnitude())));
		Box1ScalarsA3.push_back(BoxProjection.dotProduct(Axis3));
	}
	std::vector<float> Box1ScalarsA4;
	for (int i = 0; i < 4; i++)
	{
		BoxProjection = (Axis4 *((Box1Coords.at(i).dotProduct(Axis4)) / (Axis4.Magnitude() * Axis4.Magnitude())));
		Box1ScalarsA4.push_back(BoxProjection.dotProduct(Axis4));
	}
	

	std::vector<float> Box2ScalarsA1;
	for (int i = 0; i < 4; i++)
	{
		BoxProjection = (Axis1 *((Box2Coords.at(i).dotProduct(Axis1)) / (Axis1.Magnitude() * Axis1.Magnitude())));
		Box2ScalarsA1.push_back(BoxProjection.dotProduct(Axis1));
	}
	std::vector<float> Box2ScalarsA2;
	for (int i = 0; i < 4; i++)
	{
		BoxProjection = (Axis2 *((Box2Coords.at(i).dotProduct(Axis2)) / (Axis2.Magnitude() * Axis2.Magnitude())));
		Box2ScalarsA2.push_back(BoxProjection.dotProduct(Axis2));
	}
	std::vector<float> Box2ScalarsA3;
	for (int i = 0; i < 4; i++)
	{
		BoxProjection = (Axis3 *((Box2Coords.at(i).dotProduct(Axis3)) / (Axis3.Magnitude() * Axis3.Magnitude())));
		Box2ScalarsA3.push_back(BoxProjection.dotProduct(Axis3));
	}
	std::vector<float> Box2ScalarsA4;
	for (int i = 0; i < 4; i++)
	{
		BoxProjection = (Axis4 *((Box2Coords.at(i).dotProduct(Axis4)) / (Axis4.Magnitude() * Axis4.Magnitude())));
		Box2ScalarsA4.push_back(BoxProjection.dotProduct(Axis4));
	}

	std::vector<std::vector<float>> Box1Scalars;
	Box1Scalars.push_back(Box1ScalarsA1);
	Box1Scalars.push_back(Box1ScalarsA2);
	Box1Scalars.push_back(Box1ScalarsA3);
	Box1Scalars.push_back(Box1ScalarsA4);

	std::vector<std::vector<float>> Box2Scalars;
	Box2Scalars.push_back(Box2ScalarsA1);
	Box2Scalars.push_back(Box2ScalarsA2);
	Box2Scalars.push_back(Box2ScalarsA3);
	Box2Scalars.push_back(Box2ScalarsA4);

	int Counter = 0;
	//For every axis
	for (int i = 0; i < Box1Scalars.size(); i++)
	{
		float minBox1 = 1000000; //Holds the minimum value for the first box
		float maxBox1 = -1000000; //Holds the maximum value for the first box
		float minBox2 = 1000000; //Holds the minimum value for the second box
		float maxBox2 = -1000000; //Holds the maximum value for the second box

		//For each corner of the first box
		for (int j = 0; j < Box1Scalars.at(i).size(); j++)
		{
			minBox1 = fmin(minBox1, Box1Scalars.at(i).at(j)); //Get the minimum coordinate on the axis
			maxBox1 = fmax(maxBox1, Box1Scalars.at(i).at(j)); //Get the maximum coordinate on the axis
		}
		//For each corner of the second box
		for (int j = 0; j < Box2Scalars.at(i).size(); j++)
		{
			minBox2 = fmin(minBox2, Box2Scalars.at(i).at(j)); //Get the minimum coordinate on the axis
			maxBox2 = fmax(maxBox2, Box2Scalars.at(i).at(j)); //Get the maximum coordinate on the axis
		}
		//If the coordinates overlap 
		if (minBox2 <= maxBox1 && maxBox2 >= minBox1)
		{
			Counter++; //Increment the counter
		}
	}
	//If there are collisions on all of the axis
	if (Counter == 4)
	{
		//Collide
		if (Collidable1.getVelocity().x() != 0 && Collidable1.getVelocity().y() != 0)
		{
			util::Vector CollisionNormal(Collidable1.getPosition() - Collidable2.getPosition());
			CollisionNormal = CollisionNormal.unitVector();
			Collidable1.setPosition(Collidable1.getPosition().x + CollisionNormal.x(), Collidable1.getPosition().y + CollisionNormal.y());
			Collidable1.setVelocity(Collidable1.getVelocity() + (CollisionNormal * -(1 + 0.3) * Collidable1.getVelocity().dotProduct(CollisionNormal)));
		}
	}

};


Game::~Game()
{
	for (int i = 0; i < Collidables.size(); i++)
	{
		Collidables.at(i) = NULL;
	}
}