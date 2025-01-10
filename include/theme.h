#ifndef _GAME_THEME_H
#define _GAME_THEME_H

#include <raylib.h>

#include "data.h"

/*
 * Themes are defined in the c file (source/include/theme.c)
 *  const G_Theme theme[] = { ... }
 */

extern  const char *  G_SetTheme (G_App *app, const int flag);

#endif /* _GAME_THEME_H */
