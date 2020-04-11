/* $Id$ */



#include <GToolkit.h>


/* main */
int main(void)
{
	GWindow * window;

	if(gtoolkit_init() != 0)
		return 2;
	window = gwindow_new();
	gwindow_set_title(window, "Test window");
	gwindow_show(window);
	gtoolkit_main();
	gtoolkit_quit();
	return 0;
}
