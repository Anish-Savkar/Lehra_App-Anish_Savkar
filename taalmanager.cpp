#include "taalmanager.h"


TaalManager::TaalManager(QObject *parent)
    : QObject{parent}
{
    taals.append({"Teentaal",60,350,80,16,10});
    taals.append({"Jhaptaal",60,160,70,10,10});
    taals.append({"Rupak",60,240,80,7,20});
    taals.append({"Ektaal",60,240,80,12,20});
    taals.append({"Keherwa",60,400,100,8,20});
}


void TaalManager::setCurrentTaal(int index)
{
    currentTaalIndex=index;
    emit currentTaalChanged();
}

Taal TaalManager::getCurrentTaal() const
{
    return taals[currentTaalIndex];
}

int TaalManager::getminBPM() const
{
    return taals[currentTaalIndex].minBPM;
}
int TaalManager::getmaxBPM()const
{
    return taals[currentTaalIndex].maxBPM;
}
int TaalManager::getdefaultBPM() const
{
    return taals[currentTaalIndex].defaultBPM;
}
int TaalManager::getBeatCount() const
{
    return taals[currentTaalIndex].BeatCount;
}
