#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H
#include <QCoreApplication>

#include <QObject>
#include "taalmanager.h"
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QAudioOutput>
#include <QTimer>

class AudioEngine : public QObject
{
    Q_OBJECT
     Q_PROPERTY(int currentBPM READ currentBPM WRITE setCurrentBPM)
    Q_PROPERTY(int currentBeat  READ currentBeat NOTIFY currentBeatChanged)

public:
    explicit AudioEngine(QObject *parent = nullptr);

    void setTaalManager(TaalManager *m);
    void updatePlaybackRate();

    int currentBeat()const {return m_currentBeat;}

public slots:
    Q_INVOKABLE void playAudio();
    Q_INVOKABLE void pauseAudio();
    Q_INVOKABLE void stopAudio();

    int nearestRecording(int m_currentBPM) const;
    int currentBPM()const;
    void setCurrentBPM(int x);

    private:
    TaalManager *k=nullptr;
    QMediaPlayer *player;
    QAudioOutput *audioOutput;
    void handleMediaStatus(QMediaPlayer::MediaStatus status);
    int m_currentBPM=1;
    int loadedRecording=1;

    QString loadedTaal;
    QTimer *beatTimer;
    int m_currentBeat=0;

signals:
    void currentBeatChanged();

};

#endif