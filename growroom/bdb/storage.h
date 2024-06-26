#ifndef __STORAGE_H__
#define __STORAGE_H__

typedef struct _snode {
    // https://en.wikipedia.org/wiki/Binary_search_tree
    dbid_t  left;
    dbid_t  right;
    char    data[1];
} snode;

extern bool    storage_write_data (bdb *, dbid_t, void *data, size_t);
extern dbid_t  storage_alloc_id   (bdb *, size_t);
extern dbid_t  storage_alloc      (bdb *, void *data, size_t);
extern void    storage_insert_key (bdb *, void *key, dbid_t);
extern snode * storage_map        (size_t *, bdb *, dbid_t);
extern void    storage_add        (bdb *, dbid_t id, void *data, size_t);
extern dbid_t  storage_find       (bdb *, void *key);

#ifdef TESTS
extern size_t snode_size (size_t);
#endif // #ifdef TESTS

#endif // #ifndef __STORAGE_H__
