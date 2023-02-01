Project tree:

| rvm/           <-- Radio Virtual Machine source file 
|  - |include/
|  - |src/
|  - |tests/
|  - |Makefile
|fc/            <-- Front-end compiler source file 
|  - |include/
|  - |src/
|  - |tests/
|  - |Makefile
|config/
|  - |Makefile.colors
|Makefile       <-- The main Makefile for the build


Build Radio Virtual Machine and Front-end compiler
> make

Run rvm
> ./build/bin/rvm

Run front-end compiler
> ./build/bin/fc

Remove building
> clean

