#ifndef KEYBOARDLISTNER_H
#define KEYBOARDLISTNER_H

#include <windows.h>



class KeyboardListner
{
public:
    KeyboardListner();
    ~KeyboardListner();

private:
    HHOOK mKeyboardHook;

    static LRESULT CALLBACK processKeyboardEvent(int nCode, WPARAM wParam, LPARAM lParam);
};

#endif // KEYBOARDLISTNER_H
