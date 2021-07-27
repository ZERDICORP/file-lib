# zer::File v1 (outdated)

### :grey_exclamation: This is an outdated version.
### :grey_exclamation: See default branch to get [current version](https://github.com/ZERDICORP/file-lib).
### :grey_exclamation: Use this version only if it is used in your project.

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
