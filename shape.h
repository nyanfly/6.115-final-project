/* ========================================
 *
 * Copyright Willie Zhu
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

// Represents the generic "shape" class
// Constrained to 2D primitives, because I'm too lazy to implement a 3D renderer

#include "gfx.h"

#ifndef SHAPE_H
#define SHAPE_H

struct Shape_t {
    enum {
        RECTANGLE,  // data is x, y, width, height
        CIRCLE,     // data is x, y, radius
        //POLYGON,
    } type;
    void *data;
    coord_t x;
    coord_t y;
};

void drawShape(GDisplay *d, struct Shape_t *s);

#endif  // SHAPE_H

/* [] END OF FILE */
