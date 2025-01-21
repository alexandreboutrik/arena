#ifndef _GAME_DATA_H
#define _GAME_DATA_H

#include <raylib.h>
#include <stdio.h>

#include "configuration.h"

#define   FLAG_FPS          (1 << 1)
#define   FLAG_MUSIC        (1 << 2)
#define   FLAG_RETURN       (1 << 3)

#define   FLAG_WIDGET_INC   (1 << 1)

enum SCREEN
{
  PREVIOUS = 0,
  MENU_MAIN, MENU_CONFIGURATION, START_GAME
};

typedef struct G_Theme
{
  char        name[32];

  Color       background;
  Color       selected;
  Color       foreground;
} G_Theme;

typedef struct G_Image
{
  Image       image;
  Texture2D   texture;

  int         w, h;
  int         x, y;

  int flags;
} G_Image;

typedef struct G_App
{
  enum SCREEN  screen, prev_screen;
  int          flags;

  G_Image      image[MAX_IMAGES];
  size_t       n_img;

  G_Theme      current_theme;
  Music        current_music;

  Font         font;

  int          timer;               /* timer for G_Notify() */
  char         msg[64];             /* notify message */
} G_App;

extern  void    G_RemoveFlag (G_App *app, const int flag);
extern  void    G_ToggleFlag (G_App *app, const int flag);

extern  void    G_InitData (G_App *app);
extern  void    G_InitImages (G_App *app);

extern  void    G_Quit (G_App *app);

#endif /* _GAME_DATA_H */
