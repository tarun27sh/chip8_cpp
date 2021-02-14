/*
 * Ncurses based graphics
 */ 
#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_
#include<cstdarg>
#include<ncurses.h>

struct SpriteData {
    uint16_t x0;
    uint16_t y0;
    uint16_t height;
    uint16_t width;
    char     *data;
    SpriteData(uint16_t x0, uint16_t y0, uint16_t height, uint16_t width, char *data) 
    : x0(x0), y0(y0), height(height), width(width), data{data}  {}
};
struct WindowObject {
    int starty;
    int startx;
    int height;
    int width;
    int color_fg;
    int color_bg;
    int color_pair_no;
    int cur_window_row;
    WindowObject(int starty, int startx, int height, int width, int color_fg, int color_bg, int color_pair_no, int cur_window_row);
    WindowObject();
    ~WindowObject();
    WINDOW *win;
    void init(int starty, int startx, int height, int width, int color_fg, int color_bg, int color_pair_no, int cur_window_row);
    void createCustomWindow();
    void ncurses_init();
    void ncurses_cleanup();
    void ncurses_clear_window();
    void draw_sprite_on_window(const SpriteData& spd);
    void trace(const char *fmt, ...);
};

#endif  // _GRAPHICS_H_
