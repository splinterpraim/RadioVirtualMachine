## Project description
The European Telecommunications Standards Institute has proposed
a software method for implementing a reconfigurable radio, providing
use in architecture Radio Virtual Machine (RVM).

This project includes front-end compiler (fc) application for RVM and rvm application.

The front-end compiler takes an XML file with the algorithm as input and creates a binary input file for rvm, which runs it
## Project tree:
```
.
├── common      <-- Common source file 
│   ├── include
│   ├── Makefile
│   └── src
├── fc          <-- Front-end compiler source file 
│   ├── include
│   ├── Makefile
│   ├── src
│   └── tests
├── rvm         <-- Radio Virtual Machine source file 
│   ├── include
│   ├── Makefile
│   ├── src
│   └── tests
├── config      <-- Configuration for build 
│   ├── Makefile.colors
│   └── Makefile.settings
├── XML_files   <-- Examples of XML input files for Front-end compiler
├── Makefile    <-- The main Makefile for the build
└── readme.md

```
## Build and run


<details>
<summary><b>Build</b></summary>

<blockquote>

  ### Build Radio Virtual Machine and Front-end compiler
  ```
  make
  ```
  ### Build Radio Virtual Machine
  ```
  make rvm
  ```
  ### Build Front-end compiler
  ```
  make fc
  ```
</blockquote>

</details>


<details>
<summary><b>Run</b></summary>

<blockquote>

  ### Run rvm
  ```
  ./build/bin/rvm
  ```
  ### Run Front-end compiler
  ```
  ./build/bin/fc
   ```

</blockquote>

</details>

<details>
<summary><b>Cleaning</b></summary>

<blockquote>

  ### Delete all builds
  ```bash
  make clean
  ```

  ### Delete Radio Virtual Machine builds
  ```bash
  make rvm-clean
  ```

  ### Delete Front-end compiler builds
  ```bash
  make fc-clean
  ```

</blockquote>

</details>

## Platforms

+ macOS Monterey Version 12.5.1
+ Debian GNU/Linux 11 (bullseye) 