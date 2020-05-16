#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Json_UnitTest
{		
	TEST_CLASS(JsonTest)
	{
	public:
		TEST_METHOD(Test_FromJsonFile)
		{
			String strErrorMsg;

			JsonDocument JsonDoc1 = JsonDocument::FromJsonFile(_T("D:\\System.json"), strErrorMsg);

			Boolean bRet1 = JsonDoc1.IsNull();

			Assert::IsTrue(bRet1 == false);
		}

		TEST_METHOD(Test_GetKeysTest)
		{
			String strErrorMsg;

			JsonDocument JsonDoc = JsonDocument::FromJsonFile(_T("D:\\System.json"), strErrorMsg);

			JsonDocument::KeyTable Table;
			if (!JsonDoc.GetKeys(Table))
			{
				Assert::Fail(String(_T("Failed to get all keys under this root key")).ToUnicodeData().c_str());
			}
		}

		TEST_METHOD(Test_GetKeys)
		{
			String strErrorMsg;

			JsonDocument JsonDoc = JsonDocument::FromJsonFile(_T("D:\\System1.json"), strErrorMsg);

			vector<String> ValueTable;

			JsonDocument JsonObject = JsonDoc.GetKeyValue(_T("App"));

			String strData = JsonObject.GetKeyValue(_T("�豸ID")).ToString();
		}

		TEST_METHOD(Test_FromJson)
		{
			String strJson = _T("{\"�豸ID\": \"SHENGYANG-13-VCS2000-006C4004JV002B6F1\", \
				\"��ַ\" : \"http://192.168.0.101:48769\",\
				\"local_ip\" : \"192.168.0.196\",\
				\"orgName\" : \"�㶫ʡ--������������Ĵ�ѧ�о�Ժ602\",\
				\"orgNo\" : \"132154625321\",\
				\"register_date_time\" : \"2019-10-31 16:13:21\",\
				\"register_finish_date_time\" : \"2019-10-31 16:13:30\",\
				\"systemName\" : \"SHENGYANG\",\
				\"wsdl_vpr_host\" : \"http://192.168.0.101:49090\"}");

			String strErrorMsg;

			JsonDocument JsonDoc = JsonDocument::FromJson(strJson,strErrorMsg);

			String strAddr = JsonDoc.GetKeyValue(_T("��ַ")).ToString();

			Assert::IsTrue(strAddr == _T("http://192.168.0.101:48769"));

			String strEquipmentID = JsonDoc.GetKeyValue(_T("�豸ID")).ToString();

			Assert::IsTrue(strEquipmentID == _T("SHENGYANG-13-VCS2000-006C4004JV002B6F1"));

			String strOrgName = JsonDoc.GetKeyValue(_T("orgName")).ToString();

			Assert::IsTrue(strOrgName == _T("�㶫ʡ--������������Ĵ�ѧ�о�Ժ602"));

			String strRegTime = JsonDoc.GetKeyValue(_T("register_date_time")).ToString();

			DateTime RegTime = DateTime::FromString(strRegTime);

			String strDateTime = RegTime.ToString();

			Assert::IsTrue(strRegTime == strDateTime);
		}

		TEST_METHOD(Test_SetKeyValue)
		{
			JsonDocument JsonObject;

			JsonObject.SetKeyValue(_T("�豸ID"), _T("1234586"));

			JsonObject.SetKeyValue(_T("Banana"), _T("�㽶"));

			JsonObject.SetKeyValue(_T("Person"), _T("Happy"));

			JsonObject.SetKeyValue(_T("Computers"), 3);

			JsonObject.SetKeyValue(_T("Result"), 5.62);

			JsonObject.SetKeyValue(_T("IsOpen"), false,true);

			JsonDocument JsonDoc;

			JsonDoc.SetKeyValue(_T("App"), JsonObject);

			JsonDoc.Flush(_T("D:\\System1.json"));
		}

		TEST_METHOD(Test_Append)
		{
			JsonDocument JsonObject;

			JsonObject.Append(_T("������"));

			JsonObject.Append(_T("�����"));

			JsonObject.Append(_T("�Ϻ���"));

			JsonObject.Append(_T("������"));

			JsonObject.Append(_T("����ʡ"));

			JsonObject.Append(_T("����׳��������"));

			JsonDocument JsonDoc;

			JsonDoc.SetKeyValue(_T("Province"), JsonObject);

			JsonDoc.Flush(_T("D:\\System2.json"));
		}

		TEST_METHOD(Test_GetKeyValue)
		{
			String strErrorMsg;

			JsonDocument JsonDoc = JsonDocument::FromJsonFile(_T("D:\\System2.json"),strErrorMsg);

			Assert::IsTrue(!JsonDoc.IsNull());

			JsonDocument JsonObject = JsonDoc.GetKeyValue(_T("Province"));
			
			Assert::IsTrue(!JsonObject.IsNull());

			vector<String> NameTable;

			String strProName=_T("");

			if (JsonObject.IsArray())
			{
				Int32 iArraySize = JsonObject.Size();

				for (Int32 iIndex = 0; iIndex < iArraySize;++iIndex)
				{
					String strProvinceName = JsonObject[iIndex].ToString();

					NameTable.push_back(strProvinceName);

					strProName = strProName+strProvinceName+_T("\r\n");
				}
			}

			Assert::IsTrue(!NameTable.empty());

			File FileHelper;

			if (!FileHelper.Open(_T("D:\\AA.json"),File::FileMode::CREATE,File::FileAccess::READWRITE))
			{
				Assert::Fail(String(_T("Failed to create a file")).ToUnicodeData().c_str());
			}

			FileHelper.Write((SByteArray)strProName.ToUTF8Data().c_str(),
				0, 
				static_cast<File::ArraySize>(strProName.ToUTF8Data().length()));

			FileHelper.Close();
		}

		TEST_METHOD(Test_ToJson)
		{
			JsonDocument JsonObject;

			JsonObject.Append(_T("������"));

			JsonObject.Append(_T("�����"));

			JsonObject.Append(_T("�Ϻ���"));

			JsonObject.Append(_T("������"));

			JsonObject.Append(_T("����ʡ"));

			JsonObject.Append(_T("����׳��������"));

			String strJson = JsonObject.ToJson();

			File FileHelper;

			if (!FileHelper.Open(_T("D:\\ToJson.json"), File::FileMode::CREATE, File::FileAccess::READWRITE))
			{
				Assert::Fail(String(_T("Failed to create a file")).ToUnicodeData().c_str());
			}

			FileHelper.Write((SByteArray)strJson.ToUTF8Data().c_str(),
				0,
				static_cast<File::ArraySize>(strJson.ToUTF8Data().length()));

			FileHelper.Close();
		}

		TEST_METHOD(Test_Parse)
		{
			String strErrorMsg;

			JsonDocument JsonDoc = JsonDocument::FromJsonFile(_T("D:\\System1.json"), strErrorMsg);

			Assert::IsTrue(!JsonDoc.IsNull());

			String strText1 = JsonDoc.GetKeyValue("App").GetKeyValue("Banana").ToString();

			String strText2 = JsonDoc.GetKeyValue("App").GetKeyValue("Person").ToString();

			String strText3 = JsonDoc.GetKeyValue("App").GetKeyValue("�豸ID").ToString();

			Int32 iRet1 = JsonDoc.GetKeyValue("App").GetKeyValue("Computers").ToInt();

			Real dRet1 = JsonDoc.GetKeyValue("App").GetKeyValue("Result").ToDouble();

			Boolean bRet1 = JsonDoc.GetKeyValue("App").GetKeyValue("IsOpen").ToBool();

			std::map<std::string, std::string> CurMap;

			JsonDoc.ToMap(CurMap);
		}
	};
}