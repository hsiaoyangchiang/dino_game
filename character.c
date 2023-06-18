#include "character.h"
#include "scene.h"

enum IDS{PLAYER = 0, ENEMY};
ALLEGRO_BITMAP *img_cactus1 = NULL;
ALLEGRO_BITMAP *img_cactus2 = NULL;
ALLEGRO_BITMAP *img_cactus3 = NULL;
ALLEGRO_BITMAP *img_cactus4 = NULL;


//struct Cat *ptr[2];

void object_init(){
    img_cactus1 = al_load_bitmap("./asset/cactus1.png");
    img_cactus2 = al_load_bitmap("./asset/cactus2.png");
    //img_cactus3 = al_load_bitmap("./asset/catus1.png");
    //img_cactus4 = al_load_bitmap("./asset/catus2.png");

    cactus_init(cactus, NUM_CACTUS, img_cactus1, img_cactus2);
    // cactus_init(&cactus, NUM_CATUS, img_cactus2);
}
void cactus_init(struct Cactus *c, int size, ALLEGRO_BITMAP *img1, ALLEGRO_BITMAP *img2){
    printf("cactus init\n");
    for(int i = 0; i < size; i++)
	{
        //c[i].ID = ENEMY;
		c[i].ID = ENEMY;
        // c[i].x = 120+i;
        // c[i].y = 300-99;
		c[i].live = false;
		c[i].speed = 5;
		c[i].boundy_x = 18;
		c[i].boundy_y = 18;
        if(i%2) {
			c[i].type = 1;
			c[i].image = img1;
		}
        else {
			c[i].image = img2;
			c[i].type =0;
		}
        // printf("%p\n", c[i].image);
	}
}
void cactus_draw(struct Cactus *c, int size){
	for(int i = 0; i < size; i++){
		if(c[i].live){
			//al_draw_filled_circle(  20, al_map_rgb(255, 0, 0));
            al_draw_bitmap(c[i].image, c[i].x, c[i].y, 0);
            // printf("%p\n", c[i].image);
		}
	}
}
void cactus_start(struct Cactus *c, int size){
	for(int i = 0; i < size; i++)
	{
		if(!c[i].live)
		{
			if(rand() % 6500 == 0)
			{
				c[i].live = true;
				c[i].x = WIDTH;
				if(c[i].type){
					c[i].y = 300-65;
				}else{
					c[i].y = 300-85;
				}
                //printf("%d\n", c[i].x);
                //printf("%d\n", c[i].y);
				break;
			}
		}
	}
}
void cactus_update(struct Cactus *c, int size)
{
	for(int i = 0; i < size; i++){
		if(c[i].live)
		{
			c[i].x -= c[i].speed;

		}
	}
}

void cactus_collide(struct Cactus *c, int size){
    for(int i = 0; i < size; i++){
		if(c[i].live)
		{
			if(c[i].x -10 <  dino.width && 300-al_get_bitmap_height(c[i].image) < dino.y+dino.height&& c[i].x+al_get_bitmap_width(c[i].image)< 5)
				// c[i].x + c[i].boundy_x > p[i].boundy_x &&
				// c[i].y - c[i].boundy_y < p[i].y + p[i].boundy_y &&
				// c[i].y + c[i].boundy_y > p[i].y - p[i].boundy_y)
			{
				dino.life = 0;
                //printf("hit the cactus\n");
			}
		}
	}
}



void cactus_destroy(){
    al_destroy_bitmap(img_cactus1);
    al_destroy_bitmap(img_cactus2);
}


