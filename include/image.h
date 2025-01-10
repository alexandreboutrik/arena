#ifndef _GAME_IMAGE_H
#define _GAME_IMAGE_H

#include "data.h"

#define   IMG_ARROW       42
#define   IMG_COPYRIGHT   43
#define   IMG_RETURN      44
#define   IMG_MUSIC_OFF   45
#define   IMG_MUSIC_ON    46
#define   IMG_MOVIE       47

extern  void        G_LoadImage (G_App *app, const char *filename,
                        const int w, const int h,
                        const int x, const int y);
extern  void        G_LoadCard (G_App *app,
                        const int naipe, const int card);

extern  void        G_UnloadImage (G_App *app);
extern  void        G_UnloadImages (G_App *app);

extern  void        G_ResizeImage (G_App *app, const size_t index,
                        const int w, const int h);

extern  void        G_DrawImage (const G_App *app, const size_t index);
extern  void        G_DrawCard (G_App *app,
                        const int naipe, const int card,
                        const int w, const int h,
                        const int x, const int y);
extern void         G_DrawCardBack(G_App *app, const int w, const int h,
                        const int x, const int y);
extern  void        G_DrawImages (const G_App *app, const int start, int end);

#endif /* _GAME_IMAGE_H */
