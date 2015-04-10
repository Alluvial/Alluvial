#ifndef PLAYLIST_HANDLER_H
#define PLAYLIST_HANDLER_H
#include <QString>
#include <playlist_item.h>
#include <vector>

class playlist_handler
{
public:
    playlist_handler();
    ~playlist_handler();
    void nextSong();
    void previousSong();
    void jumpToSong(QString);
    void jumpToSong(int);
    void addSong(playlist_item);
    void removeSong(playlist_item);
    void moveSong(playlist_item, int);
    QString getActiveSongHash();
    QString getSongHash(int);

public slots:
    void repeatButton();
    void shuffleButton();
    void previousSong();
    void nextSong();

private:
    QString name;
    std::vector<playlist_item> songs{}; /**< The array of the songs that belong to this playlist */
    int activeSong; /**< The index of the current song that is playing */
    bool shuffle; ///< The shuffle toggle
    bool repeat; ///< The repeat toggle
};

#endif // PLAYLIST_HANDLER_H
