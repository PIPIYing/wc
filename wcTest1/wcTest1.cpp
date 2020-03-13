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
			char path[N] = { "E:\\vs project\\wcTest\\" };
			char file[N] = { "file.c" };

			int c1 = countChar(path, file);
			int c2 = countWord(path, file);
			int c3 = countLine(path, file);
			int c4 = countElse(path, file);

			Assert::AreEqual(c1, 49);
			Assert::AreEqual(c2, 5);
			Assert::AreEqual(c3, 10);
			Assert::AreEqual(c4, 4);
		};

		TEST_METHOD(TestMethod2)
		{
			//�ݹ��ļ��Ĳ��Դ���
			char path[N] = { "E:\\vs project\\wcTest\\" };
			char mode[N] = { "*" };
			//������
			int n = 0, i;
			int tag = 0;

			int c5 = searchFile(path, mode, tag);
			Assert::AreEqual(c5, 7);
		};
	};
}
