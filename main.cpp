#include <SDL.h>
#include <stdio.h>
#include <string>

#include "player.h"
#include "graphics.h"
#include "scene.h"
#include "screen.h"

//Custom object
Object CreateBox(float x, float y, float z, float size) {

	Object box;

	//Front and back
	box.addVertex(	{x, y, z},
				{x, y + size, z},
				{x, y, z - size});
	
	box.addVertex(	{x, y, z - size},
				{x, y + size, z - size},
				{x, y + size, z});

	box.addVertex(	{x + size, y, z},
				{x + size, y + size, z},
				{x + size, y, z - size});
	
	box.addVertex(	{x + size, y, z - size},
				{x + size, y + size, z - size},
				{x + size, y + size, z});

	//Left and right
	box.addVertex(	{x, y, z},
				{x + size, y, z},
				{x, y, z - size});
	
	box.addVertex(	{x, y, z - size},
				{x + size, y, z - size},
				{x + size, y, z});

	box.addVertex(	{x, y + size, z},
				{x + size, y + size, z},
				{x, y + size, z - size});
	
	box.addVertex(	{x, y + size, z - size},
				{x + size, y + size, z - size},
				{x + size, y+ size, z});

	//Bottom and top
	box.addVertex(	{x, y, z},
				{x + size, y, z},
				{x, y + size, z});
	
	box.addVertex(	{x + size, y + size, z},
				{x + size, y, z},
				{x, y + size, z});

	box.addVertex(	{x, y, z - size},
				{x + size, y, z - size},
				{x, y + size, z - size});
	
	box.addVertex(	{x + size, y + size, z - size},
				{x + size, y, z - size},
				{x, y + size, z - size});

	return box;
}

int main( int argc, char* args[] )
{

	//Screen instance
	Screen screen(1280, 720, 60);

	//Creates player instance
	Player player(&screen);
	
	//Create scene instance with pointer to player instance as parameter
	Scene scene(&player, &screen);
	scene.drawDistance = 15;

	//Draw random scene
	srand (time(NULL));

	int boxes = 250;
	Object box[boxes][boxes];

	for (int x = 0; x < boxes; x++) {
		for (int y = 0; y < boxes; y++) {
			float xPos = x;
			float yPos = y;
			float zPos = floor((4*sin(xPos/20) + 3*sin(xPos/5) + 5*cos(xPos/50)) + (4*cos(yPos/15) + 3*cos(yPos/7) + 5*sin(yPos/55)));
			box[x][y] = CreateBox(xPos, yPos, zPos, 1);
			box[x][y].setColor(0, rand() % 50 + 150, 0);	
			scene.addObject(&box[x][y]);
		}
	}

	player.x = ((float) boxes)/2;
	player.y = ((float) boxes)/2;
	player.z = -5;

	Object viewBox = CreateBox(0, 0, 0, 1);
	scene.addObject(&viewBox);

	//Start up SDL and create window
	if(!screen.init())
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Main loop flag
		bool quit = false;

		//Event handler
		SDL_Event e;

		//While application is running
		while( !quit )
		{
			//Handle events on queue
			while( SDL_PollEvent( &e ) != 0 )
			{
				//User requests quit
				if( e.type == SDL_QUIT ) quit = true;

			}

			//Update player
			player.update();

			//Render scene
			scene.renderScene();

			//Prints render time
			printf("Render time: %f\n", scene.getRenderTime());

		}
	}

	return 0;
}







