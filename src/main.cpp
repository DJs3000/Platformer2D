#include "Tilengine.h"
 
int main(void) 
{
    TLN_Tilemap background;
    TLN_Spriteset character;
 
    /* init engine and window */
    TLN_Init(480, 272, 4, 64, 0);
    TLN_CreateWindow (NULL, 0);
 
    /* setup background layer */
    background = TLN_LoadTilemap ("ruff_n_tumble.tmx", NULL);
    TLN_SetLayerTilemap (0, background);
    TLN_SetLayerPosition(0, 32, 0);
 
    /* setup sprite */
    character = TLN_LoadSpriteset("ruff1.png");
    TLN_SetSpriteSet(0, character);
    TLN_SetSpritePosition(0, 160, 192);
 
    /* loop until close */
    while (TLN_ProcessWindow())
        TLN_DrawFrame(0);
 
    /* release resources */
    TLN_DeleteSpriteset(character);
    TLN_DeleteTilemap(background);
    TLN_DeleteWindow();
    TLN_Deinit();
}
