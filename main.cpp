#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QtQuickControls2>
#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

HANDLE hSerial;


void ShowCOMPorts()
{
    //vector<LPCTSTR> result;
    int d = 0;
    for (int i = 1; i < 20; i++) {
        HANDLE Port1;



        string COM_str_id_id = "COM";
        if (i < 10) {
            auto i_c = i + '0';
            COM_str_id_id.push_back(i_c);
        }
        else {
            auto i_c = (i%10) + '0';
            COM_str_id_id.push_back('1');
            COM_str_id_id.push_back(i_c);
        }

        const char* COM_str_id = COM_str_id_id.data();

        const auto size = strlen(COM_str_id) + 1;
        wchar_t COM_TC_id[size];
        mbstowcs(COM_TC_id, COM_str_id, size);
        auto COM = (LPCTSTR) COM_TC_id;
        cout << COM_str_id << endl;

        Port1 = CreateFile(COM, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);
        if (Port1 != INVALID_HANDLE_VALUE) {
            //result[d] = COM;
            cout << COM_str_id << " available" << endl;
            d++;
            CloseHandle(Port1);
        }
    }
    //return result;
}


void ReadCOM()
{
      DWORD iSize;
      char sReceivedChar;
      while (true)
      {
            ReadFile(hSerial, &sReceivedChar, 1, &iSize, 0);  // получаем 1 байт
            if (iSize > 0)   // если что-то принято, выводим
                cout << sReceivedChar;
      }
}

void StartCOM(LPCTSTR sPortName, int Baud)
{
    hSerial = ::CreateFile(sPortName,GENERIC_READ | GENERIC_WRITE,0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);

    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength=sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams))
    {
        cout << "getting state error\n";
    }
    dcbSerialParams.BaudRate=Baud;
    dcbSerialParams.ByteSize=8;
    dcbSerialParams.StopBits=ONESTOPBIT;
    dcbSerialParams.Parity=NOPARITY;
    if(!SetCommState(hSerial, &dcbSerialParams))
    {
        cout << "error setting serial port state\n";
    }
}

bool WriteCOM(char* data)
{
    DWORD dwSize = sizeof(data);   // размер этой строки
    DWORD dwBytesWritten;    // тут будет количество собственно переданных байт
    BOOL iRet = WriteFile (hSerial,data,dwSize,&dwBytesWritten,NULL);
    cout << dwSize << " Bytes in string. " << dwBytesWritten << " Bytes sended. " << endl;
    return iRet;
}


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

    char data[] = "Hello from C++";


    int Baud = 9600;
    auto COM_str_id = "COM9";

    const auto size = strlen(COM_str_id) + 1;
    wchar_t COM_TC_id[size];
    mbstowcs(COM_TC_id, COM_str_id, size);
    auto COM = (LPCTSTR) COM_TC_id;

    ShowCOMPorts();

    cout << "TEST  ";
    StartCOM(COM, Baud);

    WriteCOM(data);


    view.show();

    app.exec();
    return 0;
}
