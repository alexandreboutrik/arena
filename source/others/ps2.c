#include <raylib.h>
#include <stdio.h>
#include <string.h>

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600

#define CARD_WIDTH  (140*0.5)
#define CARD_HEIGHT (190*0.5)

#define TITLE "PS2 Nostalgia"

int
main(const int argc, const char *argv[])
{
  int current_fps = 0;
  char title[64] = TITLE;
  char text[16] = {0};

  int dx = 0, dy = 0;
  int x = 0, y = 0;
  int timing = 0;
  int fps = 144;

  int title_pos = (SCREEN_WIDTH / 2) - ((strlen(title)*15) / 2);

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE);

  SetExitKey(KEY_F4);

  Image image = LoadImage("./assets/images/cardSpadesA.png");
  ImageResize(&image, CARD_WIDTH, CARD_HEIGHT);
  Texture2D texture = LoadTextureFromImage(image);
  UnloadImage(image);

  while (!WindowShouldClose())
  {
    SetTargetFPS(fps);

    BeginDrawing();
    ClearBackground(BLACK);

    if ((x == 0 && y == 0) || (x == 0 && y == GetScreenHeight()-CARD_HEIGHT) ||
        (y == 0 && x == GetScreenWidth()-CARD_WIDTH) ||
        (x == GetScreenWidth()-CARD_WIDTH && y == GetScreenHeight()-CARD_HEIGHT))
      timing = 20;

    if (timing > 0)
    {
      DrawText("YESSSSS !!", 50, 50, 30, WHITE);
      timing--;
    }

    if (dx == 0)
    { if (x < GetScreenWidth()-CARD_WIDTH) x++; else dx = -1; }

    else if (dx == -1)
    { if (x > 0) x--; else dx = 0; }

    if (dy == 0)
    { if (y < GetScreenHeight()-CARD_HEIGHT) y++; else dy = 1; }

    else if (dy == 1)
    { if (y > 0) y--; else dy = 0; }

    if (IsKeyPressed(KEY_UP))
      fps += 100;
    if (IsKeyPressed(KEY_DOWN))
      fps -= 100;

    DrawTexture(texture, x, y, WHITE);
    DrawText(title, title_pos, 30, 30, WHITE);

    /* DrawFPS */
    current_fps = GetFPS();
    sprintf(text, "%d FPS", current_fps);
    DrawText(text, GetScreenWidth() - 150, 100, 20, GREEN);

    EndDrawing();
  }

  UnloadTexture(texture);
  CloseWindow();

  return 0;
}
