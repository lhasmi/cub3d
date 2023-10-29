# cub3d_hh
So far (until 28.10.2023) code seems to:

1. **Check the file extension** to ensure it's a `.cub` file (`is_cub` function).
2. **Open the `.cub` file** and handle opening errors.
3. **Read lines from the file** using `get_next_line`.
4. **Parse lines** based on their prefix to identify what type of data they contain (`parse_line` function).
5. **Allocate and store texture paths** in the `t_map` structure (`parse_texture` function).
6. **Parse RGB color values** and store them in the `t_map` structure (`parse_color` function).
7. **Store the map layout** as an array of strings in the `t_map` structure (`fill_map_tiles` function).
8. **Dynamically resize the array** that holds the map layout (`manual_realloc_2D_array` function).
9. **Free allocated resources** and handle errors (`free_map_exit` and `ft_error` functions).

What appears to be missing or needs verification includes:

1. **Initialization of the map structure** (`init_map` function) with NULL pointers and zeroed dimensions.
2. **Validation function** for the map data after parsing (`map_valid` function or similar).
3. **Implementation of `parse_color`** to convert color strings into integer values.
4. **Actual content parsing in `fill_map_tiles`**, since the current function just reallocates the array but does not parse the individual tiles.
5. **Implementing a unit testing framework** to test the parsing of the `.cub` file with various test cases.
6. **Implementation of `is_space`, `ft_strtok`, and `is_path_valid`** if they're not already part of your codebase.
7. **Implementation of a function to update `cols`** in `t_map` based on the length of the longest line in the map layout.
8. **Rendering setup** for MiniLibX, including initialization of `t_img` and handling of textures and images.

Here's a revised pseudocode checklist that considers the existing code and outlines what might be missing:

```plaintext
- Initialize `t_map` struct with NULLs and zeros for all fields.
- Verify `.cub` file extension with `is_cub`.
- Open `.cub` file with `open_config_file`.
- Read lines from file using `get_next_line` in a loop until EOF.
- For each line read:
  - If line starts with a texture identifier (e.g., "NO"), call `parse_texture`.
  - If line starts with a color identifier (e.g., "F" or "C"), call `parse_color`.
  - If line is part of the map layout, call `fill_map_tiles`.
  - If any errors occur during parsing, handle with `ft_error` and exit.
- After parsing is complete, validate the map's integrity with a `map_valid` function.
- Test the parser with a suite of unit tests, including:
  - Valid `.cub` files with different map and configuration variations.
  - Invalid `.cub` files to test error handling.
- Free allocated resources properly with `free_map_exit` before exiting the program.
- Set up key hooks for MLX and event handling.
- Initialize `t_img` and load textures.
- Enter the main MLX loop and render the initial scene.
```

Ensure that each function is implemented correctly, and test each one individually. Additionally, write comprehensive unit tests for each parsing component to validate your parser's robustness. Once the parser is fully tested and validated, you can confidently integrate it with the rendering part of your game.