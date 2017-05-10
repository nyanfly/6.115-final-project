#include <device.h>
#include "gfx.h"

void cadAreaRendering(GWidgetObject* gw, void* param) {
    
}

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
    gwinSetDefaultColor(Black);
    gwinSetDefaultBgColor(White);
    gwinSetDefaultFont(font1);

    GWindowInit windowInit = {
        .x = 0,
        .y = 1,
        .width = swidth,
        .height = sheight,
        .show = TRUE
    };

    ghandle = gwinGWindowCreate(display, windowObject, &windowInit); 
    
    geventListenerInit(&glistener);
    geventAttachSource(&glistener, ginputGetMouse(0), GLISTEN_TOUCHMETA | GLISTEN_TOUCHDOWNMOVES);
    
    int a = 0;
    for (;;) {
        // wait for event
    	event = geventEventWait(&glistener, TIME_INFINITE);
		switch(event->type) {
            case GEVENT_TOUCH:
                a = 0;
                GEventMouse *mouseEvent;
                mouseEvent = (GEventMouse*) event;
                
                LCD_Char_PrintDecUint16(mouseEvent->buttons);
                
                // a touchscreen touch always shows up as LEFT button press
                switch (mouseEvent->buttons) {
                    case GINPUT_MOUSE_BTN_LEFT | GMETA_MOUSE_DOWN:
                        touchPressed = TRUE;
                    break;
                    
                    case GINPUT_MOUSE_BTN_LEFT | 0x1010:    // mouse movement (magic number?)
                    break;
                    
                    case GMETA_MOUSE_UP:
                        touchPressed = FALSE;
                    break;
                }
                break;
			default:
				break;
		}

    }

    return 0;
}
