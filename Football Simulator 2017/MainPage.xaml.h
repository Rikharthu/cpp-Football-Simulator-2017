//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace Football_Simulator_2017
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();

	private:
		void canvas_DrawAnimated(Microsoft::Graphics::Canvas::UI::Xaml::ICanvasAnimatedControl^ sender, Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedDrawEventArgs^ args);
		void canvas_Loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void canvas_CreateResources(Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedControl^ sender, Microsoft::Graphics::Canvas::UI::CanvasCreateResourcesEventArgs^ args);

		void canvas_PointerPressed(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
		void speedSlider_ValueChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs^ e);
		void startStopBtn_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);

		bool isStarted = false;
		void startStopToggleBtn_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void playersEnabledLabel2_Tapped(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e);

		void playSound();
		void mediaPlayer_Loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
