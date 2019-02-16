#pragma once

#include "interpreter/refcount/refcount.h"

struct RC_Table;

struct RC_UserData {
    struct RC *rc;        // DO NOT REARRANGE. RC MUST BE THE FIRST MEMBER OF THIS STRUCT.
    int tag;
    //struct RC_Table *mt;
    void *data;
};


struct RC_UserData *ud_new(void *data, int tag);
void ud_del_data(struct RC_UserData *ud);
void ud_del_rc(struct RC_UserData *ud);
void ud_del(struct RC_UserData *ud);
