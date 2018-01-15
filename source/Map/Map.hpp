#ifndef MAP_HPP_INCLUDED
#define MAP_HPP_INCLUDED

#include <tuple>
#include <map>
#include "../Drawable/Canvas/Canvas.hpp"
#include "../Drawable/Log/Log.hpp"
#include "../Drawable/Toast/Toast.hpp"
#include "../Sprite2D/Sprite2D.hpp"
#include "../Object/Object.hpp"
#include "../Wall/Wall.hpp"
#include "../Wall/LinkedWall/LinkedWall.hpp"
#include "../IniInterpreter/IniFile.hpp"
#include "../PixelData/PixelData.hpp"
#include "../Object/EventContainer/EventContainer.hpp"
#include "../Object/EventContainer/Trigger/Trigger.hpp"
#include "../Object/EventContainer/Item/Item.hpp"
#include "../Object/EventContainer/Autotrigger/Autotrigger.hpp"
#include "../Event/AllEventHeaders.hpp"

namespace lustro
{
	class Map
	{
		public:
			Map();
			Map(std::string, std::string, std::map<std::string, Texture>*, std::map<std::string, Animation>*);
			bool loadFromFile(std::string, std::map<std::string, Texture>*, std::map<std::string, Animation>*);
			void copyWalls(std::string, double, double, double, double, double, double, bool, bool, double, double);
			void linkWalls(std::map<std::string, Map>& maps);
			void linkEventContainers(std::map<std::string, Map>& maps, std::map<std::string, Animation>& animations, std::map<std::string, Texture>& textures, Toast* toast, Log* log);

			void acceptLinkedWalls();
			void acceptEventContainers();
			void updateObjects(double x, double y);
			void checkInteractivity(double x, double y, double rot);
			void updateSprites();
			std::string checkCollisions(double& x, double& y, double oldX, double oldY);
			PixelData getGroundColor() const;
			PixelData getSkyColor() const;
			std::string getName() const;
			Canvas* getSkybox();
			const std::vector<Wall*>& getWalls() const;
			const std::vector<Sprite2D*>& getSprites() const;
			const std::vector<Object*>& getObjects() const;
			const std::vector<EventContainer*>& getEventContainers() const;
		private:
			static unsigned int collisionDepth;
			std::vector<Wall*> walls;
			std::vector<std::tuple<LinkedWall*, std::string, std::string>> notLoadedLinkedWalls;
			std::vector<Object*> objects;
			std::vector<EventContainer*> notLinkedEventContainers;
			std::vector<Sprite2D*> sprites;
			Canvas skybox;
			PixelData sky, ground;
			std::string mapPath;
			std::string name;
			//double skyboxDistance;
	};
}

#endif
