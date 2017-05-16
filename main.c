#include <device.h>
#include "gfx.h"
//#include "cad_widget.h"

#include "shape.h"

//#define cadWidgetGCreate(so, pI) cadWidgetGCreate(GDISP, so, pI)    // helper alias

#define MAX_SHAPES 100

static struct Shape_t* cadQueue[MAX_SHAPES];
static unsigned cadQueueSize = 0;

void pushShape(struct Shape_t *shape);
void popShape();
struct Shape_t* peekShape();
void drawShapes();
void drawShapesFast();

int main()
{
    font_t font1, font2;
    coord_t swidth, sheight;
    gdispImage image;
    GDisplay *display;
    GWindowObject *windowObject = NULL;
    GHandle ghandle;
    GListener glistener;
    GEvent *event;
    bool_t touchPressed = FALSE;

    // initialize touch screen
    ResistiveTouch_Start();
    
    LCD_Char_Start();

	LCD_Char_PrintString("ready");
    
    // Initialize the uGFX library
    gfxInit();

    // Some misc stuff
    swidth = gdispGetWidth();
    sheight = gdispGetHeight();
    display = gdispGetDisplay(0);   // get default display

    // Prepare the resources
    font1 = gdispOpenFont("DejaVuSans16_aa");
    font2 = gdispOpenFont("DejaVuSans32_aa");

    // set default bg/fg colors
    gwinSetDefaultColor(Gray);
    gwinSetDefaultBgColor(White);
    gwinSetDefaultFont(font1);

    GWindowInit windowInit = {
        .x = 0,
        .y = 1,
        .width = 200,
        .height = 200,
        .show = TRUE,
    };
    
    geventListenerInit(&glistener);
    geventAttachSource(&glistener, ginputGetMouse(0), GLISTEN_TOUCHMETA | GLISTEN_TOUCHDOWNMOVES);
    
    unsigned *data = malloc(sizeof(unsigned) * 2);
    data[0] = 50;
    data[1] = 50;

    struct Shape_t shape = {
        .type = RECTANGLE,
        .data = data,
        .x = 10,
        .y = 10,
    };

    addShape(shape);

    int a = 0;
    bool_t shouldRedraw;  // should I redraw this frame?

    for (;;) {
        shouldRedraw = FALSE;
        // wait for event
    	event = geventEventWait(&glistener, TIME_INFINITE);
		switch(event->type) {
            case GEVENT_TOUCH:
                a = 0;
                GEventMouse *mouseEvent;
                mouseEvent = (GEventMouse*) event;
                
                //LCD_Char_PrintDecUint16(mouseEvent->buttons);
                
                // a touchscreen touch always shows up as LEFT button press
                switch (mouseEvent->buttons) {
                    coord_t *data; // shape data pointer

                    case GINPUT_MOUSE_BTN_LEFT | GMETA_MOUSE_DOWN:
                        touchPressed = TRUE;
                        struct Shape_t *shape = malloc(sizeof(struct Shape_t));
                        shape->x = mouseEvent->x;
                        shape->y = mouseEvent->y;
                        shape->type = RECTANGLE;
                        shape->data = malloc(sizeof(coord_t) * 2);
                        data = shape->data;
                        data[0] = 1;
                        data[1] = 1;
                        pushShape(shape);
                    break;
                        
                    case GMETA_MOUSE_UP:
                        touchPressed = FALSE;
                        shouldRedraw = TRUE;
                    break;
                        
                    default:    // just assume mouse movement
                        if (mouseEvent->buttons == 128) break;  // init??
                        struct Shape_t *currentShape = peekShape();
                        data = shape->data;

                        data[0] = mouseEvent->x - shape->x;
                        data[1] = mouseEvent->y - shape->y;

                        break;
                }
                break;

			default:
				break;
		}

        // FIXME incredibly inefficient :/
        // redraw after event
        if (shouldRedraw) {
            gdispClear(White);  // fill to white
            drawShapes();
        }

        drawShapesFast();
    }

    return 0;
}

void pushShape(struct Shape_t *shape) {
    cadQueue[cadQueueSize] = shape;
    cadQueueSize++;
}

void popShape() {
    if (cadQueueSize == 0) return;  // don't do anything for empty queue

    if (cadQueue[cadQueueSize - 1]->data != NULL) {
        free(cadQueue[cadQueueSize - 1]->data);
    }

    free(cadQueue[cadQueueSize - 1]);   // TODO fix memory management LOL
    cadQueueSize--;
}

struct Shape_t* peekShape() {
    if (cadQueueSize == 0) return NULL;
    return cadQueue[cadQueueSize - 1];
}

void drawShapes() {
    unsigned i;
    for (i = 0; i < cadQueueSize; i++) {
        drawShape(GDISP, cadQueue[i]);
    }
}

void drawShapesFast() {
    unsigned i;
    for (i = 0; i < cadQueueSize; i++) {
        drawShapeFast(GDISP, cadQueue[i]);
    }
}