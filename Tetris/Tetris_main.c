/**************************************************************
 * File Name: Tetris_main.c
**************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "GL/glut.h"
#include "Type_define.h"
#include "Tetris_config.h"
#include "Tetris_logic.h"
#include "Tetris_display.h"
#include "Tetris_operation.h"

static void scene_init(void)
{
    operation_init();
    logic_init();
    display_init();
}

int main(int argc, char *argv[])
{
	/* Step 1: Initialize the GLUT library and negotiate a session with the
	   window system */
    glutInit(&argc, argv);

	/* Step 2: Set the initial display mode, which is used when creating
	   top-level windows, subwindows, and overlays to determine the
	   OpenGL display mode for the to-be-created window or overlay */
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);

	/* Step 3: Set the initial window size in pixels */
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	/* Step 4: Create a top-level window. The name will be provided to the window
	   system as the window's name. Implicitly, the current window is set
	   to the newly created window. Each created window has a unique associated
	   OpenGL context. State changes to a window's associated OpenGL context
	   can be done immediately after the window is created. */
    glutCreateWindow("TETRIS");

    scene_init();
	/* Step 5: Define the GLUT callbacks for display, window, keyboard,
	   mouse, etc. management */
    glutDisplayFunc(display_callback);
    //glutReshapeFunc(reshape_callback);
    glutKeyboardUpFunc(keyboard_callback);
	glutSpecialUpFunc(specialkey_callback);
	glutIdleFunc(idle_callback);

	/* Final Step: Enter the GLUT event processing loop. Once called, this
	   routine will never return. It will call as necessary any callbacks
	   that have been registered. */
    glutMainLoop();

    return 0;
}