#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "gamegridcontroller.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    GameGridController * gameGridController = new GameGridController(&app);
    qmlRegisterSingletonInstance("cpp.GameGridController", 1, 0, "GameGridController", gameGridController);

    const QUrl url(u"qrc:/battleship/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
