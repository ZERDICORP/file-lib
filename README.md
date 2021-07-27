# zer::file v1

#### ![](https://via.placeholder.com/15/FF0800/000000?text=+) This is an outdated version. See branch v2.

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
