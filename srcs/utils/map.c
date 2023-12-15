#include "../../includes/rt.h"

float   map(float v, vec2 range, vec2 nrange)
{
    return ((v - range[0]) / (range[1] - range[0]) \
    * (nrange[1] - nrange[0]) + nrange[0]);
}