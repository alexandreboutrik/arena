#include "theme.h"

#include <raylib.h>

#include "configuration.h"
#include "data.h"

static const G_Theme theme[] = {
  { "Classic",
    { 0, 51, 51, 102 },
    { 140, 0, 0, 255 },
    { 255, 255, 255, 255 },
  },
  { "Retro",
    { 0, 96, 207, 255 },
    { 0, 0, 0, 255 },
    { 255, 255, 255, 255 },
  },
  { "Dark",
    { 0, 0, 0, 0 },
    { 96, 207, 255, 102 },
    { 255, 255, 255, 255 },
  },
  { "Violet",
    { 51, 0, 51, 102 },
    { 140, 0, 0, 255 },
    { 255, 255, 255, 255 },
  }
};

#define   THEMES    (int) ((sizeof(theme) / sizeof(G_Theme))-1)

extern const char *
G_SetTheme(G_App *app, const int flag)
{
  static int selected = 0;

  if (flag == NEXT)
  {
    if (selected < THEMES)
      selected ++;
    else selected = 0;
  }

  app->current_theme.background = theme[selected].background;
  app->current_theme.selected   = theme[selected].selected;
  app->current_theme.foreground = theme[selected].foreground;

  return theme[selected].name;
}
