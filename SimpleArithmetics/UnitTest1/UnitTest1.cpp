#include "pch.h"
#include "CppUnitTest.h"
#include "..\SimpleArithmetics\Operation.h"
//#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(plus11238)
		{
			Operation op("1+1238");
			string output = "1239";
			Assert::AreEqual(output, op.getOutput());

		}
	};
}
