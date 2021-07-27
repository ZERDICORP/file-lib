File::File(std::string sFilePath, std::initializer_list<FILE_MODE> modifiers)
{
	my._info.sPath = sFilePath;

	std::vector<std::string> pathParts = zer::athm::split(zer::athm::replace(my._info.sPath, "\\", "/"), "/");
	my._info.sFullName = pathParts[pathParts.size() - 1];

	std::vector<std::string> fileNameParts = zer::athm::split(my._info.sFullName, ".");
	
	my._info.sName = fileNameParts[0];
	my._info.sFormat = fileNameParts[1];

	my.setMode(modifiers);

	my._info.bExists = File::doesExists(sFilePath);
	
	if (my._info.bExists)
		my._info.iLength = std::ifstream(my._info.sPath, std::ifstream::ate).tellg();
}

void File::setMode(std::initializer_list<FILE_MODE> modifiers)
{
	for (FILE_MODE modifier : modifiers)
		my._modifiers.push_back(modifier);
}

void File::toggleVisibility()
{
	LPCSTR fileLPCSTR = my._info.sPath.c_str();
	DWORD dw = GetFileAttributes(fileLPCSTR);
	if ((dw & FILE_ATTRIBUTE_HIDDEN) == 0)
		SetFileAttributes(fileLPCSTR, dw | FILE_ATTRIBUTE_HIDDEN);
	else
		SetFileAttributes(fileLPCSTR, dw & ~FILE_ATTRIBUTE_HIDDEN);
}

void File::_open(std::ios_base::openmode mode)
{
	if (zer::athm::vectorHas(my._modifiers, FILE_MODE::BINARY))
		my._fs.open(my._info.sPath, mode | std::ios::binary);
	else
		my._fs.open(my._info.sPath, mode);
}

void File::write(std::string sData)
{
	my._open(std::fstream::out);
	
	my._fs << sData;
	
	if (!my._info.bExists)
	{
		my._info.bExists = true;
		my._info.iLength = std::ifstream(my._info.sPath, std::ifstream::ate).tellg();
	}

	my._fs.close();
}

FileResult File::read()
{
	std::string sData;

	if (!my._info.bExists)
		return FileResult(sData, FILE_RESULT_CODE::NO_OPEN_FILE_FOUND, "no open file found");

	my._open(std::fstream::in);
	
	sData = std::string((std::istreambuf_iterator<char>(my._fs)), std::istreambuf_iterator<char>());
	
	my._fs.close();

	return FileResult(sData);
}

FileResult File::readLines()
{
	std::vector<std::string> lines;

	if (!my._info.bExists)
		return FileResult(lines, FILE_RESULT_CODE::NO_OPEN_FILE_FOUND, "no open file found");

	my._open(std::fstream::in);

	std::string sLine;
	while (std::getline(my._fs, sLine))
		lines.push_back(sLine);

	my._fs.close();

	return FileResult(lines);
}

FileResult File::readSlice(int iStartPosition, int iSliceSize)
{
	std::string sData;

	if (!my._info.bExists)
		return FileResult(sData, FILE_RESULT_CODE::NO_OPEN_FILE_FOUND, "no open file found");

	if (!(iStartPosition >= 0 && iStartPosition < my._info.iLength))
		return FileResult(sData, FILE_RESULT_CODE::SLICE_START_POSITION_OUT_OF_RANGE, "slice start position out of range");

	if (iSliceSize <= 0)
		return FileResult(sData, FILE_RESULT_CODE::INCORRECT_SLICE_SIZE, "incorrect slice size, should be > 0");

	my._open(std::fstream::in | std::ifstream::ate);

	int iEndPosition = iStartPosition + iSliceSize;

	if (iEndPosition > my._info.iLength)
		iEndPosition -= iEndPosition - my._info.iLength;

	int iTempSliceSize = iEndPosition - iStartPosition;
	
	sData.resize(iTempSliceSize);

	my._fs.seekg(iStartPosition);
	my._fs.read(&sData[0], iTempSliceSize);

	my._fs.close();

	return FileResult(sData);
}

bool File::doesExists(std::string sFilePath)
{
	struct stat buffer;
	return stat(sFilePath.c_str(), &buffer) == 0;
}