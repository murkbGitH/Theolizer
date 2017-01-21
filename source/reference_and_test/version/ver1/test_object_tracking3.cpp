﻿//############################################################################
//      Theolizer仕様／テスト・プログラム
//
//          オブジェクト追跡3
//              MinGWのFile too bigエラー対策のため分割。
/*
    Copyright (c) 2016 Yohinori Tahara(Theoride Technology) - http://theolizer.com/

    商用ライセンス
        有効なTheolizer商用ライセンスを保持している人は、
        田原良則(Theoride Technology)と締結している商用ライセンス契約の
        使用条件に従って、このファイルを取り扱うことができます。

    General Public License Version 3(以下GPLv3)
        Free Software Foundationが公表するGPLv3の使用条件に従って、
        あなたはこのファイルを取り扱うことができます。
        GPLv3の内容を https://www.gnu.org/licenses/gpl.txt にて確認して下さい。
        GPLv3のコピーをLICENSE.TXTファイルにおいてます。
*/
//############################################################################

#include "disable_test.h"
#ifndef DISABLE_OBJECT_TRACKING3_TEST

// ***************************************************************************
//      インクルード
// ***************************************************************************

// 標準ライブラリ
#include <iostream>
#include <fstream>
#include <ctime>

// theolizerライブラリ
#include <theolizer/serializer_binary.h>
#include <theolizer/serializer_json.h>
#include <theolizer/memory.h>

// プロジェクト・ヘッダ
#include "common.h"
#include "test_object_tracking.h"

// 自動生成ソース
#include "test_object_tracking3.cpp.theolizer.hpp"

//############################################################################
//      組み合わせテスト
//############################################################################

// ***************************************************************************
//      保存
// ***************************************************************************

template<class tSerializer>
void saveObjectTracking3(tSerializer& iSerializer)
{
//----------------------------------------------------------------------------
//      オーナー・ポインタのテスト
//----------------------------------------------------------------------------

//      ---<<< 手動(トップ・レベル)によるポインタの保存 >>>---

    {
        // ボインタ群
        OwnerList aOwnerListNull;
        OwnerList aOwnerList{true};

        // nullptrポインタ保存
        std::cout << "        saveOwner() : aOwnerListNull" << std::endl;
        saveOwner(iSerializer, aOwnerListNull);

        // 領域有りポインタ保存
        std::cout << "        saveOwner() : aOwnerList" << std::endl;
        saveOwner(iSerializer, aOwnerList);

        iSerializer.clearTracking();
    }

//      ---<<< 自動メンバ・リスト生成によるポインタの保存 >>>---

    {
        // ボインタ群
        OwnerList aOwnerListNull;
        OwnerList aOwnerList{true};

        // nullptrポインタ保存
        std::cout << "        THEOLIZER_PROCESS() : aOwnerListNull" << std::endl;
        THEOLIZER_PROCESS(iSerializer, aOwnerListNull);

        // 領域有りポインタ保存
        std::cout << "        THEOLIZER_PROCESS() : aOwnerList" << std::endl;
        THEOLIZER_PROCESS(iSerializer, aOwnerList);

        iSerializer.clearTracking();
    }

//      ---<<< 手動(非トップ・レベル)によるポインタの保存 >>>---

    {
        // ポインタ群
        OwnerListManual aManualClass4OwnerListNull;
        OwnerListManual aManualClass4OwnerList{true};

        // nullptrポインタ保存
        std::cout << "        THEOLIZER_PROCESS() : aManualClass4OwnerListNull" << std::endl;
        THEOLIZER_PROCESS(iSerializer, aManualClass4OwnerListNull);

        // 領域有りポインタ保存
        std::cout << "        THEOLIZER_PROCESS() : aManualClass4OwnerList" << std::endl;
        THEOLIZER_PROCESS(iSerializer, aManualClass4OwnerList);

        iSerializer.clearTracking();
    }
}

INSTANTIATION_ALL(saveObjectTracking3);

// ***************************************************************************
//      回復
// ***************************************************************************

template<class tSerializer>
void loadObjectTracking3(tSerializer& iSerializer)
{
//----------------------------------------------------------------------------
//      オーナー・ポインタのテスト
//----------------------------------------------------------------------------

//      ---<<< 手動(トップ・レベル)によるポインタの回復 >>>---

    {
        // ボインタ群
        OwnerList aOwnerListNull;
        OwnerList aOwnerList{true};

        // nullptrポインタ回復
        std::cout << "        loadOwner() : aOwnerListNull" << std::endl;
        loadOwner(iSerializer, aOwnerListNull);

        // 領域有りポインタ回復
        std::cout << "        loadOwner() : aOwnerList" << std::endl;
        loadOwner(iSerializer, aOwnerList);

        iSerializer.clearTracking();

        // 回復結果のチェック
        aOwnerListNull.check();
        aOwnerList.check(true);
    }


//      ---<<< 自動メンバ・リスト生成によるポインタの回復 >>>---

    {
        // ボインタ群
        OwnerList aOwnerListNull;
        OwnerList aOwnerList{true};

        // nullptrポインタ回復
        std::cout << "        THEOLIZER_PROCESS() : aOwnerListNull" << std::endl;
        THEOLIZER_PROCESS(iSerializer, aOwnerListNull);

        // 領域有りポインタ回復
        std::cout << "        THEOLIZER_PROCESS() : aOwnerList" << std::endl;
        THEOLIZER_PROCESS(iSerializer, aOwnerList);

        iSerializer.clearTracking();

        // 回復結果のチェック
        aOwnerListNull.check();
        aOwnerList.check(true);
    }

//      ---<<< 手動(非トップ・レベル)によるポインタの回復 >>>---

    {
        // ポインタ群
        OwnerListManual aManualClass4OwnerListNull;
        OwnerListManual aManualClass4OwnerList{true};

        // nullptrポインタ回復
        std::cout << "        THEOLIZER_PROCESS() : aManualClass4OwnerListNull" << std::endl;
        THEOLIZER_PROCESS(iSerializer, aManualClass4OwnerListNull);

        // 領域有りポインタ回復
        std::cout << "        THEOLIZER_PROCESS() : aManualClass4OwnerList" << std::endl;
        THEOLIZER_PROCESS(iSerializer, aManualClass4OwnerList);

        iSerializer.clearTracking();

        // 回復結果のチェック
        aManualClass4OwnerListNull.check();
        aManualClass4OwnerList.check(true);
    }
}

INSTANTIATION_ALL(loadObjectTracking3);

#endif  // DISABLE_OBJECT_TRACKING3_TEST
