#include "Engine.hpp"

namespace lustro
{
	Engine::Engine() : Engine("textures.lus", "maps.lus", "animations.lus") {}
	
	Engine::Engine(std::string textureFile, std::string mapFile, std::string animationFile)
	{
		setlocale(LC_ALL, "");
		initscr();
		start_color();
		nodelay(stdscr, true);
		noecho();
		curs_set(0);
		//raw();
		cbreak();
		PixelData::initalizePixelDataPairs();
	
		// 0	  1	   2      3	      4	    5		 6	   7
		// black, red, green, yellow, blue, magenta, cyan, white
	
		playerX = 0;
		playerY = 0;
		playerRot = 0;
		
		key = -1;
		prevKey = -1;
		walkLock = logLock = inventoryVisible = false;
		repeatCounter = std::pair<int, unsigned int>(-1, 0);
		
		Inventory::addItem("Empty hand", "Just an empty hand.");

		drawables["defaultCamera"] = new Raycaster();
		drawables["defaultSpriteC"] = new Spritecaster();
		drawables["defaultLog"] = new Log();
		drawables["defaultToast"] = new Toast();
		drawables["defaultInventory"] = new Popup();

		loadTextures(textureFile);
		loadAnimations(animationFile);
		loadMaps(mapFile);
		
		currentMap = &(maps["default"]);
		drawables["defaultSkybox"] = currentMap->getSkybox();
	
		checkWindowSize();
		
			
		((Raycaster*)(drawables["defaultCamera"]))->setFov(70);
		((Raycaster*)(drawables["defaultCamera"]))->setPixelRatio(0.5);
		((Raycaster*)(drawables["defaultCamera"]))->setCameraRotation(playerRot);
		((Raycaster*)(drawables["defaultCamera"]))->setCameraPosition(playerX, playerY);

		drawables["defaultLog"]->setDepth(1);
		
		((Raycaster*)(drawables["defaultCamera"]))->setGroundColor(currentMap->getGroundColor());
		((Raycaster*)(drawables["defaultCamera"]))->setSkyColor(currentMap->getSkyColor());
	
		((Canvas*)(drawables["defaultSkybox"]))->setMode(3);
		((Canvas*)(drawables["defaultSkybox"]))->setDepth(std::numeric_limits<double>::infinity());
		
		((Popup*)(drawables["defaultInventory"]))->setText("Inventory");
		((Popup*)(drawables["defaultInventory"]))->setColor(PixelData(0, 7, 0));
		((Popup*)(drawables["defaultInventory"]))->setTextPosition(8);
		
		for(auto& i : drawables)
			renderer.bindDrawable(i.second, i.first);
	}
	
	void Engine::loadTextures(std::string file)
	{
		IniInterpreter::IniFile ini(file);
		for(auto& i : ini)
		{
			textures[i.first] = Texture(i.second.getVariable<int>("width"), i.second.getVariable<int>("height"), i.second.getVariable<std::string>("file"));
		}
	}
	
	void Engine::loadAnimations(std::string file)
	{
		IniInterpreter::IniFile ini(file);
		for(auto& i : ini)
		{
			animations[i.first] = Animation(i.second.getVariable<double>("framerate"));//, i.second.getVariable<int>("height"), i.second.getVariable<std::string>("file"));
			for(unsigned int j = 0 ;; j++)
			{
				if(!i.second.isVariable(std::to_string(j))) break; 
				animations[i.first].addFrame(
					&textures[i.second.getVariable<std::string>(std::to_string(j))]);
			}
		}
		Timer::start("delta");
	}
	
	void Engine::loadMaps(std::string file)
	{
		IniInterpreter::IniFile ini(file);
		for(auto& i : ini)
			maps[i.first] = Map(i.first, i.second.getVariable<std::string>("file"), &textures, &animations);
		
		for(auto& i : maps)
			i.second.linkWalls(maps);
		
		for(auto& i : maps)
			i.second.acceptLinkedWalls();
		
		for(auto& i : maps)
			i.second.linkEventContainers(maps, animations, textures, (Toast*)drawables["defaultToast"], (Log*)drawables["defaultLog"]);
		
		for(auto& i : maps)
			i.second.acceptEventContainers();
		
	}
	
	double Engine::toRad(double angle)
	{
		return angle*M_PI/180;
	}
	
	
	void Engine::setSize(int newSizeX, int newSizeY)
	{
		renderer = Renderer(newSizeX, newSizeY);
		int cameraHeight = newSizeY*0.9;
		drawables["defaultSkybox"]->setSize(newSizeX, cameraHeight);
		drawables["defaultSpriteC"]->setSize(newSizeX, cameraHeight);
		if(!logLock)
		{
			drawables["defaultLog"]->setSize(newSizeX, std::max(4, 1-cameraHeight));
			drawables["defaultLog"]->setPosition(0, newSizeY-std::max(4, 1-cameraHeight));
		}
		else
		{
			drawables["defaultLog"]->setSize(newSizeX, newSizeY*0.4);
			drawables["defaultLog"]->setPosition(0, newSizeY-((int)newSizeY*0.4));
		}
		drawables["defaultToast"]->setSize(newSizeX*0.8, 3);
		drawables["defaultToast"]->setPosition(newSizeX*0.1, newSizeY*0.8-3);
		drawables["defaultCamera"]->setSize(newSizeX, cameraHeight);
		if(!inventoryVisible)
		{
			drawables["defaultInventory"]->setSize(newSizeX*0.35, 3);
			drawables["defaultInventory"]->setPosition(newSizeX-(int)(newSizeX*0.35)-1, 1);
		}
		else
		{
		 	drawables["defaultInventory"]->setSize(newSizeX*0.35, 3+inventoryVisible*(Inventory::getItems().size()-1));
		}	drawables["defaultInventory"]->setPosition(newSizeX-(int)(newSizeX*0.35)-1, 1);
		
		sizeX = newSizeX;
		sizeY = newSizeY;
		for(auto& i : drawables)
			renderer.bindDrawable(i.second, i.first);
	}
	
	void Engine::checkWindowSize()
	{
		int currSizeX, currSizeY;
		getmaxyx(stdscr, currSizeY, currSizeX);
		if(sizeX != currSizeX/4*4 || sizeY != currSizeY/2*2)
			setSize(currSizeX/4*4, currSizeY/2*2);
	}
	
	void Engine::castInGameView()
	{
		Timer::start("castInGameView");
		
		((Raycaster*)(drawables["defaultCamera"]))->raycast(currentMap->getWalls());
		((Spritecaster*)(drawables["defaultSpriteC"]))->spritecast(currentMap->getSprites(), *(Raycaster*)(drawables["defaultCamera"]));
		
		Timer::stop("castInGameView");
	}
	
	void Engine::showBenchmarkMessage()
	{
		std::string mess = "pos: " + std::to_string(playerX) + ", " + std::to_string(playerY) + 
			+ ", controls: " + std::to_string(Timer::getMillis("controls")) +
			"ms, castInGameView: " + std::to_string(Timer::getMillis("castInGameView")) + "ms";
			
		((Toast*)drawables["defaultToast"])->start(mess);
		
		std::string fullmess = mess + ", rendering: " + std::to_string(Timer::getMillis("rendering")) + "ms,  displaying: " +  std::to_string(Timer::getMillis("displaying")) + "ms, deltaTime: " +  std::to_string(Timer::getMillis("delta")) + "ms, FPS: " + std::to_string(1000/Timer::getMillis("delta"));
		((Log*)drawables["defaultLog"])->addMessage(fullmess);
	}
	
	void Engine::loop()
	{
		Timer::next("delta");
		Timer::start("controls");

		if(key != -1) prevKey = key;
		key = getch();

		double translateX = 0;
		double translateY = 0;
		bool useKey = false;
		
		checkWindowSize();
		
		int desiredLogHeight = (int)std::max(0.4*sizeY*logLock+sizeY-((int)(0.9*sizeY)), 4.0);
		if(drawables["defaultLog"]->getHeight() != desiredLogHeight)
		{
			int newHeight = drawables["defaultLog"]->getHeight();
			if(newHeight < desiredLogHeight)
			{
			 	newHeight += (desiredLogHeight-newHeight)*0.2+1;
				newHeight = std::min(newHeight, desiredLogHeight);
			}
			else
			{
				newHeight -= (newHeight-desiredLogHeight)*0.2+1;
				newHeight = std::max(newHeight, desiredLogHeight);
			}
			drawables["defaultLog"]->setSize(sizeX, newHeight);
			drawables["defaultLog"]->setPosition(0, sizeY-newHeight);
		}
		
		int desiredInventoryHeight = 3+inventoryVisible*(Inventory::getItems().size()-1);
		if(desiredInventoryHeight > sizeY) desiredInventoryHeight = sizeY;
		
		if(drawables["defaultInventory"]->getHeight() != desiredInventoryHeight)
		{
			int newHeight = drawables["defaultInventory"]->getHeight();
			if(newHeight < desiredLogHeight)
			{
				newHeight += (desiredInventoryHeight-newHeight)*0.1+1;
				newHeight = std::min(newHeight, desiredInventoryHeight);
			}
			else
			{
				newHeight -= (newHeight-desiredInventoryHeight)*0.1+1;
				newHeight = std::max(newHeight, desiredInventoryHeight);
			}
			drawables["defaultInventory"] -> setSize(sizeX*0.35, newHeight);
		}
		
		if(prevKey == '\n' && key != '\n')
		{
			prevKey = -1;
			useKey = true;
		}
		
		if((prevKey == 'l' || prevKey == 'L') && key != 'l' && key != 'L')
		{
			prevKey = -1;
			logLock = !logLock;
		}
		
		if((prevKey == 'i' || prevKey == 'I') && key != 'i' && key != 'I')
		{
			prevKey = -1;
			inventoryVisible = !inventoryVisible;
		}
		
		if((prevKey == 'o' || prevKey == 'O') && key != 'o' && key != 'O')
		{
			prevKey = -1;
			Inventory::selectPreviousItem();
			if(inventoryVisible) ((Toast*)drawables["defaultToast"])->start(Inventory::getCurrentItem().second);
		}
			
		if((prevKey == 'p' || prevKey == 'P') && key != 'p' && key != 'P')
		{
			prevKey = -1;
			Inventory::selectNextItem();
			if(inventoryVisible) ((Toast*)drawables["defaultToast"])->start(Inventory::getCurrentItem().second);
		}
		
		if(key == repeatCounter.first)
			repeatCounter.second++;
		else
			repeatCounter = std::pair<int, unsigned int>(key, 1);
			
		if(repeatCounter.first == -1 && prevKey != -1 && key == -1)// && repeatCounter.second <= 20)
			key = prevKey;
		
		bool runBenchmark = false;
		
		switch(key)
		{
			case 'a':
			case 'A':
				translateX = cos(toRad(playerRot-90));
    			translateY = sin(toRad(playerRot-90));
				break;
				
			case 'w':
			case 'W':
				translateX = cos(toRad(playerRot));
				translateY = sin(toRad(playerRot));
				break;
				
			case 'd':
			case 'D':
				translateX = cos(toRad(playerRot+90));
    			translateY = sin(toRad(playerRot+90));
				break;
				
			case 's':
			case 'S':
				translateX = -cos(toRad(playerRot));
				translateY = -sin(toRad(playerRot));
				break;
				
			case 'q':
			case 'Q':
				playerRot -= 1*Timer::getMillis("delta")/Timer::appFramerate;
				break;
				
			case 'e':
			case 'E':
				playerRot += 1*Timer::getMillis("delta")/Timer::appFramerate;
				break;
			
			case 'b':
			case 'B':
				runBenchmark = true;
				key = -1;
				prevKey = -1;
				break;
		}
		
		std::string inventoryItemList = "> ";
		for(unsigned int i = Inventory::getCurrentItemID(); i < Inventory::getItems().size(); i++)
			inventoryItemList += Inventory::getItems()[i].first + '\n';
			
		for(unsigned int i = 0; i < Inventory::getCurrentItemID(); i++)
			inventoryItemList += Inventory::getItems()[i].first + '\n';
			
		((Popup*)(drawables["defaultInventory"]))->setText(inventoryItemList);
		
		if(walkLock && translateX == 0 && translateY == 0)
		{
			translateX = cos(toRad(playerRot));
			translateY = sin(toRad(playerRot));
		}
		
		double oldX = playerX, oldY = playerY;
		playerX += translateX*0.05*Timer::getMillis("delta")/(1000/Timer::appFramerate);
		playerY += translateY*0.05*Timer::getMillis("delta")/(1000/Timer::appFramerate);
		
		if(playerRot < 0) playerRot = 360 + playerRot;    
    	playerRot = int(floor(playerRot))%360 + (playerRot - floor(playerRot));
		
		std::string newMap = currentMap->checkCollisions(playerX, playerY, oldX, oldY);
		if(newMap != "")
		{
			currentMap = &maps[newMap];
			drawables["defaultSkybox"] = currentMap->getSkybox();
			drawables["defaultSkybox"]->setSize(sizeX, sizeY*0.9);
			((Canvas*)(drawables["defaultSkybox"]))->setMode(3);
			((Canvas*)(drawables["defaultSkybox"]))->setDepth(std::numeric_limits<double>::infinity());
			renderer.bindDrawable(drawables["defaultSkybox"], "defaultSkybox");
		}
			
		if(((Canvas*)(drawables["defaultSkybox"]))->getTexture() != nullptr)
			((Canvas*)(drawables["defaultSkybox"]))->setShift(playerRot/360*((Canvas*)(drawables["defaultSkybox"]))->getTexture()->getWidth(),0);
		
		((Raycaster*)(drawables["defaultCamera"]))->setCameraRotation(playerRot+90);
		((Raycaster*)(drawables["defaultCamera"]))->setCameraPosition(playerX, playerY);
		
		if(useKey) currentMap->checkInteractivity(playerX, playerY, playerRot);
		currentMap->updateObjects(playerX, playerY);
		currentMap->updateSprites();
		
		Timer::stop("controls");		
		
		castInGameView();
		
		Timer::start("rendering");
		
		renderer.update();
		renderer.render();
		
		Timer::stop("rendering");
		Timer::start("displaying");
		
		renderer.print();	
		
		Timer::stop("displaying");
		
		if(runBenchmark)
			showBenchmarkMessage();
	}
}
