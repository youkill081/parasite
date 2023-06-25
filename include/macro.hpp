/*
** EPITECH PROJECT, 2023
** aze
** File description:
** eza
*/

#pragma once

enum {
    SCENE_MENU,
    SCENE_LEVEL_CHOOSE,
    SCENE_GAME
};

#define DEFAULT_FONT "ressources/font/Lato/Lato-Bold.ttf"

#define MAP_FOLDER "ressources/maps/"

#define PERSO_TEXTURE "ressources/pacanimated.bmp"
#define PERSO_TEXTURE_SQUARE 21
#define VIRUS_TEXTURE "ressources/virus.bmp"
#define VIRUS_TEXTURE_SIZE 20, 20
#define PARASITE_TEXTURE "ressources/parasite.bmp"
#define PARASITE_TEXTURE_SIZE 20, 20
#define PADLOCK_TEXTURE "ressources/padlock.bmp"
#define PADLOCK_TEXTURE_SIZE 52, 46

#define PLAYER_ANIMATION_WAIT 0.2

#define ERROR_CODE 84

#define GAME_SQUARE_SIZE 45
#define GAME_WALL_THICKNESS 5

#define TITLE_MARGIN 50

#define GAME_UPDATE_TIME 50

#define PLAYER_SPEED 8
#define VIRUS_SPEED 4

#define PARASITE_LEFT_POSITION 50, 1000
#define PARASITE_LEFT_SIZE 60
