#include "error.h"

#include <stdio.h>

#include "data.h"

extern void
G_Error(G_App *app, const char *func, const char *msg)
{
  if (func != NULL)
    fprintf(stderr, "%s", func);
  if (msg != NULL)
    fprintf(stderr, ": %s", msg);

  fprintf(stderr, "\n");
  G_Quit(app);
}
