File::File(std::string sFilePath, std::initializer_list<FILE_MODE> modifiers)
{
	my._info.sPath = sFilePath;

	std::vector<std::string> pathParts = zer::athm::split(zer::athm::replace(my._info.sPath, "\\", "/"), "/");
	my._info.sFullName = pathParts[pathParts.size() - 1];

	std::vector<std::string> fileNameParts = zer::athm::split(my._info.sFullName, ".");
	
	my._info.sName = fileNameParts[0];
	my._info.sFormat = fileNameParts[1];

	my.setMode(modifiers);

	my._update();
}

void File::_open(std::ios_base::openmode mode)
{
	if (zer::athm::vectorHas(my._modifiers, FILE_MODE::BINARY))
		my._fs.open(my._info.sPath, mode | std::ios::binary);
	else
		my._fs.open(my._info.sPath, mode);
}

void File::_update()
{
	my._info.bExists = File::doesExists(my._info.sPath);
	my._info.iSize = File::getSize(my._info.sPath);
}

FileResult File::read()
{
	my._update();

	std::string sData;

	if (!my._info.bExists)
		return FileResult(sData, FILE_RESULT_CODE::NO_OPEN_FILE_FOUND);

	my._open(std::fstream::in);
	
	sData = std::string((std::istreambuf_iterator<char>(my._fs)), std::istreambuf_iterator<char>());
	
	my._fs.close();

	return FileResult(sData, FILE_RESULT_CODE::OK);
}

FileResult File::readLines()
{
	my._update();

	std::vector<std::string> lines;

	if (!my._info.bExists)
		return FileResult(lines, FILE_RESULT_CODE::NO_OPEN_FILE_FOUND);

	my._open(std::fstream::in);

	std::string sLine;
	while (std::getline(my._fs, sLine))
		lines.push_back(sLine);

	my._fs.close();

	return FileResult(lines, FILE_RESULT_CODE::OK);
}

FileResult File::readSlice(int iStartPosition, int iSliceSize)
{
	my._update();

	std::string sData;

	if (!my._info.bExists)
		return FileResult(sData, FILE_RESULT_CODE::NO_OPEN_FILE_FOUND);

	if (!(iStartPosition >= 0 && iStartPosition < my._info.iSize))
		return FileResult(sData, FILE_RESULT_CODE::SLICE_STARTING_POSITION_IS_OUT_OF_RANGE);

	if (iSliceSize <= 0)
		return FileResult(sData, FILE_RESULT_CODE::INCORRECT_SLICE_SIZE);

	my._open(std::fstream::in | std::ifstream::ate);

	int iEndPosition = iStartPosition + iSliceSize;
	if (iEndPosition > my._info.iSize)
		iEndPosition -= iEndPosition - my._info.iSize;

	iSliceSize = iEndPosition - iStartPosition;
	
	sData.resize(iSliceSize);

	my._fs.seekg(iStartPosition);
	my._fs.read(&sData[0], iSliceSize);
	my._fs.close();

	return FileResult(sData, FILE_RESULT_CODE::OK);
}

void File::write(std::string sData)
{
	my._open(std::fstream::out);
	my._fs << sData;
	my._fs.close();
	my._update();
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

void File::setMode(std::initializer_list<FILE_MODE> modifiers)
{
	for (FILE_MODE modifier : modifiers)
		my._modifiers.push_back(modifier);
}

bool File::doesExists(std::string sFilePath)
{
	struct stat buffer;
	return stat(sFilePath.c_str(), &buffer) == 0;
}