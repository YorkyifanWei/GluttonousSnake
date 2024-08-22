//
// Created by 86180 on 24-8-22.
//

#ifndef GLUTTONOUSSNAKE_SETTINGS_H
#define GLUTTONOUSSNAKE_SETTINGS_H

// 定义颜色常量，用于后续在游戏界面中设置文本颜色
#define BLACK 0x0// 黑色
#define BLUE 0x1// 蓝色
#define GREEN 0x2// 绿色
#define PALE_GREEN 0x3 // 浅绿色
#define RED 0x4// 红色
#define PURPLE 0x5// 紫色
#define YELLOW 0x6// 黄色
#define WHITE 0x7// 白色
#define GREY 0x8// 灰色
#define BLUISH 0x9// 淡蓝色
#define ONDINE 0xA// 淡绿色
#define LIGHT_ONDINE 0xB// 淡浅绿色
#define REDDISH 0xC// 淡红色
#define LAVENDER 0xD// 淡紫色
#define FAINT_YELLOW 0xE// 淡黄色
#define GLOSS_WHITE 0xF// 亮白色

// 定义蛇结构体，用于存储蛇的相关信息
typedef struct SnakeCoord_ {
    char name[20]; // 蛇的名字
    _Bool alive; // 蛇的存活状态，真表示存活，假表示死亡
    int x; // 蛇头的x坐标
    int y; // 蛇头的y坐标
    int t_x; // 蛇尾的x坐标
    int t_y; // 蛇尾的y坐标
    int score; // 蛇的得分
    int speed; // 蛇的速度
    char direct; // 蛇的移动方向，'u':向上; 'd':向下; 'l':向左; 'r':向右
} SnakeCoord;

// 定义现代游戏设置结构体，用于存储游戏的相关参数
typedef struct GameModern_ {
    int height; // 游戏窗口的高度
    int width; // 游戏窗口的宽度
    int difficulty; // 游戏难度
    int multiplayer; // 多玩家模式，真表示多人游戏，假表示单人游戏
    int size; // 蛇的大小
} GameModern;

// 获取键盘输入的函数
// 该函数没有输入参数
// 返回值为字符型，表示用户按下的是哪个键
char GetKeyBoard(void);

// 设置控制台的显示属性的函数
// 该函数没有输入参数和返回值
void ConsoleSettings(void);


#endif //GLUTTONOUSSNAKE_SETTINGS_H
