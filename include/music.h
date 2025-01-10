#ifndef _GAME_MUSIC_H
#define _GAME_MUSIC_H

#include <raylib.h>

#include "data.h"

typedef struct G_MusicInfo
{
  char        name[MAX_FILENAME];
  char        filename[MAX_FILENAME];
} G_MusicInfo;

/*
 * Musics are defined in the c file (source/include/music.c)
 *  const G_MusicInfo metadata[] = { ... }
 */

extern  const char *  G_SetMusic (G_App *app, const int flag);

#endif /* _GAME_MUSIC_H */
