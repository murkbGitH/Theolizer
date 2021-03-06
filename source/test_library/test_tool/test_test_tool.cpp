﻿//############################################################################
//      test_tool.*のテスト
/*
    © 2016 Theoride Technology (http://theolizer.com/) All Rights Reserved.
    "Theolizer" is a registered trademark of Theoride Technology.

    "Theolizer" License
        In the case where you are in possession of a valid “Theolizer” License,
        you may use this file in accordance with the terms and conditions of 
        the use license determined by Theoride Technology.

    General Public License Version 3 ("GPLv3")
        You may use this file in accordance with the terms and conditions of 
        GPLv3 published by Free Software Foundation.
        Please confirm the contents of GPLv3 at https://www.gnu.org/licenses/gpl.txt .
        A copy of GPLv3 is also saved in a LICENSE.TXT file.

    商用ライセンス
        あなたが有効なTheolizer商用ライセンスを保持している場合、
        セオライド テクノロジーの定める使用許諾書の条件に従って、
        このファイルを取り扱うことができます。

    General Public License Version 3(以下GPLv3)
        Free Software Foundationが公表するGPLv3の使用条件に従って、
        あなたはこのファイルを取り扱うことができます。
        GPLv3の内容を https://www.gnu.org/licenses/gpl.txt にて確認して下さい。
        またGPLv3のコピーをLICENSE.TXTファイルにおいてます。
*/
//############################################################################

#define THEOLIZER_INTERNAL_EXCLUDE_VERSION_H

// ***************************************************************************
//          警告抑止
// ***************************************************************************

#if defined(_MSC_VER)
    #pragma warning(disable:4100 4127 4702)
#endif

// ***************************************************************************
//      通常のインクルード
// ***************************************************************************

#include <exception>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <locale>
using namespace std;

#include <theolizer/test_tool.h>

//############################################################################
//      ユーティリティ
//############################################################################

// ***************************************************************************
//      出力チェックし、正しく<<<FAIL>>>が出ていたら、
//          Failカウンタをデクリメントし、かつ、出力を(((FAIL)))へ置き換える。
//      そうでないなら、
//          Failカウンタをインクリメントし、かつ、<<<FAIL>>>を出力する。
// ***************************************************************************

void judgeAndReplase(ostream& iOut, bool iFailIsPass, string iResult, bool iAnd=true)
{
    bool aIsPass=true;
    size_t  aPos = iResult.find(THEOLIZER_INTERNAL_FAIL);
    if (aPos != string::npos)
    {
        // <<<FAIL>>文字列有り
        theolizer::internal::gFailCount--;
        aIsPass = iFailIsPass & iAnd;
        iResult.replace(aPos, string(THEOLIZER_INTERNAL_FAIL).length(), "(((FAIL)))");
    }
    else
    {
        // <<<FAIL>>文字列無し
        aIsPass = !iFailIsPass & iAnd;
    }
    if (!aIsPass || theolizer::DisplayPass::on())
    {
        theolizer::internal::gFailCount++;
        iOut << "\n" << ((aIsPass)?THEOLIZER_INTERNAL_PASS:THEOLIZER_INTERNAL_FAIL)
             << iResult;
    }
}

//############################################################################
//      テストのメイン関数
//############################################################################

int main(int argc, char** argv)
{
//  theolizer::DisplayPass aDisplayPass;

//  cout << "PATH=" << theolizer::getenv("PATH") << "\n";
//  cout << "THEOLIZER_LOCALE_DIR=" << theolizer::getenv("THEOLIZER_LOCALE_DIR") << "\n";

// ***************************************************************************
//      カウンタのテスト準備
// ***************************************************************************

    unsigned    aTestCounter=0;

    {   // gTotal, gFailCountは比較後にインクリメントしている
        THEOLIZER_EQUAL(theolizer::internal::gTotal, aTestCounter);
        ++aTestCounter;
        THEOLIZER_EQUAL(theolizer::internal::gFailCount, 0);
        ++aTestCounter;
    }

// ***************************************************************************
//      環境変数ツールのテスト
// ***************************************************************************

    {
        string aResult;

        theolizer::internal::putenv("THEOLIZER_TEST=Environment_Test");
        aResult = theolizer::internal::getenv("THEOLIZER_TEST");
        ++aTestCounter;
        THEOLIZER_EQUAL(aResult, "Environment_Test");

        theolizer::internal::putenv("THEOLIZER_TEST=");
        aResult = theolizer::internal::getenv("THEOLIZER_TEST");
        ++aTestCounter;
        THEOLIZER_EQUAL(aResult, "");
    }

// ***************************************************************************
//      DisplayPassとマクロのテスト
// ***************************************************************************

//----------------------------------------------------------------------------
//      各チェック・マクロのテスト準備
//----------------------------------------------------------------------------

    ostream& out = theolizer::internal::getOStream();
    stringstream    ss;

//----------------------------------------------------------------------------
//      DisplayPass
//----------------------------------------------------------------------------

//      ---<<< DisplayPass::on()がtrue時のテスト >>>---

    {
        // DisplayPass::on()をtureへ
        theolizer::DisplayPass aDisplayPass;

        // DisplayPassのデストラクトで回復することをチェック
        {
            theolizer::DisplayPass aDisplayPass2;

            // {}の中でtheolizer::DisplayPass::on()がtrueであることをチェック
            ++aTestCounter;
            THEOLIZER_CHECK(theolizer::DisplayPass::on(), theolizer::DisplayPass::on());
        }
        // {}を抜けると、theolizer::DisplayPass::on()が{}直前(true)に戻ることをチェック
        ++aTestCounter;
        THEOLIZER_EQUAL(theolizer::DisplayPass::on(), true);

        theolizer::internal::setOStream(ss);                // テスタのテスト
        ss.str("");                                         // Clear ss
        ++aTestCounter;
        THEOLIZER_CHECK(true, true);                        // <<<PASS>>が出力されること
                                                            // を以下でチェックする

        theolizer::internal::setOStream(out);               // テスト実施
        ++aTestCounter;
        THEOLIZER_CHECK((ss.str().find(THEOLIZER_INTERNAL_PASS) != string::npos), ss.str());
    }

//      ---<<< DisplayPass::on()がfalse時のテスト >>>---

    {
        theolizer::internal::setOStream(out);               // テスト実施

        // DisplayPassのデストラクトで回復することをチェック
        {
            theolizer::DisplayPass aDisplayPass;

            // {}の中でDisplayPass::on()がtrueであることをチェック
            ++aTestCounter;
            THEOLIZER_EQUAL(theolizer::DisplayPass::on(), true);
        }
        // {}を抜けると、DisplayPass::on()が{}直前(false)に戻ることをチェック
        ++aTestCounter;
        THEOLIZER_EQUAL(theolizer::DisplayPass::on(), false);

        theolizer::internal::setOStream(ss);                // テスタのテスト
        ss.str("");                                         // Clear ss
        ++aTestCounter;
        THEOLIZER_EQUAL(true, true);                        // 何も出力されないこと
                                                            // を以下でチェックする

        theolizer::internal::setOStream(out);               // テスト実施
        ++aTestCounter;
        THEOLIZER_EQUAL(ss.str().length(), 0);
    }

//----------------------------------------------------------------------------
//      THEOLIZER_EQUAL()
//----------------------------------------------------------------------------

    theolizer::internal::setOStream(ss);                    // テスタのテスト
    {
//      ---<<< string >>>---

        const string result_string = "Test";

        // Pass
        ss.str("");                                 // Clear ss
        ++aTestCounter;
        THEOLIZER_EQUAL(result_string, "Test");
        judgeAndReplase(out, false, ss.str());

        // Fail
        ss.str("");                                 // Clear ss
        ++aTestCounter;
        THEOLIZER_EQUAL(result_string, "Test-Error");
        judgeAndReplase(out, true, ss.str());

//      ---<<< int >>>---

        int     result_int = 123;

        // Pass
        ss.str("");                                 // Clear ss
        ++aTestCounter;
        THEOLIZER_EQUAL(result_int, 123);
        judgeAndReplase(out, false, ss.str());

        // Fail
        ss.str("");                                 // Clear ss
        ++aTestCounter;
        THEOLIZER_EQUAL(result_int, 456);
        judgeAndReplase(out, true, ss.str());

//      ---<<< 3つ以上の要素表示 >>>---

        int     result_int1 = 789;

        // Fail
        ss.str("");                                 // Clear ss
        ++aTestCounter;
        THEOLIZER_EQUAL(result_int, 456, result_int1);  int line=__LINE__;
        judgeAndReplase(out, true, ss.str());

        std::string test=ss.str();
        ss.str("");
        ss  << "\n<<<FAIL>>>\n"
            << "test_test_tool.cpp(" << line << ")\n"
            << "result_int : " << result_int << "\n"
            << "456 : 456\n"
            << "result_int1 : " << result_int1 << "\n";
        std::string expected=ss.str();

        // Pass
        ss.str("");
        ++aTestCounter;
        THEOLIZER_EQUAL(test, expected);
        judgeAndReplase(out, false, ss.str());
    }

//----------------------------------------------------------------------------
//      THEOLIZER_CHECK()
//----------------------------------------------------------------------------

    {
//      ---<<< string >>>---

        const string result_string = "Test";

        // Pass
        ss.str("");                                 // Clear ss
        ++aTestCounter;
        THEOLIZER_CHECK(result_string == "Test", result_string);
        judgeAndReplase(out, false, ss.str());

        // Fail
        ss.str("");                                 // Clear ss
        ++aTestCounter;
        THEOLIZER_CHECK(result_string == "Test-Error", result_string);
        judgeAndReplase(out, true, ss.str());

//      ---<<< int >>>---

        int     result_int = 123;

        // Pass
        ss.str("");                                 // Clear ss
        ++aTestCounter;
        THEOLIZER_CHECK(result_int == 123, result_int);
        judgeAndReplase(out, false, ss.str());

        // Fail
        ss.str("");                                 // Clear ss
        ++aTestCounter;
        THEOLIZER_CHECK(result_int == 456, result_int);
        judgeAndReplase(out, true, ss.str());

//      ---<<< double >>>---

        double  result_double = 123.456;

        // Pass
        ss.str("");                                 // Clear ss
        ++aTestCounter;
        THEOLIZER_CHECK(abs(result_double-123.456)<0.001, result_double);
        judgeAndReplase(out, false, ss.str());

        // Fail
        ss.str("");                                 // Clear ss
        ++aTestCounter;
        THEOLIZER_CHECK(abs(result_double-456)<0.001, result_double);
        judgeAndReplase(out, true, ss.str());
    }

//----------------------------------------------------------------------------
//      THEOLIZER_REQUIRE()
//----------------------------------------------------------------------------

    {
//      ---<<< string >>>---

        const string result_string = "Test";

        // Pass
        bool    exception=false;
        ss.str("");                                 // Clear ss
        try
        {
            ++aTestCounter;
            THEOLIZER_REQUIRE(result_string == "Test", result_string);
        }
        catch(std::runtime_error& e)
        {
            ++aTestCounter;
            THEOLIZER_EQUAL(std::string(e.what()), "Test aborted.");
            exception=true;
        }
        judgeAndReplase(out, false, ss.str(), exception == false);

        // Fail
        exception=false;
        ss.str("");                                 // Clear ss
        try
        {
            ++aTestCounter;
            THEOLIZER_REQUIRE(result_string == "Test-Error", result_string);
        }
        catch(std::runtime_error& e)
        {
            ++aTestCounter;
            THEOLIZER_EQUAL(std::string(e.what()), "Test aborted.");
            exception=true;
        }
        judgeAndReplase(out, true, ss.str(), exception == true);
    }

//----------------------------------------------------------------------------
//      THEOLIZER_CHECK_EXCEPTION()
//----------------------------------------------------------------------------

    {
        // Pass
        ss.str("");                                 // Clear ss
        ++aTestCounter;
        THEOLIZER_CHECK_EXCEPTION(throw 1; , int);
        judgeAndReplase(out, false, ss.str());

        // Fail(no-exception)
        ss.str("");                                 // Clear ss
        ++aTestCounter;
        THEOLIZER_CHECK_EXCEPTION(;, int);
        judgeAndReplase(out, true, ss.str());
    }

//----------------------------------------------------------------------------
//      THEOLIZER_REQUIRE_EXCEPTION()
//----------------------------------------------------------------------------

    {
        bool    exception=false;

        // Pass
        ss.str("");                                 // Clear ss
        try
        {
            ++aTestCounter;
            THEOLIZER_REQUIRE_EXCEPTION(throw 1; , int);
        }
        catch(std::runtime_error& e)
        {
            ++aTestCounter;
            THEOLIZER_EQUAL(std::string(e.what()), "Test aborted.");
            exception=true;
        }
        judgeAndReplase(out, false, ss.str(), exception == false);

        // Fail(no-exception)
        exception=false;
        ss.str("");                                 // Clear ss
        try
        {
            ++aTestCounter;
            THEOLIZER_REQUIRE_EXCEPTION(;, int);
        }
        catch(std::runtime_error& e)
        {
            ++aTestCounter;
            THEOLIZER_EQUAL(std::string(e.what()), "Test aborted.");
            exception=true;
        }
        judgeAndReplase(out, true, ss.str(), exception == true);
    }

//----------------------------------------------------------------------------
//      THEOLIZER_CHECK_EXCEPTION2()
//----------------------------------------------------------------------------

    {
        // Pass
        ss.str("");                                 // Clear ss
        ++aTestCounter;
        THEOLIZER_CHECK_EXCEPTION2(
            throw 1,                                // dStatements
            int e,                                  // dException
            e == 1,                                 // dJudge
            e);                                     // dResult
        judgeAndReplase(out, false, ss.str());

        // Fail(no-exception)
        ss.str("");                                 // Clear ss
        ++aTestCounter;
        THEOLIZER_CHECK_EXCEPTION2(
            ;,                                      // dStatements
            int e,                                  // dException
            e == 1,                                 // dJudge
            e);                                     // dResult
        judgeAndReplase(out, true, ss.str());

        // Fail(unmatch result)
        ss.str("");                                 // Clear ss
        ++aTestCounter;
        THEOLIZER_CHECK_EXCEPTION2(
            THEOLIZER_INTERNAL_ERROR("Test"),       // dStatements
            theolizer::ErrorInfo& e,                // dException
            e.getMessage() == "Test-Error",         // dJudge
            e.getMessage());                        // dResult
        judgeAndReplase(out, true, ss.str());
    }

//----------------------------------------------------------------------------
//      THEOLIZER_REQUIRE_EXCEPTION2()
//----------------------------------------------------------------------------

    {
        bool    exception=false;

        // Pass
        ss.str("");                                 // Clear ss
        try
        {
            ++aTestCounter;
            THEOLIZER_REQUIRE_EXCEPTION2(
                throw 1,                            // dStatements
                int e,                              // dException
                e == 1,                             // dJudge
                e);                                 // dResult
        }
        catch(std::runtime_error& e)
        {
            ++aTestCounter;
            THEOLIZER_EQUAL(std::string(e.what()), "Test aborted.");
            exception=true;
        }
        judgeAndReplase(out, false, ss.str(), exception == false);

        // Fail(no-exception)
        exception=false;
        ss.str("");                                 // Clear ss
        try
        {
            ++aTestCounter;
            THEOLIZER_REQUIRE_EXCEPTION2(
                ;,                                  // dStatements
                int e,                              // dException
                e == 1,                             // dJudge
                e);                                 // dResult
        }
        catch(std::runtime_error& e)
        {
            ++aTestCounter;
            THEOLIZER_EQUAL(std::string(e.what()), "Test aborted.");
            exception=true;
        }
        judgeAndReplase(out, true, ss.str(), exception == true);

        // Fail(unmatch result)
        exception=false;
        ss.str("");                                 // Clear ss
        try
        {
            ++aTestCounter;
            THEOLIZER_REQUIRE_EXCEPTION2(
                THEOLIZER_INTERNAL_ERROR("Test"),   // dStatements
                theolizer::ErrorInfo& e,            // dException
                e.getMessage() == "Test-Error",     // dJudge
                e.getMessage());                    // dResult
        }
        catch(std::runtime_error& e)
        {
            ++aTestCounter;
            THEOLIZER_EQUAL(std::string(e.what()), "Test aborted.");
            exception=true;
        }
        judgeAndReplase(out, true, ss.str(), exception == true);
    }

//----------------------------------------------------------------------------
//      テストの後始末
//----------------------------------------------------------------------------

    theolizer::internal::setOStream(out);

// ***************************************************************************
//      ファイル操作のテスト
// ***************************************************************************

    // フォルダを生成出来ない時、例外が投げられることを確認
    {
        ++aTestCounter;
        THEOLIZER_CHECK_EXCEPTION(
            theolizer::PrepareDir AutoDelete("/::", true); ,    // dStatements
            std::runtime_error&);                               // dException
    }

    string aDirForTest = "./TheolizerTestFolder/";
    bool result;

    // PrepareDir, isExist, remove
    {
        // aDirForTestがもしあったら削除しておく
        {
            theolizer::PrepareDir AutoDelete(aDirForTest);
            std::vector<string> aFileList=theolizer::getFileList(aDirForTest);
            for (std::size_t i=0; i < aFileList.size(); ++i)
            {
                theolizer::setWritePermission(aDirForTest+aFileList[i], true);
            }
        }

        {
            // aDirForTest生成(終了時削除しない)
            theolizer::PrepareDir AutoDelete(aDirForTest, true);

            // aDirForTest存在確認
            result = theolizer::isExist(aDirForTest);
            ++aTestCounter;
            THEOLIZER_CHECK(result, result);

            // aDirForTest削除トライ
            theolizer::removeFile(aDirForTest);

            // aDirForTest存在確認(削除されないこと)
            result = theolizer::isExist(aDirForTest);
            ++aTestCounter;
            THEOLIZER_CHECK(result, result);

            // ファイル生成
            string  aFilePath=aDirForTest + "test0.txt";
            {
                std::ofstream ofs(aFilePath);
            }

            // aFilePath存在確認
            result = theolizer::isExist(aFilePath);
            ++aTestCounter;
            THEOLIZER_CHECK(result, result);

            // aFilePath削除トライ
            theolizer::removeFile(aFilePath);

            // aFilePath存在確認(削除されること)
            result = theolizer::isExist(aFilePath);
            ++aTestCounter;
            THEOLIZER_CHECK(!result, result);

            // 複数のファイル生成
            {
                theolizer::u8string aFileName;
                aFileName=aDirForTest+u8"Ｆｉｌｅ０.txt";
                std::ofstream ofs00(aFileName.get_fstring());
                aFileName=aDirForTest+u8"Ｆｉｌｅ１.txt";
                std::ofstream ofs01(aFileName.get_fstring());
                aFileName=aDirForTest+u8"Ｆｉｌｅ２２.txt";
                std::ofstream ofs02(aFileName.get_fstring());
            }

            // ファイル・リスト獲得(正規表現無し)
            vector<string> aFileList=theolizer::getFileList(aDirForTest);
            ++aTestCounter;
            THEOLIZER_EQUAL(aFileList[0], u8"Ｆｉｌｅ０.txt");
            ++aTestCounter;
            THEOLIZER_EQUAL(aFileList[1], u8"Ｆｉｌｅ１.txt");
            ++aTestCounter;
            THEOLIZER_EQUAL(aFileList[2], u8"Ｆｉｌｅ２２.txt");
            ++aTestCounter;
            THEOLIZER_EQUAL(aFileList.size(), 3);

            // ファイル・リスト獲得(正規表現有り)
            aFileList=theolizer::getFileList(aDirForTest, u8"(Ｆｉｌｅ.\\.txt)");
            ++aTestCounter;
            THEOLIZER_EQUAL(aFileList[0], u8"Ｆｉｌｅ０.txt");
            ++aTestCounter;
            THEOLIZER_EQUAL(aFileList[1], u8"Ｆｉｌｅ１.txt");
            ++aTestCounter;
            THEOLIZER_EQUAL(aFileList.size(), 2);
        }

        // aDirForTest存在確認(削除されないこと)
        result = theolizer::isExist(aDirForTest);
        ++aTestCounter;
        THEOLIZER_CHECK(result, result);

        {
            // aDirForTest再生成(終了時削除する)
            theolizer::PrepareDir AutoDelete(aDirForTest);
        }
        // aDirForTest存在確認(削除されていること)
        result = theolizer::isExist(aDirForTest);
        ++aTestCounter;
        THEOLIZER_CHECK(!result, result);
    }

    // setWritePermission
    {
        // aDirForTest生成
        theolizer::PrepareDir AutoDelete(aDirForTest);

        // ファイル生成
        string  aFilePath=aDirForTest + "test.txt";
        {
            std::ofstream ofs(aFilePath);
        }
        // 書き込み禁止
        theolizer::setWritePermission(aFilePath, false);

// ubuntuでは書き込み禁止しても削除できてしまう。
//  書き込み禁止には頼らないのでテスト省略
#if defined(_WIN32)
        // aFilePath削除トライ
        theolizer::removeFile(aFilePath);

        // aFilePath存在確認(削除されないこと)
        result = theolizer::isExist(aFilePath);
        ++aTestCounter;
        THEOLIZER_CHECK(result, result);
#endif

        // 書き込み許可
        theolizer::setWritePermission(aFilePath, true);
    }

// ***************************************************************************
//      カウンタのテスト
// ***************************************************************************

    {   // gTotal, gFailCountは比較後にインクリメントしている
        THEOLIZER_EQUAL(theolizer::internal::gFailCount, 0);
        ++aTestCounter;
        THEOLIZER_EQUAL(theolizer::internal::gTotal, aTestCounter);
        ++aTestCounter;
    }

    return 0;
}
