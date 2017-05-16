#include <device.h>
#include "gfx.h"

#include "shape.h"

#define MAX_SHAPES 100

static struct Shape_t* cadQueue[MAX_SHAPES];
static unsigned cadQueueSize = 0;

static font_t font;

void pushShape(struct Shape_t *shape);
void popShape();
struct Shape_t* peekShape();
void drawShapes();
void drawShapesFast();
void redraw();
void drawMode();

enum State {
    DRAW_CIRCLE,
    DRAW_RECTANGLE,
} state;

const enum State nextState[] = {DRAW_RECTANGLE, DRAW_CIRCLE};
const char stateNames[] = {'R', 'C'};

int main()
{
    //font_t font1, font2;
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
    //font1 = gdispOpenFont("DejaVuSans16_aa");
    font = gdispOpenFont("DejaVuSans32_aa");

    // set default bg/fg colors
    gwinSetDefaultColor(Gray);
    gwinSetDefaultBgColor(White);
    gwinSetDefaultFont(font);

    GWindowInit windowInit = {
        .x = 0,
        .y = 1,
        .width = 200,
        .height = 200,
        .show = TRUE,
    };
    
    geventListenerInit(&glistener);
    geventAttachSource(&glistener, ginputGetMouse(0), GLISTEN_TOUCHMETA | GLISTEN_TOUCHDOWNMOVES);

    redraw();   // initial draw
    
    int a = 0;
    bool_t shouldRedraw;  // should I redraw this frame?
    
    state = DRAW_CIRCLE;

    for (;;) {
        // wait for event
    	event = geventEventWait(&glistener, TIME_INFINITE);
		switch(event->type) {
            case GEVENT_TOUCH:
                a = 0;
                GEventMouse *mouseEvent;
                mouseEvent = (GEventMouse*) event;

                // a touchscreen touch always shows up as LEFT button press
                switch (mouseEvent->buttons) {
                    coord_t *data; // shape data pointer

                    case GINPUT_MOUSE_BTN_LEFT | GMETA_MOUSE_DOWN:
                        touchPressed = TRUE;
                        if (mouseEvent->x >= 50) {
                            shouldRedraw = TRUE;
                            switch (state) {
                                case DRAW_RECTANGLE: {
                                    struct Shape_t *shape = malloc(sizeof(struct Shape_t));
                                    shape->x = mouseEvent->x;
                                    shape->y = mouseEvent->y;
                                    shape->type = RECTANGLE;
                                    shape->data = malloc(sizeof(coord_t) * 2);
                                    data = shape->data;
                                    data[0] = 1;
                                    data[1] = 1;
                                    pushShape(shape);
                                }
                                break;

                                case DRAW_CIRCLE: {
                                    struct Shape_t *shape = malloc(sizeof(struct Shape_t));
                                    shape->x = mouseEvent->x;
                                    shape->y = mouseEvent->y;
                                    shape->type = CIRCLE;
                                    shape->data = malloc(sizeof(coord_t) * 1);
                                    data = shape->data;
                                    data[0] = 1;
                                    pushShape(shape);
                                }
                                break;

                                default:
                                break;
                            }
                        } else {    // advance state
                            state = nextState[state % (sizeof(nextState) / sizeof(nextState[0]))];
                        }
                    break;

                    case GMETA_MOUSE_UP:    // only redraw on mouse up
                        touchPressed = FALSE;
                        if (shouldRedraw) {
                            redraw();
                        }

                        shouldRedraw = FALSE;
                    break;
                        
                    default:    // just assume mouse movement
                        if (mouseEvent->buttons == 128) break;  // init??
                        
                        switch (state) {
                            case DRAW_RECTANGLE: {
                                struct Shape_t *currentShape = peekShape();
                                data = currentShape->data;

                                data[0] = mouseEvent->x - currentShape->x;
                                data[1] = mouseEvent->y - currentShape->y;
                            }
                            break;
                            
                            case DRAW_CIRCLE: {
                                struct Shape_t *currentShape = peekShape();
                                data = currentShape->data;

                                double distance = (mouseEvent->x - currentShape->x) * (mouseEvent->x - currentShape->x) + 
                                    (mouseEvent->y - currentShape->y) * (mouseEvent->y - currentShape->y);
                                data[0] = (coord_t) sqrt(distance);
                            }
                            break;
                            
                            default:
                            break;
                            
                        }

                        break;
                }
                break;

			default:
				break;
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

void drawShapesFast() { // only draw the currently edited shape
    if (cadQueueSize == 0) return;
    drawShapeFast(GDISP, cadQueue[cadQueueSize - 1]);
}

void redraw() {
    gdispClear(White);  // fill to white
    drawShapes();
    drawMode();
}

void drawMode() {   // display current state
    gdispDrawChar(10, 10, stateNames[state], font, Black);
    gdispDrawBox(0, 0, 50, 50, Black);
}