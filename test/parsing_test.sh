echo color_ceiling_missing.cub
valgrind ./cub3D maps/error_maps/color_ceiling_missing.cub
echo "----------------"
echo color_floor_missing.cub
valgrind ./cub3D maps/error_maps/color_floor_missing.cub
echo "----------------"
echo color_parameter_ends_with_coma.cub
valgrind ./cub3D maps/error_maps/color_parameter_ends_with_coma.cub
echo "----------------"
echo color_parameter_max_int.cub
valgrind ./cub3D maps/error_maps/color_parameter_max_int.cub
echo "----------------"
echo color_parameter_negative.cub
valgrind ./cub3D maps/error_maps/color_parameter_negative.cub
echo "----------------"
echo color_parameter_too_long.cub
valgrind ./cub3D maps/error_maps/color_parameter_too_long.cub
echo "----------------"
echo color_parameter_too_short.cub
valgrind ./cub3D maps/error_maps/color_parameter_too_short.cub
echo "----------------"
echo color_parameter_wrong.cub
valgrind ./cub3D maps/error_maps/color_parameter_wrong.cub
echo "----------------"
echo color_set_twice.cub
valgrind ./cub3D maps/error_maps/color_set_twice.cub
echo "----------------"
echo file_extension_missing
valgrind ./cub3D maps/error_maps/file_extension_missing
echo "----------------"
echo file_extension_wrong.cubs
valgrind ./cub3D maps/error_maps/file_extension_wrong.cubs
echo "----------------"
echo map_forbidden_character.cub
valgrind ./cub3D maps/error_maps/map_forbidden_character.cub
echo "----------------"
echo map_is_not_last.cub
valgrind ./cub3D maps/error_maps/map_is_not_last.cub
echo "----------------"
echo map_is_open1.cub
valgrind ./cub3D maps/error_maps/map_is_open1.cub
echo "----------------"
echo map_is_open2.cub
valgrind ./cub3D maps/error_maps/map_is_open2.cub
echo "----------------"
echo map_missing.cub
valgrind ./cub3D maps/error_maps/map_missing.cub
echo "----------------"
echo map_no_starting_position.cub
valgrind ./cub3D maps/error_maps/map_no_starting_position.cub
echo "----------------"
echo map_too_many_starting_positions.cub
valgrind ./cub3D maps/error_maps/map_too_many_starting_positions.cub
echo "----------------"
echo texture_file_broken.cub
valgrind ./cub3D maps/error_maps/texture_file_broken.cub
echo "----------------"
echo texture_file_chmod_0.cub
valgrind ./cub3D maps/error_maps/texture_file_chmod_0.cub
echo "----------------"
echo texture_is_directory.cub
valgrind ./cub3D maps/error_maps/texture_is_directory.cub
echo "----------------"
echo texture_missing.cub
valgrind ./cub3D maps/error_maps/texture_missing.cub
echo "----------------"
echo texture_parameter_wrong.cub
valgrind ./cub3D maps/error_maps/texture_parameter_wrong.cub
echo "----------------"
echo texture_set_twice.cub
valgrind ./cub3D maps/error_maps/texture_set_twice.cub
