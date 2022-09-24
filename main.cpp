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


template<typename... T>
void print(const T&... args)
{
    ((std::cout << args << " "), ...);
    std::cout << "\n";
}


vector<string> ShowCOMPorts()
{
    vector<string> COM_list;
    int d = 0;
    for (int i = 1; i < 20; i++) {
        HANDLE Test_Port;

        string COM_string_ID = "COM";
        if (i < 10) {
            auto i_c = i + '0';
            COM_string_ID.push_back(i_c);
        }
        else {
            auto i_c = (i%10) + '0';
            COM_string_ID.push_back('1');
            COM_string_ID.push_back(i_c);
        }
        //--------------------------------------------> волшебные преобразования
        const char* COM_char_ID = COM_string_ID.data();
        const auto size = strlen(COM_char_ID) + 1;
        wchar_t COM_TC_id[size];
        mbstowcs(COM_TC_id, COM_char_ID, size);
        auto COM = (LPCTSTR) COM_TC_id;
        //-------------------------------------------->

        Test_Port = CreateFile(COM, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);
        if (Test_Port != INVALID_HANDLE_VALUE) {
            COM_list.push_back(COM_string_ID);
            d++;
            CloseHandle(Test_Port);
        }
    }
    return COM_list;
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

void StartCOM(string COM_str_id, int Baud)
{
    const char* COM_chr_id = COM_str_id.data();
    const auto size = strlen(COM_chr_id) + 1;
    wchar_t COM_TC_id[size];
    mbstowcs(COM_TC_id, COM_chr_id, size);
    auto COM = (LPCTSTR) COM_TC_id;

    hSerial = ::CreateFile(COM,GENERIC_READ | GENERIC_WRITE,0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);

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

    //-------------------------------------------------------------------> тест - отправки строки в порт
    vector<string> available_Ports = ShowCOMPorts();
    for (unsigned long long i = 0; i < available_Ports.size(); i++) {
        cout << available_Ports[i] << " available"<< endl;
    }

    int Baud = 9600;
    char data[] = "Hello from C++";

    cout << "TEST  ";
    StartCOM(available_Ports[0], Baud);
    WriteCOM(data);
    //------------------------------------------------------------------->

    view.show();
    app.exec();
    return 0;
}
