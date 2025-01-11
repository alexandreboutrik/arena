#include "screen/configuration.h"

#include <raylib.h>
#include <string.h>

#include "configuration.h"
#include "data.h"
#include "draw.h"
#include "keybind.h"
#include "image.h"

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

  G_DrawNotImplemented(app);

  G_DrawTitle("Configuration", app->current_theme);
}
