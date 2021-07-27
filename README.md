# zer::File v1 (outdated)

### :exclamation: This is an outdated version :exclamation:
### :exclamation: See [default home branch](https://github.com/ZERDICORP/file-lib) to get current version :exclamation:
### :exclamation: Use this version only if it is used in your project :exclamation:

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
