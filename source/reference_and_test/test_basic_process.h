﻿//############################################################################
//      Theolizer仕様／テスト・プログラム
//
//          THEOLIZER_PROCESS()の基本的な使い方
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

#if !defined(TEST_BASIC_PROCESS_H)
#define TEST_BASIC_PROCESS_H

#include <string>

// ***************************************************************************
//      enum型(完全自動型)
// ***************************************************************************

enum NormalEnum
{
    eneZero,
    eneOne,
    eneTwo
};

enum class ScopedEnum : long
{
    ZERO,
    ONE,
    TWO
};

// ***************************************************************************
//      クラス(完全自動型)
// ***************************************************************************

struct ClassBasicTest
{
    int         mInt;
    std::string mString;
    NormalEnum  mNormalEnum;

    ClassBasicTest() : mInt(0), mString(""), mNormalEnum(eneZero)
    { }

    // 以下は自動テスト（配列）用の定義
    ClassBasicTest(int iInt, char const* iString, NormalEnum iNormalEnum) :
        mInt(iInt),
        mString(iString),
        mNormalEnum(iNormalEnum)
    { }

    bool operator==(ClassBasicTest const& iRhs) const
    {
        return (mInt==iRhs.mInt) && (mString==iRhs.mString) && (mNormalEnum==iRhs.mNormalEnum);
    }

    friend std::ostream& operator<<(std::ostream& iOStream, ClassBasicTest const& iRhs)
    {
        iOStream <<"("<< iRhs.mInt << ", \"" << iRhs.mString << "\", " << iRhs.mNormalEnum<<")";
        return iOStream;
    }
};

#endif  // TEST_BASIC_PROCESS_H
