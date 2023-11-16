# cub3d_hh
So far (until 29.10.2023) code seems to:

```
- DONE - Initialize `t_map` struct with NULLs and zeros for all fields.
- DONE - Verify `.cub` file extension with `is_cub`.
- DONE - Open `.cub` file with `open_config_file`.
- DONE - Read lines from file using `get_next_line` in a loop until EOF.
- DONE - For each line read:
  -DONE - If line starts with a texture identifier (e.g., "NO"), call `parse_texture`.
  -DONE - If line starts with a color identifier (e.g., "F" or "C"), call `parse_color`.
  -DONE - If line is part of the map layout, call `fill_map_tiles`.
  -DONE - If any errors occur during parsing, handle with `ft_error` and exit.
- DONE - Test the parser with a suite of unit tests, including:
  - DONE - Valid `.cub` files with different map and configuration variations.
  - Invalid `.cub` files to test error handling.
- DONE - Free allocated resources properly with `free_map_exit` before exiting the program.
- DONE - After parsing is complete, validate the map's integrity with a `map_valid` function.
- DONE - Test valid maps according to validation rules fro the pdf
- DONE - test the to be validated maps, these are supposed to be valid but my parser says otherwise
- test error maps and make the parser say so
like
NO textures/Test1.png
NO textures/Test1.png
NO textures/Test1.png
```

#### TESTING PLAN
Running tests after completing the missing parts of your parser is a crucial step in ensuring that your code is robust and behaves as expected. Your planned tests should aim to cover a comprehensive range of scenarios to thoroughly exercise your code. Here's a suggested approach for your testing plan:

1. **Basic Functionality Test**:
   - Test with a perfectly valid `.cub` file to ensure that the parser can read and store all data correctly.
   - Check that all paths for textures are correctly assigned.
   - Verify that floor and ceiling colors are accurately parsed.
   - Ensure the map layout (tiles) is correctly stored in the `t_map` structure.

2. **Error Handling Test**:
   - Test with `.cub` files that have missing elements (e.g., no floor color specified) to ensure that your parser detects this and handles it appropriately.
   - Test with `.cub` files that have invalid formats (e.g., wrong color values, invalid texture paths) to ensure that `ft_error` is called.
   - Test with `.cub` files that have incorrectly formatted map layouts to ensure that the parser detects invalid map configurations.

3. **Edge Case Test**:
   - Test with `.cub` files that are at the edge of acceptable limits (e.g., very large map sizes, long lines) to ensure that your parser can handle them without crashing.
   - Test with `.cub` files that contain extra whitespace, empty lines, or unusual ordering of elements to ensure the parser is robust against such variations.

4. **Memory Leak Test**:
   - Use a tool like `valgrind` (if available on your system) to check for memory leaks for each test case.
   - Ensure that for every `malloc`, there is an appropriate `free` at all possible exit points.

5. **Integration Test**:
   - Once the parser is confirmed to be working correctly in isolation, test it as part of the larger application to ensure it integrates well with the rendering and game logic parts of your project.

6. **User Interaction Test**:
   - Simulate keypress events to ensure that the player can move and look around in the game as expected.
   - Test that the game correctly responds to the ESC key and window close events.

7. **Automated Testing**:
   - If possible, automate your tests so they can be easily rerun.
   - Implement a continuous integration system to run tests automatically upon each commit or before merges.

8. **Regression Testing**:
   - Re-run all tests whenever a change is made to the parser code to ensure that no previously working functionality has been broken.
