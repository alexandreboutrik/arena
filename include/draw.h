#ifndef _GAME_DRAW_H
#define _GAME_DRAW_H

#include "data.h"

extern  void    G_CentralizeText (const char *text, const int posY, const int fontSize, Color color);

extern  void    G_Notify (G_App *app, const char *msg);
extern  void    G_DrawWidgets (G_App *app, int flags);

extern  void    G_DrawNotImplemented (G_App *app);
extern  void    G_ChangeScreen (G_App *app, const enum SCREEN screen);
extern  void    G_DrawScreen (G_App *app);

#endif /* _GAME_DRAW_H */
