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
## Building and running

<details>
<summary><b>Building</b></summary>

> ### Build Radio Virtual Machine and Front-end compiler
> ```bash
> make
> ```
> ### Build Radio Virtual Machine
> ```bash
> make rvm
> ```
> ### Build Front-end compiler
> ```bash
> make fc
> ```

</details>

<details>
<summary><b>Running</b></summary>

> ### Run rvm
> ```bash
> ./build/bin/rvm
> ```
> ### Run Front-end compiler
> ```bash
> ./build/bin/fc
>  ```

</details>

<details>
<summary><b>Cleaning</b></summary>

> ### Remove all builds
> ```bash
> make clean
> ```

> ### Delete Radio Virtual Machine builds
> ```bash
> make rvm-clean
> ```

> ### Delete Front-end compiler builds
> ```bash
> make fc-clean
> ```

</details>

