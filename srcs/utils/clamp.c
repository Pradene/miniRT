#include "../../includes/rt.h"

// This fucntion clamp the number between 2 values
float clamp(float v, float min, float max)
{
    if (v >= min && v <= max)
        return (v);
    else if (v < min)
        return (min);
    return (max);
}