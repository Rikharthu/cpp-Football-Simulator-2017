﻿//------------------------------------------------------------------------------
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
//------------------------------------------------------------------------------
#include "pch.h"

#if defined _DEBUG && !defined DISABLE_XAML_GENERATED_BINDING_DEBUG_OUTPUT
extern "C" __declspec(dllimport) int __stdcall IsDebuggerPresent();
#endif

#include "MainPage.xaml.h"

void ::Football_Simulator_2017::MainPage::InitializeComponent()
{
    if (_contentLoaded)
    {
        return;
    }
    _contentLoaded = true;
    ::Windows::Foundation::Uri^ resourceLocator = ref new ::Windows::Foundation::Uri(L"ms-appx:///MainPage.xaml");
    ::Windows::UI::Xaml::Application::LoadComponent(this, resourceLocator, ::Windows::UI::Xaml::Controls::Primitives::ComponentResourceLocation::Application);
}

void ::Football_Simulator_2017::MainPage::Connect(int __connectionId, ::Platform::Object^ __target)
{
    switch (__connectionId)
    {
        case 1:
            {
                this->mediaPlayer = safe_cast<::Windows::UI::Xaml::Controls::MediaElement^>(__target);
                (safe_cast<::Windows::UI::Xaml::Controls::MediaElement^>(this->mediaPlayer))->Loaded += ref new ::Windows::UI::Xaml::RoutedEventHandler(this, (void (::Football_Simulator_2017::MainPage::*)
                    (::Platform::Object^, ::Windows::UI::Xaml::RoutedEventArgs^))&MainPage::mediaPlayer_Loaded);
            }
            break;
        case 2:
            {
                this->canvasAnimated = safe_cast<::Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedControl^>(__target);
                (safe_cast<::Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedControl^>(this->canvasAnimated))->Draw += ref new ::Windows::Foundation::TypedEventHandler<::Microsoft::Graphics::Canvas::UI::Xaml::ICanvasAnimatedControl^, ::Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedDrawEventArgs^>(this, (void (::Football_Simulator_2017::MainPage::*)
                    (::Microsoft::Graphics::Canvas::UI::Xaml::ICanvasAnimatedControl^, ::Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedDrawEventArgs^))&MainPage::canvas_DrawAnimated);
                (safe_cast<::Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedControl^>(this->canvasAnimated))->Loaded += ref new ::Windows::UI::Xaml::RoutedEventHandler(this, (void (::Football_Simulator_2017::MainPage::*)
                    (::Platform::Object^, ::Windows::UI::Xaml::RoutedEventArgs^))&MainPage::canvas_Loaded);
                (safe_cast<::Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedControl^>(this->canvasAnimated))->CreateResources += ref new ::Windows::Foundation::TypedEventHandler<::Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedControl^, ::Microsoft::Graphics::Canvas::UI::CanvasCreateResourcesEventArgs^>(this, (void (::Football_Simulator_2017::MainPage::*)
                    (::Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedControl^, ::Microsoft::Graphics::Canvas::UI::CanvasCreateResourcesEventArgs^))&MainPage::canvas_CreateResources);
                (safe_cast<::Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedControl^>(this->canvasAnimated))->PointerPressed += ref new ::Windows::UI::Xaml::Input::PointerEventHandler(this, (void (::Football_Simulator_2017::MainPage::*)
                    (::Platform::Object^, ::Windows::UI::Xaml::Input::PointerRoutedEventArgs^))&MainPage::canvas_PointerPressed);
            }
            break;
        case 3:
            {
                ::Windows::UI::Xaml::Controls::Slider^ element3 = safe_cast<::Windows::UI::Xaml::Controls::Slider^>(__target);
                (safe_cast<::Windows::UI::Xaml::Controls::Slider^>(element3))->ValueChanged += ref new ::Windows::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventHandler(this, (void (::Football_Simulator_2017::MainPage::*)
                    (::Platform::Object^, ::Windows::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs^))&MainPage::speedSlider_ValueChanged);
            }
            break;
        case 4:
            {
                this->startStopBtn = safe_cast<::Windows::UI::Xaml::Controls::Button^>(__target);
                (safe_cast<::Windows::UI::Xaml::Controls::Button^>(this->startStopBtn))->Click += ref new ::Windows::UI::Xaml::RoutedEventHandler(this, (void (::Football_Simulator_2017::MainPage::*)
                    (::Platform::Object^, ::Windows::UI::Xaml::RoutedEventArgs^))&MainPage::startStopBtn_Click);
            }
            break;
        case 5:
            {
                this->startStopToggleBtn = safe_cast<::Windows::UI::Xaml::Controls::Primitives::ToggleButton^>(__target);
                (safe_cast<::Windows::UI::Xaml::Controls::Primitives::ToggleButton^>(this->startStopToggleBtn))->Click += ref new ::Windows::UI::Xaml::RoutedEventHandler(this, (void (::Football_Simulator_2017::MainPage::*)
                    (::Platform::Object^, ::Windows::UI::Xaml::RoutedEventArgs^))&MainPage::startStopToggleBtn_Click);
            }
            break;
        case 6:
            {
                this->playersEnabledLabel2 = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(__target);
                (safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(this->playersEnabledLabel2))->Tapped += ref new ::Windows::UI::Xaml::Input::TappedEventHandler(this, (void (::Football_Simulator_2017::MainPage::*)
                    (::Platform::Object^, ::Windows::UI::Xaml::Input::TappedRoutedEventArgs^))&MainPage::playersEnabledLabel2_Tapped);
            }
            break;
    }
    _contentLoaded = true;
}

::Windows::UI::Xaml::Markup::IComponentConnector^ ::Football_Simulator_2017::MainPage::GetBindingConnector(int __connectionId, ::Platform::Object^ __target)
{
    __connectionId;         // unreferenced
    __target;               // unreferenced
    return nullptr;
}


