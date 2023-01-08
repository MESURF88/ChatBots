#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <DisplayLogic.hpp>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    bool a_bclient = false;
    for (int i = 1; i < argc; ++i) {
        if (!qstrcmp(argv[i], "--client"))
        {
            a_bclient = true;
        }
    }
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;



    StatSchemaProps props;
    DisplayLogic dspl(a_bclient, QString("127.0.0.1"), props);
    QQmlContext* context = engine.rootContext();
    context->setContextProperty("dspl", &dspl);

    qRegisterMetaType<StatSchemaProps*>("StatSchemaProps");
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
