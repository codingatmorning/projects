# 3D Implicit Graphing Calculator

:heavy_check_mark: I provided a distribution for windows 10 intel x86_64, run the program by click appl.exe (z is up, not y)

:heavy_check_mark: The equation I used in the example was ``` z^2=25-(10-sqrt(x^2+y^2))^2 ```

:heavy_check_mark: The front end python code has been posted however the back end code remains private. However, I provided a windows executable of the backend back.exe that works on the above system

:grey_exclamation: the python code was compiled with nuitka, and the python libraries used were numpy, pyqt5, and subprocess

:negative_squared_cross_mark: The program is usually good about closing background processes, but sometimes back.exe is left running so check task manager

- [ ] Run back.exe as daemon instead of as subprocess
