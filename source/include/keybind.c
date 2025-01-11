#include "keybind.h"

#include <raylib.h>
#include <stdio.h>

#include "data.h"
#include "draw.h"
#include "theme.h"
#include "music.h"

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
      sprintf(msg, "Theme %s loaded .", G_SetTheme(app, NEXT));
      G_Notify(app, msg);
      break;

    case KEY_N:
      sprintf(msg, "Loading music: %s .", G_SetMusic(app, NEXT));
      G_Notify(app, msg);
      break;

    case KEY_M:
      if (IsMusicStreamPlaying(app->current_music))
      {
        PauseMusicStream(app->current_music);
        G_Notify(app, "Music paused .");
      }
      else
      {
        ResumeMusicStream(app->current_music);
        G_Notify(app, "Turning the music back on ...");
      }
      G_ToggleFlag(app, FLAG_MUSIC);
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

extern void
G_KeyMouse(G_App *app, const int x, const int y)
{
  if (! IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    return;

  printf("Clicked at x:[%d], y:[%d]\n", x, y);

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
