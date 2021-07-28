
# zer::File v2 (current)

[![Build Status](https://travis-ci.com/ZERDICORP/file-lib.svg?branch=current)](https://travis-ci.com/ZERDICORP/file-lib)

## Minimum usage :older_man:
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

## Examples  :information_desk_person:

### Read from file:
___text.txt___
```
Hello, world!
Cellar door!
```
___main.cpp___
```cpp
#include <iostream>
#include "file.h"

int main()
{
	zer::File file("./text.txt");

	/*
		Reading the contents of a file.
	*/
	auto readResult = file.read();
	if (!readResult.ok())
	{
		std::cout << file.lastErrorMessage() << std::endl;
		return 1;
	}

	std::cout << readResult.get() << "\n\n";

	/*
		Reading a slice of file content.
		7 - starting index,
		5 - slice size
	*/
	auto readSliceResult = file.readSlice(7, 6);
	if (!readSliceResult.ok())
	{
		std::cout << file.lastErrorMessage() << std::endl;
		return 1;
	}

	std::cout << readSliceResult.get() << "\n\n";

	/*
		Reading the contents of a file line by line.
	*/
	auto readLinesResult = file.readLines();
	if (!readLinesResult.ok())
	{
		std::cout << file.lastErrorMessage() << std::endl;
		return 1;
	}

	std::vector<std::string> lines = readLinesResult.get();
	for (int i = 0; i < lines.size(); ++i)
		std::cout << "line [" << i + 1 << "]: " << lines[i] << std::endl;

	return 0;
}
```
__Output__
```
Hello, world!
Cellar door!

world!

line [1]: Hello, world!
line [2]: Cellar door!
```
### Write to file:
___text.txt___
```
Hello, world!
Cellar door!
```
___main.cpp___
```cpp
#include <iostream>
#include "file.h"

int main()
{
	zer::File file("./text.txt");

	std::string sFileContents = file.read().get();
	std::cout << sFileContents << "\n\n";

	file.write(sFileContents + "\nBeauty and the Beast!");

	std::cout << file.read().get() << std::endl;

	return 0;
}
```
__Output__
```
Hello, world!
Cellar door!

Hello, world!
Cellar door!
Beauty and the Beast!
```
### Get file information:
___text.txt___
```
Hello, world!
Cellar door!
Beauty and the Beast!
```
___main.cpp___
```cpp
#include <iostream>
#include "file.h"

int main()
{
	zer::File file("./text.txt");

	zer::FileInfo info = file.info();

	std::cout << "File \"" << info.sPath << "\" " << (info.bExists ? "does exists" : "does not exist") << std::endl;
	std::cout << "File size: " << info.iSize << std::endl;
	std::cout << "File path: " << info.sPath << std::endl;
	std::cout << "Full filename: " << info.sFullName << std::endl;
	std::cout << "File name: " << info.sName << std::endl;
	std::cout << "File format: " << info.sFormat << std::endl;

	return 0;
}
```
__Output__
```
File "./text.txt" does exists
File size: 50
File path: ./text.txt
Full filename: text.txt
File name: text
File format: txt
```
### Reading and writing binary data:
___image.png___

<img src="https://zerdicorp.ru/db/images/image.png" alt="image" width="100"/>

___main.cpp___
```cpp
#include <iostream>
#include "file.h"

int main()
{
	zer::File file("./image.png", {zer::FILE_MODE::BINARY});
	zer::File file2("./image2.png", {zer::FILE_MODE::BINARY});

	file2.write(file.read().get());

	return 0;
}
```
__image2.png__

<img src="https://zerdicorp.ru/db/images/image.png" alt="image" width="100"/>

## Dependencies  :couple_with_heart:
- [athm-lib](https://github.com/ZERDICORP/athm-lib/tree/v1) (v1)
