#include "keyboardlistner.h"

#include <QDebug>

#include "virtualkeys.h"



KeyboardListner::KeyboardListner()
{
    mKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, processKeyboardEvent, GetModuleHandle(NULL), 0);
}

KeyboardListner::~KeyboardListner()
{
    UnhookWindowsHookEx(mKeyboardHook);
}

LRESULT CALLBACK KeyboardListner::processKeyboardEvent(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode == HC_ACTION)
    {
        if (wParam == WM_KEYDOWN)
        {
            KBDLLHOOKSTRUCT *pKeyboard = (KBDLLHOOKSTRUCT*)lParam;

            if (
                pKeyboard->vkCode != VK_CAPITAL
                &&
                pKeyboard->vkCode != VK_LSHIFT
                &&
                pKeyboard->vkCode != VK_RSHIFT
                &&
                pKeyboard->vkCode != VK_LCONTROL
                &&
                pKeyboard->vkCode != VK_RCONTROL
                &&
                pKeyboard->vkCode != VK_LMENU
                &&
                pKeyboard->vkCode != VK_RMENU
               )
            {
                QString line;

                if (GetKeyState(VK_CAPITAL) & 0x0F)
                {
                    line.append("[CAPS LOCK]");
                }

                if (GetKeyState(VK_SHIFT) & 0xF0)
                {
                    line.append("Shift + ");
                }

                if (GetKeyState(VK_CONTROL) & 0xF0)
                {
                    line.append("Ctrl + ");
                }

                if (GetKeyState(VK_MENU) & 0xF0)
                {
                    line.append("Alt + ");
                }

                QString keyName;

                if (pKeyboard->vkCode == VK_RETURN)
                {
                    keyName = "\n";
                }
                else
                {
                    keyName = virtualKeyToString(pKeyboard->vkCode) + " (" + QString::number(pKeyboard->vkCode) + " 0x" + QString("%1").arg(pKeyboard->vkCode, 2, 16, QChar('0')).toUpper() + ")";
                }

                line.append(keyName);

                qDebug() << line;
            }
        }
    }

    return false;
}
