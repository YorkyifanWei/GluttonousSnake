//
// Created by 86180 on 24-8-22.
//
#include "settings.h"
#include <conio.h>
#include <windows.h>

// 定义游戏地图，用于存储蛇、食物和墙壁等信息
// '-1':None; '-2:边界; '-3':食物; '0~2':蛇头; '>=3':蛇身
int blocks[40][40];

// 定义蛇头坐标数组，用于存储多条蛇的头部位置
SnakeCoord heads[3];

// 定义现代游戏模式对象
GameModern modern;

// 定义食物标志变量，用于标记是否已生成食物
_Bool food = 0;

/**
 * 设置控制台窗口的显示属性，包括字体和光标信息
 * 该函数旨在优化控制台显示效果，以适应游戏需求
 */
void ConsoleSettings(void) {
    // 获取标准输出句柄，用于后续设置控制台属性
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

    // 初始化字体信息结构体
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 15;
    cfi.dwFontSize.Y = 15;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy_s(cfi.FaceName, _countof(cfi.FaceName), L"Raster");

    // 设置当前控制台的字体信息
    SetCurrentConsoleFontEx(handle, FALSE, &cfi);

    // 初始化光标信息结构体，设置光标不显示
    CONSOLE_CURSOR_INFO cursor = {1, 0};

    // 设置控制台光标属性
    SetConsoleCursorInfo(handle, &cursor);
}
