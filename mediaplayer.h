#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H
#include <QByteArray>
#include <QMediaPlayer>
#include <QObject>

class mediaPlayer:public QObject
{
    Q_OBJECT

public:
    mediaPlayer();
    ~mediaPlayer();
    void play(QByteArray);

public slots:
    void play();
    void pause();
    void skipTo(int);
    void playOrPause();
    void setVolume(int);
    void rewind();
    void fastForward();
    void durationChanged(qint64);

signals:

private:
    QMediaPlayer *player;
};


#endif // MEDIAPLAYER_H
