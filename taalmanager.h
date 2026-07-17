#ifndef TAALMANAGER_H
#define TAALMANAGER_H
#include <QObject>
#include <QString>
#include <QVector>

struct Taal
{
    QString name;
    int minBPM;
    int maxBPM;
    int defaultBPM;
    int BeatCount;
    int interval;
};

class TaalManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int minBPM READ getminBPM NOTIFY currentTaalChanged)
     Q_PROPERTY(int maxBPM READ getmaxBPM NOTIFY currentTaalChanged)
     Q_PROPERTY(int defaultBPM READ getdefaultBPM NOTIFY currentTaalChanged)
     Q_PROPERTY(int BeatCount READ getBeatCount NOTIFY currentTaalChanged)

public:
    explicit TaalManager(QObject *parent = nullptr);
    Q_INVOKABLE int getminBPM() const;
    Q_INVOKABLE int getmaxBPM() const;
    Q_INVOKABLE int getdefaultBPM() const;
    Q_INVOKABLE int getBeatCount() const;

    Taal getCurrentTaal() const;
public slots:
    void setCurrentTaal(int index);

private:
   //Code intentionally omitted to protect intellectual property.//
signals:
    void currentTaalChanged();
};


#endif // TAALMANAGER_H
