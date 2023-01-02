# aquarium-seahorse

![main](https://github.com/pretore/aquarium-seahorse/actions/workflows/cmake.yml/badge.svg?branch=main)

Collections in C.

[aquarium-coral](https://github.com/pretore/aquarium-coral) data structures
prepared with data types from 
[aquarium-seagrass](https://github.com/pretore/aquarium-seagrass),
[aquarium-sea-turtle](https://github.com/pretore/aquarium-sea-turtle) and
[aquarium-triggerfish](https://github.com/pretore/aquarium-triggerfish).

| short code | description       |       data type        |
|:----------:|:------------------|:----------------------:|
|     ni     | native integer    |       uintmax_t        |
|     p      | pointer           |         void*          |
|     i      | integer           | ``sea_turtle_integer`` |
|     s      | string            | ``sea_turtle_string``  |
|     sr     | strong reference  | ``triggerfish_strong`` |
|     wr     | weak reference    |  ``triggerfish_weak``  |

### [list](https://en.wikipedia.org/wiki/List_(abstract_data_type))

- ``seahorse_array_list_i``
- ``seahorse_array_list_ni``
- ``seahorse_array_list_p``

### [map](https://en.wikipedia.org/wiki/Associative_array)

- ``seahorse_red_black_tree_map_i_i``
- ``seahorse_red_black_tree_map_ni_i``
- ``seahorse_red_black_tree_map_ni_ni``
- ``seahorse_red_black_tree_map_ni_p``
- ``seahorse_red_black_tree_map_s_s``
- ``seahorse_red_black_tree_map_s_wr``

### [set](https://en.wikipedia.org/wiki/Set_(abstract_data_type))

- ``seahorse_linked_red_black_tree_set_ni``
- ``seahorse_red_black_tree_set_ni``

### [queue](https://en.wikipedia.org/wiki/Queue_(abstract_data_type))

- ``seahorse_linked_queue_ni``
- ``seahorse_linked_queue_sr``

### [stack](https://en.wikipedia.org/wiki/Stack_(abstract_data_type))

- ``seahorse_linked_stack_ni``
