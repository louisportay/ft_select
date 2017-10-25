`ft_select` Program to select visually a list of files

-Handle native filetypes and files extensions to print in colors, bold, italic, etc...
-The cursor moves in 4 directions.
-Signal handling well executed, will always restore the terminal as it was at the origin (Compile without ASAN)
- 'directory' option -- Open the directories given in arguments and retrieve the files inside them.
-Portable over Linux (Debian) and OS X (Sierra)
-Screen resizing without flashes
-Dynamic search with auto-completion
-Minimum Column Width for padding (Change at compile time)
