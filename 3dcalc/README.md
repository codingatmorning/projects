# 3D Implicit Graphing Calculator

The distribution should work for windows 10 intel x86-64 systems. Everything is statically linked, and if not libraries are provided. To run the program start appl.exe.

The equation I used in the example was

The front end python code has been posted however the back end code remains private. However I provided a windows executable that works on the above system.

Be wary the front end code is ussually good at handling subprocess, but sometimes the back end process will be left running so make sure after using the program open task manager and see if a process back.exe is left running
- [ ] Make back end sub process a daemon to counter left over processes
