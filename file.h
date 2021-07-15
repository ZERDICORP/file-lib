// file.h

#include <fstream>
#include <sys/stat.h>
#include <sstream>
#include <streambuf>
#include <vector>
#include <iterator>
#include <windows.h>
#include <cmath>
#include <row.h>
#include <str.h>

#ifndef ZER__FILE_MODEL
	#define ZER__FILE_MODEL
	#define mWARNING(sMessage) (std::cerr << "[warning]: " << sMessage << ".." << std::endl)
		namespace zer
		{
			namespace file
			{
				struct Info
				{
					std::string sPath;
					std::string sFullName;
					std::string sName;
					std::string sFormat;

					int iLength;
				};

				struct Modifier
				{
					const static int standard = 0;
					const static int lines = 1;
					const static int binary = 2;
					const static int hidden = 3;
				};
			};

			class File
			{
				private:
					std::fstream _fs;

					bool _bDoesExists;
					inline bool _bHasModifier(std::initializer_list<int> modifiers, int iDesiredModifier);
					inline bool _doesExists(std::string sFilePath);

					int _iSliceSize = 0;
					int _iLength = 0;
					int _iSlicesLen = 0;

					std::string _sPath;
					std::string _sFullName;
					std::string _sName;
					std::string _sFormat;
					std::string _sData;

					zer::row<std::string> _rLines;

					inline void _setFilePath(std::string sFilePath);
					inline void _write(std::string sData);
					inline void _read();
					inline void _readLines();
					inline void _slice(int iSliceIndex);

				public:
					inline File() {}
					inline File(std::string sFilePath) {this -> open(sFilePath);}
					inline ~File() {if (this -> isOpen()) this -> _fs.close();}

					void close() {this -> _fs.close();}

					int linesLen() {return this -> _rLines.len();}
					int const& len() {return this -> _iLength;}
					int const& slicesLen() {return this -> _iSlicesLen;}

					bool doesExists() {return this -> _bDoesExists;}
					bool isOpen() {return this -> _fs.is_open();}
					bool doesExists(std::string sFilePath) {return this -> _doesExists(sFilePath);}

					inline void open(std::string sFilePath);
					inline void write(std::string sData, std::string sFilePath, std::initializer_list<int> modifiers = {file::Modifier::standard});
					inline void write(std::string sData, std::initializer_list<int> modifiers = {file::Modifier::standard});
					inline void read(std::string sFilePath, std::initializer_list<int> modifiers = {file::Modifier::standard});
					inline void read(std::initializer_list<int> modifiers = {file::Modifier::standard});
					inline void setSliceSize(int iSliceSize);
					inline void slice(int iSliceIndex, std::initializer_list<int> modifiers);

					std::string const& data() {return this -> _sData;}
					std::string const& line(int iIndex) {return this -> _rLines[iIndex];}

					file::Info info() {return file::Info{this -> _sPath, this -> _sFullName, this -> _sName, this -> _sFormat, this -> _iLength};}
			};
			#include "file.inl"
		};
#endif