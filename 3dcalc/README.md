# 3D Implicit Graphing Calculator

<img src="https://user-images.githubusercontent.com/60249504/136651126-91e6ee99-4b8d-4b79-a563-aeed1d048aff.gif" alt="Img Couldn't Load" width="800">

# Basic Info

:cherry_blossom: I provided a distribution for intel x86_64, run the program by clicking appl.exe (z is up, not y)

:cherry_blossom: The equation I used in the example was ``` z^2=25-(10-sqrt(x^2+y^2))^2 ```

:cherry_blossom: The front end python code has been posted however the back end code remains private. However, I provided a x86_64 executable of the backend back.exe.

:cherry_blossom: The python code was compiled with nuitka, and the python libraries used were numpy, pyqt5, and subprocess

:new_moon: The program is usually good about closing background processes, but sometimes back.exe is left running so check task manager

- [ ] Run back.exe as daemon instead of as subprocess
