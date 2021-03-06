#include "pch.h"
#include "Application.h"
#include "Common.h"
#include "Resources.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "Sound.h"
#include "PersistantData.h"
#include "Input.h"
#include "Physics.h"

Application *Application::m_application = nullptr;

Application::Application()
{
}

void Application::Init()
{
	//performing initialization
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		LOG_DEBUG(SDL_GetError());
		exit(-1);
	}

	//setting openGL version to 4.2 
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	//setting openGL context to core, not compatibility
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	//creating window
	m_window = SDL_CreateWindow("GP3-COURSEWORK", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, m_windowWidth, m_windowHeight,
		SDL_WINDOW_OPENGL);

	SDL_CaptureMouse(SDL_TRUE);

	OpenGlInit();
	GameInit();
}

void Application::OpenGlInit()
{
	//creating context (our opengl statemachine in which all our GL calls will refer to)
	m_glContext = SDL_GL_CreateContext(m_window);
	CHECK_GL_ERROR();

	SDL_GL_SetSwapInterval(1);

	//initialsing glew (do this after establishing context!)
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		std::cout << "GLEW Error: " << glewGetErrorString(err) << std::endl;
		exit(-1);
	}

	//Smooth shading
	GL_ATTEMPT(glShadeModel(GL_SMOOTH));

	//enable depth testing
	GL_ATTEMPT(glEnable(GL_DEPTH_TEST));
	//set less or equal func for depth testing
	GL_ATTEMPT(glDepthFunc(GL_LEQUAL));

	//enabling blending
	glEnable(GL_BLEND);
	GL_ATTEMPT(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	//turn on back face culling
	GL_ATTEMPT(glEnable(GL_CULL_FACE));
	GL_ATTEMPT(glCullFace(GL_BACK));

	glDisable(GL_CULL_FACE);
}

void Application::GameInit()
{
	//loading all resources
	// Models - Room basics
	Resources::GetInstance()->AddModel("Models/Floor.obj");
	Resources::GetInstance()->AddModel("Models/Floor (Stairs).obj");
	Resources::GetInstance()->AddModel("Models/Roof.obj");
	Resources::GetInstance()->AddModel("Models/Walls (1 Door).obj");
	Resources::GetInstance()->AddModel("Models/Walls (2 Door - Straight).obj");
	Resources::GetInstance()->AddModel("Models/Walls (2 Door - Corner).obj");
	Resources::GetInstance()->AddModel("Models/Walls (3 Door).obj");
	Resources::GetInstance()->AddModel("Models/Walls (4 Door).obj");

	// Models - Room decorations
	Resources::GetInstance()->AddModel("Models/TopFloor (Straight).obj");
	Resources::GetInstance()->AddModel("Models/TopFloor (Corner).obj");
	Resources::GetInstance()->AddModel("Models/TopFloor (Single).obj");
	Resources::GetInstance()->AddModel("Models/Banner (Straight).obj");
	Resources::GetInstance()->AddModel("Models/Banner (Corner).obj");
	Resources::GetInstance()->AddModel("Models/Banner (Single).obj");
	Resources::GetInstance()->AddModel("Models/Banner (Stairs).obj");
	Resources::GetInstance()->AddModel("Models/TopFloor Chains (Straight).obj");
	Resources::GetInstance()->AddModel("Models/TopFloor Chains (Corner).obj");
	Resources::GetInstance()->AddModel("Models/TopFloor Chains (Single).obj");
	Resources::GetInstance()->AddModel("Models/ShortPillar (Full).obj");
	Resources::GetInstance()->AddModel("Models/TallPillar (Full).obj");
	Resources::GetInstance()->AddModel("Models/TallPillar (Half).obj");
	Resources::GetInstance()->AddModel("Models/TallPillar (Quarter).obj");
	Resources::GetInstance()->AddModel("Models/TallPillar (Single).obj");
	Resources::GetInstance()->AddModel("Models/Crate.obj");
	Resources::GetInstance()->AddModel("Models/Table.obj");
	Resources::GetInstance()->AddModel("Models/Chair.obj");
	Resources::GetInstance()->AddModel("Models/Cushion.obj");
	Resources::GetInstance()->AddModel("Models/Hedge (Small).obj");
	Resources::GetInstance()->AddModel("Models/Hedge (Large).obj");
	Resources::GetInstance()->AddModel("Models/HedgeBase (Small).obj");
	Resources::GetInstance()->AddModel("Models/HedgeBase (Large).obj");
	Resources::GetInstance()->AddModel("Models/Stairs.obj");
	Resources::GetInstance()->AddModel("Models/Stair Chains.obj");
	Resources::GetInstance()->AddModel("Models/StairsFrame.obj");
	Resources::GetInstance()->AddModel("Models/StairWalls.obj");
	Resources::GetInstance()->AddModel("Models/StairsPlane.obj");
	Resources::GetInstance()->AddModel("Models/Plane.obj");


	// Models - Other Level Requirements
	Resources::GetInstance()->AddModel("Models/Door.obj");
	Resources::GetInstance()->AddModel("Models/DoorFrame.obj");
	Resources::GetInstance()->AddModel("Models/DecorativeFlashing.obj");

	// Models - Player
	Resources::GetInstance()->AddModel("Models/Pan.obj");

	Log::NewLine();

	// Textures
	Resources::GetInstance()->AddTexture("Images/Textures/Tile (Simple).png");
	Resources::GetInstance()->AddTexture("Images/Textures/Brick (Simple).png");
	Resources::GetInstance()->AddTexture("Images/Textures/WoodPlanks (Simple).png");
	Resources::GetInstance()->AddTexture("Images/Textures/Tartan.png");
	Resources::GetInstance()->AddTexture("Images/Textures/Chains.png");
	Resources::GetInstance()->AddTexture("Images/Textures/Leaf.png");
	Resources::GetInstance()->AddTexture("Images/Textures/Ghost.png");
	Resources::GetInstance()->AddTexture("Images/Textures/Bat.png");
	Resources::GetInstance()->AddTexture("Images/Textures/Border 2.png");
	Resources::GetInstance()->AddTexture("Images/Textures/Button Default.png");
	Resources::GetInstance()->AddTexture("Images/Textures/Button Small.png");
	Resources::GetInstance()->AddTexture("Images/Textures/transition.png");
	Log::NewLine();

	// Shaders
	Resources::GetInstance()->AddShader(std::make_shared<ShaderProgram>(ASSET_PATH + "Shaders/simple_VERT.glsl", 
		ASSET_PATH + "Shaders/simple_FRAG.glsl"), 
		"simple"
	);
	Resources::GetInstance()->AddShader(std::make_shared<ShaderProgram>(ASSET_PATH + "Shaders/text_VERT.glsl",
		ASSET_PATH + "Shaders/text_FRAG.glsl"),
		"text"
	);
	Resources::GetInstance()->AddShader(std::make_shared<ShaderProgram>(ASSET_PATH + "Shaders/mask_VERT.glsl",
		ASSET_PATH + "Shaders/mask_FRAG.glsl"),
		"mask"
	);
	Log::NewLine();

	// Fonts
	Resources::GetInstance()->AddFont("Fonts/JMH Cthulhumbus Arcade UG.ttf");
	Resources::GetInstance()->AddFont("Fonts/Pixel Musketeer.ttf");
	Resources::GetInstance()->AddFont("Fonts/PixelNoise_erc_2007.ttf");
	Log::NewLine();

	// Sounds
	if (SoundManager::GetInstance()->InitMixer())
	{
		Resources::GetInstance()->AddSound("Audio/SFX/buttonClick.wav", SoundType::SOUNDTYPE_SFX);
		Resources::GetInstance()->AddSound("Audio/SFX/doorOpen.wav", SoundType::SOUNDTYPE_SFX);
		Resources::GetInstance()->AddSound("Audio/SFX/fryingPan.wav", SoundType::SOUNDTYPE_SFX);
		Resources::GetInstance()->AddSound("Audio/Music/Loyalty_Freak_Music_-_01_-_Monster_Parade.mp3", SoundType::SOUNDTYPE_MUSIC);
	}

	// Loading All Scenes
	SceneManager::GetInstance()->SetStartScene(GameScenes::GAMESCENE_MAINMENU);

	// Can't release unused resources due to the main game scene using procedural generation to create levels
	//Resources::GetInstance()->ReleaseUnusedResources();
}

void Application::Loop()
{
	m_appState = AppState::RUNNING;

	auto prevTicks = std::chrono::high_resolution_clock::now();
	SDL_Event event;

	while (m_appState != AppState::QUITTING)
	{
		// Handling Input Events
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				m_appState = AppState::QUITTING;
				break;
			case SDL_WINDOWEVENT_CLOSE:
				m_appState = AppState::QUITTING;
				break;
			case SDL_KEYDOWN:
				INPUT->SetHeldKey(event.key.keysym.sym, true);
				INPUT->SetDownKey(event.key.keysym.sym);
				break;
			case SDL_KEYUP:
				INPUT->SetHeldKey(event.key.keysym.sym, false);
				INPUT->SetUpKey(event.key.keysym.sym);
				break;
			case SDL_MOUSEBUTTONDOWN:
				INPUT->SetMouseDown(event.button);
				break;
			case SDL_MOUSEBUTTONUP:
				INPUT->SetMouseUp(event.button);
				break;
			case SDL_MOUSEMOTION:
				INPUT->MoveMouse(glm::ivec2(event.motion.xrel, event.motion.yrel));
				break;
			}
		}

		// Updating time between frames
		auto currentTicks = std::chrono::high_resolution_clock::now();
		float deltaTime = (float)std::chrono::duration_cast<std::chrono::microseconds>(currentTicks - prevTicks).count() / 100000;
		if (deltaTime > 0.5f)
			deltaTime = 0.5f;
		prevTicks = currentTicks;
		m_worldDeltaTime = deltaTime;
		
		// Ensures any scene changing happens outside of the update loops
		SceneManager::GetInstance()->CheckForSceneChange();

		// Updating game physics
 		Physics::GetInstance()->Update(deltaTime * m_physicsTimeScale);
		//update and render current scene entities
		SceneManager::GetInstance()->GetCurrentScene()->UpdateScene(deltaTime * m_updateTimeScale);

		// Resetting Mouse Movement of Input Manager
		// Resetting Up and Down Keys of Input Manager
		Input::GetInstance()->Reset();

		SDL_GL_SwapWindow(m_window);
	}
}

void Application::Quit()
{
	//Close SDL
	Physics::GetInstance()->Quit();
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_window);
	SDL_QuitSubSystem(SDL_INIT_EVERYTHING);
	SDL_Quit();
}

Application::~Application()
{

}

Application * Application::GetInstance()
{
	if (m_application == nullptr)
	{
		m_application = new Application();
	}
	return m_application;
}

void Application::Run()
{
	Init();
	Loop();
	Quit();
}