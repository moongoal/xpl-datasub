#ifndef DREFS_H
#define DREFS_H

#include "dsstring.h"
#include "service.h"
#include "dsarray.h"

typedef struct DSDataRef {
    DSString dataref;
    DSArray clients;
} DSDataRef;

void free_sub_drefs();
int is_dref_subscribed(const char * const dref);
void remove_sub_dref(const char * const dref);
void compact_sub_datarefs();
void add_sub_dataref(const char * const dref);
void grow_sub_datarefs_array();
DSDataRef *get_free_dref_slot();

#endif // DREFS_H
