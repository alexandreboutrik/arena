#include "screen/start_game.h"

#include <raylib.h>
#include <string.h>

#include "configuration.h"
#include "data.h"
#include "draw.h"
#include "keybind.h"
#include "image.h"

extern void
G_draw_start_game(G_App *app)
{
  app->flags |= FLAG_RETURN;

  // --- Keyboard
  for (int key = true; (key = GetKeyPressed()); G_KeyBind(app, key))
  {
    switch (key)
    {
      default:
        break;
    }
  }

  // --- Mouse
  G_KeyMouse(app, GetMouseX(), GetMouseY());

  G_DrawCardBack(app, CARD_W, CARD_H, (SCREEN_WIDTH/3)+15, (SCREEN_HEIGHT/3)+15);
  G_DrawCard(app, NAIPE_CLUBS, CARD_J, CARD_W, CARD_H, SCREEN_WIDTH/3, SCREEN_HEIGHT/3);
  DrawText("Fodinha", (SCREEN_WIDTH/3), (SCREEN_HEIGHT/3)+200, 30, WHITE);

  G_DrawCardBack(app, CARD_W, CARD_H, (int)(2*(SCREEN_WIDTH/3)+15)-CARD_W, (SCREEN_HEIGHT/3)+15);
  G_DrawCard(app, NAIPE_CLUBS, CARD_K, CARD_W, CARD_H, (int)((2*SCREEN_WIDTH)/3)-CARD_W, SCREEN_HEIGHT/3);
  DrawText("Truco", (int)(2*(SCREEN_WIDTH)/3)-CARD_W+5, (SCREEN_HEIGHT/3)+200, 30, WHITE);

  // --- Draw cards
  G_DrawCard(app, NAIPE_CLUBS, CARD_3, CARD_W, CARD_H, 30, 30+150*0);
  G_DrawCardBack(app, CARD_W, CARD_H, 30, 30+150*1);

  G_CentralizeText("Not implemented yet .", SCREEN_HEIGHT/3, 20, app->current_theme.foreground);

  G_DrawTitle("Select a game", app->current_theme);
}
