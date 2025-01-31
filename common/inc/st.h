/* This is a public domain general purpose hash table package written by Peter Moore @ UCB. */

/* @(#) st.h 5.1 89/12/14 */

#ifndef COMMON_ST_H
#define COMMON_ST_H 1

#if defined(__cplusplus)
extern "C" {
#endif


#include <stddef.h>
#include <stdint.h>

typedef unsigned long st_data_t;
#define ST_DATA_T_DEFINED

#define CHAR_BIT 8

#ifndef _
# define _(args) args
#endif

#ifndef ANYARGS
# ifdef __cplusplus
#   define ANYARGS ...
# else
#   define ANYARGS
# endif
#endif

typedef struct st_table st_table;

typedef st_data_t st_index_t;
typedef int st_compare_func(st_data_t, st_data_t);
typedef st_index_t st_hash_func(st_data_t);

typedef char st_check_for_sizeof_st_index_t[sizeof(void*) == (int)sizeof(st_index_t) ? 1 : -1];
#define SIZEOF_ST_INDEX_T SIZEOF_VOIDP

typedef int (*compare_t)(ANYARGS /*st_data_t, st_data_t*/); /* st_compare_func* */
typedef st_index_t (*hash_t)(ANYARGS /*st_data_t*/);        /* st_hash_func* */
struct st_hash_type {
    compare_t compare;
    hash_t hash;
};

#define ST_INDEX_BITS (sizeof(st_index_t) * CHAR_BIT)

struct st_table {
    const struct st_hash_type *type;
    st_index_t num_bins;
    unsigned int entries_packed : 1;
#ifdef __GNUC__
    /*
     * C spec says,
     *   A bit-field shall have a type that is a qualified or unqualified
     *   version of _Bool, signed int, unsigned int, or some other
     *   implementation-defined type. It is implementation-defined whether
     *   atomic types are permitted.
     * In short, long and long long bit-field are implementation-defined
     * feature. Therefore we want to supress a warning explicitly.
     */
    __extension__
#endif
    st_index_t num_entries : ST_INDEX_BITS - 1;
    struct st_table_entry **bins;
    struct st_table_entry *head, *tail;
};

#define st_is_member(table,key) st_lookup((table),(key),(st_data_t *)0)

enum st_retval {ST_CONTINUE, ST_STOP, ST_DELETE, ST_CHECK};

st_table *st_init_table(const struct st_hash_type *);
st_table *st_init_table_with_size(const struct st_hash_type *, st_index_t);
st_table *st_init_numtable(void);
st_table *st_init_numtable_with_size(st_index_t);
st_table *st_init_strtable(void);
st_table *st_init_strtable_with_size(st_index_t);
st_table *st_init_strcasetable(void);
st_table *st_init_strcasetable_with_size(st_index_t);
int st_delete(st_table *, st_data_t *, st_data_t *); /* returns 0:notfound 1:deleted */
int st_delete_safe(st_table *, st_data_t *, st_data_t *, st_data_t);
int st_insert(st_table *, st_data_t, st_data_t);
int st_insert2(st_table *, st_data_t, st_data_t, st_data_t (*)(st_data_t));
int st_lookup(st_table *, st_data_t, st_data_t *);
int st_get_key(st_table *, st_data_t, st_data_t *);
int st_foreach(st_table *, int (*)(ANYARGS), st_data_t);
int st_reverse_foreach(st_table *, int (*)(ANYARGS), st_data_t);
void st_add_direct(st_table *, st_data_t, st_data_t);
void st_free_table(st_table *);
void st_cleanup_safe(st_table *, st_data_t);
void st_clear(st_table *);
st_table *st_copy(st_table *);
int st_numcmp(st_data_t, st_data_t);
st_index_t st_numhash(st_data_t);
int st_strcasecmp(const char *s1, const char *s2);
int st_strncasecmp(const char *s1, const char *s2, size_t n);
size_t st_memsize(const st_table *);
st_index_t st_hash(const void *ptr, size_t len, st_index_t h);
st_index_t st_hash_uint32(st_index_t h, uint32_t i);
st_index_t st_hash_uint(st_index_t h, st_index_t i);
st_index_t st_hash_end(st_index_t h);
st_index_t st_hash_start(st_index_t h);
#define st_hash_start(h) ((st_index_t)(h))

#if defined __GNUC__ && __GNUC__ >= 4
#pragma GCC visibility pop
#endif

#if defined(__cplusplus)
#if 0
{ /* satisfy cc-mode */
#endif
}  /* extern "C" { */
#endif

#endif /* RUBY_ST_H */
