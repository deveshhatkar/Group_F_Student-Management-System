# Student Records Management System

## Release 2
<br/>


# Authors
| Members                  |Worked in                                       |
|--------------------------|------------------------------------------------|
| Qun Cao                  |Student functions                               |
| Siyuan Chen              |User functions, Testing, Repository management  |
| Devesh Prabhakar Hatkar  |File-related functions, Wiki                    |
| Mingfang Hu              |User interface functions                        |

<br/>

## Organization
- Carleton University
- University of Ottawa

<br/>

# Introduction
The Student Records Management System aims to digitize and hence ease the process of maintaining student details (such as their personal information, Grades, Courses enrolled) enrolled in an institution. The main motivation behind developing this project is to reduce the overhead of maintaining a physical file system for bookkeeping student information, which is both time consuming and prone to inconsistencies. This software ensures speedy creation/updation/deletion of this data. Additionally a digital system (and hence also this software) also ensures (almost) instant retrieval of this data based on various search parameters; which otherwise would be time consuming and effortful, if done conventionally.
Hence, this software is an attempt to utilize the perks of using a digital system for managing data. 

# File organization
- config: This folder contains the data stored by the program, e.g. student data, user data. 
- img: This folder contains the image file for Wiki.
- include: This folder contains the header files
- src: This folder contains the source files.
- test: This folder contains the header and source files for testing.
- .gitignore: "git ignore", list of files and folders to be ignored by git.
- LICENSE: License used for this repo.
- Makefile: used by make to build the executable file
- Readme.md: Readme file for this project

# Building Guidelines
Running `make` on Linux or Cygwin (windows) to build:
```
make
```

# Run
Change directory to `bin`
```
cd bin
```

Then run the binary file with the following command (in Linux):
```
./stumgr
```
or in Windows with Cygwin:
```
stumgr.exe
```

# Documentation
Please refer to Wiki pages of this repository:<br/>
[User manual](https://github.com/SiyuanChen-main/Group_F_Student-Management-System/wiki/User-Manual)<br/>
[Developer manual](https://github.com/SiyuanChen-main/Group_F_Student-Management-System/wiki/Developer-Manual)<br/>
