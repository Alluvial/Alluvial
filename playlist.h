#ifndef PLAYLIST_H
#define PLAYLIST_H
#include <QObject>
#include <QString>
#include <playlist_item.h>
#include <QVector>
#include <QTime>

class playlist
{

public:
    playlist();
    playlist(QString);
    ~playlist();
    void jumpToSong(QString);
    void jumpToSong(int);
    void addSong(playlist_item);
    void removeSong(int);
    void removeSong(playlist_item);
    void moveSong(playlist_item, int);
    QString getActiveSongHash();
    QString getSongHash(int);
    QString getPlaylistTitle();
    QString name();
    QVector<playlist_item> getSongs();
    playlist_item getSong(int);
    void setTime();
    QTime getTime();

public slots:

private:
    //! The playlist title
    /*! The title of the playlist used for displaying purposes. Must be unique. */
    QString title;
    //! The songs for this playlist
    /*! The array of the songs that belong to this playlist in a vector form. */
    QVector<playlist_item> songs;
    //! The time of the last modification done to the playlist
    /*! Every time a song is added or dropped from a playlist,
     * this value updates to ensure we are saving our changes to the database */
    QTime last_save;
};

#endif // PLAYLIST_H
