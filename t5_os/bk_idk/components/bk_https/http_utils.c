// Copyright 2019 Espressif Systems (Shanghai) PTE LTD
// Copyright 2023 Beken Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
/*
* Change Logs:
* Date			 Author 	  Notes
* 2023-05-05	 Beken	  adapter to Beken sdk
*/

#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "http_utils.h"

#ifndef mem_check
#define mem_check(x) assert(x)
#endif

char *http_utils_join_string(const char *first_str, size_t len_first, const char *second_str, size_t len_second)
{
    size_t first_str_len = len_first > 0 ? len_first : strlen(first_str);
    size_t second_str_len = len_second > 0 ? len_second : strlen(second_str);
    char *ret = NULL;
    if (first_str_len + second_str_len > 0) {
        ret = calloc(1, first_str_len + second_str_len + 1);
        mem_check(ret);
        memcpy(ret, first_str, first_str_len);
        memcpy(ret + first_str_len, second_str, second_str_len);
    }
    return ret;
}

char *http_utils_assign_string(char **str, const char *new_str, int len)
{
    int l = len;
    if (new_str == NULL) {
        return NULL;
    }
    char *old_str = *str;
    if (l < 0) {
        l = strlen(new_str);
    }
    if (old_str) {
        old_str = realloc(old_str, l + 1);
        mem_check(old_str);
        old_str[l] = 0;
    } else {
        old_str = calloc(1, l + 1);
        mem_check(old_str);
    }
    memcpy(old_str, new_str, l);
    *str = old_str;
    return old_str;
}

char *http_utils_append_string(char **str, const char *new_str, int len)
{
    int l = len;
    int old_len = 0;
    char *old_str = *str;
    if (new_str != NULL) {
        if (l < 0) {
            l = strlen(new_str);
        }
        if (old_str) {
            old_len = strlen(old_str);
            old_str = realloc(old_str, old_len + l + 1);
            mem_check(old_str);
            old_str[old_len + l] = 0;
        } else {
            old_str = calloc(1, l + 1);
            mem_check(old_str);
        }
        memcpy(old_str + old_len, new_str, l);
        *str = old_str;
    }
    return old_str;
}

void http_utils_trim_whitespace(char **str)
{
    char *end, *start;
    if (str == NULL) {
        return;
    }
    start = *str;
    if (start == NULL) {
        return;
    }
    // Trim leading space
    while (isspace((unsigned char)*start)) start ++;

    if (*start == 0) {  // All spaces?
        **str = 0;
        return;
    }

    // Trim trailing space
    end = (char *)(start + strlen(start) - 1);
    while (end > start && isspace((unsigned char)*end)) {
        end--;
    }

    // Write new null terminator
    *(end + 1) = 0;
    memmove(*str, start, strlen(start) + 1);
}

char *http_utils_get_string_between(const char *str, const char *begin, const char *end)
{
    char *found = strcasestr(str, begin);
    char *ret = NULL;
    if (found) {
        found += strlen(begin);
        char *found_end = strcasestr(found, end);
        if (found_end) {
            ret = calloc(1, found_end - found + 1);
            mem_check(ret);
            memcpy(ret, found, found_end - found);
            return ret;
        }
    }
    return NULL;
}

int http_utils_str_starts_with(const char *str, const char *start)
{
    int i;
    int match_str_len = strlen(str);
    int start_len = strlen(start);

    if (start_len > match_str_len) {
        return -1;
    }
    for (i = 0; i < start_len; i++) {
        if (tolower(str[i]) != tolower(start[i])) {
            return 1;
        }
    }
    return 0;
}
