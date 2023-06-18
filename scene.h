#include "global.h"
#include "character.h"


void menu_init();
void menu_process(ALLEGRO_EVENT event);
void start_game_process(ALLEGRO_EVENT event);
//void game_scene_process(ALLEGRO_EVENT event);

void menu_draw();
void info_draw();
void menu_destroy();
void info_destroy();

void InitBackground(struct Background *back, float x, float y, float velx, float vely, int width, int height, int dirX, int dirY, ALLEGRO_BITMAP *image);
void UpdateBackground(struct Background *back);
void DrawBackground(struct Background *back);

void game_scene_init();
void game_scene_draw();
void game_scene_destroy();

void end_game_init();
void end_game_process(ALLEGRO_EVENT event);
void end_game_draw();
void end_scene_destroy();
