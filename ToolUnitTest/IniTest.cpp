#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Ini_UnitTest
{
	TEST_CLASS(IniTest)
	{
	public:
		TEST_METHOD(Test_GetKeyValue)
		{
			Ini IniReader("D:\\Test.ini");

			Double dValue;

			Assert::IsTrue(IniReader.GetKeyValue("�߳�", "����߳���", dValue));

			Int iTaskCount;

			Assert::IsTrue(IniReader.GetKeyValue("�߳�", "Task", iTaskCount));

			Assert::IsTrue(iTaskCount == 12);

			Bool bEnable;

			Assert::IsTrue(IniReader.GetKeyValue("�߳�", "�Ƿ������߳�", bEnable));

			Assert::IsTrue(bEnable == false);

			String strValue;

			Assert::IsTrue(IniReader.GetKeyValue("�߳�", "�����Լ�", strValue));

			Assert::IsTrue(strValue ==  "����ʲô");
		}

		TEST_METHOD(Test_SetKeyValue)
		{
			Ini IniReader("D:\\Test.ini");

			Double dValue = 9.67;

			Assert::IsTrue(IniReader.SetKeyValue("�߳�", "����߳���", dValue));

			Int iTaskCount = 12;

			Assert::IsTrue(IniReader.SetKeyValue("�߳�", "Task", iTaskCount));

			Bool bEnable = false;

			Assert::IsTrue(IniReader.SetKeyValue("�߳�", "�Ƿ������߳�", bEnable));

			String strValue = "����ʲô";

			Assert::IsTrue(IniReader.SetKeyValue("�߳�", "�����Լ�", strValue));
		}
	};
}
