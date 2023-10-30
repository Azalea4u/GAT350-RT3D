#include "World01.h"
#include "World02.h"
#include "World03.h"
#include "World04.h"
#include "World05.h"
#include "Core/Core.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"

using namespace std;

int main(int argc, char* argv[])
{
	nc::StringUtils stringUtils;

	// Test ToUpper function
	std::string upperText = stringUtils.ToUpper("Hello, World!");
	std::cout << "ToUpper: " << upperText << std::endl;

	// Test ToLower function
	std::string lowerText = stringUtils.ToLower("Hello, World!");
	std::cout << "ToLower: " << lowerText << std::endl;

	// Test IsEqualIgnoreCase function
	bool isEqual = stringUtils.IsEqualIgnoreCase("Hello", "hello");
	std::cout << "IsEqualIgnoreCase: " << (isEqual ? "true" : "false") << std::endl;

	// Test CreateUnique function
	std::string uniqueText1 = stringUtils.CreateUnique("Test");
	std::cout << "CreateUnique 1: " << uniqueText1 << std::endl;

	std::string uniqueText2 = stringUtils.CreateUnique("Test");
	std::cout << "CreateUnique 2: " << uniqueText2 << std::endl;

	/*
	INFO_LOG("Initialize Engine...")

	//nc::MemoryTracker::Initialize();
	nc::seedRandom((unsigned int)time(nullptr));
	nc::setFilePath("assets");

	ENGINE.Initialize();

	auto world = make_unique<nc::World05>();
	world->Initialize();

	// main loop
	bool quit = false;
	while (!quit)
	{
		// update
		ENGINE.Update();
		quit = ENGINE.IsQuit();

		world->Update(ENGINE.GetTime().GetDeltaTime());

		// draw
		world->Draw(*ENGINE.GetSystem<nc::Renderer>());
	}

	world->Shutdown();
	ENGINE.Shutdown();*/

	return 0;
}
