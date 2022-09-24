#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QtQuickControls2>
#include "COM.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQuickStyle::setStyle("Universal");
    QQuickView view;
    view.engine()->addImportPath("qrc:/qml/imports");
    view.setSource(QUrl("qrc:/qml/Screen01.ui.qml"));
    if (!view.errors().isEmpty())
        return -1;

    //-------------------------------------------------------------------> тест - отправки строки в порт
    vector<string> available_Ports = ShowCOMPorts();
    printPorts(available_Ports);

    int Baud = 9600;
    char data[] = "Hello from C++";

    cout << "TEST  ";
    StartCOM(available_Ports[1], Baud);

    WriteCOM(data);
    //------------------------------------------------------------------->

    //---------------------------> тест считывания данных
    thread t(&ReadCOM);
    t.detach();
    //<--------------------------
    view.show();
    app.exec();
    return 0;
}
