#ifndef _SEAHORSE_RED_BLACK_TREE_MAP_S_WR_H_
#define _SEAHORSE_RED_BLACK_TREE_MAP_S_WR_H_

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <coral.h>

struct sea_turtle_string;
struct triggerfish_weak;

#define SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL               1
#define SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OUT_IS_NULL                  2
#define SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_IS_NULL                  3
#define SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_VALUE_IS_NULL                4
#define SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_MEMORY_ALLOCATION_FAILED     5
#define SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_ALREADY_EXISTS           6
#define SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_NOT_FOUND                7
#define SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_MAP_IS_EMPTY                 8
#define SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_ENTRY_IS_NULL                9
#define SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_END_OF_SEQUENCE              10
#define SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OTHER_IS_NULL                11

struct seahorse_red_black_tree_map_s_wr {
    struct coral_red_black_tree_map map;
};

struct seahorse_red_black_tree_map_s_wr_entry;

/**
 * @brief Initialize red black tree map.
 * @param [in] object instance to be initialized.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 */
bool seahorse_red_black_tree_map_s_wr_init(
        struct seahorse_red_black_tree_map_s_wr *object);

/**
 * @brief Copy initialize red black tree map.
 * @param [in] object instance to be initialized.
 * @param [in] other red black tree map to be copied.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL if object
 * is <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OTHER_IS_NULL if other is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_MEMORY_ALLOCATION_FAILED if
 * there is insufficient memory to create a copy.
 */
bool seahorse_red_black_tree_map_s_wr_init_red_black_tree_map_s_wr(
        struct seahorse_red_black_tree_map_s_wr *object,
        const struct seahorse_red_black_tree_map_s_wr *other);

/**
 * @brief Invalidate red black tree map.
 * <p>The actual <u>tree map instance is not deallocated</u> since it may
 * have been embedded in a larger structure.</p>
 * @param [in] object instance to be invalidated.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 */
bool seahorse_red_black_tree_map_s_wr_invalidate(
        struct seahorse_red_black_tree_map_s_wr *object);

/**
 * @brief Retrieve the count of entries.
 * @param [in] object instance whose count we are to retrieve.
 * @param [out] out receive the entry count.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL if object
 * is <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 */
bool seahorse_red_black_tree_map_s_wr_count(
        const struct seahorse_red_black_tree_map_s_wr *object,
        uintmax_t *out);

/**
 * @brief Add a key-value association.
 * @param [in] object tree map instance.
 * @param [in] key to which the value will be associated with.
 * @param [in] value that will returned from a lookup of key.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_IS_NULL if key is
 * <i>NULL<i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_VALUE_IS_NULL if value is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_ALREADY_EXISTS if the
 * key is already present in the tree map.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_MEMORY_ALLOCATION_FAILED if
 * there is insufficient memory to add key-value association to the tree map.
 * @note <b>key</b> and <b>value</b> are copied and then placed into the map.
 */
bool seahorse_red_black_tree_map_s_wr_add(
        struct seahorse_red_black_tree_map_s_wr *object,
        const struct sea_turtle_string *key,
        const struct triggerfish_weak *value);

/**
 * @brief Remove key-value association.
 * @param [in] object tree map instance.
 * @param [in] key for which we would like the key-value association removed.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_IS_NULL if key is
 * <i>NULL<i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_NOT_FOUND if key could
 * not be found.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_MEMORY_ALLOCATION_FAILED if
 * there is insufficient memory to find the key-value association.
 */
bool seahorse_red_black_tree_map_s_wr_remove(
        struct seahorse_red_black_tree_map_s_wr *object,
        const struct sea_turtle_string *key);

/**
 * @brief Check if tree map contains the given key.
 * @param [in] object tree map instance.
 * @param [in] key to check if it is present.
 * @param [out] out true if key is present, otherwise false.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL if object
 * is <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_IS_NULL if key is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_MEMORY_ALLOCATION_FAILED if
 * there is insufficient memory to find the key-value association.
 */
bool seahorse_red_black_tree_map_s_wr_contains(
        const struct seahorse_red_black_tree_map_s_wr *object,
        const struct sea_turtle_string *key,
        bool *out);

/**
 * @brief Set the value for the given key.
 * @param [in] object tree map instance.
 * @param [in] key used for which value is to be changed.
 * @param [in] value of new association with given key.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_IS_NULL if key is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_VALUE_IS_NULL if value is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_NOT_FOUND if key could
 * not be found.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_MEMORY_ALLOCATION_FAILED if
 * there is not enough memory to set the entry's value.
 * @note <b>value</b> is copied and then placed into the map.
 */
bool seahorse_red_black_tree_map_s_wr_set(
        struct seahorse_red_black_tree_map_s_wr *object,
        const struct sea_turtle_string *key,
        const struct triggerfish_weak *value);

/**
 * @brief Retrieve the value for the given key.
 * @param [in] object tree map instance.
 * @param [in] key used to get the associated value.
 * @param [out] out receive the value.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_IS_NULL if key is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_NOT_FOUND if key could
 * not be found.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_MEMORY_ALLOCATION_FAILED if
 * there is insufficient memory to find the key-value association.
 */
bool seahorse_red_black_tree_map_s_wr_get(
        const struct seahorse_red_black_tree_map_s_wr *object,
        const struct sea_turtle_string *key,
        const struct triggerfish_weak **out);

/**
 * @brief Retrieve the value for the given key or the next higher key.
 * @param [in] object tree map instance.
 * @param [in] key to find or the next higher key.
 * @param [out] out receive the value.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_IS_NULL if key is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_NOT_FOUND if key nor a
 * higher key is in the tree map instance.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_MEMORY_ALLOCATION_FAILED if
 * there is insufficient memory to find the key-value association.
 */
bool seahorse_red_black_tree_map_s_wr_ceiling(
        const struct seahorse_red_black_tree_map_s_wr *object,
        const struct sea_turtle_string *key,
        const struct triggerfish_weak **out);

/**
 * @brief Retrieve the value for the given key or the next lower key.
 * @param [in] object tree map instance.
 * @param [in] key to find or the next lower key.
 * @param [out] out receive the value.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_IS_NULL if key is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_NOT_FOUND if key nor a
 * lower key is in the tree map instance.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_MEMORY_ALLOCATION_FAILED if
 * there is insufficient memory to find the key-value association.
 */
bool seahorse_red_black_tree_map_s_wr_floor(
        const struct seahorse_red_black_tree_map_s_wr *object,
        const struct sea_turtle_string *key,
        const struct triggerfish_weak **out);

/**
 * @brief Retrieve the value for the next higher key.
 * @param [in] object tree map instance.
 * @param [in] key whose next higher key we are trying to find.
 * @param [out] out receive the value.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_IS_NULL if key is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_NOT_FOUND if no higher
 * key is in the tree map instance.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_MEMORY_ALLOCATION_FAILED if
 * there is insufficient memory to find the key-value association.
 */
bool seahorse_red_black_tree_map_s_wr_higher(
        const struct seahorse_red_black_tree_map_s_wr *object,
        const struct sea_turtle_string *key,
        const struct triggerfish_weak **out);

/**
 * @brief Retrieve the value for the next lower key.
 * @param [in] object tree map instance.
 * @param [in] key whose next lower key we are trying to find.
 * @param [out] out receive the value.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_IS_NULL if key is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_NOT_FOUND if no lower
 * value for key is in the tree map instance.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_MEMORY_ALLOCATION_FAILED if
 * there is insufficient memory to find the key-value association.
 */
bool seahorse_red_black_tree_map_s_wr_lower(
        const struct seahorse_red_black_tree_map_s_wr *object,
        const struct sea_turtle_string *key,
        const struct triggerfish_weak **out);

/**
 * @brief Retrieve value of first entry.
 * @param [in] object tree map instance.
 * @param [out] out receive the first entry's value.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_MAP_IS_EMPTY if tree map is
 * empty.
 */
bool seahorse_red_black_tree_map_s_wr_first(
        const struct seahorse_red_black_tree_map_s_wr *object,
        const struct triggerfish_weak **out);

/**
 * @brief Retrieve value of last entry.
 * @param [in] object tree map instance.
 * @param [out] out receive the last entry's value.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_MAP_IS_EMPTY if tree map is
 * empty.
 */
bool seahorse_red_black_tree_map_s_wr_last(
        const struct seahorse_red_black_tree_map_s_wr *object,
        const struct triggerfish_weak **out);

/**
 * @brief Retrieve entry for the given key.
 * @param [in] object tree map instance.
 * @param [in] key of the entry we are looking for.
 * @param [out] out receive the <u>address of</u> entry.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_IS_NULL if key is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_NOT_FOUND if key could
 * not be found.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_MEMORY_ALLOCATION_FAILED if
 * there is insufficient memory to find the key-value association.
 */
bool seahorse_red_black_tree_map_s_wr_get_entry(
        const struct seahorse_red_black_tree_map_s_wr *object,
        const struct sea_turtle_string *key,
        const struct seahorse_red_black_tree_map_s_wr_entry **out);

/**
 * @brief Retrieve the entry for the given key or the next higher key.
 * @param [in] object tree map instance.
 * @param [in] key to find or the next higher key.
 * @param [out] out receive the <u>address of</u> entry.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_IS_NULL if key is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_NOT_FOUND if key nor a
 * higher key is in the tree map instance.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_MEMORY_ALLOCATION_FAILED if
 * there is insufficient memory to find the key-value association.
 */
bool seahorse_red_black_tree_map_s_wr_ceiling_entry(
        const struct seahorse_red_black_tree_map_s_wr *object,
        const struct sea_turtle_string *key,
        const struct seahorse_red_black_tree_map_s_wr_entry **out);

/**
 * @brief Retrieve the entry for the given key or the next lower key.
 * @param [in] object tree map instance.
 * @param [in] key to find or the next lower key.
 * @param [out] out receive the <u>address of</u> entry.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_IS_NULL if key is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_NOT_FOUND if key nor a
 * lower key is in the tree map instance.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_MEMORY_ALLOCATION_FAILED if
 * there is insufficient memory to find the key-value association.
 */
bool seahorse_red_black_tree_map_s_wr_floor_entry(
        const struct seahorse_red_black_tree_map_s_wr *object,
        const struct sea_turtle_string *key,
        const struct seahorse_red_black_tree_map_s_wr_entry **out);

/**
 * @brief Retrieve the entry for the next higher key.
 * @param [in] object tree map instance.
 * @param [in] key whose next higher key we are trying to find.
 * @param [out] out receive the <u>address of</u> entry.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_IS_NULL if key is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_NOT_FOUND if no higher
 * key is in the tree map instance.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_MEMORY_ALLOCATION_FAILED if
 * there is insufficient memory to find the key-value association.
 */
bool seahorse_red_black_tree_map_s_wr_higher_entry(
        const struct seahorse_red_black_tree_map_s_wr *object,
        const struct sea_turtle_string *key,
        const struct seahorse_red_black_tree_map_s_wr_entry **out);

/**
 * @brief Retrieve the entry for the next lower key.
 * @param [in] object tree map instance.
 * @param [in] key whose next lower key we are trying to find.
 * @param [out] out receive the <u>address of</u> entry.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_IS_NULL if key is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_NOT_FOUND if no lower
 * value for item is in the tree map instance.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_MEMORY_ALLOCATION_FAILED if
 * there is insufficient memory to find the key-value association.
 */
bool seahorse_red_black_tree_map_s_wr_lower_entry(
        const struct seahorse_red_black_tree_map_s_wr *object,
        const struct sea_turtle_string *key,
        const struct seahorse_red_black_tree_map_s_wr_entry **out);

/**
 * @brief Retrieve first entry.
 * @param [in] object tree map instance.
 * @param [out] out receive the <u>address of</u> the first entry.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_MAP_IS_EMPTY if tree map is
 * empty.
 */
bool seahorse_red_black_tree_map_s_wr_first_entry(
        const struct seahorse_red_black_tree_map_s_wr *object,
        const struct seahorse_red_black_tree_map_s_wr_entry **out);

/**
 * @brief Retrieve last entry.
 * @param [in] object tree map instance.
 * @param [out] out receive the <u>address of</u> the last entry.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_MAP_IS_EMPTY if tree map is
 * empty.
 */
bool seahorse_red_black_tree_map_s_wr_last_entry(
        const struct seahorse_red_black_tree_map_s_wr *object,
        const struct seahorse_red_black_tree_map_s_wr_entry **out);

/**
 * @brief Remove entry.
 * @param [in] object tree map instance.
 * @param [in] entry <u>address of</u> entry to be removed.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_ENTRY_IS_NULL if entry is
 * <i>NULL</i>.
 */
bool seahorse_red_black_tree_map_s_wr_remove_entry(
        struct seahorse_red_black_tree_map_s_wr *object,
        const struct seahorse_red_black_tree_map_s_wr_entry *entry);

/**
 * @brief Retrieve the next entry.
 * @param [in] entry <u>address of</u> current entry.
 * @param [out] out receive the <u>address of</u> the next entry.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_ENTRY_IS_NULL if entry is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_END_OF_SEQUENCE if there is
 * no next entry.
 */
bool seahorse_red_black_tree_map_s_wr_next_entry(
        const struct seahorse_red_black_tree_map_s_wr_entry *entry,
        const struct seahorse_red_black_tree_map_s_wr_entry **out);

/**
 * @brief Retrieve the previous entry.
 * @param [in] entry <u>address of</u> current entry.
 * @param [out] out receive the <u>address of</u> the previous entry.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_ENTRY_IS_NULL if entry is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_END_OF_SEQUENCE if there is
 * no previous entry.
 */
bool seahorse_red_black_tree_map_s_wr_prev_entry(
        const struct seahorse_red_black_tree_map_s_wr_entry *entry,
        const struct seahorse_red_black_tree_map_s_wr_entry **out);

/**
 * @brief Retrieve the entry's key.
 * @param [in] object tree map instance.
 * @param [in] entry <u>address of</u> entry contained within the tree map
 * instance.
 * @param [out] out receive the entry's key.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_ENTRY_IS_NULL if entry is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 */
bool seahorse_red_black_tree_map_s_wr_entry_key(
        const struct seahorse_red_black_tree_map_s_wr *object,
        const struct seahorse_red_black_tree_map_s_wr_entry *entry,
        const struct sea_turtle_string **out);

/**
 * @brief Retrieve the entry's value.
 * @param [in] object tree map instance.
 * @param [in] entry <u>address of</u> entry contained within the tree map
 * instance.
 * @param [out] out receive the entry's value.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_ENTRY_IS_NULL if entry is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 */
bool seahorse_red_black_tree_map_s_wr_entry_get_value(
        const struct seahorse_red_black_tree_map_s_wr *object,
        const struct seahorse_red_black_tree_map_s_wr_entry *entry,
        const struct triggerfish_weak **out);

/**
 * @brief Set the entry's value.
 * @param [in] object tree map instance.
 * @param [in] entry <u>address of</u> entry contained within the tree map
 * instance.
 * @param [in] value to set entry's value to.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_ENTRY_IS_NULL if entry is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_VALUE_IS_NULL if value is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_MEMORY_ALLOCATION_FAILED if
 * there is not enough memory to set the entry's value.
 * @note <b>value</b> is copied and then set as the entry's value.
 */
bool seahorse_red_black_tree_map_s_wr_entry_set_value(
        const struct seahorse_red_black_tree_map_s_wr *object,
        const struct seahorse_red_black_tree_map_s_wr_entry *entry,
        const struct triggerfish_weak *value);

#endif /* _SEAHORSE_RED_BLACK_TREE_MAP_S_WR_H_ */
