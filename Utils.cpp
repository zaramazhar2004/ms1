/***********************************************************************
// OOP244 Project, Utils Module
//
// File	Utils.h
// Version 0.1
// started by Fardad
// Description
// utility function to be used in the project
// Revision History
// -----------------------------------------------------------
// Name            Date            Reason
//
/////////////////////////////////////////////////////////////////
***********************************************************************/
#include <iostream>
#include "Utils.h"
using namespace std;
namespace seneca {
    Utils ut;

    char* Utils::alocpy(const char* src) const {
        char* des{};
        return alocpy(des, src);
    }

    char* Utils::alocpy(char*& des, const char* src)const {
        delete[] des;
        des = nullptr;
        if (src) {
            des = new char[strlen(src) + 1];
            strcpy(des, src);
        }
        return des;
    }
    char* Utils::strcpy(char* des, const char* src)const {
        int i;
        for (i = 0; src[i]; i++) des[i] = src[i];
        des[i] = char(0);
        return des;
    }
    int Utils::strlen(const char* str)const {
        int len;
        for (len = 0; str[len]; len++);
        return len;
    }

    bool Utils::isspace(char ch)const {
        return ch == ' ' || ch == '\t' || ch == '\n' || ch == '\v' || ch == '\f' || ch == '\r';
    }

    bool Utils::isspace(const char* cstring) const {
        while (cstring && isspace(*cstring)) {
            cstring++;
        }
        return cstring && *cstring == 0;
    }
    int Utils::getInt() const {
        int user_Input{};
        while (true) {
            if (cin.peek() == '\n') {
                cin.ignore(10000, '\n');
                cout << "You must enter a value: ";
            }
            else {
                cin >> user_Input;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Invalid integer: ";
                }
                else if (cin.get() != '\n') {
                    cin.ignore(10000, '\n');
                    cout << "Only an integer please: ";

                }
                else {
                    return user_Input;
                }
            }
        }
    } int Utils::getInt(int min, int max)const {
        int user_Input{};
        while (true) {
            user_Input = getInt();
            if (user_Input<min || user_Input>max) {
                cout << "Invalid value: [" << min << "<= value <=" << max << "], try again: ";

            }
            else {
                return user_Input;
            }
        }
    }
}
