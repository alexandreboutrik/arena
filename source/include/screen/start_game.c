#include "screen/start_game.h"

#include <raylib.h>
#include <string.h>

#include "configuration.h"
#include "data.h"
#include "draw.h"
#include "keybind.h"
#include "image.h"

#define FODINHA_X   (SCREEN_WIDTH/3)+15
#define TRUCO_X     ((int)(2*(SCREEN_WIDTH/3)+15))-CARD_W

extern void
G_draw_start_game(G_App *app)
{
  static int selected = 0;

  app->flags |= FLAG_RETURN;

  // --- Keyboard
  for (int key = true; (key = GetKeyPressed()); G_KeyBind(app, key))
  {
    switch (key)
    {
      case KEY_RIGHT:
      case KEY_D:
        if (selected == 0)
          selected = 1;
        break;
      case KEY_LEFT:
      case KEY_A:
        if (selected != 0)
          selected = 0;
        break;
      default:
        break;
    }
  }

  // --- Mouse
  int x = GetMouseX();
  int y = GetMouseY();

  if (x > FODINHA_X && x < (int)FODINHA_X+CARD_W+15)
    selected = 0;
  if (x > TRUCO_X && x < (int)TRUCO_X+CARD_W+15)
    selected = 1;

  // ---
  if (selected == 0)
    DrawRectangle((SCREEN_WIDTH/3)-30, (SCREEN_HEIGHT/3)-30,
                  CARD_W+75, CARD_H+150,
                  app->current_theme.selected);
  if (selected == 1)
    DrawRectangle(((int)(2*(SCREEN_WIDTH/3)+15))-CARD_W-45, (SCREEN_HEIGHT/3)-30,
                  CARD_W+75, CARD_H+150,
                  app->current_theme.selected);

  G_KeyMouse(app, x, y);

  G_DrawCardBack(app, CARD_W, CARD_H, FODINHA_X, (SCREEN_HEIGHT/3)+15);
  G_DrawCard(app, NAIPE_CLUBS, CARD_J, CARD_W, CARD_H, SCREEN_WIDTH/3, SCREEN_HEIGHT/3);
  DrawText("Fodinha", FODINHA_X-15, (SCREEN_HEIGHT/3)+200, 30, WHITE);

  G_DrawCardBack(app, CARD_W, CARD_H, TRUCO_X, (SCREEN_HEIGHT/3)+15);
  G_DrawCard(app, NAIPE_CLUBS, CARD_K, CARD_W, CARD_H, TRUCO_X-15, SCREEN_HEIGHT/3);
  DrawText("Truco", TRUCO_X-5, (SCREEN_HEIGHT/3)+200, 30, WHITE);

  // --- Draw cards
  G_DrawCard(app, NAIPE_CLUBS, CARD_3, CARD_W, CARD_H, 30, 30+150*0);
  G_DrawCardBack(app, CARD_W, CARD_H, 30, 30+150*1);

  G_CentralizeText("Not implemented yet .", SCREEN_HEIGHT/4-20, 40, app->current_theme.foreground);

  G_DrawTitle("Select a game", app->current_theme);
}
