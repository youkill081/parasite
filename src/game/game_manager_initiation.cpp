/*
** EPITECH PROJECT, 2023
** ratrapage
** File description:
** the main file for the game manager
*/


#include <sys/types.h>
#include <iostream>
#include <sstream>
#include <dirent.h>
#include <fstream>
#include <algorithm>

#include "game/game_manager.hpp"
#include "macro.hpp"

void create_texture_map(struct game::map *map, window::gm_window *window);

using namespace game;

std::string get_file_content(std::string file_path)
{
    std::ifstream file(file_path);

    if (not file.is_open()) {
        std::cout << "The map file : " << file_path << " not found" << std::endl;
        return NULL;
    }

    std::string end;
    std::string line;
    
    while (std::getline(file, line)) {
        end += line + "\n";
    }
    
    file.close();
    return end;
}

std::string getline_by_number(std::string string, int line_number)
{
    std::istringstream iss(string);
    std::string line;
    
    for (int i = 0; i < line_number; i++) {
        std::getline(iss, line);
    }
    
    return line;
}

void create_map_line(struct map *end, int line_number, std::string map_string)
{
    std::string line;
        
    end->map_list[line_number] = (int *) malloc(sizeof(int) * end->size);

    if (end->map_list[line_number] == NULL) {
        std::cout << "ERROR on memory allocation (creat_map_line)" << std::endl;
        return;
    }
    
    line = getline_by_number(map_string, line_number + 2);
    for (int i = 0; line[i] != '\0'; i++) {
        switch (line[i]) {
        case 'x':
            end->map_list[line_number][i] = GM_PATH;
            break;
        case 'o':
            end->map_list[line_number][i] = GM_VOID;
            break;
        default:
            end->map_list[line_number][i] = GM_UNKNOWN;
            break;    
        }
    }
}

void get_player_spawn(struct map *map, std::string string_map)
{
    std::istringstream chain(getline_by_number(string_map, map->size + 2));
    std::string first, second;

    std::getline(chain, first, ' ');
    std::getline(chain, second);

    map->player_spawn.x = std::stoi(first);
    map->player_spawn.y = std::stoi(second);
}

void get_square_size(struct map *map, std::string string_map)
{
    std::string size_str = getline_by_number(string_map, map->size + 3);
    map->square_size = std::atoi(size_str.c_str());
}

struct map *create_new_map(std::string file_name, window::gm_window *window)
{
    struct map *end = new struct map;
    std::string string_map;
    
    if (end == NULL)
        return NULL;

    string_map = get_file_content(std::string(MAP_FOLDER) + "/" + file_name);
   
    end->size = atoi(getline_by_number(string_map, 1).c_str());
    if (end->size <= 0) {
        std::cout << "ERROR: can't load map, size is 0" << std::endl;
        delete end;
        return NULL;
    }

    end->map_list = (int **) malloc(sizeof(int *) * end->size);
    for (int i = 0; i < end->size; i++) {
        create_map_line(end, i, string_map);
    }

    get_player_spawn(end, string_map);
    get_square_size(end, string_map);
    
    create_texture_map(end, window);
    
    return end;
}

game_manager::game_manager(window::gm_window *window)
{
    DIR *dir = opendir(MAP_FOLDER);
    struct dirent *data;
    struct map *temp;
    std::list<std::string> file_list;
    
    while ((data = readdir(dir)) != NULL) {
        if (data->d_type == DT_REG) {
            file_list.push_back(data->d_name);
        }
    }
    closedir(dir);
    file_list.sort();
    std::list<std::string>::iterator curs;
    for (curs = file_list.begin(); curs != file_list.end(); curs++) {
        temp = create_new_map(*curs, window);
        this->map_list.push_back(temp);
        this->number_map++;
    }

    this->party = new game::party();
}
