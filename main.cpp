#include <QApplication>
#include <QGuiApplication>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QDebug>
#include <QUrl>
#include "settings_storage.h"
#include "mediaplayer.h"
#include <QtQml>
#include <QMediaPlayer>
#include "playlist_handler.h"

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
        ph, SLOT(shuffleButton()));

    QObject::connect(repButton, SIGNAL(clicked()),
        ph, SLOT(repeatButton()));

    QObject::connect(leftSkip, SIGNAL(clicked()),
        ph, SLOT(previousSong()));

    QObject::connect(rightSkip, SIGNAL(clicked()),
        ph, SLOT(nextSong()));

    return app.exec();
}
