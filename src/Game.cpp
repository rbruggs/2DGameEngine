#include "Game.h"
#include <iostream>
#include <SDL.h>

Game::Game() {
	isRunning = false;
	std::cout << "Game constructor called" << std::endl;
}

Game::~Game() {
	std::cout << "Game deconstructor called" << std::endl;
}

void Game::Initialize() {

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "Error initializing SDL." << std::endl;
		return;
	}
	
	//Create window
	SDL_DisplayMode displayMode;
	SDL_GetCurrentDisplayMode(0, &displayMode);
	windowWidth = 1920; //displayMode.w;
	windowHeight = 1080; //displayMode.h;

	window = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		windowWidth,
		windowHeight,
		SDL_WINDOW_BORDERLESS
		);

	if (!window) {
		std::cout << "Error creating SDL window" << std::endl;
		return;
	}

	//Create renderer
	renderer = SDL_CreateRenderer(
		window,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); //Enable accelerated GPU and VSYNC
	if (!renderer) {
	std::cout << "Error creating SDL renderer" << std::endl;
	}

	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

	isRunning = true;
}

void Game::Run() {
	while (isRunning) {
		ProcessInput();
		Update();
		Render();
	}
}

void Game::ProcessInput() {

	SDL_Event sdlEvent;

		while (SDL_PollEvent(&sdlEvent)) {
		switch(sdlEvent.type){
		case SDL_QUIT:
			isRunning = false;
			break;

		case SDL_KEYDOWN:
			if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
				isRunning = false;
			}

		}
	}

}

void Game::Update() {
	//TODO: Update game objects
}

void Game::Render() {
	SDL_SetRenderDrawColor(renderer, 111, 111, 111, 255);
	SDL_RenderClear(renderer);

	//TODO: Render game objects

	SDL_RenderPresent(renderer);
}

void Game::Destroy() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}