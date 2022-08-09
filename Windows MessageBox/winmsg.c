#include <windows.h>
#include <winuser.h>

#define WIN32_LEAN_AND_MEAN

/*
 * int WINAPI WinMainCRTStartup(void)
 * int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nShowCmd)
 */
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nShowCmd) {
    LPCTSTR msg = "Hello, world!";
    LPCTSTR title = "Test";
    TCHAR longmsg[20] = "";
    strcat(longmsg, title);
    strcat(longmsg, " ");
    strcat(longmsg, msg);

    /*
     * MessageBoxW LPCWSTR
     * MessageBox LPCTSTR
     * MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2
     * MB_ICONINFORMATION | MB_OK | MB_SYSTEMMODAL | MB_TOPMOST
     * MB_SETFOREGROUND
     * MB_TOPMOST
     */
    return MessageBox(NULL, (LPCTSTR) longmsg, title, MB_ICONQUESTION | MB_YESNOCANCEL | MB_SETFOREGROUND | MB_TOPMOST);
}
