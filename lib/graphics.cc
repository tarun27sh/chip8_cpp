/* creates two windows
 * 1. main window for chip8 graphics
 * 2. smaller debug window ( can it scroll)?
 * +--------------------+
 * |                    |
 * |       64x32        |
 * |      graphics      |
 * +--------------------+
 * |       64x5         |
 * |      debug         |
 * +--------------------+
 */ 

#include"graphics.h"
#include<assert.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<ncurses.h>
#include<fstream>
#include<iostream>
#include<vector>

using namespace std;

WindowObject::WindowObject() {
}

WindowObject::~WindowObject() {
}
void
WindowObject::init(int starty, int startx, int height, int width, int color_fg, int color_bg, int color_pair_no, int cur_window_row)
{
    this->starty = starty;
    this->startx = startx;
    this->height = height;
    this->width = width;
    this->color_fg = color_fg;
    this->color_bg = color_bg;
    this->color_pair_no = color_pair_no;
    this->cur_window_row = cur_window_row; 
}
WindowObject::WindowObject(int starty, int startx, int height, int width, int color_fg, int color_bg, int color_pair_no, int cur_window_row):
starty{starty}, startx{startx}, height{height}, width{width}, color_fg{color_fg}, color_bg{color_bg}, color_pair_no{color_pair_no}, cur_window_row{cur_window_row} 
{
//    ncurses_init(&);
}


void
WindowObject::createCustomWindow() {
    this->win = newwin(height, width, starty, startx);
    init_pair(color_pair_no, color_fg, color_bg);
    wattron(this->win, COLOR_PAIR(color_pair_no));
    box(win, 0 , 0);
    wrefresh(this->win);
}

vector<WindowObject> G_win(2);
ofstream  G_log_file;



void convert_to_binary_string(char in_num, char* buf)
{
    uint8_t num = (uint8_t )in_num;
#define PIXEL_ON_CHAR "#"
#define PIXEL_OFF_CHAR " "
#define FORMAT_STRING "%s%s%s%s%s%s%s%s"

    snprintf(buf, 9, FORMAT_STRING, 
            (num & 1<<7)>>7? PIXEL_ON_CHAR: PIXEL_OFF_CHAR,
            (num & 1<<6)>>6? PIXEL_ON_CHAR: PIXEL_OFF_CHAR,
            (num & 1<<5)>>5? PIXEL_ON_CHAR: PIXEL_OFF_CHAR,
            (num & 1<<4)>>4? PIXEL_ON_CHAR: PIXEL_OFF_CHAR,
            (num & 1<<3)>>3? PIXEL_ON_CHAR: PIXEL_OFF_CHAR,
            (num & 1<<2)>>2? PIXEL_ON_CHAR: PIXEL_OFF_CHAR,
            (num & 1<<1)>>1? PIXEL_ON_CHAR: PIXEL_OFF_CHAR,
            (num & 1<<0)>>0? PIXEL_ON_CHAR: PIXEL_OFF_CHAR
            );
}


// change this to ostream operator??
void 
WindowObject::draw_sprite_on_window(const SpriteData& spd)
{
    char sprite_row;
    char sprite_row_str[30];
    for(int i=0; i<spd.height; ++i) {
        sprite_row = spd.data[i];
        convert_to_binary_string(sprite_row, sprite_row_str);
        mvwprintw(this->win, spd.x0+i, spd.y0,sprite_row_str); 
        //mvwprintw(this->win, spd.y0, spd.x0 + i,sprite_row_str); 
        memset(sprite_row_str, 0, sizeof(sprite_row_str));
    }
    wrefresh(this->win);
}
void 
WindowObject::trace(const char *fmt, ...)
{
    va_list ap;
    int ret_size=0;
    va_start(ap, fmt);
    // s = va_arg(ap, char*);
    // use ap

    int cur_row = cur_window_row;
    char buf[60] = {0};
    snprintf(buf, 10, "[%d]", cur_row);  // adds NULL, $7 = "[2]\000\000reading rom 10"
    int offset = strlen(buf);
    ret_size = vsnprintf(buf+offset, sizeof(buf)-offset, fmt, ap);
    assert(ret_size>0 && "vnsprintf failed");
    va_end(ap);
    if (cur_row%(height - 2) == 0 ) {
        werase(win);
        box(win, 0 , 0);
    }
    mvwprintw(win, cur_row%(height-2)+1, 1, buf); 
    wrefresh(win);
    cur_window_row++;
    G_log_file << buf << endl;
}

void 
WindowObject::ncurses_clear_window()
{
    werase(win);
    box(win, 0 , 0);
    wrefresh(win);

}
void 
WindowObject::ncurses_cleanup()
{
    endwin();
    G_log_file.close();
}

void 
WindowObject::ncurses_init() 
{
    initscr();            /* Start curses mode                */
    start_color();        /* Start the color functionality    */
    //attron(COLOR_PAIR(1));
    cbreak();             /* Line buffering disabled, Pass on
                           * every thing to me               */
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
    // open trace file
    G_log_file.open("./logs.txt");
}
