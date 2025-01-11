#include <raylib.h>
#include <stdio.h>

#include "configuration.h"
#include "data.h"
#include "draw.h"
#include "theme.h"
#include "music.h"
#include "widget.h"

int
main(void)
{
  G_App app;

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE);
  InitAudioDevice();

  SetExitKey(KEY_F4);
  SetTargetFPS(60);

  G_InitData(&app);
  G_InitImages(&app);

  ToggleFullscreen();

  while (!WindowShouldClose())
  {
    SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    UpdateMusicStream(app.current_music);

    {
      BeginDrawing();

      ClearBackground(app.current_theme.background);

      G_DrawScreen(&app);
      G_DrawWidgets(&app, app.flags);

      EndDrawing();
    }
  }

  G_Quit(&app);

  return 0;
}
