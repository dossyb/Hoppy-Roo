#pragma once

enum player_state
{
    IDLE,
    JUMP
};

enum player_direction
{
    RIGHT,
    LEFT
};

struct player_data
{
    double x;
    double y;
    double width;
    double height;
    double vel;
    double acc;
    double highest_y;
    player_state state;
    player_direction face;
};

player_data new_player(double x, double y);
bitmap player_bitmap(const player_data &player);