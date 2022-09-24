#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QtQuickControls2>
#include "COM.h"
#include <thread>

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
    for (unsigned long long i = 0; i < available_Ports.size(); i++) {
        cout << available_Ports[i] << " available"<< endl;
    }

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
