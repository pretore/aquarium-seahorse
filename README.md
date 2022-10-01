# aquarium-seahorse

![main](https://github.com/pretore/aquarium-seahorse/actions/workflows/cmake.yml/badge.svg?branch=main)

[aquarium-rock](https://github.com/pretore/aquarium-rock) data structures 
prepared with data types from 
[aquarium-sea-turtle](https://github.com/pretore/aquarium-sea-turtle) or 
[aquarium-seagrass](https://github.com/pretore/aquarium-seagrass).

### array
- ``seahorse_array_ni`` - _array for uintmax_t values_.
- ``seahorse_array_i`` - _array for ``sea_turtle_integer`` values._

### map
- ``seahorse_red_black_tree_map_ni_ni`` - _red-black tree backed map with 
  uintmax_t keys and uintmax_t values._
- ``seahorse_red_black_tree_map_ni_p`` - _red-black tree backed map with 
  uintmax_t keys and void* values._
- ``seahorse_red_black_tree_map_i_i`` - _red-black tree backed map with 
  ``sea_turtle_integer`` keys and ``sea_turtle_integer`` values._
- ``seahorse_red_black_tree_map_s_s`` - _red-black tree backed map with 
  ``sea_turtle_string`` keys and ``sea_turtle_string`` values._

### set
- ``seahorse_red_black_tree_set_ni`` - _red-black tree backed set for 
  uintmax_t values_.
