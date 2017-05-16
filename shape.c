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
#include <device.h>
#include "shape.h"

 void drawShape(GDisplay *d, struct Shape_t *s) {
    // TODO is data always of coord_t?
    switch (s->type) {
        coord_t *data;
        case RECTANGLE:;
        data = s->data;
        gdispFillArea(s->x, s->y, data[0], data[1], Red);
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
