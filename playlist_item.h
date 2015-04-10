#ifndef PLAYLIST_ITEM_H
#define PLAYLIST_ITEM_H
#include <QString>

class playlist_item
{
public:
    playlist_item();
    playlist_item(QString, QString, int);
    ~playlist_item();

    QString getHash();
    QString getSongName();
    int getSongLength();

    void setHash(QString);
    void setSongName(QString);
    void setSongLength(int);

private:
    QString hash; /**< The unique identifier for the song */
    QString songName; /**< The title of the song for displaying purposes */
    int songLength; /**< The song length in int form. 1:20 song would be 80 */
};

#endif // PLAYLIST_ITEM_H
