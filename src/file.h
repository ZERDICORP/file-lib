#include <fstream>
#include <sys/stat.h>
#include <sstream>
#include <streambuf>
#include <iterator>
#include <athm.h>
#include <cmath>
#include <vector>
#include <windows.h>

#ifndef ZER__FILE_MODEL
	#define ZER__FILE_MODEL
	#define mWARNING(sMessage) (std::cerr << "[warning]: " << sMessage << ".." << std::endl)

	namespace zer
	{
		enum class FILE_MODE
		{
			STANDARD,
			BINARY,
		};

		struct FileInfo
		{
			bool bExists;

			int iLength;

			std::string sPath;
			std::string sFullName;
			std::string sName;
			std::string sFormat;
		};

		class File
		{
			private:
				private:
					File& my = *this;

					std::fstream _fs;

					FileInfo _info;

					bool _bWarnings = true;

					std::vector<FILE_MODE> _modifiers;

				public:
					inline File(std::string sFilePath, std::initializer_list<FILE_MODE> modifiers = {FILE_MODE::STANDARD});
					inline ~File() {if (my.isOpen()) my._fs.close();}

					inline const FileInfo& info() {return my._info;}

					inline std::string read();
					inline std::string readSlice(int iStartPosition, int iSliceSize);

					inline std::vector<std::string> readLines();

					inline void write(std::string sData);
					inline void makeHidden();
					inline void setMode(std::initializer_list<FILE_MODE> modifiers);
					inline void close() {my._fs.close();}
					inline void disableWarnings() {my._bWarnings = false;}

					inline bool isOpen() {return my._fs.is_open();}
					static inline bool doesExists(std::string sFilePath);
		};

		#include "file.inl"
	};
#endif
