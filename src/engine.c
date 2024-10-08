// Far Horizons Game Engine
// Copyright (C) 2022 Michael D Henderson
// Copyright (C) 2021 Raven Zachary
// Copyright (C) 2019 Casey Link, Adam Piggott
// Copyright (C) 1999 Richard A. Morneau
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "engine.h"
#include "enginevars.h"
#include "prng.h"


/* The following routine will return a score indicating how closely two strings match.
 * If the score is exactly 10000, then the strings are identical.
 * Otherwise, the value returned is the number of character matches, allowing for accidental transpositions, insertions, and deletions.
 * Excess characters in either string will subtract from the score.
 * Thus, it's possible for a score to be negative.
 *
 * In general, if the strings are at least 7 characters each, then you can assume the strings
 * are the same if the highest score equals the length of the correct string, length-1,
 * or length-2, AND if the score of the next best match is less than the highest score.
 * A non-10000 score will never be higher than the length of the correct string. */
int agrep_score(char *correct_string, char *unknown_string) {
    int score;
    char c1, c2, *p1, *p2;
    if (strcmp(correct_string, unknown_string) == 0) {
        return 10000;
    }
    score = 0;
    p1 = correct_string;
    p2 = unknown_string;
    while (1) {
        if ((c1 = *p1++) == '\0') {
            score -= strlen(p2);    /* Reduce score by excess characters, if any. */
            break;
        }
        if ((c2 = *p2++) == '\0') {
            score -= strlen(p1);    /* Reduce score by excess characters, if any. */
            break;
        }
        if (c1 == c2) {
            ++score;
        } else if (c1 == *p2 && c2 == *p1) {
            /* Transposed. */
            score += 2;
            ++p1;
            ++p2;
        } else if (c1 == *p2) {
            /* Unneeded character. */
            ++score;
            ++p2;
        } else if (c2 == *p1) {
            /* Missing character. */
            ++score;
            ++p1;
        }
    }
    return score;
}


/* This routine is intended to take a long argument and return a pointer to a string that has embedded commas to make the string more readable. */
char *commas(long value) {
    static char result_plus_commas[33];
    int i, j, n, length, negative;
    char temp[32];
    long abs_value;

    if (value < 0) {
        abs_value = -value;
        negative = TRUE;
    } else {
        abs_value = value;
        negative = FALSE;
    }
    sprintf(temp, "%ld", abs_value);
    length = strlen(temp);
    i = length - 1;
    j = 31;
    result_plus_commas[32] = '\0';
    for (n = 0; n < length; n++) {
        result_plus_commas[j--] = temp[i--];
        if (j % 4 == 0) {
            result_plus_commas[j--] = ',';
        }
    }

    j++;
    if (result_plus_commas[j] == ',') {
        j++;
    }
    if (negative) {
        result_plus_commas[--j] = '-';
    }

    return &result_plus_commas[j];
}


/* Give the gamemaster a chance to abort. */
void gamemaster_abort_option(void) {
    char answer[16];
    printf("*** Gamemaster safe-abort option ... type q or Q to quit: ");
    fflush(stdout);
    fgets(answer, 16, stdin);
    if (answer[0] == 'q' || answer[0] == 'Q') {
        exit(0);
    }
}


// logRandomCommand generates random numbers using the historical default seed value.
int logRandomCommand(int argc, char *argv[]) {
    // use the historical default seed value
    prngSetSeed(defaultHistoricalSeedValue);
    // then print out a nice set of random values
    for (int i = 0; i < 1000000; i++) {
        int r = rnd(1024 * 1024);
        if (i < 10) {
            printf("%9d %9d\n", i, r);
        } else if (1000 < i && i < 1010) {
            printf("%9d %9d\n", i, r);
        } else if ((i % 85713) == 0) {
            printf("%9d %9d\n", i, r);
        }
    }
    return 0;
}


void *ncalloc(const char *fn, int line, int count, int size) {
    void *p = calloc(count, size);
    if (p == NULL) {
        char msg[256];
        snprintf(msg, 256, "%s: %d: calloc(%d, %d) failed", fn, line, count, size);
        perror(msg);
        exit(2);
    }
    return p;
}


// readln is a helper for command parsing that coerces all line-endings to be just '\n'.
char *readln(char *dst, int len, FILE *fp) {
    static char buf[1024];
    char *p;
    int i;
    p = fgets(buf, 1024, fp);
    for (i = 0; i < 1024; i++) {
        if (buf[i] == '\r') {
            buf[i] = '\n';
        }
        if (buf[i] == '\n') {
            i++;
            break;
        }
    }
    for (; i < 1024; i++) {
        buf[i] = 0;
    }
    for (i = 0; i < len; i++) {
        dst[i] = buf[i];
    }
    dst[len - 1] = 0;
    return p;
}


// rnd returns a random int between 1 and max, inclusive.
// It uses the so-called "Algorithm M" method, which is a combination of the congruential and shift-register methods.
int rnd(unsigned int max) {
    return prng(max);
}
