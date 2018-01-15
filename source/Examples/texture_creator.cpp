#include "../Texture/Texture.hpp"
#include "../Renderer/Renderer.hpp"
#include "../Drawable/Raycaster/Raycaster.hpp"
#include "../Drawable/Canvas/Canvas.hpp"
#include "../Printer/Printer.hpp"

void fillTexture(lustro::Texture* texture, unsigned int x, unsigned int y, lustro::PixelData pixelData)
{
	lustro::PixelData last = texture->getPixelData(x, y);
	texture->setPixel(x, y, pixelData);
	if(last == texture->getPixelData(x, y)) return;
	if(x > 0 && texture->getPixelData(x-1, y) == last) fillTexture(texture, x-1, y, pixelData);
	if(x < texture->getWidth()-1 && texture->getPixelData(x+1, y) == last) fillTexture(texture, x+1, y, pixelData);
	if(y > 0 && texture->getPixelData(x, y-1) == last) fillTexture(texture, x, y-1, pixelData);
	if(y < texture->getHeight()-1 && texture->getPixelData(x, y+1) == last) fillTexture(texture, x, y+1, pixelData);
}

void saveTexture(lustro::Texture* texture, std::string filename)
{
	std::ofstream file(filename);
	for(unsigned int y = 0; y < texture->getHeight(); y++)
	{
		for(unsigned int x = 0; x < texture->getWidth(); x++)
		{
			std::string out;
			if(lustro::PixelData::getDensityFromUnicode(texture->getPixelData(x, y).getSymbol()) != 6)
				out += "\\"+std::to_string(lustro::PixelData::getDensityFromUnicode(texture->getPixelData(x, y).getSymbol()));
			else
				out += texture->getPixelData(x, y).getSymbol();
				
			out += std::to_string(texture->getPixelData(x, y).getRawPair().first);
			out += std::to_string(texture->getPixelData(x, y).getRawPair().second);
			
			file << out << " ";
		}
		file << "\n";
	}
	file.close();
}

void wallTexCreator(int sizeX, int sizeY, std::string filename, bool preview)
{
	erase();

	std::vector<lustro::PixelData> pixels;
	std::vector<lustro::Wall*> walls;
	
	lustro::PixelData defaultPixelData = lustro::PixelData(1, COLOR_MAGENTA, COLOR_GREEN);
	
	lustro::Texture texture(sizeX, sizeY, defaultPixelData);
	
	walls.push_back(new lustro::Wall(-2, 2, 2, 2, &texture, false, false));
	walls.push_back(new lustro::Wall(2, 2, 2, 0, &texture, false, false));
	walls.push_back(new lustro::Wall(2, 0, 6, 0, &texture, false, false));
	walls.push_back(new lustro::Wall(6, 0, 6, -4, &texture));
	walls.push_back(new lustro::Wall(6, -4, 2, -4, &texture));
	walls.push_back(new lustro::Wall(2, -4, -2, 0, &texture));
	walls.push_back(new lustro::Wall(-2, 0, -2, 2, &texture));
	
	lustro::Renderer renderer(132, 44);
	lustro::Raycaster raycaster;
	if(preview)
	{
		raycaster.setFov(70);
		raycaster.setSkyColor(lustro::PixelData(1, COLOR_WHITE, COLOR_BLACK));
		raycaster.setGroundColor(lustro::PixelData(2, COLOR_BLACK, COLOR_WHITE));
		raycaster.setSize(132-sizeX*2-5, 44);
		raycaster.setPosition(sizeX*2+5, 0);
		raycaster.setPixelRatio(0.5);
		raycaster.setCameraRotation(0);
		raycaster.setCameraPosition(0, 0);
	}
	
	lustro::Canvas canvas(&texture);
	canvas.setSize(sizeX*2, sizeY);
	
	lustro::Texture GUITexture(sizeX, sizeY);
	lustro::Canvas GUI(&GUITexture);
	GUI.setSize(sizeX*2, sizeY);
	
	lustro::Texture statusTexture(4, 2);
	lustro::Canvas status(&statusTexture);
	status.setSize(8, 4);
	status.setPosition(0, sizeY+2);
	
	lustro::Texture helpDialogTexture(58, 20, lustro::PixelData(0, COLOR_WHITE, COLOR_BLACK));
	lustro::Canvas helpDialog(&helpDialogTexture);
	helpDialog.setSize(132, 44);
	helpDialog.setMode(2);
	helpDialog.setDepth(10);
	
// RAW STRING BELOW
	
	lustro::Printer::addTextToTexture(&helpDialogTexture, 1, 1,
	R"raw(lustro-texture-creator by Kacper "kacperski1" Herchel

Keybindings:

H     - close (or open!) this window
WSAD  - move the cursor around
Enter - place a pixel
[     - change text color (0-7)
]     - change background color (0-7)
\     - change symbol (1-5 or any)
E     - pick color
F     - fill
R     - swap primary and secondary colors
Q     - toggle continous drawing mode
U     - undo the last action
P     - save your texture)raw", 
	COLOR_WHITE, COLOR_BLACK);
	
// RAW STRING ABOVE
	
	if(preview) renderer.bindDrawable((lustro::Drawable*)(&raycaster), "default");
	renderer.bindDrawable(&canvas, "canvas");
	renderer.bindDrawable(&GUI, "GUI");
	renderer.bindDrawable(&helpDialog, "helpDialog");
	renderer.bindDrawable(&status, "status");
	
	noecho();
	nodelay(stdscr, true);
	
	double rot = 0;
	int cursorX = 0;
	int cursorY = 0;
	int key = -1;
	bool showHelp = true;
	bool continousDrawing = false;
	
	unsigned int textColor = 7;
	unsigned int backgroundColor = 0;
	std::string symbol = "s1";
	
	unsigned int secondTextColor = 0;
	unsigned int secondBackgroundColor = 7;
	std::string secondSymbol = "s3";
	
	while(true)
	{
		key = getch();
		switch(key)
		{
			case 'w': case 'W': cursorY--; break;
			case 's': case 'S': cursorY++; break;
			case 'a': case 'A': cursorX--; break;
			case 'd': case 'D': cursorX++; break;
			case '\n':
				if(symbol.length() < 2) texture.setPixel(cursorX, cursorY, lustro::PixelData(symbol, textColor, backgroundColor));
				else texture.setPixel(cursorX, cursorY, lustro::PixelData(symbol[1]-'0'-1, textColor, backgroundColor));
				break;
			case 'Q': case 'q': continousDrawing = !continousDrawing; break;
			case 'E': case 'e':
				textColor = texture.getPixelData(cursorX, cursorY).getRawPair().first;
				backgroundColor = texture.getPixelData(cursorX, cursorY).getRawPair().second;
				symbol = texture.getPixelData(cursorX, cursorY).getSymbol();
				if(lustro::PixelData::getDensityFromUnicode(symbol) != 6)
					symbol = std::string("s")+std::to_string(lustro::PixelData::getDensityFromUnicode(symbol)+1);
				break;
			case 'F': case 'f':
				if(symbol.length() > 1)
					fillTexture(&texture, cursorX, cursorY, lustro::PixelData(symbol[1]-'0'-1, textColor, backgroundColor));
				else
					fillTexture(&texture, cursorX, cursorY, lustro::PixelData(symbol, textColor, backgroundColor));
				break;
			case 'P': case 'p':
				saveTexture(&texture, filename);
				break;
			case 'R': case 'r':
				std::swap(textColor, secondTextColor);
				std::swap(backgroundColor, secondBackgroundColor);
				std::swap(symbol, secondSymbol);
				break;
			case '[':
				nodelay(stdscr, false);
				key = getch();
				nodelay(stdscr, true);
				if(key >= '0' && key <= '7') textColor = key-'0';
				break;
			case ']':
				nodelay(stdscr, false);
				key = getch();
				nodelay(stdscr, true);
				if(key >= '0' && key <= '7') backgroundColor = key-'0';
				break;
			case '\\':
				nodelay(stdscr, false);
				key = getch();
				nodelay(stdscr, true);
				if(key >= '1' && key <= '5') symbol = std::string("s")+(char)key;
				else if(key != '\n') symbol = std::string()+(char)key;
				break;
			case 't': case 'T':
				std::swap(textColor, backgroundColor);
				break;
			case 'h': case 'H':
				if(showHelp)
				{
					renderer.unbindDrawable("helpDialog");
					showHelp = false;
				}
				else
				{
					renderer.bindDrawable(&helpDialog, "helpDialog");
					showHelp = true;
				}
				break;
		}
		
		cursorX %= sizeX;
		cursorY %= sizeY;
		
		if(cursorX < 0) cursorX = sizeX-1;
		if(cursorY < 0) cursorY = sizeY-1;
		
		GUITexture = lustro::Texture(sizeX, sizeY);
		GUITexture.setPixel(cursorX, cursorY, lustro::PixelData(1, COLOR_WHITE, COLOR_RED));
	
		statusTexture.setPixel(0, 0, lustro::PixelData(0, textColor, textColor));
		statusTexture.setPixel(1, 0, lustro::PixelData(0, backgroundColor, backgroundColor));
		if(symbol.length() < 2)
		{
			//statusTexture.setPixel(2, 0, lustro::PixelData(symbol, COLOR_WHITE, COLOR_BLACK));
			statusTexture.setPixel(3, 0, lustro::PixelData(symbol, textColor, backgroundColor));
		}
		else
		{
			//statusTexture.setPixel(2, 0, lustro::PixelData(symbol[1]-'0'-1, COLOR_WHITE, COLOR_BLACK));
			statusTexture.setPixel(3, 0, lustro::PixelData(symbol[1]-'0'-1, textColor, backgroundColor));
		}
		
		statusTexture.setPixel(0, 1, lustro::PixelData(0, secondTextColor, secondTextColor));
		statusTexture.setPixel(1, 1, lustro::PixelData(0, secondBackgroundColor, secondBackgroundColor));
		if(secondSymbol.length() < 2)
		{
			//statusTexture.setPixel(2, 1, lustro::PixelData(secondSymbol, COLOR_WHITE, COLOR_BLACK));
			statusTexture.setPixel(3, 1, lustro::PixelData(secondSymbol, secondTextColor, secondBackgroundColor));
		}
		else
		{
			//statusTexture.setPixel(2, 1, lustro::PixelData(secondSymbol[1]-'0'-1, COLOR_WHITE, COLOR_BLACK));
			statusTexture.setPixel(3, 1, lustro::PixelData(secondSymbol[1]-'0'-1, secondTextColor, secondBackgroundColor));
		}
		
		rot += 0.5;
		rot = int(rot)%360 + rot - int(rot);
		if(preview) raycaster.setCameraRotation(rot);
	
		if(preview)
		{
			renderer.clear();
			raycaster.raycast(walls);
			renderer.update();
			renderer.render();
			renderer.print();
		}
	}
}

void spriteCreator(int sizeX, int sizeY, std::string filename)
{
}

int main()
{
	setlocale(LC_ALL, "");
	initscr();
	start_color();
	//nodelay(stdscr, true);
	//noecho();
	cbreak();
	lustro::PixelData::initalizePixelDataPairs();
	// 0	  1	   2      3	      4	    5		 6	   7
	// black, red, green, yellow, blue, magenta, cyan, white
	
	//wallTexCreator(16, 16, "assets/textures/wall1.lus");
	
	mvprintw(2, 2, "lustro-texture-creator");
	mvprintw(3, 2, "Choose your destiny:");
	mvprintw(4, 3, "N) Create a new texture");
	mvprintw(5, 3, "L) Edit an existing texture");
	mvprintw(6, 3, "Q) Quit");
	refresh();
	char pressed = getch();
	std::string filename, temporary;
	int sizeX, sizeY;
	
	switch(pressed)
	{
		case 'N':
		case 'n':
			erase();
			mvprintw(2, 2, "What do you want your texture to be called? (no extension): ");
			refresh();
			while(pressed = getch())
			{
				if(pressed == '\n') break;
				filename += pressed;
			}
			erase();
			mvprintw(2, 2, "Please enter the width of your texture: ");
			refresh();
			temporary = "";
			while(pressed = getch())
			{
				if(pressed == '\n') break;
				temporary += pressed;
			}
			sizeX = std::stoi(temporary);
			erase();
			mvprintw(2, 2, "Please enter the height of your texture: ");
			refresh();
			temporary = "";
			while(pressed = getch())
			{
				if(pressed == '\n') break;
				temporary += pressed;
			}
			sizeY = std::stoi(temporary);
			erase();
			if(sizeX <= 0 || sizeY <= 0 || sizeX > 130 || sizeY > 100)
			{
				mvprintw(2, 2, "Incorrect size chosen! Quitting...");
				refresh();
				getch();
				endwin();
				return 0;
			}
			mvprintw(2, 2, ("Do you want your texture ("+filename+".lus) to be...:").c_str());
			mvprintw(3, 3, "W) A wall texture");
			mvprintw(4, 3, "S) A sprite");
			mvprintw(5, 3, "X) A skybox");
			refresh();
			pressed = getch();
			switch(pressed)
			{
				case 'W':
				case 'w':
					wallTexCreator(sizeX, sizeY, "assets/textures/"+filename+".lus", true);
					break;
				case 'S':
				case 's':
					spriteCreator(sizeX, sizeY, "assets/textures/"+filename+".lus");
					break;
				case 'X':
				case 'x':
					wallTexCreator(sizeX, sizeY, "assets/textures/"+filename+".lus", false);
					break;
				default:
					endwin();
					return 0;
					break;
			}
			break;
			
			case 'L':
			case 'l':
				erase();
				mvprintw(2, 2, "Yeah right, like this is implemented. Quitting...");
				refresh();
				getch();
				endwin();
				return 0;
	}
	
	endwin();
	return 0;
}
