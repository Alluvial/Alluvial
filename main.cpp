#include <QApplication>
#include <QGuiApplication>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QDebug>
#include <QUrl>
#include "settings_storage.h"
#include <QtQml>

/*
Settings::Settings(QObject *parent): QObject(parent){

}

void Settings::setValue(const QString &key, const QVariant &value){
    client_settings.setValue(key, value);
}
QVariant Settings::value(const QString &key, const QVariant &defaultValue) const{
    return client_settings.value(key, defaultValue);
}
*/

int main(int argc, char *argv[])
{

    qmlRegisterSingletonType(QUrl("qrc:/GlobalVars.qml"), "Alluvial.Globals", 1, 0, "Globals");
    qmlRegisterType<Settings_storing>("AlluvialSettings", 0, 1, "ClientSettings");


	QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    app.setOrganizationName("AlluvialAlphaBuild");
    app.setOrganizationDomain("couponbug.com");
    app.setApplicationName("Alluvial");

    Settings_storing *settings = new Settings_storing();


    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    engine.rootContext()->setContextProperty("clientSettings", settings);

    /*
     * IMPORTANT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
     * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     * ("../Alluvial/main.qml")
     * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     * IMPORTANT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    QQuickView *view = new QQuickView;
    QScopedPointer<QApplication> application(new QApplication(argc, argv));
    //QScopedPointer<QmlApplicationViewer> viewer(QmlApplicationViewer::create());
    Settings* settings = new Settings(application.data());
    QUrl url("file:///home/jefferson/Code/Alluvial/Alluvial");


    view->rootContext()->setContextProperty("settings", settings);
    view->setSource();
    view->showNormal();

   // engine = new QQmlEngine;
   // QQmlEngine *qmlengine = new QQmlEngine;
   // qmlengine->rootContext()->setContextProperty("settings", settings);
   //  component = new QQmlComponent(qmlengine);



    QObject *topLevel = engine.rootObjects().value(0);
    QQuickWindow *window = qobject_cast<QQuickWindow *>(topLevel);

    window->show();
*/
    return app.exec();
}
