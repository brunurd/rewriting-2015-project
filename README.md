# Tic Tac Toe - C++

A college project made in 2015 using **[Borland BGI](http://www.codecutter.net/tools/winbgim/)**.

## How to compile (Windows only)

### MinGW (cmake, make, gcc)

You can generate a project runing cmake in the root folder, I build using CLion with a MinGW i686 stack (I recommend **[msys2](https://www.msys2.org/)**). It don't work with Visual C++ because the bgi static lib is not a `.lib` file.  

### Dev-cpp

In the college we needed to use **[Dev-C++](https://sourceforge.net/projects/orwelldevcpp/files/Setup%20Releases/Dev-Cpp%205.2.0.3%20MinGW32%20Setup.exe/download)** with the MinGW embedded (It's need to be a 32 bits only version because the bgi static library). Just open the project `dev-cpp/TicTacToe.dev` and compile.  
