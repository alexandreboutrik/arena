#ifndef _GAME_CONFIGURATION_H
#define _GAME_CONFIGURATION_H

#define TITLE             "Arena"
#define VERSION           "v0.0.1-prealpha"

#define NERD_FONT          "AgaveNerdFont-Regular.ttf"

#define SCREEN_WIDTH      1920
#define SCREEN_HEIGHT     1080

#define TITLE_FTSZ        80
#define FPS_FTSZ          40

#define MAX_IMAGES        128
#define MAX_FILENAME      256

// ---------- Scaling

#define CARD_SCL          0.7
#define COPYRIGHT_SCL     0.2

// ---------- Images

#define CARD_WIDTH        140
#define CARD_HEIGHT       190

#define COPYRIGHT_DIM     128
#define COPYRIGHT_X       SCREEN_WIDTH-200
#define COPYRIGHT_Y       SCREEN_HEIGHT-40

// ---------- Menu Boxes

#define BOX_TXT_FTSZ      30
#define BOX_BORDER        7

#define BOX_X_SCALE       200
#define BOX_Y_SCALE       40

#define BOX_POSX          (SCREEN_WIDTH/2-BOX_X_SCALE)
#define BOX_WIDTH         (BOX_X_SCALE*2)
#define BOX_POSY          (SCREEN_HEIGHT/4)
#define BOX_HEIGHT        (BOX_Y_SCALE*2)

// ----------

#define CARD_W            (CARD_WIDTH  * CARD_SCL)
#define CARD_H            (CARD_HEIGHT * CARD_SCL)
#define COPYRIGHT_WH      (COPYRIGHT_DIM  * COPYRIGHT_SCL)

// ---------- Needed CTE

#define FIRST             0
#define SAME              -1
#define END               -1
#define NEXT              -1

#define NAIPE_DIAMONDS    0
#define NAIPE_SPADES      1
#define NAIPE_HEARTS      2
#define NAIPE_CLUBS       3

#define CARD_A            1
#define CARD_2            2
#define CARD_3            3
#define CARD_4            4
#define CARD_5            5
#define CARD_6            6
#define CARD_7            7
#define CARD_Q            8
#define CARD_J            9
#define CARD_K            10

#ifndef ASSETS
#define ASSETS "."
#endif

#endif /* _GAME_CONFIGURATION_H */
