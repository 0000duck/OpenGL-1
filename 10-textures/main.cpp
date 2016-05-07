#include "Configuration.h"
#include "RendererFactory.h"

//#define CRTDBG_MAP_ALLOC
//#include <crtdbg.h>

int main(void) 
{
	//_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	Configuration *config = Configuration::getInstance();
	config->load("config.cfg");

	std::string type = config->getConfiguration("API");

	IRenderer* renderer = RendererFactory::makeRenderer(type);

	renderer->loop();

	return 0;
}