#include "terminal.h"

// 设置控制台颜色的函数，使用256色模式
void terminal::setColor(Color color, bool isForeground)
{
    // 根据是否设置为前景色，选择相应的 ANSI escape code
    std::cout << "\033[" << (isForeground ? 38 : 48) << ";5;" << static_cast<int>(color) << 'm';
}

// 设置控制台样式的函数
void terminal::setStyle(Style style)
{
    std::cout << "\033[" << static_cast<int>(style) << 'm';
}

// 设置光标位置的函数
void terminal::setCursor(int row, int col)
{
    std::cout << "\033[" << row << ';' << col << 'H';
}

// 隐藏光标的函数
void terminal::hideCursor()
{
    std::cout << "\033[?25l";
}

// 显示光标的函数
void terminal::showCursor()
{
    std::cout << "\033[?25h";
}

// 清屏的函数
void terminal::clearScreen()
{
    std::cout << "\033[2J";
}

// 重置控制台的函数
void terminal::reset()
{
    std::cout << "\033[0m";
}

// 绘制计时时间
void terminal::drawTick(int64_t minutes, int64_t seconds, int64_t milliseconds)
{
    std::cout << std::setfill('0')
              << std::setw(2) << minutes << ":"
              << std::setw(2) << seconds << ":"
              << std::setw(3) << milliseconds
              << std::flush;
}