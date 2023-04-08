#include "splashkit.h"
#include "platform.h"

platform_data new_platform(double x, double y, platform_size size)
{
    platform_data result;

    result.x = x;
    result.y = y;
    result.size = size;

    return result;
}

bitmap platform_bitmap(const platform_data &platform)
{
    string bitmap_name;
    bitmap_name = "platform";

    switch (platform.size)
    {
        case EXTRA_SMALL:
            bitmap_name += "-xs";
            break;
        case MEDIUM:
            bitmap_name += "-m";
            break;
        case LARGE:
            bitmap_name += "-l";
            break;
        case EXTRA_LARGE:
            bitmap_name += "-xl";
            break;
        case SMALL:
        default:
            bitmap_name += "-s";
    }

    return bitmap_named(bitmap_name);
}
