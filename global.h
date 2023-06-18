#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED
#define GAME_TERMINATE -1
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#define NUM_CACTUS 50 // 數字隨你改

// note that you can't assign initial value here!
extern const float FPS;
extern const int WIDTH;
extern const int HEIGHT;
extern int score;
extern int LEVEL;
//extern const int NUM_CATUS;
extern bool key_state[ALLEGRO_KEY_MAX];
extern bool judge_to_game;
extern bool judge_to_info;
extern bool judge_to_end;
extern bool judge_to_finished_game;
extern bool render;
struct Background{
	float x;
	float y;
	float velX;
	float velY;
	int dirX;
	int dirY;
	int width;
	int height;
	ALLEGRO_BITMAP *image;
};
// background component
extern struct Background FLOOR;
extern struct Background C1;
extern struct Background C2;

// game object: catus, dino, (addpoint)
// catus component
struct Cactus{
	int ID;
	int x;
	int y;
	bool live;
	int speed;
	int boundy_x;
	int boundy_y;
	int type;
	ALLEGRO_BITMAP *image;
};
extern struct Cactus cactus[NUM_CACTUS];

typedef struct character{
   int y,jump_times,anime_time,anime,highest,width,height,life;
   bool state,just_jump,space;
    ALLEGRO_BITMAP *img_run[2];
    ALLEGRO_BITMAP *img_jump;
    ALLEGRO_BITMAP *img_die;
    ALLEGRO_SAMPLE_INSTANCE *sound_jump;
    ALLEGRO_SAMPLE_INSTANCE *sound_die;
    int boundy_x, boundy_y;
	int x;
}Character;
extern Character dino;

extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_TIMER *fps;
#endif