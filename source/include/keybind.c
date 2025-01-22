#include "keybind.h"

#include <raylib.h>
#include <stdio.h>

#include "data.h"
#include "draw.h"
#include "image.h"
#include "theme.h"
#include "music.h"
#include "widget.h"

extern void
G_KeyBind(G_App *app, const int key)
{
  char msg[128];

  switch (key)
  {
    case KEY_ESCAPE:
      G_ChangeScreen(app, PREVIOUS);
      break;

    case KEY_T:
      sprintf(msg, "Theme %s loaded", G_SetTheme(app, NEXT));
      G_Notify(app, msg);
      break;

    case KEY_N:
      sprintf(msg, "Loading music: %s", G_SetMusic(app, NEXT));
      G_Notify(app, msg);
      break;

    case KEY_M:
      if (IsMusicStreamPlaying(app->current_music))
      {
        PauseMusicStream(app->current_music);
        G_Notify(app, "Music paused");
      }
      else
      {
        ResumeMusicStream(app->current_music);
        G_Notify(app, "Turning the music back on");
      }
      G_ToggleFlag(app, FLAG_MUSIC);
        break;

    case KEY_K:
      app->music_volume += 0.1;
      /* FALLTHROUGH */
    case KEY_J:
      app->music_volume -= 0.05;
      if (app->music_volume < 0.0) app->music_volume = 0.0;
      if (app->music_volume > 1.0) app->music_volume = 1.0;
      sprintf(msg, "Set music volume to %.2lf", app->music_volume);
      G_Notify(app, msg);
      SetMusicVolume(app->current_music, app->music_volume);
      break;

    case KEY_F:
      if (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL))
        G_ToggleFlag(app, FLAG_FPS);
      break;

    case KEY_O:
      if (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL))
        G_ChangeScreen(app, MENU_CONFIGURATION);
      break;

    case KEY_F11:
      ToggleFullscreen();
      break;
  }
}

static inline void
G_Zero_WidgetFlags(G_App *app)
{
  app->image[IMG_MOVIE].flags     = 0;
  app->image[IMG_MUSIC_ON].flags  = 0;
  app->image[IMG_MUSIC_OFF].flags = 0;
  app->image[IMG_CONFIG].flags    = 0;
  app->image[IMG_RETURN].flags    = 0;
}

static inline void
G_Set_WidgetFlag(G_App *app, const size_t index)
{
  G_Zero_WidgetFlags(app);
  app->image[index].flags = FLAG_WIDGET_INC;
}

extern void
G_KeyMouse(G_App *app, const int x, const int y)
{
  if (y > 40 && y < 65)
  {
    if (x > 1670 && x < 1720)
      G_Set_WidgetFlag(app, IMG_MOVIE);
    else if (x > 1720 && x < 1770)
    {
      G_Set_WidgetFlag(app, IMG_MUSIC_ON);
      app->image[IMG_MUSIC_OFF].flags = FLAG_WIDGET_INC;
    }
    else if (x > 1770 && x < 1820)
      G_Set_WidgetFlag(app, IMG_CONFIG);
    else if (x > 1820 && x < 1870)
      G_Set_WidgetFlag(app, IMG_RETURN);
    else
      G_Zero_WidgetFlags(app);
  }
  else
    G_Zero_WidgetFlags(app);

  if (! IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    return;

  if (y > 40 && y < 65)
  {
    if (x > 1670 && x < 1720)
      G_KeyBind(app, KEY_T);
    if (x > 1720 && x < 1770)
      G_KeyBind(app, KEY_M);
    if (x > 1770 && x < 1820)
      G_ChangeScreen(app, MENU_CONFIGURATION);
    if (x > 1820 && x < 1870)
      G_KeyBind(app, KEY_ESCAPE);
  }
}
