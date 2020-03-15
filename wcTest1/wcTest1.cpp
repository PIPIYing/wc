#include "pch.h"
#include "CppUnitTest.h"
#include "../wc/wc.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace wcTest1
{
	TEST_CLASS(wcTest1)
	{
	public:
		TEST_METHOD(TestMethod1)
		{
			//ͳ���ַ����������������������������Ĳ��Դ���
			char path[N] = { "E:\\test\\" };
			char file[N] = { "file.c" };

			int c1 = countChar(path, file);
			int c2 = countWord(path, file);
			int c3 = countLine(path, file);
			int c4 = countElse(path, file);

			Assert::AreEqual(c1, 51);
			Assert::AreEqual(c2, 5);
			Assert::AreEqual(c3, 10);
			Assert::AreEqual(c4, 5);
		};

		TEST_METHOD(TestMethod2)
		{
			//�ݹ��ļ��Ĳ��Դ���
			char path[N] = { "E:\\vs project\\wcTest\\" };
			char mode[N] = { "*" };
			int tag = 0;

			int c5 = searchFile(path, mode, tag);
			//ͨ���ļ����е��ļ�����ȷ���ݹ麯���Ƿ���ȷ�ݹ�
			Assert::AreEqual(c5, 7);
		};

		TEST_METHOD(TestMethod3)
		{
			//���·���Ĳ��Դ���
			char path1[N] = { "E:\\test\\*.c" };
			char path2[N] = { "E:\\test" };
			char mode[N] = { 0 };

			int c6 = splitPath(path1,mode);
			int c7 = splitPath(path2, mode);

			Assert::AreEqual(c6, 1);
			Assert::AreEqual(c7, -1);
		};
	};
}
