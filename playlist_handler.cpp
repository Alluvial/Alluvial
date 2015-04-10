#include "playlist_handler.h"
#include <vector>

playlist_handler::playlist_handler()
{
    this->name = "Untitled Playlist";
    this->songs = new playlist_item[];
    this->activeSong = 0;
    this->shuffle = false;
    this->repeat = false;
}

playlist_handler::~playlist_handler()
{

}

/*!
 * \brief A function to relocate a song in the playlist
 * \param songToMove The song that is to be relocated
 * \param newPosition Where we want the song to end up in the playlist
*/
playlist_handler::moveSong(playlist_item songToMove, int newPosition)
{
    QString deleteSongHash = songToMove.hash;
    for ( int index = 0; index < this->songs.size() ; index++ )
    {
        if ( this->songs[index].hash == deleteSongHash )
        {
            this->songs.erase(index);
            break;
        }
    }
    this->songs.insert(newPosition, songToMove)
}

/*!
 * \brief playlist_handler::addSong Add a song to the start of the playlist
 * \param newSong The song to be added
 */
playlist_handler::addSong(playlist_item newSong)
{
    this->songs.insert(this->songs.begin(), newSong);
}

/*!
 * \brief playlist_handler::removeSong Used to remove a song from the playlist
 * \param deleteSong The song to be deleted from the playlist
 */
playlist_handler::removeSong(playlist_item deleteSong)
{
    QString deleteSongHash = deleteSong.hash;
    for ( int index = 0; index < this->songs.size() ; index++ )
    {
        if ( this->songs[index].hash == deleteSongHash )
        {
            this->songs.erase(index);
            break;
        }
    }
}

/*!
 * \brief The playlist incrementer
*/
playlist_handler::nextSong()
{
    this->activeSong = this->activeSong + 1;
    if ( this->activeSong >= this->songs.size() )
    {
        this->activeSong = 0;
    }
}

/*!
 * \brief The playlist decrementer
 */
playlist_handler::previousSong()
{
    this->activeSong = this->activeSong - 1;
    if ( this->activeSong < 0 )
    {
        this->activeSong = this->songs.size() - 1;
    }
}

/*!
 * \brief playlist_handler::jumpToSong Jump to song by hash
 * \param newSongHash The hash of the song we want to jump to
 */
playlist_handler::jumpToSong(QString newSongHash)
{
    for ( int index = 0; index < this->songs.size() ; index++ )
    {
        if ( this->songs[index].hash == newSongHash )
        {
            this->activeSong = index;
            break;
        }
    }
}

/*!
 * \brief playlist_handler::jumpToSong Skip to song position
 * \param newIndex The index to jump to
 */
playlist_handler::jumpToSong(int newIndex)
{
    this->activeSong = newIndex;
}

/*!
 * \brief Get the hash of the song to be played.
 */
playlist_handler::getActiveSongHash()
{
    return this->songs[activeSong].hash;
}

/*!
 * \brief playlist_handler::getSongHash Get the hash of a song by its index
 * \param songIndex The index of the song to be gotten
 */
playlist_handler::getSongHash(int songIndex)
{
    return this->songs[songIndex].hash;
}













