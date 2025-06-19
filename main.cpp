#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "gamegridcontroller.h"
#include "statecontroller.h"
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    BoardState* state = new BoardState();

    GameGridController * gameGridController = new GameGridController(&app, state);
    StateController * stateController = new StateController(&app, state);

    qmlRegisterSingletonInstance("cpp.GameGridController", 1, 0, "GameGridController", gameGridController);
    qmlRegisterSingletonInstance("cpp.StateController", 1, 0, "StateController", stateController);

    const QUrl url(u"qrc:/battleship/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
