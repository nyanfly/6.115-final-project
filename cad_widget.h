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

#include "gfx.h"
#include "shape.h"

#ifndef CAD_WIDGET_H
#define CAD_WIDGET_H

typedef struct CadWidgetObject_t {
    GWidgetObject w;
} CadWidgetObject;

void addShape(struct Shape_t shape);
void cadWidgetRenderingFunction(GWidgetObject* gw, void* param);
GHandle cadWidgetGCreate(GDisplay* g, CadWidgetObject* wo, GWidgetInit* pInit);


#endif  /* CAD_WIDGET_H */

/* [] END OF FILE */
