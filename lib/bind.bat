@echo off

:: ✅ Fixed: no quotes in the variable itself
set PYTHON_INC=C:\Users\Ahmed Mustafa\AppData\Local\Programs\Python\Python312\include
set PYTHON_LIB_DIR=C:\Users\Ahmed Mustafa\AppData\Local\Programs\Python\Python312\libs
set PYBIND11_INC=C:\Users\Ahmed Mustafa\Desktop\acture-server\env\Lib\site-packages\pybind11\include

:: ✅ Build with MSVC's cl.exe (run this from Developer Command Prompt)
cl /LD /EHsc /std:c++17 intrastation_bind.cpp ^
   /I"%PYTHON_INC%" /I"%PYBIND11_INC%" ^
   /link /LIBPATH:"%PYTHON_LIB_DIR%" python312.lib /OUT:pystation.pyd

pause
