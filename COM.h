#ifndef COM_H
#define COM_H
#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

static HANDLE hSerial;

template<typename... T>
void print(const T&... args);

vector<string> ShowCOMPorts();

void ReadCOM();

void StartCOM(string COM_str_id, int Baud);

bool WriteCOM(char* data);
#endif // COM_H
