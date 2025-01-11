#include "draw.h"

#include <raylib.h>
#include <stdio.h>
#include <string.h>

#include "configuration.h"
#include "data.h"
#include "image.h"
#include "screen/menu_main.h"

extern inline void
G_CentralizeText(const char *text, const int posY, const int fontSize, Color color)
{
  int center_width = MeasureText(text, fontSize);

  DrawText(text, (SCREEN_WIDTH/2)-(center_width/2), posY, fontSize, color);
}

extern inline void
G_ChangeScreen(G_App *app, const enum SCREEN screen)
{
  if (screen == PREVIOUS)
    app->screen = app->prev_screen;

  app->prev_screen = app->screen;
  app->screen      = screen;

  app->flags &= FLAG_MUSIC;
}

static inline void
G_DrawIcon(const G_App *app, const int index)
{
  G_DrawImage(app, index);
}

static inline void
G_DrawMessage(G_App *app)
{
  if (app->timer < 180)
  {
    DrawText(app->msg, 30, SCREEN_HEIGHT-47, 30, app->current_theme.foreground);

    app->timer++;
  }
}

extern inline void
G_Notify(G_App *app, const char *msg)
{
  app->timer = 0;
  strcpy(app->msg, msg);
}

extern inline void
G_DrawNotImplemented(G_App *app)
{
  G_CentralizeText("Not implemented yet .", SCREEN_HEIGHT/3, 30, app->current_theme.foreground);

  G_DrawCard(app, NAIPE_DIAMONDS, CARD_4, CARD_W, CARD_H, 30, 30);
  G_DrawCardBack(app, CARD_W, CARD_H, 30, 30+150*1);
}

extern inline void
G_DrawScreen(G_App *app)
{
  G_DrawIcon(app, IMG_MOVIE);
  G_DrawMessage(app);

  switch (app->screen)
  {
    case MENU_CONFIGURATION:
      G_draw_configuration(app);
      break;

    default:
      G_draw_main_menu(app);
  }
}
