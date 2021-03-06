﻿//############################################################################
//      
/*!
@brief      Theolizerライブラリの標準コンテナ・サポート(キー無しresize有り用)
@ingroup    TheolizerLib
@file       container_no_key.inc
@author     Yoshinori Tahara(Theoride Technology)
@date       2017/02/01 Created
*/
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

//############################################################################
//      Begin
//############################################################################

#ifndef THEOLIZER_INTERNAL_DOXYGEN

// ***************************************************************************
//      前準備
// ***************************************************************************

#define THEOLIZER_INTERNAL_FULL_NAME                                        \
    THEOLZIER_INTERNAL_CONTAINER_NAME<THEOLZIER_INTERNAL_CONTAINER_ARGUMENT>

//############################################################################
//      標準型
//############################################################################

// ***************************************************************************
//      シリアライズ指定
// ***************************************************************************

THEOLIZER_NON_INTRUSIVE_TEMPLATE_ORDER((THEOLZIER_INTERNAL_CONTAINER_PARAMETER),
                                        (THEOLIZER_INTERNAL_FULL_NAME), 1,
                                        THEOLZIER_INTERNAL_CONTAINER_UNIQUE);

//----------------------------------------------------------------------------
//      ユーザ定義
//          回復処理の注意事項：
//              余分なデータの破棄、および、ClassType終了処理のため、
//              必ずiSerializer.readPreElement()がfalseを返却するまで
//              処理しておくこと。
//----------------------------------------------------------------------------

//      ---<<< Version.1 >>>---

THEOLZIER_INTERNAL_CONTAINER_PARAMETER
template<class tMidSerializer, class tTheolizerVersion>
struct TheolizerNonIntrusive<THEOLIZER_INTERNAL_FULL_NAME>::
    TheolizerUserDefine<tMidSerializer, tTheolizerVersion, 1>
{
    // 保存
    static void saveClassManual
    (
        tMidSerializer& iSerializer,
        typename tTheolizerVersion::TheolizerTarget const*const& iInstance
    )
    {
        THEOLIZER_REGISTER_TEMPLATE_PARAMETER(Alloc);

        THEOLIZER_PROCESS(iSerializer, iInstance->size());
        auto itr=iInstance->begin();
        for (std::size_t i=0; i < iInstance->size(); ++i, ++itr)
        {
#ifndef THEOLIZER_INTERNAL_IS_VECTOR
    #ifndef THEOLIZER_INTERNAL_POINTEE
            THEOLIZER_PROCESS(iSerializer, *itr);
    #else
            THEOLIZER_PROCESS_POINTEE(iSerializer, *itr);
    #endif
#else
            typedef typename tTheolizerVersion::TheolizerTarget TheolizerTarget;
            typedef typename TheolizerTarget::value_type        ValueType;
    #ifndef THEOLIZER_INTERNAL_POINTEE
            theolizer::internal::SupportVector<TheolizerTarget,ValueType, tTheolizerVersion>::
                save(iSerializer,*itr);
    #else
            theolizer::internal::SupportVectorPointee
            <
                TheolizerTarget,
                ValueType,
                tTheolizerVersion
            >::save(iSerializer,*itr);
    #endif
#endif
        }
    }

    // 回復
    static void loadClassManual
    (
        tMidSerializer& iSerializer,
        typename tTheolizerVersion::TheolizerTarget*& oInstance
    )
    {
        THEOLIZER_REGISTER_TEMPLATE_PARAMETER(Alloc);

        // もし、nullptrなら、インスタンス生成
        if (!oInstance)   oInstance=new typename tTheolizerVersion::TheolizerTarget();

        std::size_t aSize;
        THEOLIZER_PROCESS(iSerializer, aSize);

        // 先に領域をvector内部に生成してから、そこへ回復する。
        //  これにより、要素のコピーやムーブが発生しないようにすることで、
        //  「親」へのポインタが壊れないようにしている。
        if (oInstance->size() < aSize) oInstance->resize(aSize);
        auto itr=oInstance->begin();
        for (std::size_t i=0; i < aSize; ++i, ++itr)
        {
#ifndef THEOLIZER_INTERNAL_IS_VECTOR
    #ifndef THEOLIZER_INTERNAL_POINTEE
            THEOLIZER_PROCESS(iSerializer, *itr);
    #else
            THEOLIZER_PROCESS_POINTEE(iSerializer, *itr);
    #endif
#else
            typedef typename tTheolizerVersion::TheolizerTarget TheolizerTarget;
            typedef typename TheolizerTarget::value_type        ValueType;
    #ifndef THEOLIZER_INTERNAL_POINTEE
            theolizer::internal::SupportVector<TheolizerTarget,ValueType, tTheolizerVersion>::
                load(iSerializer,*itr);
    #else
            theolizer::internal::SupportVectorPointee
            <
                TheolizerTarget,
                ValueType,
                tTheolizerVersion
            >::load(iSerializer,*itr);
    #endif
#endif
        }
    }
};

//############################################################################
//      End
//############################################################################

#endif  // THEOLIZER_INTERNAL_DOXYGEN
