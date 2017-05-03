﻿//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------
#include "pch.h"
#include "XamlTypeInfo.g.h"

#include "App.xaml.h"
#include "MainPage.xaml.h"
#include "XamlBindingInfo.g.hpp"
#include "App.g.hpp"
#include "MainPage.g.hpp"

template<typename T>
::Platform::Object^ ActivateType()
{
    return ref new T;
}

template<typename TInstance, typename TItem>
void CollectionAdd(::Platform::Object^ instance, ::Platform::Object^ item)
{
    safe_cast<TInstance^>(instance)->Append((TItem)item);
}

template<typename TInstance, typename TKey, typename TItem>
void DictionaryAdd(::Platform::Object^ instance, ::Platform::Object^ key, ::Platform::Object^ item)
{
    safe_cast<TInstance^>(instance)->Insert((TKey)key, (TItem)item);
}

template<typename T>
::Platform::Object^ FromStringConverter(::XamlTypeInfo::InfoProvider::XamlUserType^ userType, ::Platform::String^ input)
{
    return ref new ::Platform::Box<T>((T)userType->CreateEnumUIntFromString(input));
}

template<typename TDeclaringType, typename TValue>
::Platform::Object^ GetValueTypeMember_Dpi(::Platform::Object^ instance)
{
    return ref new ::Platform::Box<TValue>(safe_cast<TDeclaringType^>(instance)->Dpi);
}

template<typename TDeclaringType, typename TValue>
::Platform::Object^ GetValueTypeMember_UseSharedDevice(::Platform::Object^ instance)
{
    return ref new ::Platform::Box<TValue>(safe_cast<TDeclaringType^>(instance)->UseSharedDevice);
}

template<typename TDeclaringType, typename TValue>
::Platform::Object^ GetValueTypeMember_TargetElapsedTime(::Platform::Object^ instance)
{
    return ref new ::Platform::Box<TValue>(safe_cast<TDeclaringType^>(instance)->TargetElapsedTime);
}

template<typename TDeclaringType, typename TValue>
::Platform::Object^ GetValueTypeMember_Paused(::Platform::Object^ instance)
{
    return ref new ::Platform::Box<TValue>(safe_cast<TDeclaringType^>(instance)->Paused);
}

template<typename TDeclaringType, typename TValue>
::Platform::Object^ GetValueTypeMember_IsFixedTimeStep(::Platform::Object^ instance)
{
    return ref new ::Platform::Box<TValue>(safe_cast<TDeclaringType^>(instance)->IsFixedTimeStep);
}

template<typename TDeclaringType, typename TValue>
::Platform::Object^ GetValueTypeMember_ForceSoftwareRenderer(::Platform::Object^ instance)
{
    return ref new ::Platform::Box<TValue>(safe_cast<TDeclaringType^>(instance)->ForceSoftwareRenderer);
}

template<typename TDeclaringType, typename TValue>
::Platform::Object^ GetValueTypeMember_DpiScale(::Platform::Object^ instance)
{
    return ref new ::Platform::Box<TValue>(safe_cast<TDeclaringType^>(instance)->DpiScale);
}

template<typename TDeclaringType, typename TValue>
::Platform::Object^ GetValueTypeMember_ClearColor(::Platform::Object^ instance)
{
    return ref new ::Platform::Box<TValue>(safe_cast<TDeclaringType^>(instance)->ClearColor);
}

template<typename TDeclaringType, typename TValue>
::Platform::Object^ GetValueTypeMember_HasGameLoopThreadAccess(::Platform::Object^ instance)
{
    return ref new ::Platform::Box<TValue>(safe_cast<TDeclaringType^>(instance)->HasGameLoopThreadAccess);
}

template<typename TDeclaringType, typename TValue>
::Platform::Object^ GetValueTypeMember_ReadyToDraw(::Platform::Object^ instance)
{
    return ref new ::Platform::Box<TValue>(safe_cast<TDeclaringType^>(instance)->ReadyToDraw);
}

template<typename TDeclaringType, typename TValue>
::Platform::Object^ GetValueTypeMember_Size(::Platform::Object^ instance)
{
    return ref new ::Platform::Box<TValue>(safe_cast<TDeclaringType^>(instance)->Size);
}

template<typename TDeclaringType>
::Platform::Object^ GetReferenceTypeMember_Device(::Platform::Object^ instance)
{
    return safe_cast<TDeclaringType^>(instance)->Device;
}

template<typename TDeclaringType>
::Platform::Object^ GetReferenceTypeMember_CustomDevice(::Platform::Object^ instance)
{
    return safe_cast<TDeclaringType^>(instance)->CustomDevice;
}

template<typename TDeclaringType, typename TValue>
void SetValueTypeMember_UseSharedDevice(::Platform::Object^ instance, ::Platform::Object^ value)
{
    safe_cast<TDeclaringType^>(instance)->UseSharedDevice = safe_cast<::Platform::IBox<TValue>^>(value)->Value;
}

template<typename TDeclaringType, typename TValue>
void SetValueTypeMember_TargetElapsedTime(::Platform::Object^ instance, ::Platform::Object^ value)
{
    safe_cast<TDeclaringType^>(instance)->TargetElapsedTime = safe_cast<::Platform::IBox<TValue>^>(value)->Value;
}

template<typename TDeclaringType, typename TValue>
void SetValueTypeMember_Paused(::Platform::Object^ instance, ::Platform::Object^ value)
{
    safe_cast<TDeclaringType^>(instance)->Paused = safe_cast<::Platform::IBox<TValue>^>(value)->Value;
}

template<typename TDeclaringType, typename TValue>
void SetValueTypeMember_IsFixedTimeStep(::Platform::Object^ instance, ::Platform::Object^ value)
{
    safe_cast<TDeclaringType^>(instance)->IsFixedTimeStep = safe_cast<::Platform::IBox<TValue>^>(value)->Value;
}

template<typename TDeclaringType, typename TValue>
void SetValueTypeMember_ForceSoftwareRenderer(::Platform::Object^ instance, ::Platform::Object^ value)
{
    safe_cast<TDeclaringType^>(instance)->ForceSoftwareRenderer = safe_cast<::Platform::IBox<TValue>^>(value)->Value;
}

template<typename TDeclaringType, typename TValue>
void SetValueTypeMember_DpiScale(::Platform::Object^ instance, ::Platform::Object^ value)
{
    safe_cast<TDeclaringType^>(instance)->DpiScale = safe_cast<::Platform::IBox<TValue>^>(value)->Value;
}

template<typename TDeclaringType, typename TValue>
void SetValueTypeMember_ClearColor(::Platform::Object^ instance, ::Platform::Object^ value)
{
    safe_cast<TDeclaringType^>(instance)->ClearColor = safe_cast<::Platform::IBox<TValue>^>(value)->Value;
}

template<typename TDeclaringType, typename TValue>
void SetReferenceTypeMember_CustomDevice(::Platform::Object^ instance, ::Platform::Object^ value)
{
    safe_cast<TDeclaringType^>(instance)->CustomDevice = safe_cast<TValue^>(value);
}

struct TypeInfo
{
    PCWSTR  typeName;
    PCWSTR contentPropertyName;
    ::Platform::Object^ (*activator)();
    void (*collectionAdd)(::Platform::Object^, ::Platform::Object^);
    void (*dictionaryAdd)(::Platform::Object^, ::Platform::Object^, ::Platform::Object^);
    ::Platform::Object^ (*fromStringConverter)(::XamlTypeInfo::InfoProvider::XamlUserType^, ::Platform::String^);
    int     baseTypeIndex;
    int     firstMemberIndex;
    int     firstEnumValueIndex;
    ::Windows::UI::Xaml::Interop::TypeKind kindofType;
    bool    isLocalType;
    bool    isSystemType;
    bool    isReturnTypeStub;
    bool    isBindable;
};

TypeInfo TypeInfos[] = 
{
    //   0
    L"Object", L"",
    nullptr, nullptr, nullptr, nullptr,
    -1,
    0, 0, ::Windows::UI::Xaml::Interop::TypeKind::Metadata,
    false, true,  false, false,
    //   1
    L"Single", L"",
    nullptr, nullptr, nullptr, nullptr,
    -1,
    0, 0, ::Windows::UI::Xaml::Interop::TypeKind::Metadata,
    false, true,  false, false,
    //   2
    L"Boolean", L"",
    nullptr, nullptr, nullptr, nullptr,
    -1,
    0, 0, ::Windows::UI::Xaml::Interop::TypeKind::Metadata,
    false, true,  false, false,
    //   3
    L"Windows.UI.Color", L"",
    nullptr, nullptr, nullptr, nullptr,
    4, // System.ValueType
    0, 0, ::Windows::UI::Xaml::Interop::TypeKind::Metadata,
    false, false, true,  false,
    //   4
    L"System.ValueType", L"",
    nullptr, nullptr, nullptr, nullptr,
    0, // Object
    0, 0, ::Windows::UI::Xaml::Interop::TypeKind::Metadata,
    false, false, false, false,
    //   5
    L"Windows.Foundation.Size", L"",
    nullptr, nullptr, nullptr, nullptr,
    -1,
    0, 0, ::Windows::UI::Xaml::Interop::TypeKind::Metadata,
    false, true,  false, false,
    //   6
    L"Windows.Foundation.TimeSpan", L"",
    nullptr, nullptr, nullptr, nullptr,
    -1,
    0, 0, ::Windows::UI::Xaml::Interop::TypeKind::Metadata,
    false, true,  false, false,
    //   7
    L"Windows.UI.Xaml.Controls.Page", L"",
    nullptr, nullptr, nullptr, nullptr,
    -1,
    0, 0, ::Windows::UI::Xaml::Interop::TypeKind::Metadata,
    false, true,  false, false,
    //   8
    L"Football_Simulator_2017.MainPage", L"",
    &ActivateType<::Football_Simulator_2017::MainPage>, nullptr, nullptr, nullptr,
    7, // Windows.UI.Xaml.Controls.Page
    0, 0, ::Windows::UI::Xaml::Interop::TypeKind::Custom,
    true,  false, false, false,
    //   9
    L"Windows.UI.Xaml.Controls.UserControl", L"",
    nullptr, nullptr, nullptr, nullptr,
    -1,
    0, 0, ::Windows::UI::Xaml::Interop::TypeKind::Metadata,
    false, true,  false, false,
    //  10
    L"Microsoft.Graphics.Canvas.CanvasDevice", L"",
    nullptr, nullptr, nullptr, nullptr,
    0, // Object
    0, 0, ::Windows::UI::Xaml::Interop::TypeKind::Metadata,
    false, false, true,  false,
    //  11
    L"Microsoft.Graphics.Canvas.UI.Xaml.CanvasAnimatedControl", L"",
    &ActivateType<::Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedControl>, nullptr, nullptr, nullptr,
    9, // Windows.UI.Xaml.Controls.UserControl
    0, 0, ::Windows::UI::Xaml::Interop::TypeKind::Metadata,
    false, false, false, false,
    //  Last type here is for padding
    L"", L"",
    nullptr, nullptr, nullptr, nullptr,
    -1, 
    13, 0,::Windows::UI::Xaml::Interop::TypeKind::Custom,
    false, false, false, false,
};

UINT TypeInfoLookup[] = { 
      0,   //   0
      0,   //   1
      0,   //   2
      0,   //   3
      0,   //   4
      0,   //   5
      0,   //   6
      2,   //   7
      3,   //   8
      3,   //   9
      3,   //  10
      3,   //  11
      3,   //  12
      3,   //  13
      3,   //  14
      3,   //  15
      3,   //  16
      5,   //  17
      5,   //  18
      5,   //  19
      5,   //  20
      5,   //  21
      5,   //  22
      5,   //  23
      6,   //  24
      6,   //  25
      6,   //  26
      6,   //  27
      7,   //  28
      7,   //  29
      8,   //  30
      8,   //  31
      8,   //  32
      9,   //  33
      9,   //  34
      9,   //  35
      9,   //  36
     10,   //  37
     10,   //  38
     11,   //  39
     11,   //  40
     11,   //  41
     11,   //  42
     11,   //  43
     11,   //  44
     11,   //  45
     11,   //  46
     11,   //  47
     11,   //  48
     11,   //  49
     11,   //  50
     11,   //  51
     11,   //  52
     11,   //  53
     11,   //  54
     11,   //  55
     12,   //  56
};

struct MemberInfo 
{
    PCWSTR shortName;
    ::Platform::Object^ (*getter)(::Platform::Object^);
    void (*setter)(::Platform::Object^, ::Platform::Object^);
    int typeIndex;
    int targetTypeIndex;
    bool isReadOnly;
    bool isDependencyProperty;
    bool isAttachable;
};

MemberInfo MemberInfos[] = 
{
    //   0 - Microsoft.Graphics.Canvas.UI.Xaml.CanvasAnimatedControl.Device
    L"Device",
    &GetReferenceTypeMember_Device<::Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedControl>,
    nullptr,
    10, // Microsoft.Graphics.Canvas.CanvasDevice
    -1,
    true,  false, false,
    //   1 - Microsoft.Graphics.Canvas.UI.Xaml.CanvasAnimatedControl.Dpi
    L"Dpi",
    &GetValueTypeMember_Dpi<::Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedControl, ::default::float32>,
    nullptr,
    1, // Single
    -1,
    true,  false, false,
    //   2 - Microsoft.Graphics.Canvas.UI.Xaml.CanvasAnimatedControl.UseSharedDevice
    L"UseSharedDevice",
    &GetValueTypeMember_UseSharedDevice<::Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedControl, ::Platform::Boolean>,
    &SetValueTypeMember_UseSharedDevice<::Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedControl, ::Platform::Boolean>,
    2, // Boolean
    -1,
    false, false, false,
    //   3 - Microsoft.Graphics.Canvas.UI.Xaml.CanvasAnimatedControl.TargetElapsedTime
    L"TargetElapsedTime",
    &GetValueTypeMember_TargetElapsedTime<::Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedControl, ::Windows::Foundation::TimeSpan>,
    &SetValueTypeMember_TargetElapsedTime<::Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedControl, ::Windows::Foundation::TimeSpan>,
    6, // Windows.Foundation.TimeSpan
    -1,
    false, false, false,
    //   4 - Microsoft.Graphics.Canvas.UI.Xaml.CanvasAnimatedControl.Paused
    L"Paused",
    &GetValueTypeMember_Paused<::Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedControl, ::Platform::Boolean>,
    &SetValueTypeMember_Paused<::Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedControl, ::Platform::Boolean>,
    2, // Boolean
    -1,
    false, false, false,
    //   5 - Microsoft.Graphics.Canvas.UI.Xaml.CanvasAnimatedControl.IsFixedTimeStep
    L"IsFixedTimeStep",
    &GetValueTypeMember_IsFixedTimeStep<::Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedControl, ::Platform::Boolean>,
    &SetValueTypeMember_IsFixedTimeStep<::Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedControl, ::Platform::Boolean>,
    2, // Boolean
    -1,
    false, false, false,
    //   6 - Microsoft.Graphics.Canvas.UI.Xaml.CanvasAnimatedControl.ForceSoftwareRenderer
    L"ForceSoftwareRenderer",
    &GetValueTypeMember_ForceSoftwareRenderer<::Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedControl, ::Platform::Boolean>,
    &SetValueTypeMember_ForceSoftwareRenderer<::Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedControl, ::Platform::Boolean>,
    2, // Boolean
    -1,
    false, false, false,
    //   7 - Microsoft.Graphics.Canvas.UI.Xaml.CanvasAnimatedControl.DpiScale
    L"DpiScale",
    &GetValueTypeMember_DpiScale<::Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedControl, ::default::float32>,
    &SetValueTypeMember_DpiScale<::Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedControl, ::default::float32>,
    1, // Single
    -1,
    false, false, false,
    //   8 - Microsoft.Graphics.Canvas.UI.Xaml.CanvasAnimatedControl.CustomDevice
    L"CustomDevice",
    &GetReferenceTypeMember_CustomDevice<::Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedControl>,
    &SetReferenceTypeMember_CustomDevice<::Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedControl, ::Microsoft::Graphics::Canvas::CanvasDevice>,
    10, // Microsoft.Graphics.Canvas.CanvasDevice
    -1,
    false, false, false,
    //   9 - Microsoft.Graphics.Canvas.UI.Xaml.CanvasAnimatedControl.ClearColor
    L"ClearColor",
    &GetValueTypeMember_ClearColor<::Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedControl, ::Windows::UI::Color>,
    &SetValueTypeMember_ClearColor<::Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedControl, ::Windows::UI::Color>,
    3, // Windows.UI.Color
    -1,
    false, false, false,
    //  10 - Microsoft.Graphics.Canvas.UI.Xaml.CanvasAnimatedControl.HasGameLoopThreadAccess
    L"HasGameLoopThreadAccess",
    &GetValueTypeMember_HasGameLoopThreadAccess<::Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedControl, ::Platform::Boolean>,
    nullptr,
    2, // Boolean
    -1,
    true,  false, false,
    //  11 - Microsoft.Graphics.Canvas.UI.Xaml.CanvasAnimatedControl.ReadyToDraw
    L"ReadyToDraw",
    &GetValueTypeMember_ReadyToDraw<::Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedControl, ::Platform::Boolean>,
    nullptr,
    2, // Boolean
    -1,
    true,  false, false,
    //  12 - Microsoft.Graphics.Canvas.UI.Xaml.CanvasAnimatedControl.Size
    L"Size",
    &GetValueTypeMember_Size<::Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedControl, ::Windows::Foundation::Size>,
    nullptr,
    5, // Windows.Foundation.Size
    -1,
    true,  false, false,
};

PCWSTR GetShortName(PCWSTR longName)
{
    PCWSTR separator = wcsrchr(longName, '.');
    return separator != nullptr ? separator + 1: longName;
}

TypeInfo* GetTypeInfo(::Platform::String^ typeName)
{
    int typeNameLength = typeName->Length();
    if (typeNameLength < _countof(TypeInfoLookup) - 1)
    {
        for (UINT i = TypeInfoLookup[typeNameLength]; i < TypeInfoLookup[typeNameLength+1]; i++)
        {
            if (typeName == ::Platform::StringReference(TypeInfos[i].typeName))
            {
                return &TypeInfos[i];
            }
        }
    }
    return nullptr;
}

MemberInfo* GetMemberInfo(::Platform::String^ longMemberName)
{
    for (int lastDotIndex = longMemberName->Length(); lastDotIndex >= 0; lastDotIndex--)
    {
        if (longMemberName->Data()[lastDotIndex] == '.')
        {
            TypeInfo* pTypeInfo = GetTypeInfo(ref new ::Platform::String(longMemberName->Data(), lastDotIndex));
            TypeInfo* pNextTypeInfo = pTypeInfo + 1;
            if (pTypeInfo)
            {
                PCWSTR shortMemberName = GetShortName(longMemberName->Data());
                for (int i = pTypeInfo->firstMemberIndex; i < pNextTypeInfo->firstMemberIndex; i++)
                {
                    if (wcscmp(shortMemberName, MemberInfos[i].shortName) == 0)
                    {
                        return &MemberInfos[i];
                    }
                }
            }
            break;
        }
    }
    return nullptr;
}

::Platform::Collections::Vector<::Windows::UI::Xaml::Markup::IXamlMetadataProvider^>^ ::XamlTypeInfo::InfoProvider::XamlTypeInfoProvider::OtherProviders::get()
{
    if(_otherProviders == nullptr)
    {
        auto otherProviders = ref new ::Platform::Collections::Vector<::Windows::UI::Xaml::Markup::IXamlMetadataProvider^>();
        _otherProviders = otherProviders;
    }
    return _otherProviders;
}

::Windows::UI::Xaml::Markup::IXamlType^ ::XamlTypeInfo::InfoProvider::XamlTypeInfoProvider::CreateXamlType(::Platform::String^ typeName)
{
    TypeInfo* pTypeInfo = GetTypeInfo(typeName);
    TypeInfo* pNextTypeInfo = pTypeInfo + 1;
    if (pTypeInfo == nullptr || pNextTypeInfo == nullptr)
    {
        return nullptr;
    }
    else if (pTypeInfo->isSystemType)
    {
        return ref new ::XamlTypeInfo::InfoProvider::XamlSystemBaseType(typeName);
    }
    else
    {
        ::XamlTypeInfo::InfoProvider::XamlUserType^ userType = ref new ::XamlTypeInfo::InfoProvider::XamlUserType(
            this, 
            ::Platform::StringReference(pTypeInfo->typeName), 
            this->GetXamlTypeByName(::Platform::StringReference(pTypeInfo->baseTypeIndex >= 0 ? TypeInfos[pTypeInfo->baseTypeIndex].typeName : L"")));
        userType->KindOfType = pTypeInfo->kindofType;
        userType->Activator = pTypeInfo->activator;
        userType->CollectionAdd = pTypeInfo->collectionAdd;
        userType->DictionaryAdd = pTypeInfo->dictionaryAdd;
        userType->FromStringConverter = pTypeInfo->fromStringConverter;
        userType->ContentPropertyName = ::Platform::StringReference(pTypeInfo->contentPropertyName);
        userType->IsLocalType = pTypeInfo->isLocalType;
        userType->IsReturnTypeStub = pTypeInfo->isReturnTypeStub;
        userType->IsBindable = pTypeInfo->isBindable;
        int nextMemberIndex = pTypeInfo->firstMemberIndex;
        for (int i=pTypeInfo->firstMemberIndex; i < pNextTypeInfo->firstMemberIndex; i++)
        {
            userType->AddMemberName(::Platform::StringReference(MemberInfos[i].shortName));
            nextMemberIndex++;
        }
        return userType;
    }
}

::Windows::UI::Xaml::Markup::IXamlMember^ ::XamlTypeInfo::InfoProvider::XamlTypeInfoProvider::CreateXamlMember(::Platform::String^ longMemberName)
{
    ::XamlTypeInfo::InfoProvider::XamlMember^ xamlMember = nullptr;
    MemberInfo* pMemberInfo = GetMemberInfo(longMemberName);
    if (pMemberInfo != nullptr)
    {
        xamlMember = ref new ::XamlTypeInfo::InfoProvider::XamlMember(
            this,
            ::Platform::StringReference(pMemberInfo->shortName),
            ::Platform::StringReference(TypeInfos[pMemberInfo->typeIndex].typeName));
        xamlMember->Getter = pMemberInfo->getter;
        xamlMember->Setter = pMemberInfo->setter;
        xamlMember->TargetTypeName = pMemberInfo->targetTypeIndex >= 0 ? ::Platform::StringReference(TypeInfos[pMemberInfo->targetTypeIndex].typeName) : L"";
        xamlMember->IsReadOnly = pMemberInfo->isReadOnly;
        xamlMember->IsDependencyProperty = pMemberInfo->isDependencyProperty;
        xamlMember->IsAttachable = pMemberInfo->isAttachable;
    }
    return xamlMember;
}

