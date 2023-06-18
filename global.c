#include "global.h"

// variables for global usage
enum{low = 200, medium = 500, tough = 10000};
const float FPS = 60.0;
const int WIDTH = 1400;
const int HEIGHT = 450;
const int NUM_CATUS = 10;

ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *fps = NULL;
bool key_state[ALLEGRO_KEY_MAX] = {false};
bool judge_to_info = false;
bool judge_to_game = false;
bool judge_to_end = false;
bool judge_to_finished_game = false;
bool render = false;
int score = 0;
int LEVEL = tough;


struct Background FLOOR;
struct Background C1;
struct Background C2;

// struct Dinosaur DINO;
struct Cactus cactus[NUM_CACTUS];
Character dino;
