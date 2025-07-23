/*
** Jo Sega Saturn Engine
** Copyright (c) 2012-2017, Johannes Fetz (johannesfetz@gmail.com)
** All rights reserved.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are met:
**     * Redistributions of source code must retain the above copyright
**       notice, this list of conditions and the following disclaimer.
**     * Redistributions in binary form must reproduce the above copyright
**       notice, this list of conditions and the following disclaimer in the
**       documentation and/or other materials provided with the distribution.
**     * Neither the name of the Johannes Fetz nor the
**       names of its contributors may be used to endorse or promote products
**       derived from this software without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
** ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
** WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
** DISCLAIMED. IN NO EVENT SHALL Johannes Fetz BE LIABLE FOR ANY
** DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
** (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
** LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
** ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
** SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. DIBIDIDOO!!!
MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWNXK00OOO0KXXNWWMMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMMMMMMMWKkdllllllllllloddk0XWMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMMMMMWXklccclloooooooollllloONMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMMMMWKxlllllloooooooooodooolokXWMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMMMN0dllllllllllllooodddddoollxKWMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMMNOolllloll::;;;;;:cloddddoooodONMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMNkollllllc:;;,,,,,,;;cloodddooooONMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMWOllllllllc:;,,'..',;::cloooooooldKMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMXdcloollllc:;:c;'',:lcccllooooooloOWMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMWOoloooooollccccc:::cllllloodoooollxNMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMXxllooooolllllllloooooolloodddoolllo0WMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMNkollooooooooooooooooooooooddddooollldKWMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMWKdllloooododoollllooooollclooddddooollloOWMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMWOlclloooooollccccccccccccc:ccloooooollccxXMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMW0oclllooollc::ccllllcclllcc::cclllolllclkNMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMNOolllloollc:;,;:cclllcc:;,;:cclloollllxXWMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMW0olllooooolc:::cccclcc::::clooooolllxXMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMNOoloodddddoollllllllllloooddddoolloKWMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMXxlloodddddoooooooooooooddddddollo0WMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMXxlllooooooooooddddodddddoooollo0WMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMMXxccclllooooodddddoooooolllcco0WMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMMW0l::cccclloooooooooollcccc:cxNMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMWXOdc;';:::::::cccccccccc::::::;,,:ok0NWMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMNOl,.   .,::::;;;;:::;;;;;:::::::;..  ..;dKWMMMMMMMMMMMM
MMMMMMMMMMMMMMMNx'.     .';:::;;;;;;;;;;;;;;:::::;.      .:0WMMMMMMMMMMM
MMMMMMMMMMMMMMMK:.       .,:c::::;;;;;;;;;::::cc:'.      ..oNMMMMMMMMMMM
MMMMMMMMMMMMMMWk,.       .';cccc::::::::::::ccc:,.        .cXMMMMMMMMMMM
MMMMMWWNXK0Okxl,.         .';:cccccccccccccccc:;.          .:dkO0KXNWWMM
MMKdcc:;,.....             .';cllllcllllcllll:,..            .....',:cll
MMk'.................      ..':::::::::::c:::,....    ..................
*/

#include <jo/jo.h>
#include <stdlib.h>
#include <time.h>
#include "pcmsys.h"

short snd_dibidi;

typedef enum {
	STATE_MENU,
	STATE_GAME,
	STATE_STORY
}	GameState;

GameState current_state = STATE_MENU;

bool increasing = true;
float title_rotation = 0.0f;
int player_x = 0;
int player_y = 60;
int score = 0;
bool player_jumping = false;
float x_speed = 0.0f;
float y_speed = 0.0f;
static jo_sound dibidi;
bool cd_playing = false;
int current_cd_track = 0;
int fruit_select = 0;

typedef struct{
	int x;
	int y;
	int rot;
	int sprite;
}	TitleFruit;

//title screen fruits
#define TITLE_FRUITS 12
TitleFruit title_fruits_array[TITLE_FRUITS];

typedef struct{
	int x;
	int y;
	int rot;
	int sprite;
}	Fruit;

//game fruits
#define FRUITS 7
Fruit fruits_array[FRUITS];


void draw_menu(void);
void draw_story(void);
void draw_game(void);
void frutordia_title(void);

int random_in_range(int min, int max) {
    return min + rand() % (max - min + 1);
}


//GAME STATE
void			state_loop(void)
{
	switch (current_state){
		case STATE_MENU:
			draw_menu();
			break;
		case STATE_STORY:
			draw_story();
			break;
		case STATE_GAME:
			draw_game();
			break;
		default:
			break;
	}
	
}

void jo_main(void)
{
	jo_core_init(JO_COLOR_Black);
	jo_sprite_add_tga("TEX", "VOID.TGA", JO_COLOR_RGB(255,0,255));	//INDEX: 0
	jo_sprite_add_tga("BG", "TITLE.TGA", JO_COLOR_RGB(255,0,255));	//INDEX: 1
	jo_sprite_add_tga("BG", "GAMEBOY.TGA", JO_COLOR_RGB(255,0,255));	//INDEX: 2
	jo_sprite_add_tga("TEX", "FRUTO.TGA", JO_COLOR_RGB(255,0,255));	//INDEX: 3
	jo_sprite_add_tga("BG", "BG.TGA", JO_COLOR_RGB(255,0,255));	//INDEX: 4
	jo_sprite_add_tga("TEX", "BUBBLE.TGA", JO_COLOR_RGB(255,0,255));	//INDEX: 5

	//fruits
	jo_sprite_add_tga("TEX", "AP.TGA", JO_COLOR_RGB(255,0,255));	//INDEX: 6
	jo_sprite_add_tga("TEX", "ALMI.TGA", JO_COLOR_RGB(255,0,255));	//INDEX: 7
	jo_sprite_add_tga("TEX", "FRES.TGA", JO_COLOR_RGB(255,0,255));	//INDEX: 8
	jo_sprite_add_tga("TEX", "PE.TGA", JO_COLOR_RGB(255,0,255));	//INDEX: 9
	jo_sprite_add_tga("TEX", "PIN.TGA", JO_COLOR_RGB(255,0,255));	//INDEX: 10
	jo_sprite_add_tga("TEX", "WAT.TGA", JO_COLOR_RGB(255,0,255));	//INDEX: 11
	jo_sprite_add_tga("TEX", "EX.TGA", JO_COLOR_RGB(255,0,255));	//INDEX: 12

	jo_sprite_add_tga("TEX", "DIBIDI.TGA", JO_COLOR_RGB(255,0,255));	//INDEX: 13
	jo_sprite_add_tga("BG", "SKY.TGA", JO_COLOR_RGB(255,0,255));	//INDEX: 14

	//load_drv(ADX_MASTER_2304);
	//snd_dibidi = load_16bit_pcm((Sint8 *)"DIBIDI.PCM", 20500);

	//title screen fruits
	for (int i = 0; i < TITLE_FRUITS; i++){
		title_fruits_array[i].x = random_in_range(-160, 160);
		title_fruits_array[i].y = random_in_range(-192, -152);
		title_fruits_array[i].rot = random_in_range(0, 72);
		title_fruits_array[i].sprite = random_in_range(6, 11);
	}

	//game fruits
	for (int i = 0; i < FRUITS; i++){
		fruits_array[i].x = random_in_range(-160, 160);
		fruits_array[i].y = random_in_range(-992, -192);
		fruits_array[i].rot = random_in_range(0, 72);
		fruits_array[i].sprite = random_in_range(6, 12);
	}

	jo_core_add_callback(state_loop);
	jo_core_add_vblank_callback(sdrv_vblank_rq);

	jo_core_run();
}

//MAIN MENU
void draw_menu(void){
	jo_set_displayed_screens(JO_NBG2_SCREEN);
    jo_clear_screen();
	//jo_nbg2_clear();
    jo_set_printf_color_index(JO_COLOR_INDEX_White);
	//jo_sprite_draw3D(4, 0, 0, 100);
	jo_set_default_background_color(JO_COLOR_RGB(115, 214, 255));
	frutordia_title();
	title_fruits();
	fruit_select = random_in_range(6,11);
	play_track(2);

	if (jo_is_pad1_key_down(JO_KEY_A)) {
		player_x = 0;
		player_y = 60;
		score = 0;
		player_jumping = false;
		x_speed = 0.0f;
		y_speed = 0.0f;

	for (int i = 0; i < FRUITS; i++){
		fruits_array[i].x = random_in_range(-160, 160);
		fruits_array[i].y = random_in_range(-992, -192);
		fruits_array[i].rot = random_in_range(0, 72);
		fruits_array[i].sprite = random_in_range(6, 12);
	}

        current_state = STATE_GAME;
	}

	if (jo_is_pad1_key_down(JO_KEY_B)) {
        current_state = STATE_STORY;
	}


};

void title_fruits(void){

	for (int i = 0; i < TITLE_FRUITS; i++){
			if (title_fruits_array[i].y > 60){
			title_fruits_array[i].y = random_in_range(-372, -152);
			title_fruits_array[i].x = random_in_range(-160, 160);
			title_fruits_array[i].rot = random_in_range(0, 72);
			title_fruits_array[i].sprite = random_in_range(6, 11);
	}
	

	title_fruits_array[i].y += 2;
	title_fruits_array[i].rot += 3;

	jo_sprite_draw3D_and_rotate(title_fruits_array[i].sprite, title_fruits_array[i].x, title_fruits_array[i].y, 100, title_fruits_array[i].rot);

	}

	jo_sprite_draw3D_and_rotate(3, 0, -80, 100, (int)title_rotation);
	jo_sprite_draw3D(1, 0, 0, 100);

}

void frutordia_title(void){
	
	if (increasing){
		title_rotation+=0.3;
		if (title_rotation>=3){
			increasing=false;
		}
	}
	else 
	{
		title_rotation-=0.3;
		if (title_rotation<=-3){
			increasing=true;
		}
	}
}

//STORY
void draw_story(void){
    jo_clear_screen();
    jo_set_printf_color_index(JO_COLOR_INDEX_White);
	jo_sprite_draw3D(2, 0, 0, 100);
	play_track(3);

	if (jo_is_pad1_key_down(JO_KEY_B)) {
        current_state = STATE_MENU;
	}

};

//GAME
void draw_game(void){
    jo_clear_screen();
	//jo_nbg3_clear();
    jo_set_printf_color_index(JO_COLOR_INDEX_White);
	jo_sprite_draw3D(4, 0, 0, 100);
	jo_sprite_draw3D(13, player_x, player_y, 100);
	jo_sprite_draw3D(5, 0, 90, 100);
	game_fruits();
	//jo_nbg3_print(1, 1, "Dinero:", score);


	play_track(4);

	if (jo_is_pad1_key_down(JO_KEY_C)) {
        current_state = STATE_MENU;
	}

	if (jo_is_pad1_key_down(JO_KEY_A)) {
        player_jump();
	}

	if (jo_is_pad1_key_pressed(JO_KEY_RIGHT)){
		x_speed = 4;
	}
	
	if (jo_is_pad1_key_pressed(JO_KEY_LEFT)){
		x_speed = -4;
	}

	//physics
		//jumping
	if (player_jumping){
		y_speed -= 0.4;
		player_y -= (int)y_speed;

		if (player_y >= 60){
			player_y = 60;
			y_speed = 0.0f;
			player_jumping = false;
		}
	}

		//running
	if (x_speed > 0){
		x_speed -= 0.3;
		if (x_speed < 0) x_speed = 0;
	} 
	else if (x_speed < 0)
	{
		x_speed += 0.3;
		if (x_speed > 0) x_speed = 0;
	}
	

	player_x += (int)x_speed;

	if (player_x >= 144){
		player_x = 144;
	}

	if (player_x <= -144){
		player_x = -144;
	}



};

void game_fruits(void){
	for (int i = 0; i < FRUITS; i++){
		if (jo_hitbox_detection(13, player_x, player_y, fruits_array[i].sprite, fruits_array[i].x, fruits_array[i].y)){
			if (fruits_array[i].sprite == 12){
				score -= 15; //bombs
			}
			else if (fruits_array[i].sprite != fruit_select){
				score -= 15; //incorrect fruit
			}
			else{
				score += 20; //correct fruit
			}

		fruits_array[i].x = random_in_range(-160, 160);
		fruits_array[i].y = random_in_range(-992, -192);
		fruits_array[i].rot = random_in_range(0, 72);
		fruits_array[i].sprite = random_in_range(6, 12);
		}

		if (fruits_array[i].y > 60){
		fruits_array[i].x = random_in_range(-160, 160);
		fruits_array[i].y = random_in_range(-992, -192);
		fruits_array[i].rot = random_in_range(0, 72);
		fruits_array[i].sprite = random_in_range(6, 12);
	}
	

	fruits_array[i].y += 2;
	fruits_array[i].rot += 3;

	jo_sprite_draw3D_and_rotate(fruits_array[i].sprite, fruits_array[i].x, fruits_array[i].y, 100, fruits_array[i].rot);

	}
}

void play_track(int track_number){
	if (current_cd_track != track_number){
	jo_audio_stop_cd();
	jo_audio_play_cd_track(track_number, track_number,true);
	current_cd_track = track_number;
	cd_playing = true;
	}
}

void player_jump(void){
	if (!player_jumping){
		player_jumping = true;
		y_speed = 7.2;
		//pcm_play(snd_dibidi, PCM_SEMI, 6);
	}

}

/*
** END OF FILE
*/
