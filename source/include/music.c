#include "music.h"

#include <raylib.h>

#include "configuration.h"
#include "data.h"

static const G_MusicInfo metadata[] = {
  {
    "AntalyaTV - Soldiers of Truth",
    ASSETS "/music/soldiers-of-truth-13807.mp3",
  },
};

#define   MUSICS    (int) ((sizeof(metadata) / sizeof(G_MusicInfo))-1)

extern const char *
G_SetMusic(G_App *app, const int flag)
{
  static int selected = 0;

  if (flag == NEXT)
  {
    if (selected < MUSICS)
      selected ++;
    else selected = 0;
  }

  if (flag != FIRST)
    UnloadMusicStream(app->current_music);

  app->current_music = LoadMusicStream(metadata[selected].filename);
  PlayMusicStream(app->current_music);

  return metadata[selected].name;
}
