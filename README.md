# zer::file ```diff - !DEPRECATED!```

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
