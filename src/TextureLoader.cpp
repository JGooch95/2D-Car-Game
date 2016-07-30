#include "../include/TextureLoader.h"

TextureLoader::TextureLoader()
{
}

void TextureLoader::LoadTextures(std::vector<std::string> Files)
{
	sf::Texture CurrentTexture;

	//Loads the textures into the vector of textures
	for (int i = 0; i < Files.size(); i++)
	{
		if (!CurrentTexture.loadFromFile(baseDirectory + Files.at(i)))
		{
			//If the texture fails output error
			sf::err() << "Texture not loaded";
		}

		Textures.push_back(CurrentTexture);
	}
}

void TextureLoader::setBaseDirectory(std::string dir)
{
	baseDirectory = dir;
}

std::vector<sf::Texture>::iterator TextureLoader::getTextureIterator(const int &k_iIndex)
{
	return  std::vector<sf::Texture>::iterator(Textures.begin() + k_iIndex);
}

