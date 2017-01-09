﻿//############################################################################
//      Theolizer仕様／テスト・プログラム
//
//          オブジェクト追跡2
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
#ifndef DISABLE_OBJECT_TRACKING2_TEST

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
#include "test_object_tracking2.cpp.theolizer.hpp"

//############################################################################
//      2番目以降の基底クラス・ポインタのオブジェクト追跡テスト
//      組み合わせテスト
//############################################################################

// ***************************************************************************
//      保存
// ***************************************************************************

template<class tSerializer>
void saveObjectTracking(tSerializer& iSerializer)
{
    // オブジェクト追跡前準備
    //  ここに来るまでにオブジェクト追跡テーブルに登録され、その領域が開放されるので必要。
    //  (オブジェクト追跡単位内でシリアライズした領域を開放してはいけない。)
    iSerializer.clearTracking();

//----------------------------------------------------------------------------
//      2番目以降の基底クラス・ポインタのオブジェクト追跡テスト
//----------------------------------------------------------------------------

    {
        ObjectTrackingDerived   aObjectTrackingDerived;
        THEOLIZER_PROCESS(iSerializer, aObjectTrackingDerived);

        ObjectTrackingBase1* aObjectTrackingBase1 = &aObjectTrackingDerived;
        THEOLIZER_PROCESS(iSerializer, aObjectTrackingBase1);

        iSerializer.clearTracking();
    }

//----------------------------------------------------------------------------
//      通常ポインタのテスト
//----------------------------------------------------------------------------

//      ---<<< 手動(トップ・レベル)によるポインタの保存 >>>---

    {

        // ポイント先群
        PointeeList         aPointeeList{true};
        PointeeList         aPointeeList2{2};
        PointeeListManual   aPointeeListManual{true};

        // ボインタ群
        PointerList aPointerListA{aPointeeList,  aPointeeList2};
        PointerList aPointerListB{aPointeeList,  aPointeeListManual};
        PointerList aPointerListC{aPointeeList2, aPointeeListManual};

        // ポイント先保存1：手動(トップ・レベル)
        std::cout << "        savePointee() : aPointeeList" << std::endl;
        savePointee(iSerializer, aPointeeList);

        // ポイント先保存前／後にポインタ保存
        std::cout << "        savePointer() : aPointerListA" << std::endl;
        savePointer(iSerializer, aPointerListA);

        // ポイント先保存2：自動メンバ・リスト生成
        std::cout << "        THEOLIZER_PROCESS() : aPointeeList2" << std::endl;
        THEOLIZER_PROCESS(iSerializer, aPointeeList2);

        // ポイント先保存前／後にポインタ保存
        std::cout << "        savePointer() : aPointerListB" << std::endl;
        savePointer(iSerializer, aPointerListB);

        // ポイント先保存3：手動(非トップ・レベル)
        std::cout << "        THEOLIZER_PROCESS() : aPointeeListManual" << std::endl;
        THEOLIZER_PROCESS(iSerializer, aPointeeListManual);

        // ポイント先保存後にポインタ保存
        std::cout << "        savePointer() : aPointerListC" << std::endl;
        savePointer(iSerializer, aPointerListC);

        iSerializer.clearTracking();
    }

//      ---<<< 自動メンバ・リスト生成によるポインタの保存 >>>---

    {
        // ポイント先群
        PointeeList         aPointeeList{true};
        PointeeList         aPointeeList2{2};
        PointeeListManual   aPointeeListManual{true};

        // ボインタ群
        PointerList aPointerListA{aPointeeList,  aPointeeList2};
        PointerList aPointerListB{aPointeeList,  aPointeeListManual};
        PointerList aPointerListC{aPointeeList2, aPointeeListManual};

        // ポイント先保存1：手動(トップ・レベル)
        std::cout << "        savePointee() : aPointeeList" << std::endl;
        savePointee(iSerializer, aPointeeList);

        // ポイント先保存前／後にポインタ保存
        std::cout << "        THEOLIZER_PROCESS() : aPointerListA" << std::endl;
        THEOLIZER_PROCESS(iSerializer, aPointerListA);

        // ポイント先保存2：自動メンバ・リスト生成
        std::cout << "        THEOLIZER_PROCESS() : aPointeeList2" << std::endl;
        THEOLIZER_PROCESS(iSerializer, aPointeeList2);

        // ポイント先保存前／後にポインタ保存
        std::cout << "        THEOLIZER_PROCESS() : aPointerListB" << std::endl;
        THEOLIZER_PROCESS(iSerializer, aPointerListB);

        // ポイント先保存3：手動(非トップ・レベル)
        std::cout << "        THEOLIZER_PROCESS() : aPointeeListManual" << std::endl;
        THEOLIZER_PROCESS(iSerializer, aPointeeListManual);

        // ポイント先保存後にポインタ保存
        std::cout << "        THEOLIZER_PROCESS() : aPointerListC" << std::endl;
        THEOLIZER_PROCESS(iSerializer, aPointerListC);

        iSerializer.clearTracking();
    }

//      ---<<< 手動(非トップ・レベル)によるポインタの保存 >>>---

    {
        // ポイント先群
        PointeeList         aPointeeList{true};
        PointeeList         aPointeeList2{2};
        PointeeListManual   aPointeeListManual{true};

        // ポインタ群
        ManualClass4PointerList aManualClass4PointerListA{aPointeeList,  aPointeeList2};
        ManualClass4PointerList aManualClass4PointerListB{aPointeeList,  aPointeeListManual};
        ManualClass4PointerList aManualClass4PointerListC{aPointeeList2, aPointeeListManual};

        // ポイント先保存1：手動(トップ・レベル)
        std::cout << "        savePointee() : aPointeeList" << std::endl;
        savePointee(iSerializer, aPointeeList);

        // ポイント先保存前／後にポインタ保存
        std::cout << "        THEOLIZER_PROCESS() : aManualClass4PointerListA" << std::endl;
        THEOLIZER_PROCESS(iSerializer, aManualClass4PointerListA);

        // ポイント先保存2：自動メンバ・リスト生成
        std::cout << "        THEOLIZER_PROCESS() : aPointeeList2" << std::endl;
        THEOLIZER_PROCESS(iSerializer, aPointeeList2);

        // ポイント先保存前／後にポインタ保存
        std::cout << "        THEOLIZER_PROCESS() : aManualClass4PointerListB" << std::endl;
        THEOLIZER_PROCESS(iSerializer, aManualClass4PointerListB);

        // ポイント先保存3：手動(非トップ・レベル)
        std::cout << "        THEOLIZER_PROCESS() : aPointeeListManual" << std::endl;
        THEOLIZER_PROCESS(iSerializer, aPointeeListManual);

        // ポイント先保存後にポインタ保存
        std::cout << "        THEOLIZER_PROCESS() : aManualClass4PointerListC" << std::endl;
        THEOLIZER_PROCESS(iSerializer, aManualClass4PointerListC);

        iSerializer.clearTracking();
    }
}

INSTANTIATION_ALL(void, saveObjectTracking);

// ***************************************************************************
//      回復
// ***************************************************************************

template<class tSerializer>
void loadObjectTracking(tSerializer& iSerializer)
{
    // オブジェクト追跡前準備
    //  ここに来るまでにオブジェクト追跡テーブルに登録され、その領域が開放されるので必要。
    //  (オブジェクト追跡単位内でシリアライズした領域を開放してはいけない。)
    iSerializer.clearTracking();

//----------------------------------------------------------------------------
//      2番目以降の基底クラス・ポインタのオブジェクト追跡テスト
//----------------------------------------------------------------------------

    {
        ObjectTrackingDerived   aObjectTrackingDerived;
        THEOLIZER_PROCESS(iSerializer, aObjectTrackingDerived);

        ObjectTrackingBase1* aObjectTrackingBase1 = nullptr;
        THEOLIZER_PROCESS(iSerializer, aObjectTrackingBase1);

        iSerializer.clearTracking();

        THEOLIZER_EQUAL_PTR(&aObjectTrackingDerived, aObjectTrackingBase1);
    }

//----------------------------------------------------------------------------
//      通常ポインタのテスト
//----------------------------------------------------------------------------

//      ---<<< 手動(トップ・レベル)によるポインタ（左辺値）の回復 >>>---

    {
        // ポイント先群
        PointeeList         aPointeeList;
        PointeeList         aPointeeList2;
        PointeeListManual   aPointeeListManual;

        // ポインタ群
        PointerList aPointerListA;
        PointerList aPointerListB;
        PointerList aPointerListC;

        // ポイント先回復1：手動(トップ・レベル)
        std::cout << "        loadPointee() : aPointeeList" << std::endl;
        loadPointee(iSerializer, aPointeeList);
        aPointeeList.check(true);

        // ポイント先回復前／後にポインタ回復
        std::cout << "        loadPointer() : aPointerListA" << std::endl;
        loadPointer(iSerializer, aPointerListA);

        // ポイント先回復2：自動メンバ・リスト生成
        std::cout << "        THEOLIZER_PROCESS() : aPointeeList2" << std::endl;
        THEOLIZER_PROCESS(iSerializer, aPointeeList2);
        aPointeeList2.check(2);

        // ポイント先回復前／後にポインタ回復
        std::cout << "        loadPointer() : aPointerListB" << std::endl;
        loadPointer(iSerializer, aPointerListB);

        // ポイント先回復3：手動(非トップ・レベル)
        std::cout << "        THEOLIZER_PROCESS() : aPointeeListManual" << std::endl;
        THEOLIZER_PROCESS(iSerializer, aPointeeListManual);
        aPointeeListManual.check(true);

        // ポイント先回復後にポインタ回復
        std::cout << "        loadPointer() : aPointerListC" << std::endl;
        loadPointer(iSerializer, aPointerListC);

        // アドレス解決確認
        iSerializer.clearTracking();

        // 回復結果のチェック
        aPointerListA.check(aPointeeList,  aPointeeList2);
        aPointerListB.check(aPointeeList,  aPointeeListManual);
        aPointerListC.check(aPointeeList2, aPointeeListManual);
    }

//      ---<<< 自動メンバ・リスト生成によるポインタの回復 >>>---

    {
        // ポイント先群
        PointeeList         aPointeeList;
        PointeeList         aPointeeList2;
        PointeeListManual   aPointeeListManual;

        // ポインタ群
        PointerList aPointerListA;
        PointerList aPointerListB;
        PointerList aPointerListC;

        // ポイント先回復1：手動(トップ・レベル)
        std::cout << "        loadPointee() : aPointeeList" << std::endl;
        loadPointee(iSerializer, aPointeeList);
        aPointeeList.check(true);

        // ポイント先回復前／後にポインタ回復
        std::cout << "        THEOLIZER_PROCESS() : aPointerListA" << std::endl;
        THEOLIZER_PROCESS(iSerializer, aPointerListA);

        // ポイント先回復2：自動メンバ・リスト生成
        std::cout << "        THEOLIZER_PROCESS() : aPointeeList2" << std::endl;
        THEOLIZER_PROCESS(iSerializer, aPointeeList2);
        aPointeeList2.check(2);

        // ポイント先回復前／後にポインタ回復
        std::cout << "        THEOLIZER_PROCESS() : aPointerListB" << std::endl;
        THEOLIZER_PROCESS(iSerializer, aPointerListB);

        // ポイント先回復3：手動(非トップ・レベル)
        std::cout << "        THEOLIZER_PROCESS() : aPointeeListManual" << std::endl;
        THEOLIZER_PROCESS(iSerializer, aPointeeListManual);
        aPointeeListManual.check(true);

        // ポイント先回復後にポインタ回復
        std::cout << "        THEOLIZER_PROCESS() : aPointerListC" << std::endl;
        THEOLIZER_PROCESS(iSerializer, aPointerListC);

        // アドレス解決確認
        iSerializer.clearTracking();

        // 回復結果のチェック
        aPointerListA.check(aPointeeList,  aPointeeList2);
        aPointerListB.check(aPointeeList,  aPointeeListManual);
        aPointerListC.check(aPointeeList2, aPointeeListManual);
    }

//      ---<<< 手動(非トップ・レベル)によるポインタの回復 >>>---

    {
        // ポイント先群
        PointeeList         aPointeeList;
        PointeeList         aPointeeList2;
        PointeeListManual   aPointeeListManual;

        // ポインタ
        ManualClass4PointerList aManualClass4PointerListA;
        ManualClass4PointerList aManualClass4PointerListB;
        ManualClass4PointerList aManualClass4PointerListC;

        // ポイント先回復1：手動(トップ・レベル)
        std::cout << "        loadPointee() : aPointeeList" << std::endl;
        loadPointee(iSerializer, aPointeeList);
        aPointeeList.check(true);

        // ポイント先回復前／後にポインタ回復
        std::cout << "        THEOLIZER_PROCESS() : aManualClass4PointerListA" << std::endl;
        THEOLIZER_PROCESS(iSerializer, aManualClass4PointerListA);

        // ポイント先回復2：自動メンバ・リスト生成
        std::cout << "        THEOLIZER_PROCESS() : aPointeeList2" << std::endl;
        THEOLIZER_PROCESS(iSerializer, aPointeeList2);
        aPointeeList2.check(2);

        // ポイント先回復前／後にポインタ回復
        std::cout << "        THEOLIZER_PROCESS() : aManualClass4PointerListB" << std::endl;
        THEOLIZER_PROCESS(iSerializer, aManualClass4PointerListB);

        // ポイント先回復3：手動(非トップ・レベル)
        std::cout << "        THEOLIZER_PROCESS() : aPointeeListManual" << std::endl;
        THEOLIZER_PROCESS(iSerializer, aPointeeListManual);
        aPointeeListManual.check(true);

        // ポイント先回復後にポインタ回復
        std::cout << "        THEOLIZER_PROCESS() : aManualClass4PointerListC" << std::endl;
        THEOLIZER_PROCESS(iSerializer, aManualClass4PointerListC);

        // アドレス解決確認
        iSerializer.clearTracking();

        // 回復結果のチェック
        aManualClass4PointerListA.check(aPointeeList,  aPointeeList2);
        aManualClass4PointerListB.check(aPointeeList,  aPointeeListManual);
        aManualClass4PointerListC.check(aPointeeList2, aPointeeListManual);
    }
}

INSTANTIATION_ALL(void, loadObjectTracking);

#endif  // DISABLE_OBJECT_TRACKING2_TEST