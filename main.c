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
#include <math.h>
#include <stdio.h>
#include "pcmsys.h"

static jo_palette      palette1;

short snd_dibidi;

typedef enum {
	STATE_MENU,
	STATE_GAME,
	STATE_STORY,
	STATE_END
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
int timer = 0;
float hud_size = 0.0f;
bool player_move = false;
bool game_run = false;
int dibididoo_tim = 0;
bool speed_up = false;
int bombs_tim = 0;
int fruit_hud_state = 0;
float hud_rotation = 0.0f;
int hud_state = 0;
int hud_timer = 0;
int speed_up_timer = 0;
int y_end = -200;

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
void title_fruits(void);
void play_track(int track_number);
void player_jump(void);
void fruit_hud(void);
void the_end_is_near(void);
void ending(void);

int random_in_range(int min, int max) {
    return min + rand() % (max - min + 1);
}

int get_digit_from_left(int c, int k) {
    if (c == 0) {
        return (k == 0) ? 0 : -1;
    }
    if (c < 0) c = -c;

    int temp = c;
    int num_digits = 0;
    while (temp > 0) {
        temp /= 10;
        num_digits++;
    }

    if (k >= num_digits) return -1;

    for (int i = 0; i < num_digits - k - 1; i++) {
        c /= 10;
    }
    return c % 10;
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
		case STATE_END:
			ending();
			break;
		default:
			break;
	}
	
}

// Each time a 8 bits TGA is loaded, this function is called. (jo_set_tga_palette_handling)
jo_palette      *my_tga_palette_handling(void)
{
    // Here you can handle palettes as you want.
    // You can create a new one or pass an existing.
    // jo_create_palette() also give you an ID for your palette (palette1.id)
    jo_create_palette(&palette1);
    // The palette returned will be filled using color map inside TGA file
    // If you return JO_NULL, the palette inside the TGA is ignored
    // ▲ Note : Only 8 palettes are available. So try to mutualize them as much as you can
    return (&palette1);
}

void jo_main(void)
{
	jo_core_init(JO_COLOR_Black);
	jo_sprite_restore_sprite_scale();
	jo_set_tga_palette_handling(my_tga_palette_handling);
	jo_sprite_add_tga("TEX", "VOID.TGA", 228);	//INDEX: 0
	jo_set_tga_palette_handling(JO_NULL);
	jo_sprite_add_tga("BG", "TITLE.TGA", 228);	//INDEX: 1
	jo_sprite_add_tga("BG", "GAMEBOY.TGA", 228);	//INDEX: 2
	jo_sprite_add_tga("TEX", "FRUTO.TGA", 228);	//INDEX: 3
	jo_sprite_add_tga("BG", "BG.TGA", 228);	//INDEX: 4
	jo_sprite_add_tga("TEX", "BUBBLE.TGA", 228);	//INDEX: 5

	//fruits
	jo_sprite_add_tga("TEX", "AP.TGA", 228);	//INDEX: 6
	jo_sprite_add_tga("TEX", "ALMI.TGA", 228);	//INDEX: 7
	jo_sprite_add_tga("TEX", "FRES.TGA", 228);	//INDEX: 8
	jo_sprite_add_tga("TEX", "PE.TGA", 228);	//INDEX: 9
	jo_sprite_add_tga("TEX", "PIN.TGA", 228);	//INDEX: 10
	jo_sprite_add_tga("TEX", "WAT.TGA", 228);	//INDEX: 11
	jo_sprite_add_tga("TEX", "EX.TGA", 228);	//INDEX: 12

	jo_sprite_add_tga("TEX", "DIBIDI.TGA", 228);	//INDEX: 13
	jo_sprite_add_tga("BG", "SKY.TGA", 228);	//INDEX: 14

	//NUMBERS AND HUD
	jo_sprite_add_tga("BG", "0.TGA", 228);	//INDEX: 15
	jo_sprite_add_tga("BG", "1.TGA", 228);	//INDEX: 16
	jo_sprite_add_tga("BG", "2.TGA", 228);	//INDEX: 17
	jo_sprite_add_tga("BG", "3.TGA", 228);	//INDEX: 18
	jo_sprite_add_tga("BG", "4.TGA", 228);	//INDEX: 19
	jo_sprite_add_tga("BG", "5.TGA", 228);	//INDEX: 20
	jo_sprite_add_tga("BG", "6.TGA", 228);	//INDEX: 21
	jo_sprite_add_tga("BG", "7.TGA", 228);	//INDEX: 22
	jo_sprite_add_tga("BG", "8.TGA", 228);	//INDEX: 23
	jo_sprite_add_tga("BG", "9.TGA", 228);	//INDEX: 24
	jo_sprite_add_tga("BG", "DIN.TGA", 228);	//INDEX: 25

	//SPEECH BUBBLES
	jo_sprite_add_tga("TEX", "AP_B.TGA", 228);	//INDEX: 26
	jo_sprite_add_tga("TEX", "ALMI_B.TGA", 228);	//INDEX: 27
	jo_sprite_add_tga("TEX", "FRES_B.TGA", 228);	//INDEX: 28
	jo_sprite_add_tga("TEX", "PE_B.TGA", 228);	//INDEX: 29
	jo_sprite_add_tga("TEX", "PIN_B.TGA", 228);	//INDEX: 30
	jo_sprite_add_tga("TEX", "WAT_B.TGA", 228);	//INDEX: 31

	//MISC
	jo_sprite_add_tga("BG", "EXIT_MSG.TGA", 228);	//INDEX: 32
	jo_sprite_add_tga("TEX", "ORB.TGA", 228);	//INDEX: 33
	jo_sprite_add_tga("TEX", "15.TGA", 228);	//INDEX: 34
	jo_sprite_add_tga("TEX", "20.TGA", 228);	//INDEX: 35
	jo_sprite_add_tga("TEX", "GULP.TGA", 228);	//INDEX: 36
	jo_sprite_add_tga("TEX", "PREP1.TGA", 228);	//INDEX: 37
	jo_sprite_add_tga("TEX", "PREP2.TGA", 228);	//INDEX: 38
	jo_sprite_add_tga("TEX", "PREP3.TGA", 228);	//INDEX: 39
	jo_sprite_add_tga("TEX", "SPLAT.TGA", 228);	//INDEX: 40
	jo_sprite_add_tga("TEX", "DIBIZUL.TGA", 228);	//INDEX: 41
	jo_sprite_add_tga("BG", "END.TGA", 228);	//INDEX: 42

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
    jo_clear_screen();
    jo_set_printf_color_index(JO_COLOR_INDEX_White);
	jo_sprite_set_palette(palette1.id);
	jo_sprite_restore_sprite_scale();
	jo_set_default_background_color(JO_COLOR_RGB(115, 214, 255));
	frutordia_title();
	title_fruits();
	play_track(2);
	player_move = false;
	game_run = false;

	if (jo_is_pad1_key_down(JO_KEY_A)) {
		player_x = 0;
		player_y = 60;
		score = 0;
		player_jumping = false;
		x_speed = 0.0f;
		y_speed = 0.0f;
		fruit_select = random_in_range(6,11);
		timer = 0;
		hud_timer = 0;
		dibididoo_tim = 0;
		speed_up = false;
		bombs_tim = 0;
		fruit_hud_state = 0;
		hud_rotation = 0.0f;
		hud_state = 0;
		hud_timer = 0;
		speed_up_timer = 0;
		y_end = -200;

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
	jo_sprite_draw3D(1, 0, 35, 100);

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
	jo_set_default_background_color(JO_COLOR_RGB(0, 0, 0));
	jo_sprite_draw3D(2, 0, 0, 100);
	jo_sprite_draw3D(32, 0, 115, 100);
	play_track(3);

	if (jo_is_pad1_key_down(JO_KEY_B)) {
        current_state = STATE_MENU;
	}

};

//GAME
void draw_game(void){
    jo_clear_screen();
	//jo_nbg3_clear();
	jo_sprite_restore_sprite_scale();
    jo_set_printf_color_index(JO_COLOR_INDEX_White);
	jo_sprite_draw3D(4, 0, 80, 100);
	if (bombs_tim > 0){
		if (bombs_tim % 10 == 0){
			jo_sprite_draw3D(13, player_x, player_y, 100);
		}
		else{
			//null lol
		}
	}
	else if (speed_up == true){
		jo_sprite_draw3D(41, player_x, player_y, 100);
	}
	else{
		jo_sprite_draw3D(13, player_x, player_y, 100);
	}
	jo_sprite_draw3D((fruit_select + 20), 0, 90, 100);

	if (score < 0){ score = 0;}
	//HUD
	jo_sprite_draw3D(25, -124, -91, 100);
	jo_sprite_draw3D((get_digit_from_left(score, 0) + 15), -78, -99, 100);
	jo_sprite_draw3D((get_digit_from_left(score, 1) + 15), -62, -99, 100);
	jo_sprite_draw3D((get_digit_from_left(score, 2) + 15), -46, -99, 100);
	jo_sprite_draw3D(fruit_select, 140, 104, 100);

	//so this whole thing is the 3, 2, 1, start!
	if (timer == 0 || timer == 30){ hud_size = 0.1; }

	if (hud_size > 1){ hud_size = 1; }	

	if (hud_size != 1){ hud_size += 0.1; }

	if (timer < 30){
		jo_audio_stop_cd();
		jo_sprite_change_sprite_scale(hud_size);
		jo_sprite_draw3D(37, 0, 0, 100);
		jo_sprite_restore_sprite_scale();
	}
	else if (timer < 60){
		jo_sprite_change_sprite_scale(hud_size);
		jo_sprite_draw3D(38, 0, 0, 100);
		jo_sprite_restore_sprite_scale();
	}
	else if (timer < 90){
		jo_sprite_restore_sprite_scale();
		jo_sprite_draw3D(39, random_in_range(-10,10), 0, 100);
	}
	else if (timer < 105){
		jo_sprite_draw3D(39, random_in_range(-5,5), 0, 100);
	}
	else if (timer < 120){
		jo_sprite_draw3D(39, 0, 0, 100);
	}
	else if (timer < 150){
		jo_sprite_draw3D(0, 555, 0, 100);
		player_move = true;
		game_run = true;
		play_track(4);
	}
	else {
		jo_sprite_draw3D(0, 555, 0, 100);
	}
	
	game_fruits();

	timer++;

	fruit_hud();

	if (player_move == true){

			if (jo_is_pad1_key_down(JO_KEY_C)) {
    	    current_state = STATE_MENU;
		}

		if (jo_is_pad1_key_down(JO_KEY_A)) {
    	    player_jump();
		}

		if (jo_is_pad1_key_pressed(JO_KEY_RIGHT)){
			if (speed_up == true){
				x_speed = 8;
			}
			else{
				x_speed = 4;
			}
		}
	
		if (jo_is_pad1_key_pressed(JO_KEY_LEFT)){
			if (speed_up == true){
				x_speed = -8;
			}
			else{
				x_speed = -4;
			}
		}

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

	the_end_is_near();

};

void game_fruits(void){
	if (game_run == true){
		
		bombs_tim--;
		speed_up_timer--;
		
		if (bombs_tim <= 0){
			player_move = true;
		}

		if (speed_up_timer <= 0){
			speed_up = false;
		}

		for (int i = 0; i < FRUITS; i++){
			if (jo_hitbox_detection(13, player_x, player_y, fruits_array[i].sprite, fruits_array[i].x, fruits_array[i].y)){
				if (fruits_array[i].sprite == 12){
					score -= 15; //bombs
					bombs_tim = 100;
					player_move = false;
					hud_rotation = 0;
					hud_size = 0.001;
					fruit_hud_state = 0;
					hud_state = 0;
					fruit_hud_state = 0;
					hud_state = -1;

				}
				else if (fruits_array[i].sprite == 33){
					speed_up_timer = 272;
					speed_up = true;
				}
				else if (fruits_array[i].sprite != fruit_select){
					if (speed_up == true){
						fruit_hud_state = 0;
						hud_state = -2;
					}else{
						score -= 15; //incorrect fruit
						hud_rotation = 0;
						hud_size = 0.001;
						fruit_hud_state = 0;
						hud_state = 0;
						fruit_hud_state = 0;
						hud_state = -1;
					}

				}
				else{
					score += 20; //correct fruit
					hud_rotation = 0;
					hud_size = 0.001;
					fruit_hud_state = 0;
					hud_state = 0;
					fruit_hud_state = 0;
					hud_state = 1;
				}

			fruits_array[i].x = random_in_range(-160, 160);
			fruits_array[i].y = random_in_range(-992, -192);
			fruits_array[i].rot = random_in_range(0, 72);
			if (random_in_range(1, 30) == 1){
				fruits_array[i].sprite = 33;
			}else{
				fruits_array[i].sprite = random_in_range(6, 12);
			}
			}

			if (fruits_array[i].y > 60){
			fruits_array[i].x = random_in_range(-160, 160);
			fruits_array[i].y = random_in_range(-992, -192);
			fruits_array[i].rot = random_in_range(0, 72);
			if (random_in_range(1, 35) == 1){
				fruits_array[i].sprite = 33;
			}else{
				fruits_array[i].sprite = random_in_range(6, 12);
			}
		}
		

		fruits_array[i].y += 2;
		fruits_array[i].rot += 3;

		jo_sprite_draw3D_and_rotate(fruits_array[i].sprite, fruits_array[i].x, fruits_array[i].y, 100, fruits_array[i].rot);

		}

	}
	
}


void fruit_hud(void){

    if (fruit_hud_state == 1){
        hud_rotation += 15;
        hud_size -= 0.2f;

        if (hud_rotation >= 360){
            hud_rotation = 360;
            hud_size = 1;
            hud_timer = 60;
            fruit_hud_state = 2;
        }
    }
    else if (fruit_hud_state == 2)
    {
        hud_timer--;
        if (hud_timer <= 0){
            fruit_hud_state = 3;
        }
    }
    else if (fruit_hud_state == 3){
        hud_rotation -= 15;
        hud_size -= 0.2f;

        if (hud_rotation <= 0){
            hud_rotation = 0;
            hud_size = 0.001;
            fruit_hud_state = 0;
			hud_state = 0;
        }
    }
	
	if (hud_state == 1 && fruit_hud_state == 0){
    fruit_hud_state = 1;
	}
	else if (hud_state == -1 && fruit_hud_state == 0){
    fruit_hud_state = 1;
	}
	else if (hud_state == -2 && fruit_hud_state == 0){
    fruit_hud_state = 1;
	}

    if (hud_state == 1){
        jo_sprite_change_sprite_scale(hud_size);
        jo_sprite_draw3D_and_rotate(35, 114, -91, 100, (int)hud_rotation);
        jo_sprite_restore_sprite_scale();
    } 
	else if (hud_state == -1){
        jo_sprite_change_sprite_scale(hud_size);
        jo_sprite_draw3D_and_rotate(34, 114, -91, 100, (int)hud_rotation);
        jo_sprite_restore_sprite_scale();
	}
	else if (hud_state == -2){
        jo_sprite_change_sprite_scale(hud_size);
        jo_sprite_draw3D_and_rotate(36, 114, -91, 100, (int)hud_rotation);
        jo_sprite_restore_sprite_scale();
	}
	else {
		jo_sprite_draw3D_and_rotate(36, 605, -91, 100, 0);
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

void the_end_is_near(void){

	if (score >= 100){
		jo_audio_stop_cd();
		game_run = false;
		player_move = false;
		jo_sprite_draw3D(42, 0, y_end, 100);
		y_end++;

		if (y_end >= 0){
			current_state = STATE_END;
		}

	} //72

}

void ending(void){
    jo_clear_screen();
    jo_set_printf_color_index(JO_COLOR_INDEX_White);
	jo_set_default_background_color(JO_COLOR_RGB(0, 0, 0));
	jo_sprite_draw3D(42, 0, 0, 100);
	play_track(5);

	if (jo_is_pad1_key_down(JO_KEY_C)) {
        current_state = STATE_MENU;
	}

};

/*
** END OF FILE
*/
