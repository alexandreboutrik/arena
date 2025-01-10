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

static  inline  void    G_Widget_FPS (const int flags);
static  inline  void    G_Widget_Music (G_App *app, const int flags);
static  inline  void    G_Copyright (const G_App *app);

static inline void
G_Widget_FPS(const int flags)
{
  if ((flags & FLAG_FPS) == 0)
    return;

  int current_fps = 0;
  char text[16] = {0};

  current_fps = GetFPS();
  sprintf(text, "%d FPS", current_fps);
  DrawText(text, SCREEN_WIDTH-300, 150, FPS_FTSZ, GREEN);
}

static inline void
G_Widget_Music(G_App *app, const int flags)
{
  if (flags & FLAG_MUSIC)
    G_DrawImage(app, IMG_MUSIC_ON);
  else
    G_DrawImage(app, IMG_MUSIC_OFF);
}

extern inline void
G_Widget_Return(G_App *app, const int flags)
{
  if (flags & FLAG_RETURN)
    G_DrawImage(app, IMG_RETURN);
}

static inline void
G_Copyright(const G_App *app)
{
  int version_measure = MeasureText(VERSION, 20);
  DrawText(VERSION, SCREEN_WIDTH-220-version_measure, SCREEN_HEIGHT-37, 20, WHITE);

  G_DrawImage(app, IMG_COPYRIGHT);
  DrawText("Boutrik", SCREEN_WIDTH-160, SCREEN_HEIGHT-37, 20, WHITE);
}

extern inline void
G_DrawWidgets(G_App *app, const int flags)
{
  G_Widget_FPS(flags);
  G_Widget_Music(app, flags);
  G_Widget_Return(app, flags);
  G_Copyright(app);
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
