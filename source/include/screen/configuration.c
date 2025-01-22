#include "screen/configuration.h"

#include <raylib.h>
#include <string.h>

#include "configuration.h"
#include "data.h"
#include "draw.h"
#include "keybind.h"
#include "image.h"

#define BOX_X         (2.0*SCREEN_WIDTH/10.0)
#define BOX_Y         (SCREEN_HEIGHT/3.0)
#define BOX_SPACING   50

static  inline  void    draw_box (const G_App *app, const char *letter,
                                  const char *text, const int opt);

static inline void
draw_box(const G_App *app, const char *letter, const char *text, const int opt)
{
  size_t lx, ly, lftsz;

  size_t lsz = strlen(letter);
  switch (lsz)
  {
    case 1:
      lx = 9;
      ly = 3;
      lftsz = 25;
      break;
    case 2:
      lx = 5;
      ly = 5;
      lftsz = 20;
      break;
    default:
      lx = 5;
      ly = 8;
      lftsz = 15;
  }
  if (lsz == 1)
  { lx = 9; ly = 3; lftsz = 25; }

  DrawRectangle(BOX_X-2, BOX_Y-2+opt*BOX_SPACING,
                34, 34, app->current_theme.selected);

  DrawRectangle(BOX_X, BOX_Y+opt*BOX_SPACING,
                30, 30, BLACK);

  DrawTextEx(app->font, letter,
            (Vector2) { BOX_X+lx, BOX_Y+opt*BOX_SPACING+ly },
            lftsz, 0, app->current_theme.foreground);

  DrawTextEx(app->font, text,
             (Vector2) { BOX_X+75, BOX_Y+opt*BOX_SPACING+3 },
             25, 0, app->current_theme.foreground);
}

extern void
G_draw_configuration(G_App *app)
{
  app->flags |= FLAG_RETURN;

  // --- Keyboard
  for (int key = true; (key = GetKeyPressed()); G_KeyBind(app, key))
  {
    switch (key)
    {
      case KEY_LEFT:
        G_ChangeScreen(app, PREVIOUS);
        break;
      default:
        break;
    }
  }

  // --- Mouse
  G_KeyMouse(app, GetMouseX(), GetMouseY());

  DrawTextEx(app->font, "Shortcuts:",
             (Vector2) { BOX_X+20, BOX_Y-50 },
             30, 0, app->current_theme.foreground);

  draw_box(app, "T", "Change theme", 0);
  draw_box(app, "N", "Next music", 1);
  draw_box(app, "M", "Mute music", 2);
  draw_box(app, "J", "Decrease music volume", 3);
  draw_box(app, "K", "Increase music volume", 4);
  draw_box(app, "C-F", "Show fps", 5);
  draw_box(app, "F4", "Quit", 6);

  // --- Draw cards
  G_DrawCard(app, NAIPE_DIAMONDS, CARD_A, CARD_W, CARD_H, 30, 30+150*0);
  G_DrawCardBack(app, CARD_W, CARD_H, 30, 30+150*1);

  G_CentralizeText("Not implemented yet .", SCREEN_HEIGHT/4-20, 40, app->current_theme.foreground);

  G_DrawTitle("Configuration", app->current_theme);
}
