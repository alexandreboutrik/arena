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
