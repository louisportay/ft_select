*ft_select* Program to select visually a list of files

**Features**

#Handle native filetypes and files extensions to print in colors, bold, italic, etc...
#The cursor moves in 4 directions (More complicated to implement than to say...)
#Signal handling well executed (no ioctl call), will always restore the terminal as it was at the origin, even if deadly signal happen (Compile without ASAN)
#Job control working fine (CTRL-Z, fg, bg), TERM environment handled properly
# 'directory' mode -- Open the directories given in arguments and retrieve the files inside them. Do not pass arguments of length greater than 512(Or it will likely crash or cause an heap-buffer overflow)
#Portable over Linux (Debian) and OS X (Sierra)
#Screen Resizing (without flashes)
#'Smart Padding' will change when the matched files change
#Minimum Column Width for minimum filename padding (Change at compile time)
#Dynamic search with auto-completion (display a subset a files matching the buffer)
#See extensive documentation in the header file (`includes/ft_select.h`), every source file contain documentation
#Comprehensive Error Messages
#Clean code, deallocate everything at the end, do not browse the list up-and-down for no use (O(n) complexity)
#Light Memory Footprint (except for the Termcap part), little dynamic memory allocation in the program
#Minimum number of Syscalls (stored the values into the program data structures)

**Known issues**

#Screen flash when processing the list very quickly
#Buffer get filled when processing too quickly the list with the trackpad or the mouse Button 3 (Set *c_cc.[VMIN], c_cc[VTIME]* properly ?)
