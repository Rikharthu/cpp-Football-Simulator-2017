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
#include "Drawable.h"
#include "Human.h"

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
IRandomAccessStreamWithContentType ^ audioStream;

MediaElement ^ element;

MainPage::MainPage()
{
	InitializeComponent();
}

void Football_Simulator_2017::MainPage::playSound(Sound sound)
{
	String^sound_file_name;
	switch (sound) {
	case Kick1:
		sound_file_name = "Kick1.wav";
		break;
	case Kick2:
		sound_file_name = "Kick2.wav";
		break;
	case Kick3:
		sound_file_name = "Kick3.wav";
		break;
	case Mencheer:
		sound_file_name = "mencheer.wav";
		break;
	case SuccessTada:
		sound_file_name = "successtada.wav";
		break;
	case Whistle:
		sound_file_name = "whistle.wav";
		break;
	default:
		return;
	}
	sound_file_name = "ms-appx:///Assets/" + sound_file_name;
	Uri ^fileUri = ref new Uri(sound_file_name);

	auto getSoundFileOperation = StorageFile::GetFileFromApplicationUriAsync(fileUri);
	// convert IAsyncOperation to task
	auto getSoundFileTask = concurrency::create_task(getSoundFileOperation);
	// write a lambda function that will execute when task finishes
	getSoundFileTask.then([](StorageFile ^ sfile) {
		auto openFileReadOperation = sfile->OpenReadAsync();
		auto openFileReadTask = concurrency::create_task(openFileReadOperation);
		openFileReadTask.then([](IRandomAccessStreamWithContentType ^ sstream) {
			/*element->SetSource(sstream, "audio/x-ms-wma");
			element->Play();*/
			CoreApplication::MainView->CoreWindow->Dispatcher->RunAsync(
				Core::CoreDispatcherPriority::Normal,
				ref new Windows::UI::Core::DispatchedHandler([sstream]()
			{
				// lazy init
				/*if (audioStream == nullptr) {
				audioStream = sstream;
				}*/
				element->SetSource(sstream, "audio/x-ms-wma");
				element->Play();
			}));
		});
	});
}

void Football_Simulator_2017::MainPage::canvas_DrawAnimated(Microsoft::Graphics::Canvas::UI::Xaml::ICanvasAnimatedControl^ sender, Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedDrawEventArgs^ args)
{
	gameManager->ball->moveTo(random(600), random(600));
	int x, y;
	gameManager->ball->getCoord(x, y);
	if (gameManager->field->isGoalLeft(x, y)) {
		playSound(Sound::SuccessTada);
	}
	gameManager->render();
	// static content (field is pre-drawn on this command list)
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
	//gameManager->field->drawLines();
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

	//playSound();

	//TODO debug
	//gameManager->render();

	playSound(Sound::Kick1);
}

void Football_Simulator_2017::MainPage::mediaPlayer_Loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	element = static_cast<MediaElement^>(sender);
}

void MainView::playSound(Sound sound) {
	//playSound(sound);
}

//TODO make use of only one listener through the use of regex (PlayerXTeamY)

void Football_Simulator_2017::MainPage::playersEnabledLabel2_Tapped(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e)
{
	// TODO change both 2nd player's checkboxes state and call according events if needed
	/*EnablePlayer2Team1_CheckBox->IsChecked = !EnablePlayer2Team1_CheckBox->IsChecked;
	EnablePlayer2Team2_CheckBox->IsChecked = !EnablePlayer2Team2_CheckBox->IsChecked;*/
}

///<summary>
/// Retrieves checkox tag, which is int32 type "XY", where X -is team number and Y- player number
///</summary>
void Football_Simulator_2017::MainPage::EnablePlayerXTeamY_CheckBox_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	CheckBox ^ chkbx = static_cast<CheckBox^>(sender);
	auto chkbx_tag = chkbx->Tag;
	int player_id = safe_cast<int32>(chkbx_tag);
	int team_number = player_id / 10;
	int player_number = player_id % 10;

	//TODO send player to workbench/release
}
