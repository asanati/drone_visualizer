#include "drone_visualizer.h"

int main(int argc, char * argv[])
{
	MyTestApp app;
	app.initApp();
	app.getRoot()->startRendering();
	app.closeApp();
	return 0;
}