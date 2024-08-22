//
// Created by 86180 on 24-8-22.
//

#ifndef GLUTTONOUSSNAKE_FUNCTIONS_H
#define GLUTTONOUSSNAKE_FUNCTIONS_H

// 函数GotoXY将光标移动到指定的位置
// 参数x和y分别代表目标位置的横坐标和纵坐标
void GotoXY(int x, int y);

// 函数WinnerName返回胜利者的名称
// 该函数在游戏结束时调用，用于显示胜利者的信息
char *WinnerName(void);

// 函数GetKeyBoard用于获取用户输入的按键
// 该函数返回用户按下键的键值
char GetKeyBoard(void);

// 函数PrintTitle用于打印游戏的标题
// 该函数在游戏开始时调用，用于显示游戏的标题信息
void PrintTitle(void);

// 函数Initial用于初始化游戏
// 该函数在游戏开始前调用，用于设置初始状态
void Initial(void);

// 函数KeyProcess处理按键事件
// 参数key代表用户按下的键，函数返回按键对应的处理结果
char KeyProcess(char key);

// 函数PrintScreen用于打印游戏界面
// 该函数在每次游戏状态更新后调用，用于刷新屏幕显示
void PrintScreen(void);

// 函数SnakeMove控制蛇的移动
// 参数player_code代表玩家的标识，用于确定哪条蛇需要移动
void SnakeMove(int player_code);

// 函数SnakeHit检测蛇是否碰到墙壁或自身
// 参数player_code代表玩家的标识，用于确定检测哪条蛇
// 该函数返回一个整数值，表示蛇是否碰到墙壁或自身
int SnakeHit(int player_code);

// 函数FoodRefresh用于刷新食物的位置
// 该函数在食物被吃掉后调用，用于生成新的食物位置
void FoodRefresh(void);



#endif //GLUTTONOUSSNAKE_FUNCTIONS_H
