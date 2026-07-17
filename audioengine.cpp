#include "audioengine.h"
#include <QDebug>


AudioEngine::AudioEngine(QObject *parent): QObject{parent}
{

    audioOutput=new QAudioOutput(this);
    player=new QMediaPlayer(this);
    player->setAudioOutput(audioOutput);

    audioOutput->setVolume(1.0);

    connect
        (player, &QMediaPlayer::mediaStatusChanged,
         this,&AudioEngine::handleMediaStatus);

    beatTimer=new QTimer(this);

    connect(beatTimer,&QTimer::timeout,this,[this]()
    {
        qint64 position = player->position();
        double beatDuration=59500.0/m_currentBPM;
        Taal a= k->getCurrentTaal();

        int beat=static_cast<int>(position/beatDuration)% a.BeatCount;

        if(beat!=m_currentBeat)
        {
            m_currentBeat=beat;
            emit currentBeatChanged();
        }
    });
}
void AudioEngine::setTaalManager(TaalManager *m)
{
    k= m;
}
void AudioEngine::handleMediaStatus(QMediaPlayer::MediaStatus status)
{
    player->setLoops(QMediaPlayer::Infinite);
}
void AudioEngine::setCurrentBPM(int x)
{
    if(m_currentBPM==x)
        return;
    m_currentBPM=x;
    if(player->playbackState()==QMediaPlayer::PlayingState)
    {
        if(nearestRecording(m_currentBPM)!=loadedRecording)
            playAudio();
        else
            updatePlaybackRate();
    }
}
int AudioEngine::currentBPM()const
{
    return m_currentBPM;
}
int AudioEngine::nearestRecording(int m_currentBPM) const
{
    Taal a= k->getCurrentTaal();
    int currentInterval=a.interval;
    return ((m_currentBPM+currentInterval/2)/currentInterval)*currentInterval;
}
void AudioEngine::updatePlaybackRate()
{
    int recording= nearestRecording(m_currentBPM);
    double rate=static_cast<double>(m_currentBPM)/recording;
    player->setPlaybackRate(rate);
}

void AudioEngine::playAudio()
{
    Taal a= k->getCurrentTaal();
    int recording= nearestRecording(m_currentBPM);

    if(recording!=loadedRecording || a.name!= loadedTaal)
    {
        player->stop();

        QString path= QCoreApplication::applicationDirPath();
        path+="/Audio/";
        path+= a.name;
        path+="/";
        path+=a.name;
        path+=" ";
        path+=QString::number(recording);
        path+=".wav";

        player->setSource(QUrl::fromLocalFile(path));
        loadedRecording=recording;
        loadedTaal=a.name;
    }
    updatePlaybackRate();
    player->play();
    beatTimer->start(10);
}

    void AudioEngine::pauseAudio()
    {
        player->pause();
        beatTimer->stop();
    }
    void AudioEngine::stopAudio()
    {
        player->stop();
         beatTimer->stop();
        m_currentBeat=0;
         emit currentBeatChanged();
    }
