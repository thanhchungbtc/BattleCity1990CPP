#ifndef GUARD_TEXTUREMANAGER_H
#define GUARD_TEXTUREMANAGER_H
#include <map>
#include <string>
#include "SDL.h"
class TextureManager
{
public:
	static TextureManager* Instance(){
		if (!s_pInstance)
		{
			s_pInstance = new TextureManager();
		}
		return s_pInstance;
	}
	bool load(std::string fileName, std::string id, SDL_Renderer* pRenderer);

	void drawImage(std::string id, int x, int y, int width, int height, SDL_Renderer* prenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawFrame(std::string id, int x, int y, int width, int height,
		int currentRow, int currentFrame, SDL_Renderer* pRenderer, int margin = 0,  SDL_RendererFlip flip = SDL_FLIP_NONE);

	void drawTile(std::string id, int margin, int spacing, int x, int y, int width, int height,
		int currentRow, int currentFrame, SDL_Renderer* pRenderer);
private:
	TextureManager(){}
	static TextureManager* s_pInstance;

	std::map<std::string, SDL_Texture*> m_textureMap;
};
#endif