#include "widget.h"

#include <raylib.h>

#include "image.h"

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


