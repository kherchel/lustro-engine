#include "Map.hpp"

namespace lustro
{
	unsigned int Map::collisionDepth = 0;
	
	Map::Map() {}
	
	Map::Map(std::string name, std::string filename, std::map<std::string, Texture>* textures, std::map<std::string, Animation>* animations) : name(name), mapPath(filename)
	{
		loadFromFile(filename, textures, animations);
	}
	
	/*Map::Map(std::string filename)
	{
		if(!loadFromFile(filename)) printw("The map couldn't be loaded :(");
	}*/
	
	PixelData Map::getSkyColor() const
	{
		return sky;
	}
	
	PixelData Map::getGroundColor() const
	{
		return ground;
	}
	
	Canvas* Map::getSkybox()
	{
		return &skybox;
	}

	const std::vector<Sprite2D*>& Map::getSprites() const
	{
		return sprites;
	}
	
	const std::vector<Wall*>& Map::getWalls() const
	{
		return walls;
	}
	
	const std::vector<Object*>& Map::getObjects() const
	{
		return objects;
	}
	
	const std::vector<EventContainer*>& Map::getEventContainers() const
	{
		return notLinkedEventContainers;
	}
	
	void Map::copyWalls(std::string prefix, double x1, double y1, double x2, double y2, double translateX, double translateY, bool mirroredX, bool mirroredY, double originX, double originY)
	{
		std::vector<Wall*> nWalls;
		for(auto& i : walls)
			if(i->getX1() >= x1 && i->getX2() >= x1 && i->getY1() >= y1 && i->getY2() >= y1
				&& i->getX1() <= x2 && i->getX2() <= x2 && i->getY1() <= y2 && i->getY2() <= y2)
			{	
				double newX1 = ((mirroredX) ? (originX*2 - i->getX1()) : (i->getX1())) + translateX;
				double newX2 = ((mirroredX) ? (originX*2 - i->getX2()) : (i->getX2())) + translateX;
				double newY1 = ((mirroredY) ? (originY*2 - i->getY1()) : (i->getY1())) + translateY;
				double newY2 = ((mirroredY) ? (originY*2 - i->getY2()) : (i->getY2())) + translateY;
				
				nWalls.push_back(new Wall(newX1, newY1, newX2, newY2,
						i->getTexture(), i->isCollidable(), i->isLooping(), i->getActivityState())); 
				nWalls[nWalls.size()-1]->setName(prefix + i->getName());
			}
			
		for(auto& i : nWalls)
			walls.push_back(i);
			
		std::vector<std::tuple<LinkedWall*, std::string, std::string>> nLWalls;
		
		for(auto& i : notLoadedLinkedWalls)
			if(std::get<0>(i)->getX1() >= x1 && std::get<0>(i)->getX2() >= x1 && std::get<0>(i)->getY1() >= y1 && std::get<0>(i)->getY2() >= y1
				&& std::get<0>(i)->getX1() <= x2 && std::get<0>(i)->getX2() <= x2 && std::get<0>(i)->getY1() <= y2 && std::get<0>(i)->getY2() <= y2)
			{
				double newX1 = ((mirroredX) ? (originX*2 - std::get<0>(i)->getX2()) : (std::get<0>(i)->getX1())) + translateX;
				double newX2 = ((mirroredX) ? (originX*2 - std::get<0>(i)->getX1()) : (std::get<0>(i)->getX2())) + translateX;
				double newY1 = ((mirroredY) ? (originY*2 - std::get<0>(i)->getY2()) : (std::get<0>(i)->getY1())) + translateY;
				double newY2 = ((mirroredY) ? (originY*2 - std::get<0>(i)->getY1()) : (std::get<0>(i)->getY2())) + translateY;
				
				nLWalls.push_back(std::tuple<LinkedWall*, std::string, std::string>(
					new LinkedWall(newX1, newY1, newX2, newY2,
						std::get<0>(i)->getTexture(), std::get<0>(i)->isCollidable(), std::get<0>(i)->isLooping()),
					std::get<1>(i), std::get<2>(i)));
				std::get<0>(nLWalls[nLWalls.size()-1])->setName(prefix+std::get<0>(i)->getName());
				std::get<0>(nLWalls[nLWalls.size()-1])->setActivityState(std::get<0>(i)->getActivityState());
			}	
			
		for(auto& i : nLWalls)
			notLoadedLinkedWalls.push_back(i);
	}
	bool Map::loadFromFile(std::string filename, std::map<std::string, Texture>* textures, std::map<std::string, Animation>* animations)
	{
		IniInterpreter::IniFile ini(filename);
		
		if(!ini) return false;
		
		for(auto& i : ini)
		{

			std::string codeword = i.first.substr(0, i.first.find(' '));
			if(codeword == "Wall")
			{
				double x1, x2, y1, y2;
				std::string textureName;
				bool collidable, looping;
				
				x1 = i.second.getVariable<double>("x1");
				x2 = i.second.getVariable<double>("x2");
				y1 = i.second.getVariable<double>("y1");
				y2 = i.second.getVariable<double>("y2");
				
				textureName = i.second.getVariable<std::string>("texture");
				collidable = (!i.second.isVariable("collidable")
				 				|| i.second.getVariable<bool>("collidable"));
				 				
				looping = (!i.second.isVariable("looping")
				 				|| i.second.getVariable<bool>("looping"));
				 				
				walls.push_back(new Wall(x1, y1, x2, y2, &((*textures)[textureName]), collidable, looping));
				walls[walls.size()-1]->setName(i.first.substr(codeword.length()+1));
			}
			
			else if(codeword == "Object")
			{
				double x, y;
				std::string name = i.first.substr(codeword.length()+1), animationName;
				bool isActive;
				
				x = i.second.getVariable<double>("x");
				y = i.second.getVariable<double>("y");
				animationName = i.second.getVariable<std::string>("animation");
				isActive = (!i.second.isVariable("active")
				 				|| i.second.getVariable<bool>("active"));
			
				objects.push_back(new Object(
					name, x, y, isActive, ((*animations)[animationName])));
			}
			
			else if(codeword == "Item")
			{
				double x, y;
				std::string name = i.first.substr(codeword.length()+1), animationName;
				bool isActive;
				
				x = i.second.getVariable<double>("x");
				y = i.second.getVariable<double>("y");
				animationName = i.second.getVariable<std::string>("animation");
				isActive = (!i.second.isVariable("active")
				 				|| i.second.getVariable<bool>("active"));
			
				notLinkedEventContainers.push_back(new Item(
					name, x, y, isActive, ((*animations)[animationName])));
			}
			
			else if(codeword == "Trigger")
			{
				double x1, y1, x2, y2;
				std::string name = i.first.substr(codeword.length()+1);
				
				x1 = i.second.getVariable<double>("x1");
				x2 = i.second.getVariable<double>("x2");
				y1 = i.second.getVariable<double>("y1");
				y2 = i.second.getVariable<double>("y2");
				
				notLinkedEventContainers.push_back(new Trigger(name, x1, y1, x2, y2));
			}
			else if(codeword == "Autotrigger")
			{
				std::string name = i.first.substr(codeword.length()+1);
				bool isActive;
				
				isActive = (!i.second.isVariable("active") 
								|| i.second.getVariable<bool>("active"));		
		
				notLinkedEventContainers.push_back(new Autotrigger(
					name, isActive));
			}
			else if(codeword == "Sky" || codeword == "Ceiling")
			{
				std::string symbol;
				unsigned short int textColor, backgroundColor;
				
				symbol = i.second.getVariable<std::string>("symbol");
				textColor = i.second.getVariable<int>("textColor");
				backgroundColor = i.second.getVariable<int>("backgroundColor");
				
				sky = PixelData(symbol, textColor, backgroundColor);
			}
			
			else if(codeword == "CopyWalls")
			{
				double x1, y1, x2, y2, originX, originY;
				double translateX, translateY;
				bool mirroredX, mirroredY;
				std::string prefix;
				
				x1 = i.second.getVariable<double>("x1");
				y1 = i.second.getVariable<double>("y1");
				x2 = i.second.getVariable<double>("x2");
				y2 = i.second.getVariable<double>("y2");
				mirroredX = i.second.isVariable("originX");
				originX = i.second.getVariable<double>("originX");
				mirroredY = i.second.isVariable("originY");
				originY = i.second.getVariable<double>("originY");
				
				
				translateX = i.second.getVariable<double>("translateX");
				translateY = i.second.getVariable<double>("translateY");
				prefix = i.second.getVariable<std::string>("prefix");
				
				copyWalls(prefix, std::min(x1, x2), std::min(y1, y2),
						std::max(x1, x2), std::max(y1, y2), translateX, translateY, mirroredX, mirroredY, originX, originY);

			}
			
			else if(codeword == "Ground" || codeword == "Floor")
			{
				std::string symbol;
				unsigned short int textColor, backgroundColor;
				
				symbol = i.second.getVariable<std::string>("symbol");
				textColor = i.second.getVariable<int>("textColor");
				backgroundColor = i.second.getVariable<int>("backgroundColor");
				
				ground = PixelData(symbol, textColor, backgroundColor);
			}
			
			else if(codeword == "Skybox")
			{
				std::string textureName;
				textureName = i.second.getVariable<std::string>("texture");
				
				skybox = Canvas(&((*textures)[textureName]));
			}
			
			else if(codeword == "LinkedWall")
			{
				double x1, x2, y1, y2;
				std::string textureName;
				std::string linkMap, linkWall, wallName = "";
				bool collidable;
				
				if(i.first.length() != codeword.length())
					wallName = i.first.substr(codeword.length()+1);
					
				if(wallName == "")continue;
				
				x1 = i.second.getVariable<double>("x1");
				x2 = i.second.getVariable<double>("x2");
				y1 = i.second.getVariable<double>("y1");
				y2 = i.second.getVariable<double>("y2");
				textureName = i.second.getVariable<std::string>("texture");
				collidable = (!i.second.isVariable("collidable")
				 				|| i.second.getVariable<bool>("collidable"));
				 				
				
				linkMap = i.second.getVariable<std::string>("linkMap");
				linkWall = i.second.getVariable<std::string>("linkWall");
			
				notLoadedLinkedWalls.push_back(std::tuple<LinkedWall*, std::string, std::string>
					(new LinkedWall(x1, y1, x2, y2, &((*textures)[textureName]), collidable, false), linkMap, linkWall));
				std::get<0>(notLoadedLinkedWalls[notLoadedLinkedWalls.size() - 1])->setName(wallName);
			}
		}
		
		updateSprites();
			
		return true;
	}
	
	std::string Map::getName() const
	{
		return name;
	}
	
	void Map::linkWalls(std::map<std::string, Map>& maps)
	{
		for(auto& i : notLoadedLinkedWalls)
		{
			if(maps.count(std::get<1>(i)) == 0) continue;
			for(auto& j : maps[std::get<1>(i)].notLoadedLinkedWalls)
			{
				if(std::get<0>(j)->getName() == std::get<2>(i))
				{
					std::get<0>(i)->link(&maps[std::get<1>(i)], std::get<0>(j));
					break;
				}	 
			}
		}	
	}
	
	std::string Map::checkCollisions(double& x, double& y, double oldX, double oldY)
	{
		if(collisionDepth == 9) return "";
		if(x == oldX && y == oldY) return "";
		double rot = atan2(y-oldY, x-oldX) - M_PI*0.5;
		collisionDepth++;
		double A, B, C, sq;
		if(sin(rot) == 0)
		{
			A = 1;
			B = 0;
			C = -oldX;
		}
		else if(cos(rot) == 0)
		{
			A = 0;
			B = 1;
			C = -oldY;
		}
		else
		{
			A = -1./tan(rot);
			B = -1;
			C = oldY - A*oldX;
		}
		
		sq = sqrt(A*A+B*B);
		double closestX = std::numeric_limits<double>::infinity();
		double closestY = closestX;
		Wall* closestWall = nullptr;
		for(auto& i: walls)
		{
			
			if(!(i->isCollidable())) continue;  
			double collisionPointX = 0, collisionPointY = 0, wg = 0;
			wg = A*i->getB() - B*i->getA();
			if(wg == 0) continue;
			collisionPointX = (B*i->getC() - C*i->getB())/wg;
			collisionPointY = (C*i->getA() - A*i->getC())/wg;
			if(fabs(x*i->getA()+y*i->getB()+i->getC()) / i->getSqrt() >= 0.005)
			{
				if(!(i->isPointOnWall(collisionPointX, collisionPointY))) continue;
				if(std::max(x, oldX) < collisionPointX || std::min(x, oldX) > collisionPointX
					|| std::max(y, oldY) < collisionPointY || std::min(y, oldY) > collisionPointY) continue;
				
			}
			
			if((oldX-closestX)*(oldX-closestX) + (oldY-closestY)*(oldY-closestY) <
				(oldX-collisionPointX)*(oldX-collisionPointX) + (oldY-collisionPointY)*(oldY-collisionPointY)) continue;
			
			closestX = collisionPointX;
			closestY = collisionPointY;
			closestWall = i;
		}
		if(closestWall == nullptr)
		{
			collisionDepth--;
			return "";
		}
		
		std::string ret = closestWall->applyCollision(x, y, oldX, oldY, closestX, closestY);
		if(ret == "")ret = checkCollisions(x, y, oldX, oldY);
		collisionDepth--;
		return ret;
	}
	
	void Map::updateSprites()
	{
		sprites.clear();
		for(auto& i : objects)
		{
			sprites.push_back(i->getSprite2D());
		}
	}
	
	void Map::updateObjects(double x, double y)
	{
		for(auto& i : objects)
		{
			i->update(x, y);
		}
	}
	
	void Map::checkInteractivity(double x, double y, double rot)
	{
		for(auto& i : objects)
		{
			i->checkInteractivity(x, y, rot);
		}
	}
	
	void Map::acceptLinkedWalls()
	{
		for(auto& i : notLoadedLinkedWalls)
		{
			walls.push_back(std::get<0>(i));
		}
		notLoadedLinkedWalls.clear();
	}
	
	void Map::linkEventContainers(std::map<std::string, Map>& maps, 
		std::map<std::string, Animation>& animations, std::map<std::string, Texture>& textures, Toast* toast, Log* log)
	{
		for(auto& i : notLinkedEventContainers)
		{
			std::string eventFilePath = mapPath.substr(0, mapPath.find(".")) + "_" + i->getName() + ".lus";
			IniInterpreter::IniFile file(eventFilePath);
			if(!file) continue;
			
			for(auto& j : file)
			{
				std::string codeword = j.first.substr(0, j.first.find(' '));
				if(codeword == "ChangeAnimationEvent")
					i->addEvent(
						new ChangeAnimationEvent(&maps, &animations, &(j.second)), j.second.getVariable<std::string>("group"), j.second.getVariable<int>("step"));
				
				else if(codeword == "ChangeTextureEvent")
					i->addEvent(
						new ChangeTextureEvent(&maps, &textures, &(j.second)), j.second.getVariable<std::string>("group"), j.second.getVariable<int>("step"));
				
				else if(codeword == "ChangeSkyboxEvent")
					i->addEvent(
						new ChangeSkyboxEvent(&maps, &textures, &(j.second)), j.second.getVariable<std::string>("group"), j.second.getVariable<int>("step"));
				
				else if(codeword == "ChangeObjectStateEvent")
					i->addEvent(
						new ChangeObjectStateEvent(&maps, &(j.second)), j.second.getVariable<std::string>("group"), j.second.getVariable<int>("step"));
				
				else if(codeword == "ChangeWallStateEvent")
					i->addEvent(
						new ChangeWallStateEvent(&maps, &(j.second)), j.second.getVariable<std::string>("group"), j.second.getVariable<int>("step"));
				
				else if(codeword == "SetVariableEvent")
					i->addEvent(
						new SetVariableEvent(&(j.second)), j.second.getVariable<std::string>("group"), j.second.getVariable<int>("step"));
				
				else if(codeword == "WaitEvent")
					i->addEvent(
						new WaitEvent(&(j.second)), j.second.getVariable<std::string>("group"), j.second.getVariable<int>("step"));
				
				else if(codeword == "WaitForVariableEvent")
					i->addEvent(
						new WaitForVariableEvent(&(j.second)), j.second.getVariable<std::string>("group"), j.second.getVariable<int>("step"));
			
				else if(codeword == "DisplayMessageEvent")
					i->addEvent(
						new DisplayMessageEvent(toast, log, &(j.second)), j.second.getVariable<std::string>("group"), j.second.getVariable<int>("step"));
			
				else if(codeword == "AddItemEvent")
					i->addEvent(
						new AddItemEvent(&(j.second)), j.second.getVariable<std::string>("group"), j.second.getVariable<int>("step"));
			
				else if(codeword == "LinkWallEvent")
					i->addEvent(
						new LinkWallEvent(&maps, &(j.second)), j.second.getVariable<std::string>("group"), j.second.getVariable<int>("step"));
					
				else
					i->setMode(j.first, j.second.getVariable<std::string>("mode"));	
				
			}
							
		}
				
	} 
	
	void Map::acceptEventContainers()
	{
		for(auto& i : notLinkedEventContainers)
		{
			objects.push_back(i);
		}
		notLinkedEventContainers.clear();
	}
	
}
