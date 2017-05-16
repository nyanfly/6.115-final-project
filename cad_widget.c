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
#include "gfx.h"
#include "src/gwin/gwin_class.h"

#include "cad_widget.h"
#include "shape.h"

#define MAX_SHAPES 10

static struct Shape_t cadQueue[MAX_SHAPES];
static unsigned cadQueueSize = 0;

static const gwidgetVMT cadWidgetVMT = {
    {
        "CadWidget",                // The classname
        sizeof(CadWidgetObject),     // The object size
        _gwidgetDestroy,            // The destroy routine
        _gwidgetRedraw,             // The redraw routine
        0,                          // The after-clear routine
    },
    cadWidgetRenderingFunction,            // The default drawing routine
    #if GINPUT_NEED_MOUSE
        {
            0,                      // Process mouse down events
            0,                      // Process mouse up events
            0,
        },
    #endif
    #if GINPUT_NEED_KEYBOARD || GWIN_NEED_KEYBOARD
        {
            0           // Process keyboard events
        },
    #endif
    #if GINPUT_NEED_TOGGLE
        {
            0,            // 1 toggle role
            0,            // Assign Toggles
            0,            // Get Toggles
            0,            // Process toggle off events (NOT USED)
            0,            // Process toggle on events
        },
    #endif
    #if GINPUT_NEED_DIAL
        {
            0,            // 1 dial roles
            0,            // Assign Dials
            0,            // Get Dials
            0,            // Process dial move events
        },
    #endif
};

void addShape(struct Shape_t shape) {
    cadQueue[cadQueueSize] = shape;
    cadQueueSize++;
}

void cadWidgetRenderingFunction(GWidgetObject* gw, void* param) {
    unsigned i;
    for (i = 0; i < cadQueueSize; i++) {
        drawCadShape(&gw->g, &cadQueue[i]);
    }
}

GHandle cadWidgetGCreate(GDisplay* g, CadWidgetObject* wo, GWidgetInit* pInit) {
    // Create the base class (the actual widget)
    if (!(wo = (CadWidgetObject*) _gwidgetCreate(g, &wo->w, pInit, &cadWidgetVMT))) {
        return 0;
    }

    // Set the initial visibility
    gwinSetVisible((GHandle)wo, pInit->g.show);

    // Return a proper GHandle
    return (GHandle) wo;
}

/* [] END OF FILE */
