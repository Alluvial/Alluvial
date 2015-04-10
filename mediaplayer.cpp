#include "mediaplayer.h"
#include <QByteArray>
#include <QFile>
#include <QMediaPlayer>
#include <QFileInfo>
#include <QDir>
#include <QQmlComponent>
#include <QQmlApplicationEngine>

mediaPlayer::mediaPlayer()
{
    player = new QMediaPlayer();

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    QDir homePath = QDir::currentPath() + "/../Alluvial";
    QFile example(homePath.absolutePath() + "/music/GiDeMo/Thousand Enemies.mp3");
    example.open(QIODevice::ReadOnly);
    QByteArray dat = example.readAll();

    connect(player, SIGNAL(durationChanged(qint64)), SLOT(durationChanged(qint64)));

    this->play(dat);
}

mediaPlayer::~mediaPlayer()
{

}

/*!
 * \brief mediaPlayer::play Continue the song to play
 */
void mediaPlayer::play ()
{
    player->play();
}

/*!
 * \brief mediaPlayer::play Play a brand new song
 * \param data The data of the song to play
 */
void mediaPlayer::play (QByteArray data)
{
    QFile tmp_file("tmp.mp3");
    QDir path = QDir::currentPath();

    if(!tmp_file.open(QIODevice::WriteOnly)) {
        qDebug() << "opening location didn't work";
        return ;
    }

    //qDebug() << "Now starting to write data of size" << data.size();

    if(tmp_file.write(data) < 0) {
        qDebug() << "file write failed" << tmp_file.errorString();
        return ;
    }
    tmp_file.close();

    QMediaContent song = QMediaContent(QUrl::fromLocalFile(path.absolutePath() + "/tmp.mp3"));
    player->setMedia(song);
    player->setVolume(50);
    player->play();
}

/*!
 * \brief mediaPlayer::pause Pause the current song
 */
void mediaPlayer::pause ()
{
    player->pause();
}

/*!
 * \brief mediaPlayer::playOrPause Switch the playback state
 */
void mediaPlayer::playOrPause()
{
    int state = player->state();

    if (state == 1)
    {
        this->pause();
    }
    else
    {
        this->play();
    }
}

/*!
 * \brief mediaPlayer::skipTo Jump to a specific position in the song
 * \param position The position to jump to in milliseconds
 */
void mediaPlayer::skipTo(int position)
{
    // position in milliseconds
    player->setPosition(position);
}

/*!
 * \brief mediaPlayer::setVolume Change the playback volume
 * \param vol The value to change to on a scale of 1 - 100
 */
void mediaPlayer::setVolume(int vol)
{
    player->setVolume(vol);
}

/*!
 * \brief mediaPlayer::rewind Skip ahead 10 seconds
 */
void mediaPlayer::rewind()
{
    player->setPosition(player->position()-10000);
}

/*!
 * \brief mediaPlayer::fastForward Skip ahead 10 seconds
 */
void mediaPlayer::fastForward()
{
    player->setPosition(player->position()+10000);
}

/*!
 * \brief mediaPlayer::durationChanged Change the duration of the song. NEEDS FIXING!!!
 * \param duration The length of the song in seconds
 */
void mediaPlayer::durationChanged(qint64 duration)
{
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    QObject *root = engine.rootObjects().first();
    QObject *playbackSlider = root->findChild<QObject*>("playbackSlider");
    QObject *activeSongMeta = root->findChild<QObject*>("activeSongMeta");
    QObject *songEnd = root->findChild<QObject*>("songEnd");
    playbackSlider->setProperty("maximumValue", duration/1000);
    activeSongMeta->setProperty("length", duration/1000);
    //songEnd->setProperty("text", QVariant("4:48"));
    //qDebug() << "The duration label:" << songEnd->property("text");
}
