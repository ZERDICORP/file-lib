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
	
	if (!my._info.bExists && my._bWarnings)
		mWARNING("file \"" << my._info.sPath << "\" does not exists");
	else
		my._info.iLength = std::ifstream(my._info.sPath, std::ifstream::ate).tellg();
}

void File::setMode(std::initializer_list<FILE_MODE> modifiers)
{
	for (FILE_MODE modifier : modifiers)
		my._modifiers.push_back(modifier);
}

void File::makeHidden()
{
	LPCSTR fileLPCSTR = my._info.sPath.c_str();
	DWORD dw = GetFileAttributes(fileLPCSTR);
	if ((dw & FILE_ATTRIBUTE_HIDDEN) == 0)
		SetFileAttributes(fileLPCSTR, dw | FILE_ATTRIBUTE_HIDDEN);
}

void File::write(std::string sData)
{
	if (zer::athm::vectorHas(my._modifiers, FILE_MODE::BINARY))
		my._fs.open(my._info.sPath, std::fstream::out | std::ios::binary);
	else
		my._fs.open(my._info.sPath, std::fstream::out);

	my._fs << sData;
}

std::string File::read()
{
	if (my._info.bExists)
	{
		if (zer::athm::vectorHas(my._modifiers, FILE_MODE::BINARY))
			my._fs.open(my._info.sPath, std::fstream::in | std::ios::binary);
		else
			my._fs.open(my._info.sPath, std::fstream::in);

		return std::string((std::istreambuf_iterator<char>(my._fs)), std::istreambuf_iterator<char>());
	}
	else
		mWARNING("no open file found");

	return "";
}

std::vector<std::string> File::readLines()
{
	std::vector<std::string> lines;

	if (my._info.bExists)
	{
		std::string sLine;
		while (std::getline(my._fs, sLine))
			lines.push_back(sLine);
	}
	else
		mWARNING("no open file found");

	return lines;
}

std::string File::readSlice(int iStartPosition, int iSliceSize)
{
	std::string sData;

	if (my._info.bExists)
	{
		if (zer::athm::vectorHas(my._modifiers, FILE_MODE::BINARY))
			my._fs.open(my._info.sPath, std::ifstream::ate | std::fstream::in | std::ios::binary);
		else
			my._fs.open(my._info.sPath, std::ifstream::ate | std::fstream::in);
		
		if (iStartPosition >= 0 && iStartPosition + iSliceSize < my._info.iLength)
		{
			int iEndPosition = iStartPosition + iSliceSize;

			if (iEndPosition > my._info.iLength)
				iEndPosition -= iEndPosition - my._info.iLength;

			int iTempSliceSize = iEndPosition - iStartPosition;
			
			sData.resize(iTempSliceSize);

			my._fs.seekg(iStartPosition);
			my._fs.read(&sData[0], iTempSliceSize);
		}
		else
			mWARNING("index out of range");
	}
	else
		mWARNING("no open file found");

	return sData;
}

bool File::doesExists(std::string sFilePath)
{
	struct stat buffer;
	return stat(sFilePath.c_str(), &buffer) == 0;
}