#include "../Texture/Texture.hpp"
#include "../Drawable/Raycaster/Raycaster.hpp"
#include "../Drawable/Spritecaster/Spritecaster.hpp"
#include "../Drawable/Toast/Toast.hpp"
#include "../Drawable/Log/Log.hpp"
#include "../Drawable/Popup/Popup.hpp"
#include "../Map/Map.hpp"
#include "../IniInterpreter/IniFile.hpp"
#include "../Renderer/Renderer.hpp"
#include "../Inventory/Inventory.hpp"
#include "../Printer/Printer.hpp"

#include <sys/types.h>
#include "../Timer/Timer.hpp"
#include <ncurses.h>
#include <string>
#include <map>

namespace lustro
{
	class Engine
	{
		public:
			Engine();
			Engine(std::string, std::string, std::string);
			void loadTextures(std::string);
			void loadAnimations(std::string);
			void loadMaps(std::string);
			void loop();
		private:
			std::map<std::string, Drawable*> drawables;
			std::map<std::string, Texture> textures;
			std::map<std::string, Animation> animations;
			std::map<std::string, Map> maps;
			
			double toRad(double);
			void setSize(int, int);
			void checkWindowSize();
			void castInGameView();
			void showBenchmarkMessage();
			double playerX, playerY;
			double playerRot;
			Renderer renderer;
			Map* currentMap;
			
			int key, prevKey;
			int sizeX, sizeY;
			bool walkLock, logLock, inventoryVisible;
			double currentLogHeight, currentInventoryHeight;
			std::pair<int, unsigned int> repeatCounter;
	};
}
