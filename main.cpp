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

    QObject *root = engine.rootObjects().first();
    QObject *playButton = root->findChild<QObject*>("playButton");
    QObject *playbackSlider = root->findChild<QObject*>("playbackSlider");
    QObject *volSlider = root->findChild<QObject*>("volumeSlider");
    QObject *ffButton = root->findChild<QObject*>("fastForwardButton");

    mediaPlayer *mp = new mediaPlayer();

    // Pause or play the song
    QObject::connect(playButton, SIGNAL(playClicked()),
        mp, SLOT(playOrPause()));

    // Adjust the volume according to the position of the volume slider
    QObject::connect(volSlider, SIGNAL(changeVol(int)),
        mp, SLOT(setVolume(int)));

    // Skip ahead - NEEDS TO BE FIXED TO HANDLE HOLD DOWN
    QObject::connect(ffButton, SIGNAL(clicked()),
        mp, SLOT(fastForward()));

    // Skip to position based off of the slider
    QObject::connect(playbackSlider, SIGNAL(playbackPosChanged(int)),
        mp, SLOT(skipTo(int)));

    // Skip to position based off of the slider
    QObject::connect(playbackSlider, SIGNAL(playbackPosChanged(int)),
        mp, SLOT(skipTo(int)));

    return app.exec();
}
