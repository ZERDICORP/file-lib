#include <iostream>
#include <cxxtest/TestSuite.h>
#include <file.h>

using namespace zer;

class TestSuite : public CxxTest::TestSuite
{
	public:
		void test__info(void)
		{
			File file("./resources/oneline.txt");

			FileInfo info = file.info();

			TS_ASSERT(info.sPath == "./resources/oneline.txt");
			TS_ASSERT(info.sFullName == "oneline.txt");
			TS_ASSERT(info.sName == "oneline");
			TS_ASSERT(info.sFormat == "txt");
			TS_ASSERT(info.iSize == 13);
			TS_ASSERT(info.bExists == true);
		}

		void test__getSize(void)
		{
			TS_ASSERT(File::getSize("./resources/oneline.txt") == 13);
		}

		void test__doesExists(void)
		{
			TS_ASSERT(File::doesExists("./resources/oneline.txt") == true);
			TS_ASSERT(File::doesExists("./resources/text.txt") == false);
		}

		void test__readSlice(void)
		{
			TS_ASSERT(File("./resources/oneline.txt").readSlice(4, 4).get() == "o, w");
		}

		void test__readLines(void)
		{
			TS_ASSERT(File("./resources/multiline.txt").readLines().get() == std::vector<std::string>({"abc", "123", "!?&"}));
		}

		void test__write_read(void)
		{
			File file("./resources/empty.txt");

			file.write("Hello, world!");

			TS_ASSERT(file.read().get() == "Hello, world!");

			file.write("");

			TS_ASSERT(file.read().get() == "");
		}
};
