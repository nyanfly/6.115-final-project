/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include "shape.h"

 void drawCadShape(GHandle gh, struct Shape_t *s) {
    switch (s->type) {
        case RECTANGLE:;
        coord_t *coords;
       // coords = (coord_t *) s->data;
      //  gwinDrawBox(gh, s->x, s->y, coords[0], coords[1]);
        gwinDrawBox(gh, s->x, s->y, 100, 100);
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
