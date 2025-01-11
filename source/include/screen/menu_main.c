#include "screen/menu_main.h"

#include <raylib.h>
#include <string.h>

#include "configuration.h"
#include "data.h"
#include "draw.h"
#include "keybind.h"
#include "image.h"

#define BOX_TXT_FTSZ      30
#define BOX_BORDER        7

#define BOX_X_SCALE       200
#define BOX_Y_SCALE       40

#define BOX_POSX          (SCREEN_WIDTH/2-BOX_X_SCALE)
#define BOX_WIDTH         (BOX_X_SCALE*2)
#define BOX_POSY          (SCREEN_HEIGHT/4)
#define BOX_HEIGHT        (BOX_Y_SCALE*2)

static  inline  void    draw_box (const int selected, const G_Theme theme);
static  inline  void    HandleInput_main_menu (G_App *app, const int key, int *selected);

#define BOX_N 3

static inline void
draw_box(const int selected, const G_Theme theme)
{
  const char *text[] = { "Start Game", "Configuration", "Quit", NULL };

  Color box_color;
  int box_posY = BOX_POSY;
  int i;

  for (i = 0; text[i] != NULL; i++, box_posY += 125)
  {
    DrawRectangle(BOX_POSX, box_posY, BOX_WIDTH, BOX_HEIGHT, theme.selected);
    box_color = (selected == i) ? theme.selected : theme.background;
    DrawRectangle(BOX_POSX+BOX_BORDER, box_posY+BOX_BORDER, BOX_WIDTH-2*BOX_BORDER, BOX_HEIGHT-2*BOX_BORDER, box_color);
    G_CentralizeText(text[i], box_posY+4*BOX_BORDER, BOX_TXT_FTSZ, theme.foreground);
  }
}

static inline void
HandleInput_main_menu(G_App *app, const int key, int *selected)
{
  switch (key)
  {
    case KEY_DOWN:
    case KEY_S:
      if (*selected < (BOX_N-1))
        (*selected)++;
      break;
    case KEY_UP:
    case KEY_W:
      if (*selected > 0)
        (*selected)--;
      break;
    case KEY_SPACE:
    case KEY_ENTER:
    case KEY_RIGHT:
    case KEY_D:
      if (*selected == 0)
        G_ChangeScreen(app, START_GAME);
      if (*selected == 1)
        G_ChangeScreen(app, MENU_CONFIGURATION);
      if (*selected == 2)
        G_Quit(app);
      break;
  }
}

extern void
G_draw_main_menu(G_App *app)
{
  static int selected = 0;

  // --- Keyboard
  for (int key = true; (key = GetKeyPressed()); G_KeyBind(app, key))
    HandleInput_main_menu(app, key, &selected);

  // --- Mouse
  int x = GetMouseX();
  int y = GetMouseY();

  if (x > BOX_POSX && x < (BOX_POSX + BOX_WIDTH))
  {
    for (int i = 0; i < BOX_N; i++)
    {
      if (y > BOX_POSY+(i*125) && y < (BOX_POSY + BOX_HEIGHT)+(i*125))
      {
        selected = i;

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
          HandleInput_main_menu(app, KEY_ENTER, &selected);
      }
    }
  }
  G_KeyMouse(app, x, y);

  // --- Arrow
  app->image[IMG_ARROW].y = BOX_POSY + selected*125;
  G_DrawImage(app, IMG_ARROW);

  // --- Draw cards
  G_DrawCard(app, NAIPE_CLUBS, CARD_3, CARD_W, CARD_H, 30, 30+150*0);
  G_DrawCardBack(app, CARD_W, CARD_H, 30, 30+150*1);

  G_DrawTitle(TITLE, app->current_theme);
  draw_box(selected, app->current_theme);
}
