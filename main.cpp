#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>

#include "LibraryManager.h"

// main
//-----------------------------------------------------------------------------------------------------------------

int main(int argc, char* argv[]) {
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // manager is NOW on the heap because it is created using new instead of "LibraryManager manager;"
    LibraryManager* manager = new LibraryManager(&app);

    // give the manager to QML so it can call its methods (functions)
    engine.rootContext()->setContextProperty("backend", manager);

    // load the UI resource file
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}