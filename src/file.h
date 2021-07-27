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

	namespace zer
	{
		enum class FILE_RESULT_CODE
		{
			OK,
			NO_OPEN_FILE_FOUND,
			SLICE_STARTING_POSITION_IS_OUT_OF_RANGE,
			INCORRECT_SLICE_SIZE
		};

		enum class FILE_MODE
		{
			STANDARD,
			BINARY,
		};

		std::map<FILE_RESULT_CODE, std::string> resultMessages({
			{FILE_RESULT_CODE::OK, "all is ok"},
			{FILE_RESULT_CODE::NO_OPEN_FILE_FOUND, "no open file found"},
			{FILE_RESULT_CODE::SLICE_STARTING_POSITION_IS_OUT_OF_RANGE, "slice starting position is out of range"},
			{FILE_RESULT_CODE::INCORRECT_SLICE_SIZE, "incorrect slice size"},
		});

		struct FileInfo
		{
			bool bExists;

			int iSize;

			std::string sPath;
			std::string sFullName;
			std::string sName;
			std::string sFormat;
		};

		struct FileResult
		{
			private:
				FILE_RESULT_CODE _resultCode;

				std::string _sMessage;
				std::string _sData;

				std::vector<std::string> _lines;

			public:
				FileResult() {}
				FileResult(std::string sData, FILE_RESULT_CODE resultCode = FILE_RESULT_CODE::OK) : _sData(sData), _resultCode(resultCode), _sMessage(resultMessages[resultCode]) {}
				FileResult(std::vector<std::string> lines, FILE_RESULT_CODE resultCode = FILE_RESULT_CODE::OK) : _lines(lines), _resultCode(resultCode), _sMessage(resultMessages[resultCode]) {}

				const FILE_RESULT_CODE& code() {return this -> _resultCode;}
				
				const std::string& message() {return this -> _sMessage;}
				std::string& data() {return this -> _sData;}

				std::vector<std::string>& lines() {return this -> _lines;}
		};

		class File
		{
			private:
				File& my = *this;

				std::fstream _fs;

				FileInfo _info;

				std::vector<FILE_MODE> _modifiers;

				inline void _open(std::ios_base::openmode mode);
				inline void _update();

			public:
				inline File(std::string sFilePath, std::initializer_list<FILE_MODE> modifiers = {FILE_MODE::STANDARD});
				inline ~File() {if (my.isOpen()) my._fs.close();}

				inline const FileInfo& info() {return my._info;}

				FileResult read();
				FileResult readSlice(int iStartPosition, int iSliceSize);

				FileResult readLines();

				inline void write(std::string sData);
				inline void toggleVisibility();
				inline void setMode(std::initializer_list<FILE_MODE> modifiers);

				inline bool isOpen() {return my._fs.is_open();}

				static inline bool doesExists(std::string sFilePath);

				static inline int getSize(std::string sFilePath) {return std::ifstream(sFilePath, std::ifstream::ate).tellg();}
		};

		#include "file.inl"
	};
#endif