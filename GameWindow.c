#include "GameWindow.h"

bool draw = false;
int window = 1;
int status = 0;
// window 1 = menu
// window 2 = info
// window 3 = game
// window 4 = end

const char *title = "Chrome恐龍遊戲";

// ALLEGRO Variables
ALLEGRO_DISPLAY* display = NULL;
ALLEGRO_SAMPLE *song=NULL;
ALLEGRO_SAMPLE_INSTANCE *sample_instance;

int Game_establish() {
    int msg = 0;

    game_init();
    game_begin();

    while ( msg != GAME_TERMINATE ) {
        msg = game_run();
        if ( msg == GAME_TERMINATE )
            printf( "Game Over\n" );
    }

    game_destroy();
    return 0;
}

void game_init() {
    printf( "Game Initializing...\n" );
    al_init();
    // init audio
    al_install_audio();
    al_init_acodec_addon();
    // Create display
    display = al_create_display(WIDTH, HEIGHT);
    // create event queue
    event_queue = al_create_event_queue();
    // Initialize Allegro settings
    al_set_window_position(display, 0, 0);
    al_set_window_title(display, title);
    al_init_primitives_addon();

    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon(); // initialize the ttf (True Type Font) addon
    al_init_image_addon(); // initialize the image addon
    al_init_acodec_addon(); // initialize acodec addon

    al_install_keyboard(); // install keyboard event
    al_install_mouse();    // install mouse event
    al_install_audio();    // install audio event
    // Register event
    al_register_event_source(event_queue, al_get_display_event_source( display ));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    fps  = al_create_timer( 1.0 / FPS );
    al_register_event_source(event_queue, al_get_timer_event_source( fps )) ;
    // initialize the icon on the display
    // 這裡應該要放恐龍的display loading?
    //***********************************************************************
    dino_init();
}

void game_begin() {
    //Load sound
    song = al_load_sample("./sound/hello.wav");
    al_reserve_samples(20);
    sample_instance = al_create_sample_instance(song);
    // Loop the song until the display closes
    al_set_sample_instance_playmode(sample_instance, ALLEGRO_PLAYMODE_LOOP);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(sample_instance, al_get_default_mixer());
    // set the volume of instance
    al_set_sample_instance_gain(sample_instance, 1) ;
    al_play_sample_instance(sample_instance);
    al_start_timer(fps);
    //initialize the menu before entering the loop
    menu_init();
}

int game_run() {
    int error = 0;
    if(draw){
        game_draw();
        draw = false;
    }
    if (!al_is_event_queue_empty(event_queue) ) {
        error = process_event();
    }
    return error;
}

int process_event(){
    // Request the event
    ALLEGRO_EVENT event;
    al_wait_for_event(event_queue, &event);
    // process the event of other component
    if( window == 1 ){
        menu_process(event);
        start_game_process(event);
    }if( window == 2 ){
        start_game_process(event);
    }if( window == 3 ){
        //end_game_process(event);
        //*************************************************************
        dino_process(event);
    }if(window == 4){
        if (event.type == ALLEGRO_EVENT_KEY_UP){
            if (event.keyboard.keycode == ALLEGRO_KEY_SPACE){
                return GAME_TERMINATE;
            }
        }
    }

    // Shutdown our program
    if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
        return GAME_TERMINATE;
    }

    else if(event.type == ALLEGRO_EVENT_TIMER){
        if(event.timer.source == fps){
            draw = true;
        } 
        UpdateBackground(&FLOOR);
        UpdateBackground(&C1);
        UpdateBackground(&C2);
        cactus_start(cactus, NUM_CACTUS);
        cactus_update(cactus, NUM_CACTUS);
        cactus_collide(cactus, NUM_CACTUS);
		render = true;

    }

    if(draw) game_update();
    return 0;
}

void game_update(){
    if( judge_to_info ){
        if( window == 1 ){
            // not back menu anymore, therefore destroy it
            printf("menu to info\n");
            //menu_destroy();
            // initialize next scene
            //game_scene_init();
            //judge_next_info = false;
            window = 2;
        }
    }
    if(judge_to_game){
        if( window == 1 ) {
            printf("menu to game\n");
            menu_destroy();
            game_scene_init();
            object_init();
            judge_to_game = false;
            judge_to_info = false;
            window = 3;
        }if(window == 2){
            printf("info to game\n");
            menu_destroy();
            game_scene_init();
            object_init();
            judge_to_game = false;
            judge_to_info = false;
            window = 3;
        }
    }
    if(judge_to_end){
        if( window == 3){
            judge_to_end = false;
            game_scene_destroy();
            cactus_destroy();
            end_game_init();
            window = 4;
        }
    }
    if(window==3){
        dino_update();
        if(dino.life == 1 && score >= LEVEL) {
            end_game_init();
            game_scene_destroy();
            cactus_destroy();
            window  = 4;
            status = 1;
        }
    }
}

void game_draw(){
    if( window == 1 ){
        //printf("show menu\n");
        menu_draw();
        al_flip_display();
    }else if( window == 2 ){
        //printf("show info\n");
        info_draw();
        al_flip_display();
    }else if(render && window == 3 ){
        game_scene_draw();
        //********************************************************************
        dino_draw();
        cactus_draw(cactus, NUM_CACTUS);
        al_flip_display();
        //printf("show game\n");
    }else if( window == 4 ){
        // printf("show game\n");
        if(status) win_game_draw();
        else end_game_draw();
        al_flip_display();
    }

}

void game_destroy() {
    // Make sure you destroy all things
    //al_destroy_event_queue(event_queue);
    end_scene_destroy();
    al_destroy_display(display);
    game_scene_destroy();
    //*******************************************************************
}
