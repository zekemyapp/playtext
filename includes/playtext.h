/**
 * @file playtext.h
 * @copyright Copyright (c) 2022 Zekemyapp
 * All rights reserved.
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. 
 */

#ifndef _PLAYTEXT
#define _PLAYTEXT

#include "pd_api.h"

struct playtext {
    PlaydateAPI* pd;
    const char **text_list;
    size_t list_size;
    float text_speed;
    float last_ts;
    float wait_time;

    int current_text;
    size_t current_position;
    char *current_printable;
};

typedef struct playtext* playtext_t;

/**
 * @brief Initialize playtext library
 * 
 * @param pd Pointer to playdate API object
 * @param tl List of texts to be printed
 * @param list_size Size oof tl
 * @return playtext_t 
 */
playtext_t playtext_init(PlaydateAPI* pd, const char** tl, size_t list_size);

/**
 * @brief Destroy playtext object
 * 
 * @param pt Pointer to playtext object
 */
void playtext_destroy(playtext_t pt);

/**
 * @brief Go to text in the stored text list
 * 
 * @param pt pointer to playtext object
 * @param n position in the list
 */
void playtext_goto(playtext_t pt, int n);

/**
 * @brief Update playtext state
 * 
 * @param pt pointer to playtext object
 * @param ts time stamp. This will be used too calculate time
 *           elapsed time since last update
 * @return uint8_t 0 if reached end of list
 */
uint8_t playtext_update(playtext_t pt, float ts);

/**
 * @brief Returns the current text to be printed on screen
 *        calculated by teh library
 * 
 * @param pt pointer to playtext object
 * @return const char* to printable text
 */
const char* playtext_print(playtext_t pt);

/**
 * @brief Calculate width of current text being printed
 * 
 * @param pt pointer to playtext object
 * @param font lcd font being used
 * @return int return width in columns of the LCD screen
 */
int playtext_getWidth(playtext_t pt, LCDFont* font);

#endif /* _PLAYTEXT */