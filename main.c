//
// Created by 86180 on 24-8-22.
//
#include "settings.h"
#include "functions.h"
#include <stdio.h>
#include <conio.h>
#include <windows.h>

// define global variable
extern int blocks[40][40];
extern SnakeCoord heads[3];
extern GameModern modern;
extern _Bool food;

// 主函数，游戏的入口点
int main(void) {
    // 初始化控制台设置，为游戏提供合适的输出环境
    ConsoleSettings();
    char key;
    unsigned int count;
    int i;
    _Bool flag = 1;
    // 主循环，只要flag为真，游戏就继续进行
    while (flag) {
        // 初始化游戏状态，包括蛇的位置、食物的位置等
        Initial();
        count = 0;
        // 无限循环，直到游戏结束
        while (TRUE) {
            // 获取键盘输入，用于控制蛇的移动或其他操作
            key = GetKeyBoard();
            // 如果食物被吃光，则重新刷新食物
            if (food == 0) {
                FoodRefresh();
            }
            // 更新屏幕显示，包括蛇的移动、食物的位置等
            PrintScreen();
            // 处理键盘输入，更新蛇的移动方向或其他操作
            key = KeyProcess(key);
            // 如果按下'q'键或所有蛇都死亡，则游戏结束
            if (key == 'q' || (!heads[0].alive && !heads[1].alive && !heads[2].alive)) {
                // 清屏并显示游戏结束信息
                system("cls");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
                printf("Game Over!\n");
                PrintScreen();
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
                printf("\n");
                printf("The winner is \"%s\"\n", WinnerName());
                printf("\n");
                printf("Enter \'r\' to restart game, or enter any other key to quit game.\n");
                // 获取用户是否愿意重新开始游戏的输入
                key = (char)_getch();
                // 如果不是'r'键，则结束游戏
                if (key != 'r') {
                    flag = 0;
                }
                break;
            }
            // 更新每条蛇的位置，根据速度决定是否移动
            for (i = 0; i < modern.multiplayer; i++) {
                if (heads[i].alive && count % heads[i].speed == 0) {
                    SnakeMove(i);
                }
            }
            // 更新帧计数器，并限制游戏帧率
            count += 1;
            count %= 720;
            Sleep(50);
            // 将光标返回到屏幕左上角，准备下一次绘制
            GotoXY(0, 0);
        }
    }
    // 游戏结束，清屏
    system("cls");

    return 0;
}
