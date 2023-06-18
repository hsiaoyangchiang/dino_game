#include "global.h"

// 這裡留給dino
// void dino_init();
// void dino_process(ALLEGRO_EVENT event);
// void dino_update();
// void dino_draw();
// void dino_destory();
// catus
// bool keys[5] = {false, false, false, false, false};
void object_init();
void cactus_init(struct Cactus *c, int size, ALLEGRO_BITMAP *img1, ALLEGRO_BITMAP *img2);
void cactus_draw(struct Cactus *c, int size);
void cactus_start(struct Cactus *c, int size);
void cactus_update(struct Cactus *c, int size);
void cactus_collide(struct Cactus *c, int size);
void cactus_destroy();


// dino
// void dino_init();
// void dino_process(ALLEGRO_EVENT event);
// void dino_update();
// void dino_draw();
// void dino_destory();
