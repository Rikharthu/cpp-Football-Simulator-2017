//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include "GameManager.h"
#include "Field.h"
#include "Utils.h"
#include "Ball.h"

using namespace Football_Simulator_2017;

using namespace Windows::UI;
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Microsoft::Graphics::Canvas::UI::Xaml;
using namespace Windows::Storage;
using namespace Windows::Storage::Streams;
using namespace Windows::ApplicationModel::Core;

int width, height;

Field * field;
CanvasCommandList^ field_cl;

extern GameManager * gameManager;
GameManager * gameManager;

MediaElement ^ element;

MainPage::MainPage()
{
	InitializeComponent();
}


void Football_Simulator_2017::MainPage::playSound() {
	auto fileUri = ref new Uri("ms-appx:///Assets/successtada.wav");
	auto file = StorageFile::GetFileFromApplicationUriAsync(fileUri);
	auto fileTask = concurrency::create_task(file);
	fileTask.then([](StorageFile ^ sfile) {
		int x = 4;
		auto stream = sfile->OpenReadAsync();
		auto streamTask = concurrency::create_task(stream);
		streamTask.then([](IRandomAccessStreamWithContentType ^ sstream) {
			/*element->SetSource(sstream, "audio/x-ms-wma");
			element->Play();*/
			CoreApplication::MainView->CoreWindow->Dispatcher->RunAsync(
				Core::CoreDispatcherPriority::Normal,
				ref new Windows::UI::Core::DispatchedHandler([sstream]()
			{
				element->SetSource(sstream, "audio/x-ms-wma");
				element->Play();
			}));
		});

	});
}

void Football_Simulator_2017::MainPage::canvas_DrawAnimated(Microsoft::Graphics::Canvas::UI::Xaml::ICanvasAnimatedControl^ sender, Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedDrawEventArgs^ args)
{
	Ball ball;
	ball.moveTo(random(600), random(600));
	ball.draw();
	// static content (field)
	args->DrawingSession->DrawImage(gameManager->field_cl);
	// dynamic content (ball, players, etc)
	args->DrawingSession->DrawImage(gameManager->render_target);
	// TODO test
	args->DrawingSession->DrawText("asdasd", random(0, 500), random(0, 500), Colors::Red);
}


void Football_Simulator_2017::MainPage::canvas_Loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	//gameManager->canvas = safe_cast<CanvasAnimatedControl^>(sender);
}


void Football_Simulator_2017::MainPage::canvas_CreateResources(Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedControl^ sender, Microsoft::Graphics::Canvas::UI::CanvasCreateResourcesEventArgs^ args)
{
	field_cl = ref new CanvasCommandList(sender);
	gameManager = new GameManager(field_cl);
	gameManager->canvas = safe_cast<CanvasAnimatedControl^>(sender);
	gameManager->init();

	gameManager->field->draw();
	gameManager->field->drawLines();

}

// for testing
void Football_Simulator_2017::MainPage::canvas_PointerPressed(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
#ifdef _DEBUG
	int x = e->GetCurrentPoint(canvasAnimated)->Position.X;
	int y = e->GetCurrentPoint(canvasAnimated)->Position.Y;
	bool isInside = gameManager->field->isInside(x, y);
	bool isOutLeft = gameManager->field->isOutLeft(x, y);
	bool isOutRight = gameManager->field->isOutRight(x, y);
	bool isGoalLeft = gameManager->field->isGoalLeft(x, y);
	bool isGoalRight = gameManager->field->isGoalRight(x, y);
	char*str = new char[256];
	sprintf(str, "x:%d, y:%d\nisInside=%d\nisOutLeft=%d\nisOutRight=%d\nisGoalLeft=%d\nisGoalRight=%d\n",
		x, y, isInside, isOutLeft, isOutRight, isGoalLeft, isGoalRight);
	OutputDebugStringA(str);
#endif // _DEBUG
}

void Football_Simulator_2017::MainPage::speedSlider_ValueChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs^ e)
{
	Slider ^ speedSlider = safe_cast<Slider^>(sender);
	double newValue = speedSlider->Value;
	// TODO use this value
	double speedMultiplier = newValue / 100;
}


void Football_Simulator_2017::MainPage::startStopBtn_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{

}


void Football_Simulator_2017::MainPage::startStopToggleBtn_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	// TODO use game manager
	isStarted = !isStarted;

	if (isStarted) {
		// start
		startStopToggleBtn->Content = "Stop";
	}
	else {
		// stop
		startStopToggleBtn->Content = "Start";
	}

	playSound();
}

void Football_Simulator_2017::MainPage::playersEnabledLabel2_Tapped(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e)
{
	// TODO change both 2nd player's checkboxes state and call according events if needed
}


void Football_Simulator_2017::MainPage::mediaPlayer_Loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	element = safe_cast<MediaElement^>(sender);
}
