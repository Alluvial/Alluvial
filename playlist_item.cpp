#include "playlist_item.h"

playlist_item::playlist_item()
{
    this->hash = "";
    this->songName = "";
    this->songLength = 0;
}

playlist_item::playlist_item(QString hash, QString songName, int length)
{
    this->hash = hash;
    this->songName = songName;
    this->songLength = length;
}

playlist_item::~playlist_item()
{

}

/*!
 * \brief playlist_item::getHash Get the hash of the song for the database
 */
QString playlist_item::getHash()
{
    return this->hash;
}

/*!
 * \brief playlist_item::getSongName Get the name of the song
 */
QString playlist_item::getSongName()
{
    return this->songName;
}

/*!
 * \brief playlist_item::getSongLength Get the length of the song in seconds
 */
int playlist_item::getSongLength()
{
    return this->songLength;
}

/*!
 * \brief playlist_item::setHash Set the hash of the song for the database
 * \param newHash The hash to assign
 */
void playlist_item::setHash(QString newHash)
{
    this->hash = newHash;
}

/*!
 * \brief playlist_item::setSongName Set the name of the song
 * \param newName The name to assign
 */
void playlist_item::setSongName(QString newName)
{
    this->songName = newName;
}

/*!
 * \brief playlist_item::setSongLength Set the length of the song in seconds
 * \param newLength The length of the song in seconds
 */
void playlist_item::setSongLength(int newLength)
{
    this->songLength = newLength;
}
