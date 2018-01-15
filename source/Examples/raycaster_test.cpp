#include "../Texture/Texture.hpp"
#include "../Drawable/Raycaster/Raycaster.hpp"
#include "../Wall/LinkedWall/LinkedWall.hpp"

int main()
{
	setlocale(LC_ALL, "");
	initscr();
	start_color();
	lustro::PixelData::initalizePixelDataPairs();
	lustro::Texture texture(10, 5), texture2(10, 5), texture3(10, 5), texture4(10, 5), texture5(10, 5);
	
	for(unsigned int i = 0; i != 5; i++)
	{
		texture.copy(lustro::Texture(10, 1, lustro::PixelData("x", COLOR_GREEN, COLOR_BLUE)), 0, i);
		texture2.copy(lustro::Texture(10, 1, lustro::PixelData(i, COLOR_RED, COLOR_YELLOW)), 0, i);	
		texture3.copy(lustro::Texture(10, 1, lustro::PixelData(i, COLOR_MAGENTA, COLOR_GREEN)), 0, i);
		texture4.copy(lustro::Texture(10, 1, lustro::PixelData(i, COLOR_YELLOW, COLOR_BLUE)), 0, i);
		texture5.copy(lustro::Texture(10, 1, ((i % 2) ? (lustro::PixelData(3, COLOR_BLACK, COLOR_BLACK)) 
					: (lustro::PixelData()))), 0, i);
	}
		
	std::vector<lustro::Wall*> walls;
	walls.push_back(new lustro::Wall(-2, -3, 0, -5, &texture));
	walls.push_back(new lustro::Wall(0, -5, 2, -3, &texture2));
	walls.push_back(new lustro::Wall(-2, -3, -2, 10, &texture3));
	walls.push_back(new lustro::Wall(2, -3, 2, 10, &texture4));
	walls.push_back(new lustro::Wall(-2, -3, 2, -3, &texture5));
	walls.push_back(new lustro::Wall(-2, 10, 2, 10, &texture5));
	walls.push_back(new lustro::Wall(-0.5, 14, 0.5, 14, &texture4));
	
	lustro::LinkedWall test;
	
	lustro::Raycaster raycaster;
	raycaster.setFov(70);
	raycaster.setSkyColor(lustro::PixelData(1, COLOR_WHITE, COLOR_BLACK));
	raycaster.setGroundColor(lustro::PixelData(2, COLOR_BLACK, COLOR_WHITE));
	raycaster.setSize(132, 44);
	raycaster.setPixelRatio(0.5);
	raycaster.setCameraRotation(10);
	
	int keyPressed;
	double rotation = 10, x = 0, y = 0;
	
	while(keyPressed = getch())
	{
		if(keyPressed == 97) rotation -= 5;
		if(keyPressed == 100) rotation += 5;
		if(keyPressed == 119)
		{
			x += 0.06*cos((rotation-90)/180*M_PI);
			y += 0.06*sin((rotation-90)/180*M_PI);
		}
		if(keyPressed == 115)
		{
			x -= 0.06*cos((rotation-90)/180*M_PI);
			y -= 0.06*sin((rotation-90)/180*M_PI);
		}
		while(rotation < 0) rotation += 360;
		while(rotation > 360) rotation -= 360;
	
		raycaster.setCameraRotation(rotation);
		raycaster.setCameraPosition(x, y);
	
		erase();
		raycaster.raycast(walls);
	
		for(unsigned int y = 0; y < raycaster.getHeight(); y++)
		{
			for(unsigned int x = 0; x < raycaster.getWidth(); x++)
			{
				attron(COLOR_PAIR(raycaster.getPixel(x, y).getPair()));
				printw(raycaster.getPixel(x, y).getSymbol().c_str());
				//printw("xd");
			}
			printw("\n");
		}
		attron(COLOR_PAIR(8));
		printw("x: %f, y: %f, rotation: %f, colorpairs: %d, keypressed:", (float)x, (float)y, (float)rotation,  (int)COLOR_PAIRS);
		printw(std::to_string(keyPressed).c_str());
		refresh();
	}
	
	refresh();
	getch();
	endwin();
	return 0;
}
