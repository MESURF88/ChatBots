#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <DisplayLogic.hpp>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QString ipaddr = "";
    bool a_bclient = false;
    for (int i = 1; i < argc; ++i) {
        if (!qstrcmp(argv[i], "--client"))
        {
            a_bclient = true;
        }

    }
	
	if (a_bclient)
	{
	   // read in arguments ipaddr
	  if (argc == 3u)
	  {
		ipaddr = argv[2u];
	  }
	  else
	  {
		qDebug() << "invalid arguments:";
		return 1u;
	  }
	}
	
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;



    StatSchemaProps props;
    DisplayLogic dspl(a_bclient, (a_bclient) ? ipaddr : QString("127.0.0.1"), props);
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
