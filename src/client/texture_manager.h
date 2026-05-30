#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SDL.h>

extern SDL_Texture* playerTexture;

extern SDL_Texture* alienTexture1;
extern SDL_Texture* alienTexture2;
extern SDL_Texture* alienTexture3;

extern SDL_Texture* explosionTexture;

extern SDL_Texture* bunkerTexture;

extern SDL_Texture* ufoTexture;

void loadTextures(SDL_Renderer* renderer);
void destroyTextures();

#endif