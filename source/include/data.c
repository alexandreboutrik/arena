#include "data.h"

#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "configuration.h"
#include "image.h"
#include "theme.h"
#include "music.h"

extern inline void
G_RemoveFlag(G_App *app, const int flag)
{
  if (app->flags & flag) app->flags -= flag;
}

extern inline void
G_ToggleFlag(G_App *app, const int flag)
{
  app->flags = (app->flags & flag) ? (app->flags - flag) : (app->flags | flag);
}

extern inline void
G_InitData(G_App *app)
{
  app->flags       = FLAG_MUSIC;
  app->screen      = MENU_MAIN;
  app->prev_screen = MENU_MAIN;

  bzero(app->image, MAX_IMAGES * sizeof(G_Image));
  app->n_img  = 0;

  G_SetMusic(app, 0);
  G_SetTheme(app, 0);

  app->timer = 120;
  bzero(app->msg, 64 * sizeof(char));
}

extern inline void
G_Quit(G_App *app)
{
  UnloadMusicStream(app->current_music);
  G_UnloadImages(app);
  CloseWindow();

  exit(EXIT_SUCCESS);
}
