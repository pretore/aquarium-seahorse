#ifndef _SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_H_
#define _SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_H_

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <rock.h>

#define SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OBJECT_IS_NULL              1
#define SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OUT_IS_NULL                 2
#define SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_KEY_ALREADY_EXISTS          3
#define SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_MEMORY_ALLOCATION_FAILED    4
#define SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_KEY_NOT_FOUND               5
#define SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_MAP_IS_EMPTY                6
#define SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_ENTRY_IS_NULL               7
#define SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_END_OF_SEQUENCE             8

struct seahorse_red_black_tree_map_ni_ni {
    struct rock_red_black_tree_map map;
};

struct seahorse_red_black_tree_map_ni_ni_entry;

/**
 * @brief Initialize red-black tree map.
 * @param [in] object instance to be initialized.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OBJECT_IS_NULL if object
 * is <i>NULL</i>.
 */
bool seahorse_red_black_tree_map_ni_ni_init(
        struct seahorse_red_black_tree_map_ni_ni *object);

/**
 * @brief Invalidate red-black tree map.
 * <p>The actual <u>tree map instance is not deallocated</u> since it may
 * have been embedded in a larger structure.</p>
 * @param [in] object instance to be invalidated.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OBJECT_IS_NULL if object
 * is <i>NULL</i>.
 */
bool seahorse_red_black_tree_map_ni_ni_invalidate(
        struct seahorse_red_black_tree_map_ni_ni *object);

/**
 * @brief Retrieve the count of entries.
 * @param [in] object instance whose count we are to retrieve.
 * @param [out] out receive the entry count.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OBJECT_IS_NULL if object
 * is <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 */
bool seahorse_red_black_tree_map_ni_ni_count(
        const struct seahorse_red_black_tree_map_ni_ni *object,
        uintmax_t *out);

/**
 * @brief Add a key-value association.
 * @param [in] object tree map instance.
 * @param [in] key to which the value will be associated with.
 * @param [in] value that will returned from a lookup of key.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OBJECT_IS_NULL if object
 * is <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_KEY_ALREADY_EXISTS if the
 * key is already present in the tree map.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_MEMORY_ALLOCATION_FAILED
 * if there is not enough memory to add key-value association to the tree map.
 */
bool seahorse_red_black_tree_map_ni_ni_add(
        struct seahorse_red_black_tree_map_ni_ni *object,
        uintmax_t key,
        uintmax_t value);

/**
 * @brief Remove key-value association.
 * @param [in] object tree map instance.
 * @param [in] key for which we would like the key-value association removed.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OBJECT_IS_NULL if object
 * is <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_KEY_NOT_FOUND if key could
 * not be found.
 */
bool seahorse_red_black_tree_map_ni_ni_remove(
        struct seahorse_red_black_tree_map_ni_ni *object,
        uintmax_t key);

/**
 * @brief Check if tree map contains the given key.
 * @param [in] object tree map instance.
 * @param [in] key to check if it is present.
 * @param [out] out true if key is present, otherwise false.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OBJECT_IS_NULL if object
 * is <i>NULL</i>.
 */
bool seahorse_red_black_tree_map_ni_ni_contains(
        const struct seahorse_red_black_tree_map_ni_ni *object,
        uintmax_t key,
        bool *out);

/**
 * @brief Set the value for the given key.
 * @param [in] object tree map instance.
 * @param [in] key used for which value is to be changed.
 * @param [in] value of new association with given key.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OBJECT_IS_NULL if object
 * is <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_KEY_NOT_FOUND if key could
 * not be found.
 */
bool seahorse_red_black_tree_map_ni_ni_set(
        struct seahorse_red_black_tree_map_ni_ni *object,
        uintmax_t key,
        uintmax_t value);

/**
 * @brief Retrieve the value for the given key.
 * @param [in] object tree map instance.
 * @param [in] key used to get the associated value.
 * @param [out] out receive the <u>address of</u> value.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OBJECT_IS_NULL if object
 * is <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_KEY_NOT_FOUND if key could
 * not be found.
 */
bool seahorse_red_black_tree_map_ni_ni_get(
        const struct seahorse_red_black_tree_map_ni_ni *object,
        uintmax_t key,
        const uintmax_t **out);

/**
 * @brief Retrieve the value for the given key or the next higher key.
 * @param [in] object tree map instance.
 * @param [in] key to find or the next higher key.
 * @param [out] out receive the <u>address of</u> value.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_KEY_NOT_FOUND if key nor a
 * higher key is in the tree map instance.
 */
bool seahorse_red_black_tree_map_ni_ni_ceiling(
        const struct seahorse_red_black_tree_map_ni_ni *object,
        uintmax_t key,
        const uintmax_t **out);

/**
 * @brief Retrieve the value for the given key or the next lower key.
 * @param [in] object tree map instance.
 * @param [in] key to find or the next lower key.
 * @param [out] out receive the <u>address of</u> value.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_KEY_NOT_FOUND if key nor a
 * lower key is in the tree map instance.
 */
bool seahorse_red_black_tree_map_ni_ni_floor(
        const struct seahorse_red_black_tree_map_ni_ni *object,
        uintmax_t key,
        const uintmax_t **out);

/**
 * @brief Retrieve the value for the next higher key.
 * @param [in] object tree map instance.
 * @param [in] key whose next higher key we are trying to find.
 * @param [out] out receive the <u>address of</u> value.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_KEY_NOT_FOUND if no higher
 * key is in the tree map instance.
 */
bool seahorse_red_black_tree_map_ni_ni_higher(
        const struct seahorse_red_black_tree_map_ni_ni *object,
        uintmax_t key,
        const uintmax_t **out);

/**
 * @brief Retrieve the value for the next lower key.
 * @param [in] object tree map instance.
 * @param [in] key whose next lower key we are trying to find.
 * @param [out] out receive the <u>address of</u> value.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_KEY_NOT_FOUND if no lower
 * value for key is in the tree map instance.
 */
bool seahorse_red_black_tree_map_ni_ni_lower(
        const struct seahorse_red_black_tree_map_ni_ni *object,
        uintmax_t key,
        const uintmax_t **out);

/**
 * @brief Retrieve value of first entry.
 * @param [in] object tree map instance.
 * @param [out] out receive the <u>address of</u> the first entry's value.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_MAP_IS_EMPTY if tree map
 * is empty.
 */
bool seahorse_red_black_tree_map_ni_ni_first(
        const struct seahorse_red_black_tree_map_ni_ni *object,
        const uintmax_t **out);

/**
 * @brief Retrieve value of last entry.
 * @param [in] object tree map instance.
 * @param [out] out receive the <u>address of</u> the last entry's value.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_MAP_IS_EMPTY if tree map
 * is empty.
 */
bool seahorse_red_black_tree_map_ni_ni_last(
        const struct seahorse_red_black_tree_map_ni_ni *object,
        const uintmax_t **out);

/**
 * @brief Retrieve entry for the given key.
 * @param [in] object tree map instance.
 * @param [in] key of the entry we are looking for.
 * @param [out] out receive the <u>address of</u> entry.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_KEY_NOT_FOUND if key could
 * not be found.
 */
bool seahorse_red_black_tree_map_ni_ni_get_entry(
        const struct seahorse_red_black_tree_map_ni_ni *object,
        uintmax_t key,
        const struct seahorse_red_black_tree_map_ni_ni_entry **out);

/**
 * @brief Retrieve the entry for the given key or the next higher key.
 * @param [in] object tree map instance.
 * @param [in] key to find or the next higher key.
 * @param [out] out receive the <u>address of</u> entry.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_KEY_NOT_FOUND if key nor a
 * higher key is in the tree map instance.
 */
bool seahorse_red_black_tree_map_ni_ni_ceiling_entry(
        const struct seahorse_red_black_tree_map_ni_ni *object,
        uintmax_t key,
        const struct seahorse_red_black_tree_map_ni_ni_entry **out);

/**
 * @brief Retrieve the entry for the given key or the next lower key.
 * @param [in] object tree map instance.
 * @param [in] key to find or the next lower key.
 * @param [out] out receive the <u>address of</u> entry.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_KEY_NOT_FOUND if key nor a
 * lower key is in the tree map instance.
 */
bool seahorse_red_black_tree_map_ni_ni_floor_entry(
        const struct seahorse_red_black_tree_map_ni_ni *object,
        uintmax_t key,
        const struct seahorse_red_black_tree_map_ni_ni_entry **out);

/**
 * @brief Retrieve the entry for the next higher key.
 * @param [in] object tree map instance.
 * @param [in] key whose next higher key we are trying to find.
 * @param [out] out receive the <u>address of</u> entry.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_KEY_NOT_FOUND if no higher
 * key is in the tree map instance.
 */
bool seahorse_red_black_tree_map_ni_ni_higher_entry(
        const struct seahorse_red_black_tree_map_ni_ni *object,
        uintmax_t key,
        const struct seahorse_red_black_tree_map_ni_ni_entry **out);

/**
 * @brief Retrieve the entry for the next lower key.
 * @param [in] object tree map instance.
 * @param [in] key whose next lower key we are trying to find.
 * @param [out] out receive the <u>address of</u> entry.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_KEY_NOT_FOUND if no lower
 * value for item is in the tree map instance.
 */
bool seahorse_red_black_tree_map_ni_ni_lower_entry(
        const struct seahorse_red_black_tree_map_ni_ni *object,
        uintmax_t key,
        const struct seahorse_red_black_tree_map_ni_ni_entry **out);

/**
 * @brief Retrieve first entry.
 * @param [in] object tree map instance.
 * @param [out] out receive the <u>address of</u> the first entry.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_MAP_IS_EMPTY if tree map
 * is empty.
 */
bool seahorse_red_black_tree_map_ni_ni_first_entry(
        const struct seahorse_red_black_tree_map_ni_ni *object,
        const struct seahorse_red_black_tree_map_ni_ni_entry **out);

/**
 * @brief Retrieve last entry.
 * @param [in] object tree map instance.
 * @param [out] out receive the <u>address of</u> the last entry.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_MAP_IS_EMPTY if tree map
 * is empty.
 */
bool seahorse_red_black_tree_map_ni_ni_last_entry(
        const struct seahorse_red_black_tree_map_ni_ni *object,
        const struct seahorse_red_black_tree_map_ni_ni_entry **out);

/**
 * @brief Remove entry.
 * @param [in] object tree map instance.
 * @param [in] entry <u>address of</u> entry to be removed.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_ENTRY_IS_NULL if entry is
 * <i>NULL</i>.
 */
bool seahorse_red_black_tree_map_ni_ni_remove_entry(
        struct seahorse_red_black_tree_map_ni_ni *object,
        const struct seahorse_red_black_tree_map_ni_ni_entry *entry);

/**
 * @brief Retrieve the next entry.
 * @param [in] entry <u>address of</u> current entry.
 * @param [out] out receive the <u>address of</u> the next entry.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_ENTRY_IS_NULL if entry is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_END_OF_SEQUENCE if there is
 * no next entry.
 */
bool seahorse_red_black_tree_map_ni_ni_next_entry(
        const struct seahorse_red_black_tree_map_ni_ni_entry *entry,
        const struct seahorse_red_black_tree_map_ni_ni_entry **out);

/**
 * @brief Retrieve the previous entry.
 * @param [in] entry <u>address of</u> current entry.
 * @param [out] out receive the <u>address of</u> the previous entry.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_ENTRY_IS_NULL if entry is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_END_OF_SEQUENCE if there is
 * no previous entry.
 */
bool seahorse_red_black_tree_map_ni_ni_prev_entry(
        const struct seahorse_red_black_tree_map_ni_ni_entry *entry,
        const struct seahorse_red_black_tree_map_ni_ni_entry **out);

/**
 * @brief Retrieve the entry's key.
 * @param [in] object tree map instance.
 * @param [in] entry <u>address of</u> entry contained within the tree map
 * instance.
 * @param [out] out receive the <u>address of</u> the entry's key.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_ENTRY_IS_NULL if entry is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 */
bool seahorse_red_black_tree_map_ni_ni_entry_key(
        const struct seahorse_red_black_tree_map_ni_ni *object,
        const struct seahorse_red_black_tree_map_ni_ni_entry *entry,
        const uintmax_t **out);

/**
 * @brief Retrieve the entry's value.
 * @param [in] object tree map instance.
 * @param [in] entry <u>address of</u> entry contained within the tree map
 * instance.
 * @param [out] out receive the <u>address of</u> the entry's value.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_ENTRY_IS_NULL if entry is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 */
bool seahorse_red_black_tree_map_ni_ni_entry_get_value(
        const struct seahorse_red_black_tree_map_ni_ni *object,
        const struct seahorse_red_black_tree_map_ni_ni_entry *entry,
        const uintmax_t **out);

/**
 * @brief Set the entry's value.
 * @param [in] object tree map instance.
 * @param [in] entry <u>address of</u> entry contained within the tree map
 * instance.
 * @param [in] value to set entry's value to.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_ENTRY_IS_NULL if entry is
 * <i>NULL</i>.
 */
bool seahorse_red_black_tree_map_ni_ni_entry_set_value(
        const struct seahorse_red_black_tree_map_ni_ni *object,
        const struct seahorse_red_black_tree_map_ni_ni_entry *entry,
        uintmax_t value);

#endif /* _SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_H_ */
