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

struct shape_t {
    enum {
        RECTANGLE,  // data is x, y, width, height
        CIRCLE,     // data is x, y, radius
        //POLYGON,
    } type;
    void *data;
    coord_t x;
    coord_t y;
};

void drawShape(GHandle gh, struct shape_t *s) {
    switch (s->type) {
        case RECTANGLE:;
        coord_t *coords;
        coords = (coord_t *) s->data;
        gwinDrawBox(gh, s->x, s->y, coords[0], coords[1]);
        break;
        
        case CIRCLE:
       // gwinDrawCircle(gh, s->x, s->y, s->data[2]);
        break;
        
     //   case POLYGON:
       // gwinDrawBox(gh, s->data[0], s->data[1], s->data[2], s->data[3]);
       // break;
        
        default:
        break;
    }
}
    
/* [] END OF FILE */
