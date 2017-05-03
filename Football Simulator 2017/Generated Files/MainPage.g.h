﻿#pragma once
//------------------------------------------------------------------------------
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
//------------------------------------------------------------------------------


namespace Windows {
    namespace UI {
        namespace Xaml {
            namespace Controls {
                ref class MediaElement;
                ref class Button;
                ref class CheckBox;
                ref class TextBlock;
            }
        }
    }
}
namespace Microsoft {
    namespace Graphics {
        namespace Canvas {
            namespace UI {
                namespace Xaml {
                    ref class CanvasAnimatedControl;
                }
            }
        }
    }
}
namespace Windows {
    namespace UI {
        namespace Xaml {
            namespace Controls {
                namespace Primitives {
                    ref class ToggleButton;
                }
            }
        }
    }
}

namespace Football_Simulator_2017
{
    [::Windows::Foundation::Metadata::WebHostHidden]
    partial ref class MainPage : public ::Windows::UI::Xaml::Controls::Page, 
        public ::Windows::UI::Xaml::Markup::IComponentConnector,
        public ::Windows::UI::Xaml::Markup::IComponentConnector2
    {
    public:
        void InitializeComponent();
        virtual void Connect(int connectionId, ::Platform::Object^ target);
        virtual ::Windows::UI::Xaml::Markup::IComponentConnector^ GetBindingConnector(int connectionId, ::Platform::Object^ target);
    
    private:
        bool _contentLoaded;
    
        private: ::Windows::UI::Xaml::Controls::MediaElement^ mediaPlayer;
        private: ::Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedControl^ canvasAnimated;
        private: ::Windows::UI::Xaml::Controls::Button^ startStopBtn;
        private: ::Windows::UI::Xaml::Controls::Primitives::ToggleButton^ startStopToggleBtn;
        private: ::Windows::UI::Xaml::Controls::CheckBox^ EnablePlayer2Team1_CheckBox;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ playersEnabledLabel2;
        private: ::Windows::UI::Xaml::Controls::CheckBox^ EnablePlayer2Team2_CheckBox;
    };
}

