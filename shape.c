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

// color when shape is being edited
#define EDITING_COLOR Gray
// color after shape is placed onto sketch
#define SKETCH_COLOR Black
// color for outlining different shapes
#define SKETCH_OUTLINE_COLOR Gray

 void drawShape(GDisplay *d, struct Shape_t *s) {
    // TODO is data always of coord_t?
    coord_t x, y;

    x = s->x;
    y = s->y;

    switch (s->type) {
        coord_t *data;
        case RECTANGLE: {
            coord_t width, height;

            data = s->data;

            width = data[0];
            height = data[1];

            if (width < 0) {
                x += width;
                width = -width;
            }
            
            if (height < 0) {
                y += height;
                height = -height;
            }

            gdispFillArea(x, y, width, height, SKETCH_COLOR);
            gdispDrawBox(x, y, width, height, SKETCH_OUTLINE_COLOR);
        }
        break;
        
        case CIRCLE: {
            coord_t radius;

            data = s->data;

            radius = data[0];

            gdispFillCircle(x, y, radius, SKETCH_COLOR);
            gdispDrawCircle(x, y, radius, SKETCH_OUTLINE_COLOR);
        }
        break;
        
     //   case POLYGON:
       // gwinDrawBox(gh, s->data[0], s->data[1], s->data[2], s->data[3]);
       // break;
        
        default:
        break;
    }
}

 void drawShapeFast(GDisplay *d, struct Shape_t *s) {
    // TODO is data always of coord_t?
    coord_t x, y;

    x = s->x;
    y = s->y;

    switch (s->type) {
        coord_t *data;
        case RECTANGLE: {
            coord_t width, height;

            data = s->data;

            width = data[0];
            height = data[1];

            if (width < 0) {
                x += width;
                width = -width;
            }
            
            if (height < 0) {
                y += height;
                height = -height;
            }

            gdispDrawBox(x, y, width, height, EDITING_COLOR);
        }
        break;
        
        case CIRCLE: {
            coord_t radius;

            data = s->data;
            radius = data[0];

            gdispDrawCircle(x, y, radius, EDITING_COLOR);
        }
        break;
        
     //   case POLYGON:
       // gwinDrawBox(gh, s->data[0], s->data[1], s->data[2], s->data[3]);
       // break;
        
        default:
        break;
    }
}
/* [] END OF FILE */
