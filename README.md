# zer::File v2

[![Build Status](https://travis-ci.com/ZERDICORP/file-lib.svg?branch=current)](https://travis-ci.com/ZERDICORP/file-lib)

### Minimum usage:
```cpp
zer::File file("text.txt");

/*
    Read.
*/
std::string sData = file.read().get();

/*
    Write.
*/
file.write("Hello, world!");
```

### Dependencies:
- [athm.h](https://github.com/ZERDICORP/athm-lib.git)
