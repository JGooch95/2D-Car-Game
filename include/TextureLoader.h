#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <iostream>
#include <SFML/Graphics.hpp>

////////////////////////////////////////////////////////////
/// \brief A texture loader to manage how many textures are loaded into memory.
////////////////////////////////////////////////////////////
class TextureLoader
{
	private:
		std::vector<sf::Texture> Textures; //!< Holds the textures in a single data structure
		std::string baseDirectory; //!< Holds the base directory where all of the textures are to be loaded from

	public:
		////////////////////////////////////////////////////////////
		/// \brief Default constructor
		////////////////////////////////////////////////////////////
		TextureLoader();

		////////////////////////////////////////////////////////////
		/// \brief Sets the base directory for the texture loader to check.
		///
		/// \param dir Holds the directory where the files to be loaded are stored
		///
		/// \see baseDirectory
		////////////////////////////////////////////////////////////
		void setBaseDirectory(std::string dir);

		////////////////////////////////////////////////////////////
		/// \brief Loads the textures given from the base directory and stores them in the vector of textures
		///
		/// \param Files Holds all of the file names to be loaded from the base directory
		///
		/// \see baseDirectory
		////////////////////////////////////////////////////////////
		void LoadTextures(std::vector<std::string> Files);

		////////////////////////////////////////////////////////////
		/// \brief Returns a pointer to the location of the texture at the index given.
		///
		/// \param k_iIndex Holds the location in the texture iterator of the texture wanted.
		///
		/// \return Returns a pointer to the location of the texture at the index given.
		///
		/// \see Textures
		////////////////////////////////////////////////////////////
		std::vector<sf::Texture>::iterator getTextureIterator(const int &k_iIndex);
};

////////////////////////////////////////////////////////////
/// \class TextureLoader
///
/// The texture loader handles how textures are loaded so only one of each texture is loaded into memory
/// The textures are loaded from the directory and stored rather than them being stored within each object.
///
////////////////////////////////////////////////////////////