#include "Configuration.h"
#include "RendererFactory.h"
#include "IWindowSystem.h"
#include "WindowSystemFactory.h"
#include <memory>

//#define CRTDBG_MAP_ALLOC
//#include <crtdbg.h>

int main(int argc, char **argv) 
{
	//_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	Configuration *config = Configuration::getInstance();
	config->load("config.cfg");

	/* get a window */
	std::unique_ptr<IWindowSystem> window = WindowSystemFactory::makeWindowSystem(Configuration::getInstance()->getConfiguration("WINSYS"));
	window->initWindow(argc, argv);
	
	/* get a renderer */
	IRenderer* r = RendererFactory::makeRenderer(config->getConfiguration("API"));
	r->setWindowManager(window.get());	// needed for the draw callback

	window->loop();

	return 0;
}