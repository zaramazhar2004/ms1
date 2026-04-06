/***********************************************************************
// OOP244 Project, Utils Module
//
// File	Utils.h
// Version 0.1
// started by Fardad and completed by Zara Mazhar
// Description
// utility function to be used in the project
// Revision History
First: 12 march
second: 13 march 
third: 16 march
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
    //MS2 part
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
    char* Utils::makeBillFileName(char* generatedFileName, size_t currentBillNumber)const {
        char temporaryBillFileName[21] = "bill_";
        size_t copiedBillNumber = currentBillNumber;
        int digitPosition = 5;
        int totalLength;
        do {
            digitPosition++;
            copiedBillNumber /= 10;
        } while (copiedBillNumber > 0);
        totalLength = digitPosition;
        while (currentBillNumber > 0) {
            temporaryBillFileName[--digitPosition] = (currentBillNumber % 10) + '0';
            currentBillNumber /= 10;

        }
        if (temporaryBillFileName[digitPosition - 1] == '\0') {
            temporaryBillFileName[--digitPosition] = '0';
        }
        for (int i = 0; ".txt"[i]; i++) {
            temporaryBillFileName[totalLength++] = ".txt"[i];
        }
        temporaryBillFileName[totalLength] = '\0';
        strcpy(generatedFileName, temporaryBillFileName);
        return generatedFileName;
    }

}
