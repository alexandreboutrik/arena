#include <raylib.h>
#include <stdio.h>
#include <string.h>

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 450

#define TITLE "FPS Counter"

int
main(const int argc, const char *argv[])
{
  int current_fps = 0;
  char text[256] = {0};
  int title_pos;
  char title[64] = "FPS Counter";

  title_pos = (SCREEN_WIDTH / 2) - ((strlen(title)*15) / 2);

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE);

  SetExitKey(KEY_F4);
  Texture2D texture3 = LoadTexture("./assets/images/cardClubs3.png");

  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(BLUE);

    current_fps = GetFPS();
    sprintf(text, "%d FPS", current_fps);
    DrawText(text, GetScreenWidth() - 150, 100, 20, GREEN);

    DrawTexture(texture3, 30, 30, WHITE);
    DrawText(title, title_pos, 30, 30, WHITE);

    EndDrawing();
  }

  const Color theme[] = { GetColor(0x60cfff), GetColor(0x000000ff), WHITE,

                          GetColor(0x333366), GetColor(0x8c0000ff), WHITE,
                          GetColor(0x000000), GetColor(0x60cfff66), WHITE,
                          GetColor(0x33003366), GetColor(0xDD994455), WHITE
  };

  for (int i = 0; i < 12; i+=3)
  {
    printf("Theme: %d\n", i);

    printf(" --- r[%d] g[%d] b[%d] a[%d]\n", theme[i].r, theme[i].g, theme[i].b, theme[i].a);
    printf(" --- r[%d] g[%d] b[%d] a[%d]\n", theme[i+1].r, theme[i+1].g, theme[i+1].b, theme[i+1].a);
    printf(" --- r[%d] g[%d] b[%d] a[%d]\n", theme[i+2].r, theme[i+2].g, theme[i+2].b, theme[i+2].a);
  }

  UnloadTexture(texture3);
  CloseWindow();

  return 0;
}
