#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "gamegridcontroller.h"
#include "statecontroller.h"
#include "heatmapcontroller.h"
#include "informationmapcontroller.h"
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    BoardState* state = new BoardState();

    GameGridController * gameGridController = new GameGridController(&app, state);
    StateController * stateController = new StateController(&app, state);
    HeatmapController * heatmapController = new HeatmapController(&app, state);
    InformationMapController * informationMapController = new InformationMapController(&app, state);

    qmlRegisterSingletonInstance("cpp.GameGridController", 1, 0, "GameGridController", gameGridController);
    qmlRegisterSingletonInstance("cpp.StateController", 1, 0, "StateController", stateController);
    qmlRegisterSingletonInstance("cpp.HeatmapController", 1, 0, "HeatmapController", heatmapController);
    qmlRegisterSingletonInstance("cpp.InformationMapController", 1, 0, "InformationMapController", informationMapController);

    const QUrl url(u"qrc:/battleship/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
