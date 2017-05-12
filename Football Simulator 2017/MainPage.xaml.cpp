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
#include <locale>
#include <codecvt>
#include <string>
#include <sstream>

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
bool isDebugEnabled = false;
bool isStarted = false;
MediaElement ^ element;
long long original_duration;

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

// DRAWING
void Football_Simulator_2017::MainPage::canvas_DrawAnimated(Microsoft::Graphics::Canvas::UI::Xaml::ICanvasAnimatedControl^ sender, Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedDrawEventArgs^ args)
{
	gameManager->render();
	syncUI();
	// static content (field is pre-drawn on this command list)
	args->DrawingSession->DrawImage(gameManager->field_cl);
	// dynamic content (ball, players, etc)
	args->DrawingSession->DrawImage(gameManager->render_target);
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
	original_duration = gameManager->canvas->TargetElapsedTime.Duration;
	gameManager->init();

	gameManager->field->draw();
	//gameManager->field->drawLines();
}

// for testing
void Football_Simulator_2017::MainPage::canvas_PointerPressed(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
//#ifdef _DEBUG
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
	if (isDebugEnabled) {
		gameManager->ball->moveTo(x, y);
	}
//#endif // _DEBUG
}

void Football_Simulator_2017::MainPage::startStopBtn_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{

}


void Football_Simulator_2017::MainPage::startStopToggleBtn_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (!isStarted) {
		// first start
		isStarted = true;
		gameManager->startGame();
	}
	else {
		if (gameManager->gameState == sStop) {
			gameManager->gameState = sRunning;
			startStopToggleBtn->Content = "Stop";
		}
		else {
			gameManager->gameState = sStop;
			startStopToggleBtn->Content = "Start";
		}
	}
}

void Football_Simulator_2017::MainPage::mediaPlayer_Loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	element = static_cast<MediaElement^>(sender);
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
	Player * selectedPlayer = team_number == 1 ?
		gameManager->team1.at(player_number - 1)
		: gameManager->team2.at(player_number - 1);

	selectedPlayer->inGame = !selectedPlayer->inGame;
}


void Football_Simulator_2017::MainPage::debug_btn_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	gameManager->moveAll();
	//log_chat_message("Referee", "Player 1 disqualified");
}


void Football_Simulator_2017::MainPage::debug_enabled_chkbx_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	isDebugEnabled = debug_enabled_chkbx->IsChecked->Value;
}

void Football_Simulator_2017::MainPage::log_chat_message(string tag, string message)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	std::wstring intermediateForm = converter.from_bytes(tag + ": " + message);
	Platform::String^ retVal = ref new Platform::String(intermediateForm.c_str());
	//log_TextBlock->Text = log_TextBlock->Text+retVal +"\n";
}


void Football_Simulator_2017::MainPage::Page_Unloaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	canvasAnimated->RemoveFromVisualTree();
	delete gameManager;
	delete canvasAnimated;
}

// uses polling approach
void Football_Simulator_2017::MainPage::syncUI()
{
	CoreApplication::MainView->CoreWindow->Dispatcher->RunAsync(
		Core::CoreDispatcherPriority::Normal,
		ref new Windows::UI::Core::DispatchedHandler([this]()
	{
		gameManager->calculateEnergy();
		// sync ui with gamemanager's parameters such as energy, score and etc
		Team1Energy_ProgressBar->Value = gameManager->team1_energy;
		Team2Energy_ProgressBar->Value = gameManager->team2_energy;

		Team1Score_TextBlock->Text = gameManager->team1_score.ToString();
		Team2Score_TextBlock->Text = gameManager->team2_score.ToString();

		// last kick and message
		char &lt = gameManager->last_kick_team;
		char &lp = gameManager->last_kick_player;
		if (lt != -1 && lp != -1) {
			KickInfo_TextBlock->Text = "Team " + lt.ToString()
				+ ", Player #" + lp.ToString();
		}
		// game comment
		state & current_state = gameManager->gameState;
		switch (current_state) {
		case sGoal:
			Comment_TextBlock->Text = "Team #"+gameManager->last_kick_team.ToString()+" Scored!";
			break;
		case sStop:
			Comment_TextBlock->Text = "Stopped";
			break;
		case sFirstKick:
		case sRestartGame:
		case sRunning:
			Comment_TextBlock->Text = "In Progress";
			break;
		}

		element->IsLooping = gameManager->isLoopSound;

		// play enqueued sounds
		while (!gameManager->sound_queue.empty()) {
			try {
				if (sound_enabled_chkbx->IsChecked->Value) {
					playSound(gameManager->sound_queue.front());
				}
				gameManager->sound_queue.pop();
			}
			catch (...) {

			}
		}
	}));
}

// we use canvas as tick source
void Football_Simulator_2017::MainPage::canvasAnimated_Update(Microsoft::Graphics::Canvas::UI::Xaml::ICanvasAnimatedControl^ sender, Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedUpdateEventArgs^ args)
{
	if (gameManager->gameState != sStop) {
		gameManager->tick();
	}
}

void Football_Simulator_2017::MainPage::ComboBox_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e)
{
	if (canvasAnimated != nullptr) {
		ComboBox ^ cmb = safe_cast<ComboBox^>(sender);
		int selected_index = cmb->SelectedIndex;
		double multiplier = 1;
		switch (selected_index) {
		case 0:
			//25%
			multiplier = 0.25f;
			break;
		case 1:
			//50%	
			multiplier = 0.25f;
			break;
		case 2:
			// 75%
			multiplier = 0.75f;
			break;
		case 3:
			// 100%
			multiplier = 1;
			break;
		case 4:
			// 125%
			multiplier = 1.25f;
			break;
		case 5:
			// 150%
			multiplier = 1.5f;
			break;
		case 6:
			// 200%
			multiplier = 2;
			break;
		case 7:
			// 300%
			multiplier = 3;
			break;
		case 8:
			// 500%
			multiplier = 5;
			break;
		case 9:
			// 1000%
			multiplier = 10;
			break;
		}

		TimeSpan canvas_upd_timespan = canvasAnimated->TargetElapsedTime;
		canvas_upd_timespan.Duration = original_duration / multiplier;
		canvasAnimated->TargetElapsedTime = canvas_upd_timespan;
	}
}


void Football_Simulator_2017::MainPage::girls_enabled_chkbx_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	bool isEnabled = girls_enabled_chkbx->IsChecked->Value;
	gameManager->isGirlsAllowed = isEnabled;
}


void Football_Simulator_2017::MainPage::Comment_TextBlock_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{

}


void Football_Simulator_2017::MainPage::onAddEnergyButtonClicked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int team_number = safe_cast<int32>(static_cast<Button^>(sender)->Tag);
	gameManager->addEnergy(team_number, 200);
}
