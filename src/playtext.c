/**
 * @file playtext.c
 * @copyright Copyright (c) 2022 Zekemyapp
 * All rights reserved.
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. 
 */

#include "playtext.h"

static uint8_t is_special(char c);
static uint8_t advance_current(playtext_t pt);


playtext_t playtext_init(PlaydateAPI* pd, const char** list, size_t list_size)
{
    playtext_t pt;
    pt = pd->system->realloc(NULL, sizeof(struct playtext));
    pt->pd = pd;
    pt->text_list = list;
    pt->list_size = list_size;

    pt->current_printable = pt->pd->system->realloc(NULL, sizeof(char));
    pt->current_printable[0] = 0;

    playtext_goto(pt, 0);

    pt->text_speed = 0.1f;
    pt->last_ts = 0;
    return pt;
}

void playtext_destroy(playtext_t pt)
{
    /* TODO: Handle errors */
    pt->pd->system->realloc(pt->current_printable, 0);
    pt->pd->system->realloc(pt, 0);
}

void playtext_goto(playtext_t pt, int n)
{
    /* TODO: Check n */
    pt->current_text = n;
    pt->current_position = -1;
    pt->current_printable = pt->pd->system->realloc(
        pt->current_printable, strlen(pt->text_list[n])+1 * sizeof(char));
    memset(pt->current_printable, 0, strlen(pt->text_list[n])+1 * sizeof(char));
    pt->last_ts = 0;
    pt->wait_time = 0;
}

uint8_t playtext_update(playtext_t pt, float ts)
{
    float dt = ts - pt->last_ts;
    if (dt >= pt->text_speed && dt >= pt->wait_time) {
        if (!advance_current(pt)) {
            if (pt->current_text + 1 >= pt->list_size) {
                pt->last_ts = ts;
                return 0;
            }

            /* "next" method? */
            pt->current_text += 1;
            playtext_goto(pt, pt->current_text);
       
        } else {
            if (pt->text_list[pt->current_text][pt->current_position] == ':') {
                pt->wait_time = .5f;
            } else {
                pt->current_printable[strlen(pt->current_printable)] =
                    pt->text_list[pt->current_text][pt->current_position];
                pt->wait_time = 0;
            }
        }

        /* update reference timestamp */
        pt->last_ts = ts;
	}
    return 1;
}

const char* playtext_print(playtext_t pt)
{
    return pt->current_printable;
}

int playtext_getWidth(playtext_t pt, LCDFont* font)
{
    return pt->pd->graphics->getTextWidth(font,
            pt->text_list[pt->current_text],
            strlen(pt->text_list[pt->current_text]),
            kASCIIEncoding, 0);
}

static uint8_t is_special(char c)
{
	if (c == ':')
		return 1;
	else
		return 0;
}

static uint8_t advance_current(playtext_t pt) {
	if (pt->current_position == (size_t) -1) {
		pt->current_position = 0;
		return 1;
	}

    if (pt->current_position + 1 >= strlen(pt->text_list[pt->current_text]))
        return 0;
	
	pt->current_position += 1;
	return 1;
}