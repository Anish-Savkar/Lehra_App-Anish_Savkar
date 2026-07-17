#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "audioengine.h"
#include <QQmlContext>
#include "taalmanager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    AudioEngine audioEngine;
    TaalManager tm;
    audioEngine.setTaalManager(&tm);
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("audioEngine", &audioEngine);
    engine.rootContext()->setContextProperty("tm", &tm);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("LehraApp", "Main");

    app.setApplicationDisplayName("Lehra App - Anish Savkar");

   return QGuiApplication::exec();
}
