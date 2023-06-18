#include "dino.h"
#include "scene.h"

// the state of character
// typedef struct character{
//    int y,jump_times,anime_time,anime,highest,width,height,life;
//    bool state,just_jump,space;
//     ALLEGRO_BITMAP *img_run[2];
//     ALLEGRO_BITMAP *img_jump;
//     ALLEGRO_BITMAP *img_die;
//     ALLEGRO_SAMPLE_INSTANCE *sound_jump;
//     ALLEGRO_SAMPLE_INSTANCE *sound_die;
//     int boundy_x, boundy_y;
// }Character;
// Character dino;

ALLEGRO_SAMPLE *sound_dino_jump=NULL;
ALLEGRO_SAMPLE *sound_dino_die=NULL;

void dino_init(){

    dino.img_run[0]=al_load_bitmap("./asset/d2.png");
    dino.img_run[1]=al_load_bitmap("./asset/d3.png");
    dino.img_jump= al_load_bitmap("./asset/d1.png");
    dino.img_die= al_load_bitmap("./asset/d4.png");

    sound_dino_jump = al_load_sample("./sound/jump.wav");
    al_reserve_samples(20);
    dino.sound_jump = al_create_sample_instance(sound_dino_jump);
    // Loop the song until the display closes
    al_set_sample_instance_playmode(dino.sound_jump, ALLEGRO_PLAYMODE_ONCE);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(dino.sound_jump, al_get_default_mixer());
    // set the volume of instance
    al_set_sample_instance_gain(dino.sound_jump, 2) ;

    sound_dino_die = al_load_sample("./sound/die.wav");
    al_reserve_samples(20);
    dino.sound_die = al_create_sample_instance(sound_dino_die);
    // Loop the song until the display closes
    al_set_sample_instance_playmode(dino.sound_die, ALLEGRO_PLAYMODE_ONCE);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(dino.sound_die, al_get_default_mixer());
    // set the volume of instance
    al_set_sample_instance_gain(dino.sound_die, 2) ;

    dino.width = al_get_bitmap_width(dino.img_run[0]);
    dino.height = al_get_bitmap_height(dino.img_run[0]);
    dino.boundy_x = 2;
    dino.state=true;
    dino.highest=300-dino.height;
    dino.anime = 0;
    dino.anime_time = 30;
    dino.x = 10;
    dino.y=300-dino.height;
    dino.life=true;
    dino.just_jump=false;
    dino.space=false;
}
void dino_process(ALLEGRO_EVENT event){
    if( event.type == ALLEGRO_EVENT_TIMER ){
        if( event.timer.source == fps ){
            dino.anime++;
            dino.anime %= dino.anime_time;
        }
    // process the keyboard event
    }else if( event.type == ALLEGRO_EVENT_KEY_DOWN ){
        if (event.keyboard.keycode == ALLEGRO_KEY_SPACE){
                dino.anime = 0;
                dino.space=true;
         }
        // key_state[event.keyboard.keycode] = true;
        // dino.anime = 0;
        // dino.space=true;
    }else if( event.type == ALLEGRO_EVENT_KEY_UP ){
        key_state[event.keyboard.keycode] = false;
    }
    
}
void dino_update(){
        if(dino.just_jump==true){
            dino.just_jump=false;
        }
        if(dino.space==true){
                dino.space=false;
                puts("detect space!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
                if(dino.highest>180-dino.height){
                    dino.highest=180-dino.height;
                    dino.just_jump=true;
                    dino.state=false;
                }else if(dino.highest==180-dino.height){
                    dino.highest=dino.y-dino.height;
                    dino.just_jump=true;
                    dino.state=false;
                }
        }
        if(dino.y<=dino.highest+8){
                dino.state=true;
        }
        if(dino.state==false&&dino.y>dino.highest){
            dino.y-=8;
        }else if(dino.state==true&&dino.y<300-dino.height){
            dino.y+=8;
            if(dino.y==300-dino.height){
                dino.highest=300-dino.height;
            }
        }if(dino.life == 0){
            judge_to_end = true;     
        }
        printf("%d\n", dino.life);
}
void dino_draw(){
   if(dino.life==true){
        if(dino.y<300-dino.height){
            al_draw_bitmap(dino.img_jump, 10, dino.y, 0);
            if(dino.just_jump==true){
                al_play_sample_instance(dino.sound_jump);
            }
        }else if( dino.anime < dino.anime_time/2 ){
            al_draw_bitmap(dino.img_run[0],10, dino.y, 0);
        }else{
            al_draw_bitmap(dino.img_run[1],10, dino.y, 0);
        }
   }else{
        al_draw_bitmap(dino.img_die,10, dino.y, 0);
        al_play_sample_instance(dino.sound_die);
   }
}

void dino_destory(){
    al_destroy_bitmap(dino.img_run[0]);
    al_destroy_bitmap(dino.img_run[1]);
    al_destroy_bitmap(dino.img_jump);
    al_destroy_bitmap(dino.img_die);
    al_destroy_sample_instance(dino.sound_die);
    al_destroy_sample_instance(dino.sound_jump);
    //al_destroy_sample_instance(sound_dino_jump);
    //al_destroy_sample_instance(sound_dino_die);
}
