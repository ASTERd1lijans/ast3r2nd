#include <time.h>
#include <iostream>
#include <windows.h>
#include <windowsx.h>

using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void DrawGuy(HWND hwnd);
void DrawLegs(HDC hdc);
void DrawArms(HDC hdc);
void DrawBody(HDC hdc);
void DrawHead(HDC hdc);
void DrawFloor(HDC hdc, HWND hwnd);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    PWSTR lpCmdLine, int nCmdShow) {

    MSG  msg;
    WNDCLASSW wc = { 0 };

    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpszClassName = L"The Tree";
    wc.hInstance = hInstance;
    wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc.lpfnWndProc = WndProc;
    wc.hCursor = LoadCursor(0, IDC_ARROW);

    RegisterClassW(&wc);
    CreateWindowW(wc.lpszClassName, L"Pixels",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        100, 100, 500, 550, NULL, NULL, hInstance, NULL);

    while (GetMessage(&msg, NULL, 0, 0)) {

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    srand(time(NULL));

    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
    WPARAM wParam, LPARAM lParam) {

    switch (msg) {

    case WM_PAINT:

        DrawGuy(hwnd);
        break;

    case WM_DESTROY:

        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProcW(hwnd, msg, wParam, lParam);
}
void DrawGuy(HWND hwnd) {

    PAINTSTRUCT ps;
    RECT r;

    GetClientRect(hwnd, &r);

    if (r.bottom == 0) {

        return;
    }

    HDC hdc = BeginPaint(hwnd, &ps);

    DrawLegs(hdc);
    DrawFloor(hdc, hwnd);
    DrawArms(hdc);
    DrawBody(hdc);
    DrawHead(hdc);

    EndPaint(hwnd, &ps);
}

void DrawLegs(HDC hdc) {
    HPEN pen = CreatePen(BS_SOLID, 2, RGB(0, 0, 0));

    SelectPen(hdc, pen);
    MoveToEx(hdc, 210, 340, NULL);
    LineTo(hdc, 180, 480);

    MoveToEx(hdc, 240, 340, NULL);
    LineTo(hdc, 250, 480);

    DeleteObject(pen);
}

void DrawFloor(HDC hdc, HWND hwnd) {
    RECT WinCoord = {};
    HBRUSH brush = CreateSolidBrush(RGB(0, 251, 63));
    GetWindowRect(hwnd, &WinCoord);
    SelectBrush(hdc, brush);
    Rectangle(hdc, -1, 480, WinCoord.right, WinCoord.bottom);
    DeleteObject(brush);
}

void DrawArms(HDC hdc) {
    HPEN pen = CreatePen(BS_SOLID, 2, RGB(0, 0, 0));

    SelectPen(hdc, pen);
    MoveToEx(hdc, 250, 260, NULL);
    LineTo(hdc, 400, 260);

    MoveToEx(hdc, 205, 260, NULL);
    LineTo(hdc, 100, 100);

    DeleteObject(pen);
}

void DrawBody(HDC hdc) {
    HPEN pen = CreatePen(BS_SOLID, 2, RGB(0, 0, 0));

    SelectPen(hdc, pen);
    MoveToEx(hdc, 225, 240, NULL);
    LineTo(hdc, 225, 200);
    DeleteObject(pen);

    HBRUSH brush = CreateSolidBrush(RGB(255, 52, 249));
    SelectBrush(hdc, brush);
    Rectangle(hdc, 200, 230, 250, 350);
    DeleteObject(brush);
}

void DrawHead(HDC hdc) {
    HBRUSH brush = CreateSolidBrush(RGB(255, 52, 249));
    SelectBrush(hdc, brush);

    Ellipse(hdc, 175, 110, 275, 210);
    DeleteObject(brush);

    HBRUSH brushs = CreateSolidBrush(RGB(255, 255, 255));
    SelectBrush(hdc, brushs);
    Ellipse(hdc, 195, 140, 210, 155);
    Ellipse(hdc, 235, 140, 250, 155);

    HPEN pen = CreatePen(BS_SOLID, 2, RGB(0, 0, 0));

    SelectPen(hdc, pen);
    MoveToEx(hdc, 225, 160, NULL);
    LineTo(hdc, 225, 180);

    MoveToEx(hdc, 210, 195, NULL);
    LineTo(hdc, 240, 195);

    DeleteObject(pen);

    HBRUSH el_brush = CreateSolidBrush(RGB(0, 0, 255));
    SelectBrush(hdc, el_brush);
    Ellipse(hdc, 500, 300, 700, 500);
    DeleteObject(el_brush);
}