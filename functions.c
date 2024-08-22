//
// Created by 86180 on 24-8-22.
//
#include "settings.h"
#include "functions.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

/* 定义了一个全局数组blocks，用于存储游戏地图的信息。 */
/* 每个元素代表地图上的一个格子，大小为40x40。 */
extern int blocks[40][40];

/* 定义了一个全局数组heads，用于存储三条蛇的头部坐标。 */
/* 每个元素是一个SnakeCoord结构体，包含蛇头的x和y坐标。 */
extern SnakeCoord heads[3];

/* 定义了一个全局变量modern，用于存储游戏的现代模式设置。 */
/* 使用GameModern结构体来管理游戏的各种现代模式设定。 */
extern GameModern modern;

/* 定义了一个全局布尔变量food，用于标记游戏地图上食物的存在与否。 */
/* true表示食物存在，false表示食物不存在。 */
extern _Bool food;


/**
 * 定义一个函数，用于将控制台光标移动到指定的坐标位置
 * 参数x表示目标位置的横坐标
 * 参数y表示目标位置的纵坐标
 */
void GotoXY(int x, int y) {
    // 获取标准输出句柄，用于后续操作控制台输出位置
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

    // 创建一个COORD结构体，用于存储坐标信息
    COORD pos;

    // 设置COORD结构体的横纵坐标为传入的参数值
    pos.X = x;
    pos.Y = y;

    // 设置控制台光标的位置为坐标pos所指定的位置
    SetConsoleCursorPosition(handle, pos);
}

/**
 * 获取胜利者的名字
 *
 * 本函数通过比较三个选手的分数来确定胜利者，并返回胜利者的姓名。
 * 分数最高的选手将被认定为胜利者。如果有两名选手分数相同且最高，则名字在先的选手将被认定为胜利者。
 *
 * @return 返回胜利者的姓名作为字符串。
 */
char *WinnerName(void) {
    // 比较第一个选手的分数是否高于或等于其他两个选手的分数
    if (heads[0].score >= heads[1].score && heads[0].score >= heads[2].score) {
        return heads[0].name;
    }
        // 如果第一个选手的分数不是最高，比较第二个选手的分数是否高于第三个选手的分数
    else if (heads[1].score >= heads[2].score) {
        return heads[1].name;
    }
        // 如果前两个选手的分数都不最高，返回第三个选手的姓名
    else {
        return heads[2].name;
    }
}

/**
 * 函数名称：GetKeyBoard
 * 函数功能：从键盘获取一个字符，无需等待按键释放
 * 返回值：获取到的字符，如果没有按键按下，则返回0
 *
 * 注意：此函数使用了'_kbhit()'和'_getch()'两个非标准库函数，它们通常在Windows环境下可用，
 * 用于检测是否有按键被按下以及获取按键值。
 */
char GetKeyBoard(void) {
    char key = 0; // 初始化变量key，用于存储按键的值
    // 检查是否有按键按下
    if (_kbhit()) {
        key = _getch(); // 如果有按键按下，获取按键值并赋给key
    }
    return key; // 返回按键值，如果没有按下按键，则返回0
}

/**
 * 打印标题栏
 *
 * 该函数用于输出一个具有固定长度的标题栏，标题栏内容为"Gluttonous Snake"，
 * 通过在标题前后打印一定数量的连字符来构成标题栏的边框。
 *
 * 无参数。
 *
 * 无返回值。
 */
void PrintTitle(void) {
    int i;
    // 打印标题栏的上边框
    for (i = 0; i < 34; i++) {
        printf("-");
    }
    // 打印标题内容
    printf("Gluttonous Snake");
    // 打印标题栏的下边框
    for (i = 0; i < 34; i++) {
        printf("-");
    }
    // 换行，为打印后续内容做准备
    printf("\n");
}

// 初始化游戏设置
void Initial(void) {
    // 获取标准输出句柄
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    // 定义并初始化字体信息
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 16;
    cfi.dwFontSize.Y = 24;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy_s(cfi.FaceName, _countof(cfi.FaceName), L"Raster");
    // 设置当前控制台字体
    SetCurrentConsoleFontEx(handle, FALSE, &cfi);

    // 初始化变量用于用户输入验证
    int i, j;
    _Bool flag = 1;
    char str[10];
    // 定义难度和尺寸选项
    char difficulties[4][7] = {"Simple", "Normal", "Hard", "Hell"};
    char sizes[3][7] = {"Small", "Normal", "Large"};

    // 设置控制台文本属性并打印游戏标题
    SetConsoleTextAttribute(handle, YELLOW);
    PrintTitle();
    Sleep(1000);
    system("cls");
    PrintTitle();

    // 提示用户选择游戏难度，并验证输入
    printf("The game has four difficulties:\nSimple, Normal, Hard, Hell.\n");
    printf("The speed of snake and the size of map are different in different difficulties.\n");
    printf("Please choose the difficulty: ");
    while (TRUE) {
        scanf("%s", str);
        switch (str[0]) {
            case 'S': {
                modern.difficulty = 0;
                flag = 0;
                for (i = 1; i < 6; i++) {
                    if (str[i] != difficulties[0][i]) {
                        flag = 1;
                        break;
                    }
                }
                break;
            }
            case 'N': {
                modern.difficulty = 1;
                flag = 0;
                for (i = 1; i < 6; i++) {
                    if (str[i] != difficulties[1][i]) {
                        flag = 1;
                        break;
                    }
                }
                break;
            }
            case 'H': {
                switch (str[1]) {
                    case 'a': {
                        modern.difficulty = 2;
                        flag = 0;
                        for (i = 2; i < 4; i++) {
                            if (str[i] != difficulties[2][i]) {
                                flag = 1;
                                break;
                            }
                        }
                        break;
                    }
                    case 'e': {
                        modern.difficulty = 3;
                        flag = 0;
                        for (i = 2; i < 4; i++) {
                            if (str[i] != difficulties[3][i]) {
                                flag = 1;
                                break;
                            }
                        }
                        break;
                    }
                    default: {
                        break;
                    }
                }
                break;
            }
            default: {
                break;
            }
        }
        if (!flag) {
            break;
        } else {
            system("cls");
            PrintTitle();
            printf("The game has four difficulties:\nSimple, Normal, Hard, Hell.\n");
            printf("The speed of snake and the size of map are different in different difficulties.\n");
            SetConsoleTextAttribute(handle, RED);
            printf("(You enter wrong difficulty. Now please enter again.)\n");
            SetConsoleTextAttribute(handle, YELLOW);
            printf("Please choose the difficulty: ");
        }
    }
    Sleep(500);
    system("cls");
    PrintTitle();

    // 提示用户选择游戏尺寸，并验证输入
    printf("The game has three sizes:\nSmall, Normal, Large.\n");
    printf("Please choose the size: ");
    flag = 1;
    while (TRUE) {
        scanf("%s", str);
        switch (str[0]) {
            case 'S': {
                modern.size = 2;
                flag = 0;
                for (i = 1; i < 5; i++) {
                    if (str[i] != sizes[0][i]) {
                        flag = 1;
                        break;
                    }
                }
                break;
            }
            case 'N': {
                modern.size = 3;
                flag = 0;
                for (i = 1; i < 6; i++) {
                    if (str[i] != sizes[1][i]) {
                        flag = 1;
                        break;
                    }
                }
                break;
            }
            case 'L': {
                modern.size = 4;
                flag = 0;
                for (i = 1; i < 5; i++) {
                    if (str[i] != sizes[2][i]) {
                        flag = 1;
                        break;
                    }
                }
                break;
            }
            default: {
                break;
            }
        }
        if (!flag) {
            break;
        } else {
            system("cls");
            PrintTitle();
            printf("The game has three sizes:\nSmall, Normal, Large.\n");
            SetConsoleTextAttribute(handle, RED);
            printf("(You enter wrong size. Now please enter again.)\n");
            SetConsoleTextAttribute(handle, YELLOW);
            printf("Please choose the size: ");
        }
    }
    Sleep(500);
    system("cls");
    PrintTitle();

    // 提示用户选择玩家数量，并验证输入
    printf("The game allow at most three players.\n");
    printf("How many players(arabic numeral): ");
    while (TRUE) {
        scanf("%s", str);
        if (str[0] == '1' || str[0] == '2' || str[0] == '3') {
            break;
        }
        else {
            Sleep(500);
            system("cls");
            PrintTitle();
            printf("The game allow at most three players.\n");
            SetConsoleTextAttribute(handle, RED);
            printf("(You enter wrong number. Now please enter again.)\n");
            SetConsoleTextAttribute(handle, YELLOW);
            printf("How many players(arabic numeral): ");
        }
    }
    modern.multiplayer = str[0] - '0';
    Sleep(500);
    system("cls");
    PrintTitle();

    // 提示用户输入玩家名称
    printf("Now please enter the name%s of player%s.\n", (modern.multiplayer == 1) ? "" : "s", (modern.multiplayer == 1) ? "" : "s");
    for (i = 0; i < modern.multiplayer; i++) {
        printf("Please enter the name of player %d: ", i + 1);
        scanf("%s", heads[i].name);
    }
    Sleep(500);
    system("cls");

    // 根据玩家数量和选择的游戏尺寸设置游戏区域大小
    modern.height = modern.size * 9;
    modern.width = modern.height;
    // 初始化游戏区域
    for (i = 0; i < modern.height; i++) {
        for (j = 0; j < modern.width; j++) {
            if (i * j == 0 || i == modern.height - 1 || j == modern.width - 1) {
                blocks[i][j] = -2;
            }
            else {
                blocks[i][j] = -1;
            }
        }
    }
    // 初始化玩家信息
    for (i = 0; i < 3; i++) {
        heads[i].score = heads[i].alive = 0;
    }
    for (i = 0; i < modern.multiplayer; i++) {
        heads[i].x = heads[i].t_x = heads[i].y = heads[i].t_y = (modern.height / (modern.multiplayer + 1)) * (i + 1);
        blocks[heads[i].x][heads[i].y] = i;
        heads[i].alive = 1;
        heads[i].speed = 9 - modern.difficulty;
        heads[i].direct = 'l';
    }
    food = 0;
    PrintTitle();
    printf("Now Game Start!");
    Sleep(1000);
    system("cls");

    // 调整控制台字体大小和颜色以开始游戏
    SetConsoleTextAttribute(handle, WHITE);
    cfi.dwFontSize.X = 15;
    cfi.dwFontSize.Y = 15;
    SetCurrentConsoleFontEx(handle, FALSE, &cfi);
}

char KeyProcess(char key) {
    switch (key) {
        case 'p': {
            printf("Now you paused the game\nPlease press any key to continue!");
            _getch();
            system("cls");
            key = 0;
            break;
        }
        case 'q': {
            printf("Are you sure you want to quit the game?\nPress \'q\' again to quit!\nPress any other key to continue!");
            key = _getch();
            system("cls");
            key = (key == 'q') ? 'q' : 0;
            break;
        }
        case 'w': {
            if (heads[0].direct != 'd') {
                heads[0].direct = 'u';
            }
            key = 0;
            break;
        }
        case 's': {
            if (heads[0].direct != 'u') {
                heads[0].direct = 'd';
            }
            key = 0;
            break;
        }
        case 'a': {
            if (heads[0].direct != 'r') {
                heads[0].direct = 'l';
            }
            key = 0;
            break;
        }
        case 'd': {
            if (heads[0].direct != 'l') {
                heads[0].direct = 'r';
            }
            key = 0;
            break;
        }
        default: {
            if (modern.multiplayer == 1) {
                key = 0;
                break;
            }
            switch (key) {
                case 'y': {
                    if (heads[1].direct != 'd') {
                        heads[1].direct = 'u';
                    }
                    key = 0;
                    break;
                }
                case 'h': {
                    if (heads[1].direct != 'u') {
                        heads[1].direct = 'd';
                    }
                    key = 0;
                    break;
                }
                case 'g': {
                    if (heads[1].direct != 'r') {
                        heads[1].direct = 'l';
                    }
                    key = 0;
                    break;
                }
                case 'j': {
                    if (heads[1].direct != 'l') {
                        heads[1].direct = 'r';
                    }
                    key = 0;
                    break;
                }
                default: {
                    if (modern.multiplayer == 2) {
                        key = 0;
                        break;
                    }
                    switch (key) {
                        case 'o': {
                            if (heads[2].direct != 'd') {
                                heads[2].direct = 'u';
                            }
                            key = 0;
                            break;
                        }
                        case 'l':
                        {
                            if (heads[2].direct != 'u')
                                heads[2].direct = 'd';
                            key = 0;
                            break;
                        }
                        case 'k': {
                            if (heads[2].direct != 'r') {
                                heads[2].direct = 'l';
                            }
                            key = 0;
                            break;
                        }
                        case ';': {
                            if (heads[2].direct != 'l') {
                                heads[2].direct = 'r';
                            }
                            key = 0;
                            break;
                        }
                    }
                    break;
                }
            }
            break;
        }
    }
    return key;
}
/**
 * 打印游戏屏幕
 * 该函数负责在控制台上渲染游戏的当前状态，包括游戏的标题、版本信息、作者、游戏难度、玩家信息以及玩家的得分。
 * 它通过设置不同的文本属性来实现彩色输出，使得信息更加清晰，同时根据游戏的配置和状态来决定打印哪些信息。
 */
void PrintScreen(void) {
    // 获取标准输出句柄，用于后续设置文本属性和打印信息
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    int i, j;
    // 定义游戏难度级别字符串数组
    char difficulties[4][7] = {"Simple", "Normal", "Hard", "Hell"};

    // 设置文本属性为淡黄色，用于打印标题
    SetConsoleTextAttribute(handle, FAINT_YELLOW);
    PrintTitle();

    // 遍历游戏地图的每一行和每一列，根据地图块的类型设置不同的文本属性并打印相应的字符
    for (i = 0; i < modern.height; i++) {
        for (j = 0; j < modern.width; j++) {
            switch (blocks[i][j]) {
                case -1: {
                    printf(" "); // 打印空格，表示没有障碍物
                    break;
                }
                case -2: {
                    SetConsoleTextAttribute(handle, PURPLE);
                    printf("#"); // 打印紫色的墙
                    break;
                }
                case -3: {
                    SetConsoleTextAttribute(handle, YELLOW);
                    printf("*"); // 打印黄色的特殊障碍物
                    break;
                }
                default: {
                    // 根据块的类型设置颜色并打印相应的字符
                    switch (blocks[i][j] % 3) {
                        case 0: {
                            SetConsoleTextAttribute(handle, RED);
                            printf(blocks[i][j] == 0 ? "@" : "O"); // 红色的玩家或食物
                            break;
                        }
                        case 1: {
                            SetConsoleTextAttribute(handle, GREEN);
                            printf(blocks[i][j] == 1 ? "@" : "O"); // 绿色的玩家或食物
                            break;
                        }
                        case 2: {
                            SetConsoleTextAttribute(handle, BLUISH);
                            printf(blocks[i][j] == 2 ? "@" : "O"); // 蓝色的玩家或食物
                            break;
                        }
                    }
                    break;
                }
            }
        }
        // 在每一行的末尾打印两个空格，用于后续打印游戏信息
        SetConsoleTextAttribute(handle, WHITE);
        printf("  ");
        SetConsoleTextAttribute(handle, FAINT_YELLOW);

        // 根据行号打印不同的游戏信息，如版本、作者、下载链接、地图大小、游戏难度、玩家等
        switch (i) {
            case 0: {
                printf("Game Version: v0.3.1d");
                break;
            }
            case 1: {
                printf("Author: YorkyifanWei.");
                break;
            }
            case 2: {
                printf("(You can download history versions on Github)");
                break;
            }
            case 3: {
                printf("Map Size: %d x %d", modern.height, modern.width);
                break;
            }
            case 4: {
                printf("Game Difficulty: %s", difficulties[modern.difficulty]);
                break;
            }
            case 5: {
                // 打印玩家名字和状态
                printf("Players: ");
                for (j = 0; j < modern.multiplayer; j++) {
                    if (heads[j].alive == 0) {
                        SetConsoleTextAttribute(handle, GREY);
                    }
                    else {
                        SetConsoleTextAttribute(handle, (j == 0) ? RED : ((j == 1) ? GREEN : BLUISH));
                    }
                    printf("%s", heads[j].name);
                    if (j != modern.multiplayer - 1) {
                        printf(", ");
                    }
                }
                break;
            }
            case 6: {
                // 打印玩家得分
                if (heads[0].alive) {
                    SetConsoleTextAttribute(handle, RED);
                }
                else {
                    SetConsoleTextAttribute(handle, GREY);
                }
                printf("%s: %d", heads[0].name, heads[0].score);
                break;
            }
            default: {
                // 处理额外的玩家得分显示
                if (modern.multiplayer >= 2) {
                    if (i == 7) {
                        if (heads[1].alive) {
                            SetConsoleTextAttribute(handle, GREEN);
                        }
                        else {
                            SetConsoleTextAttribute(handle, GREY);
                        }
                        printf("%s: %d", heads[1].name, heads[1].score);
                    }
                    else if (modern.multiplayer == 3 && i == 8) {
                        if (heads[2].alive) {
                            SetConsoleTextAttribute(handle, BLUISH);
                        }
                        else {
                            SetConsoleTextAttribute(handle, GREY);
                        }
                        printf("%s: %d", heads[2].name, heads[2].score);
                    }
                }
                break;
            }
        }
        printf("\n"); // 换行，准备打印下一行信息
    }

    // 打印游戏控制信息
    SetConsoleTextAttribute(handle, WHITE);
    printf("Press \'p\' to pause, \'q\' to quit.\n");
    SetConsoleTextAttribute(handle, FAINT_YELLOW);
    printf("Key Configuration:\n");
    SetConsoleTextAttribute(handle, RED);
    printf("P1: up:\'w\' down:\'s\' left:\'a\' right:\'d\'\n");
    if (modern.multiplayer > 1) {
        SetConsoleTextAttribute(handle, GREEN);
        printf("P2: up:\'y\' down:\'h\' left:\'g\' right:\'j\'\n");
        if (modern.multiplayer == 3) {
            SetConsoleTextAttribute(handle, BLUISH);
            printf("P3: up:\'o\' down:\'l\' left:\'k\' right:\';\'\n");
        }
    }
    SetConsoleTextAttribute(handle, WHITE);
}

/**
 * 控制蛇移动的函数
 * @param player_code 蛇玩家的代码，用于区分不同玩家
 */
void SnakeMove(int player_code) {
    // 计算蛇头的下一个位置
    int x_next = heads[player_code].x + (heads[player_code].direct == 'd') - (heads[player_code].direct == 'u');
    int y_next = heads[player_code].y + (heads[player_code].direct == 'r') - (heads[player_code].direct == 'l');

    // 检查蛇是否撞墙或自身
    int hit = SnakeHit(player_code);

    // 获取当前蛇尾的块类型
    int tail = blocks[heads[player_code].t_x][heads[player_code].t_y];

    // 如果撞墙，设置蛇为死亡状态，并移除所有属于该玩家的蛇块
    if (hit == -1) {
        heads[player_code].alive = FALSE;
        for (int i = 0; i < modern.height; i++) {
            for (int j = 0; j < modern.width; j++) {
                if (blocks[i][j] >= 0 && blocks[i][j] % 3 == player_code) {
                    blocks[i][j] = -1;
                }
            }
        }
    }
        // 如果吃到食物，增加分数
    else if (hit == 1) {
        heads[player_code].score += 1;
    }

    // 如果没有撞墙，更新蛇的位置和块类型
    if (hit >= 0) {
        _Bool flag = !hit;
        for (int i = 0; i < modern.height; i++) {
            for (int j = 0; j < modern.width; j++) {
                if (blocks[i][j] >= 0 && blocks[i][j] % 3 == player_code) {
                    blocks[i][j] += 3;
                }
                // 如果是新尾部，则更新蛇尾的位置
                if (flag && hit == 0 && blocks[i][j] == tail) {
                    blocks[heads[player_code].t_x][heads[player_code].t_y] = -1;
                    heads[player_code].t_x = i;
                    heads[player_code].t_y = j;
                }
            }
        }
        // 移动蛇头到新位置
        heads[player_code].x = x_next;
        heads[player_code].y = y_next;
        // 在新位置放置蛇头块
        blocks[x_next][y_next] = player_code;
    }

    // 更新蛇尾的块类型，并根据蛇尾类型调整蛇的速度
    tail = blocks[heads[player_code].t_x][heads[player_code].t_y];
    tail /= 15;
    if (tail > 5) {
        tail = 5;
    }
    heads[player_code].speed = 9 - modern.difficulty - tail;
}

/**
 * 判断蛇是否撞墙或吃到食物。
 *
 * @param player_code 蛇玩家的代码，用于确定蛇头的位置和方向。
 * @return 不同的返回值代表不同的情况：0 表示没有撞墙，-1 表示撞墙，1 表示吃到食物。
 */
int SnakeHit(int player_code) {
    // 根据蛇头当前的x坐标、y坐标和方向，计算蛇头下一步的坐标
    int x_next = heads[player_code].x + (heads[player_code].direct == 'd') - (heads[player_code].direct == 'u');
    int y_next = heads[player_code].y + (heads[player_code].direct == 'r') - (heads[player_code].direct == 'l');

    // 根据下一步蛇头所在的位置，判断结果
    switch (blocks[x_next][y_next]) {
        case -1: {
            // 蛇头下一步的位置是墙壁，返回0表示撞墙
            return 0;
        }
        case -2: {
            // 蛇头下一步的位置是不可通过的障碍，返回-1表示撞墙
            return -1;
        }
        case -3: {
            // 蛇头下一步的位置是食物，将食物标记为已吃掉并返回1表示吃到食物
            food = 0;
            return 1;
        }
        default: {
            // 蛇头下一步的位置是空地，但存在其他逻辑上的问题，返回-1表示异常情况
            return -1;
        }
    }
}

/**
 * @brief 随机刷新食物的位置
 *
 * 本函数用于在地图上随机选择一个位置刷新食物。为了避免食物刷新在地图边缘
 * 或已被占用的位置，通过循环直至找到合适的位置。食物刷新后，相应位置的
 * blocks 数组被标记为特定值，同时将全局变量 food 设置为 1，表示有食物存在。
 */
void FoodRefresh(void) {
    // 初始化食物的潜在坐标
    int f_x, f_y;

    // 初始化随机数生成器，确保每次运行时的随机序列不同
    srand((int)time(0));

    do {
        // 随机生成食物的 x 和 y 坐标
        f_x = rand() % modern.height;
        f_y = rand() % modern.width;
    } while (f_x * f_y == 0 || f_x == modern.height - 1 || f_y == modern.width - 1 || blocks[f_x][f_y] != -1);

    // 在生成的位置放置食物，用特定的值-3标记
    blocks[f_x][f_y] = -3;

    // 设置全局变量 food，表示食物已刷新
    food = 1;
}
