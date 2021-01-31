#ifndef DREFS_H
#define DREFS_H

void free_sub_drefs();
int is_dref_subscribed(const char * const dref);
void remove_sub_dref(const char * const dref);
void compact_sub_datarefs();
void add_sub_dataref(const char * const dref);
void grow_sub_datarefs_array();
char **get_free_dref_slot();

#endif // DREFS_H
