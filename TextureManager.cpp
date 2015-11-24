#include "TextureManager.h"
#include "SDL_image.h"
TextureManager* TextureManager::s_pInstance = 0;
bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer* pRenderer)
{
	SDL_Surface* pTemp = IMG_Load(fileName.c_str());
	if (pTemp == 0)
	{
		return false;
	}
	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTemp);
	SDL_FreeSurface(pTemp);
	if (pTexture == 0)
	{
		return false;
	}
	m_textureMap[id] = pTexture;
	return true;
}
void TextureManager::drawImage(std::string id, int x, int y, int width, int height, 
							   SDL_Renderer* prenderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect, destRect;
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(prenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}
void TextureManager::drawFrame(std::string id, int x, int y, int width, int height,
							   int currentRow, int currentFrame, SDL_Renderer* pRenderer, int margin,
							   SDL_RendererFlip flip)
{
	SDL_Rect srcRect, destRect;
	srcRect.x = width*currentFrame + margin;
	srcRect.y = height* currentRow;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::drawTile(std::string id, int margin, int spacing, int x, int y, int width, int height,
							  int currentRow, int currentFrame, SDL_Renderer* pRenderer)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;
	srcRect.x = margin + (spacing + width)*currentFrame;
	srcRect.y = margin + (spacing + height)*currentRow;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
}