#include <QApplication>
#include <QGuiApplication>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QDebug>
#include <QUrl>
#include <QtQml>
#include <QMediaPlayer>
#include "settings_storage.h"
#include "mediaplayer.h"
#include "playlist.h"
#include "playlist_handler.h"
#include "dataobject.h"

int main(int argc, char *argv[])
{
    qmlRegisterSingletonType(QUrl("qrc:/GlobalVars.qml"), "Alluvial.Globals", 1, 0, "Globals");

	QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    app.setOrganizationName("AlluvialAlphaBuild");
    app.setApplicationName("Alluvial");

    Settings_storing *settings = new Settings_storing();
    engine.rootContext()->setContextProperty("clientSettings", settings);

    mediaPlayer *mp = new mediaPlayer();
    playlist_handler *ph = new playlist_handler();

    QObject *root = engine.rootObjects().first();
    QObject *playButton = root->findChild<QObject*>("playButton");
    QObject *playbackSlider = root->findChild<QObject*>("playbackSlider");
    QObject *volSlider = root->findChild<QObject*>("volumeSlider");
    QObject *rwButton = root->findChild<QObject*>("rewindButton");
    QObject *ffButton = root->findChild<QObject*>("fastForwardButton");
    QObject *leftSkip = root->findChild<QObject*>("leftSkipButton");
    QObject *rightSkip = root->findChild<QObject*>("rightSkipButton");
    QObject *shufButton = root->findChild<QObject*>("shuffleButton");
    QObject *repButton = root->findChild<QObject*>("repeatButton");

    QObject *playlistDropDown = root->findChild<QObject*>("dropdownPlaylistOptions");
    QObject *trackListings = root->findChild<QObject*>("trackListings");
    QObject *trackModel = root->findChild<QObject*>("trackModel");

    // Pause or play the song
    QObject::connect(playButton, SIGNAL(playClicked()),
        mp, SLOT(playOrPause()));

    // Adjust the volume according to the position of the volume slider
    QObject::connect(volSlider, SIGNAL(changeVol(int)),
        mp, SLOT(setVolume(int)));

    // Skip back - NEEDS TO BE FIXED TO HANDLE HOLD DOWN
    QObject::connect(rwButton, SIGNAL(clicked()),
        mp, SLOT(rewind()));

    // Skip ahead - NEEDS TO BE FIXED TO HANDLE HOLD DOWN
    QObject::connect(ffButton, SIGNAL(clicked()),
        mp, SLOT(fastForward()));

    // Skip to position based off of the slider
    QObject::connect(playbackSlider, SIGNAL(playbackPosChanged(int)),
        mp, SLOT(skipTo(int)));

    // Skip to position based off of the slider
    QObject::connect(playbackSlider, SIGNAL(playbackPosChanged(int)),
        mp, SLOT(skipTo(int)));

    QObject::connect(shufButton, SIGNAL(clicked()),
        ph, SLOT(shuffleSwitch()));

    QObject::connect(repButton, SIGNAL(clicked()),
        ph, SLOT(repeatSwitch()));

    QObject::connect(leftSkip, SIGNAL(clicked()),
        ph, SLOT(previousSong()));

    QObject::connect(rightSkip, SIGNAL(clicked()),
        ph, SLOT(nextSong()));

    QObject::connect(playlistDropDown, SIGNAL(activePlaylistChanged(int)),
        ph, SLOT(changeTrackListings(int)));

    playlist_item *newSong = new playlist_item("#0", "song 1", 5);

    ph->addPlaylist("Playlist 1");
    ph->addSong(0, *newSong);
    ph->addSong(0, *newSong);
    ph->addSong(0, *newSong);
    ph->addPlaylist("Playlist 2");
    ph->addSong(1, *newSong);
    ph->addSong(1, *newSong);
    ph->addPlaylist("Playlist 3");
    ph->addSong(2, *newSong);
    ph->addSong(2, *newSong);
    ph->addSong(2, *newSong);
    ph->addSong(2, *newSong);

    QStringList playlists;
    for ( int index = 0; index < ph->getPlaylists().size(); index++ )
    {
        playlists.append(ph->getPlaylist(index).getPlaylistTitle());
    }

    QStringList songs;
    for ( int index = 0; index < ph->getPlaylistSongNames(ph->getActivePlaylistIndex()).size(); index++ )
    {
        songs.append(ph->getPlaylistSongNames(ph->getActivePlaylistIndex()).at(index));
    }

    std::vector<playlist_item> songNameVector = ph->getActivePlaylist().getSongs();
    QStringList songNameList;
    for ( int i = 0 ; i < songNameVector.size() ; i++ )
    {
        songNameList.append(songNameVector.at(i).getSongName());
    }
    qDebug() << QVariant::fromValue(songNameList);

    std::vector<QString> data = ph->getPlaylistSongNames(0);
    QList<QObject*> dataList;
    for ( int i = 0 ; i < data.size() ; i++ )
    {
        dataList.append(new DataObject(data.at(i)));
    }
    engine.rootContext()->setContextProperty("cppModel", QVariant::fromValue(dataList));
    engine.rootContext()->setContextProperty("playlistModel", QVariant::fromValue(playlists));


    return app.exec();
}
