# zer::file v1 (outdated)

### ! This is an outdated version.
### ! See default branch to get [current version](https://github.com/ZERDICORP/file-lib).
### ! Use this version only if it is used in your project.

***

### Minimum usage:
```cpp
zer::File file("text.txt");

/*
    Read.
*/
file.read();
std::string sData = file.data();

/*
    Write.
*/
file.write("Hello, world!");
```

### Dependencies:
- [athm.h](https://github.com/ZERDICORP/athm-lib.git)
