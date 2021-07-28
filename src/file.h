#include <fstream>
#include "athm.h"

#ifndef ZER__FILE_MODEL
	#define ZER__FILE_MODEL

	namespace zer
	{
		enum class FILE_RESULT_CODE
		{
			OK,
			NO_OPEN_FILE_FOUND,
			SLICE_STARTING_INDEX_IS_OUT_OF_RANGE,
			INCORRECT_SLICE_SIZE
		};

		enum class FILE_MODE
		{
			STANDARD,
			BINARY
		};

		std::map<FILE_RESULT_CODE, std::string> fileResultMessages({
			{FILE_RESULT_CODE::OK, "all is ok"},
			{FILE_RESULT_CODE::NO_OPEN_FILE_FOUND, "no open file found"},
			{FILE_RESULT_CODE::SLICE_STARTING_INDEX_IS_OUT_OF_RANGE, "slice starting index is out of range"},
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

		class FileResult
		{
			private:
				FILE_RESULT_CODE _resultCode;

			public:
				inline FileResult(FILE_RESULT_CODE resultCode) : _resultCode(resultCode) {}

				inline bool ok() {return this -> _resultCode == FILE_RESULT_CODE::OK;}
		};

		class FileResultStandard : public FileResult
		{
			private:
				std::string _sData;

			public:
				inline FileResultStandard(std::string sData, FILE_RESULT_CODE resultCode = FILE_RESULT_CODE::OK) : _sData(sData), FileResult::FileResult(resultCode) {}

				inline std::string& get() {return this -> _sData;}
		};

		class FileResultLines : public FileResult
		{
			private:
				std::vector<std::string> _lines;

			public:
				inline FileResultLines(std::vector<std::string> lines, FILE_RESULT_CODE resultCode = FILE_RESULT_CODE::OK) : _lines(lines), FileResult::FileResult(resultCode) {}

				inline std::vector<std::string>& get() {return this -> _lines;}
		};

		class File
		{
			private:
				File& my = *this;

				std::fstream _fs;

				FileInfo _info;

				std::vector<FILE_MODE> _modifiers;

				std::string _sLastErrorMessage;

				inline void _open(std::ios_base::openmode mode);
				inline void _update();

			public:
				inline File(std::string sFilePath, std::initializer_list<FILE_MODE> modifiers = {FILE_MODE::STANDARD});

				inline const FileInfo& info() {return my._info;} 

				inline FileResultStandard read();
				inline FileResultStandard readSlice(int iStartIndex, int iSliceSize);

				inline FileResultLines readLines();

				inline void write(std::string sData);
				inline void setMode(std::initializer_list<FILE_MODE> modifiers);
				#ifdef _WIN32
					inline void toggleVisibility();
				#endif

				inline bool ok() {return my._info.bExists;}
				static inline bool doesExists(std::string sFilePath);

				inline std::string lastErrorMessage() {return this -> _sLastErrorMessage;}

				static inline int getSize(std::string sFilePath) {return std::ifstream(sFilePath, std::ifstream::ate).tellg();}
		};

		#include "file.inl"
	};
#endif
