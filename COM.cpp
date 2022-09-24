#include "COM.h"

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
            ReadFile(hSerial, &sReceivedChar, 1, &iSize, 0);
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

    hSerial = ::CreateFile(COM ,GENERIC_READ | GENERIC_WRITE,0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);

    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength=sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams))
    {
        print("getting state error\n");
    }
    dcbSerialParams.BaudRate=Baud;
    dcbSerialParams.ByteSize=8;
    dcbSerialParams.StopBits=ONESTOPBIT;
    dcbSerialParams.Parity=NOPARITY;
    if(!SetCommState(hSerial, &dcbSerialParams))
    {
        print("error setting serial port state\n");
    }
}

bool WriteCOM(char* data)
{
    DWORD dwSize = strlen(data);   // размер входной строки
    DWORD dwBytesWritten;    // кол-во переданных байт
    BOOL iRet = WriteFile (hSerial, data, dwSize, &dwBytesWritten, NULL);
    print(dwSize, " Bytes in string. ", dwBytesWritten, " Bytes sended. "); //debug info
    return iRet;
}

