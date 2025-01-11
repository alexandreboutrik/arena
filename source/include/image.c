#include "image.h"

#include <string.h>
#include <strings.h>

extern void
G_LoadImage(G_App *app, const char *filename,
             const int w, const int h,
             const int x, const int y)
{
  Image image = LoadImage(filename);
  ImageResize(&image, w, h);
  Texture2D texture = LoadTextureFromImage(image);

  app->image[app->n_img].image   = image;
  app->image[app->n_img].texture = texture;
  app->image[app->n_img].w       = w;
  app->image[app->n_img].h       = h;
  app->image[app->n_img].x       = x;
  app->image[app->n_img].y       = y;

  app->n_img++;
}

extern inline void
G_UnloadImage(G_App *app)
{
  UnloadTexture(app->image[--app->n_img].texture);
  UnloadImage(app->image[app->n_img].image);

  bzero(&app->image[app->n_img], sizeof(G_Image));
}

extern inline void
G_UnloadImages(G_App *app)
{
  while (app->n_img > 0)
    G_UnloadImage(app);
}

extern void
G_LoadCard(G_App *app, const int naipe, const int card)
{
  char cn[16][16] = { "Diamonds", "Spades", "Hearts", "Clubs" };
  char cc[16] = "A234567QJK";

  char filename[MAX_FILENAME] = {0};

  sprintf(filename, ASSETS "/images/card%s%c.png", cn[naipe], cc[card]);

  G_LoadImage(app, filename, CARD_WIDTH, CARD_HEIGHT, 0, 0);
}

extern inline void
G_ResizeImage(G_App *app, const size_t index, const int w, const int h)
{
  if (app->image[index].w == w && app->image[index].h == h)
    return;

  UnloadTexture(app->image[index].texture);

  ImageResize(&app->image[index].image, w, h);

  app->image[index].texture = LoadTextureFromImage(app->image[index].image);
  app->image[index].w       = w;
  app->image[index].h       = h;
}

extern inline void
G_DrawImage(const G_App *app, const size_t index)
{
  DrawTexture(app->image[index].texture, app->image[index].x, app->image[index].y, WHITE);
}

extern inline void
G_DrawCard(G_App *app, const int naipe, const int card,
            const int w, const int h, const int x, const int y)
{
  int index = ((10*naipe)+card)-1;

  G_ResizeImage(app, index, w, h);

  app->image[index].x = x;
  app->image[index].y = y;

  G_DrawImage(app, index);
}

extern inline void
G_DrawCardBack(G_App *app, const int w, const int h, const int x, const int y)
{
  G_DrawCard(app, 4, 1, w, h, x, y);
}

extern inline void
G_DrawImages(const G_App *app, const int start, int end)
{
  if (end == -1) end = app->n_img;

  for (int i = start; i < end; i++)
    G_DrawImage(app, i);
}

extern inline void
G_InitImages(G_App *app)
{
  // --- Cards go from 0 to 40
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 10; j++)
      G_LoadCard(app, i, j);

  G_LoadImage(app, ASSETS "/images/cardBack_red.png", CARD_WIDTH, CARD_HEIGHT, 0, 0);
  G_LoadImage(app, ASSETS "/images/cardJoker.png", CARD_WIDTH, CARD_HEIGHT, 0, 0);

  // --- UI assets from 42 on
  G_LoadImage(app, ASSETS "/ui/arrowRight.png",
               80, 80, (SCREEN_WIDTH/16)*5, 0);

  G_LoadImage(app, "/home/boutrik/Downloads/output-onlinepngtools.png",
               COPYRIGHT_WH, COPYRIGHT_WH, COPYRIGHT_X, COPYRIGHT_Y);

  // --- 44; 48
  G_LoadImage(app, ASSETS "/ui/return.png", 40, 40, SCREEN_WIDTH-100, 30);
  G_LoadImage(app, ASSETS "/ui/wrench.png", 40, 40, SCREEN_WIDTH-150, 30);
  G_LoadImage(app, ASSETS "/ui/musicOff.png", 40, 40, SCREEN_WIDTH-200, 30);
  G_LoadImage(app, ASSETS "/ui/musicOn.png", 40, 40, SCREEN_WIDTH-200, 30);
  G_LoadImage(app, ASSETS "/ui/movie.png", 40, 40, SCREEN_WIDTH-250, 30);
}
