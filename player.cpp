#include "splashkit.h"
#include "player.h"

player_data new_player(double x, double y)
{
    player_data result;

    result.x = x;
    result.y = y;
    result.vel = 0;
    result.acc = 0.125;
    result.highest_y = 0;
    result.state = IDLE;
    result.face = RIGHT;

    return result;
}

bitmap player_bitmap(const player_data &player)
{
    string bitmap_name;
    bitmap_name = "player";

    if (player.face == LEFT && player.state == IDLE)
    {
        bitmap_name += "-idle-l";
    }
    if (player.face == LEFT && player.state == JUMP)
    {
        bitmap_name += "-jump-l";
    }
    if (player.face == RIGHT && player.state == IDLE)
    {
        bitmap_name += "-idle-r";
    }
    if (player.face == RIGHT && player.state == JUMP)
    {
        bitmap_name += "-jump-r";
    }

    return bitmap_named(bitmap_name);
}


