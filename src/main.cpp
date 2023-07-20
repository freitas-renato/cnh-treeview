#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "inc/Model.h"
#include "inc/TreeItemData.h"
#include <QFile>



int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    QFile file(":/database.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    Model model(file.readAll());
    file.close();

    engine.rootContext()->setContextProperty("treeModel", &model);

    qmlRegisterType<TreeItemData>("cnh.treeview", 1, 0, "TreeItemData");


    const QUrl url(u"qrc:/cnh-treeview/views/main.qml"_qs);

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
