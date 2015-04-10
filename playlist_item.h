#ifndef PLAYLIST_ITEM_H
#define PLAYLIST_ITEM_H
#include <QString>

class playlist_item
{
public:
    playlist_item();
    ~playlist_item();

private:
    QString hash; /**< The unique identifier for the song */
    QString songName; /**< The title of the song for displaying purposes */
    int songLength; /**< The song length in int form. 1:20 song would be 80 */
    QString songLengthDisplay; /**< The song length in display form. A 80 second song would be '1:20' */
};

#endif // PLAYLIST_ITEM_H
