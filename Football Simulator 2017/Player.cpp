#include "pch.h"
#include "Player.h"
#include "GameManager.h"
#include "Utils.h"

extern GameManager * gameManager;

Player::Player(int t, int n)
{
	teamNo = t;
	No = n;
	color = t == 1 ? Colors::Blue : Colors::Red;
	speed = 0;
	sound = 0;
	/*font = new TFont;
	font->Name = "Courier New";
	font->Height = 2 * r + 1;*/
	inGame = true;
}

void Player::draw()
{
	Human::draw();
	CanvasDrawingSession ^ session = gameManager->render_target->CreateDrawingSession();
	//TODO or draw right inside ?
	session->DrawText(No.ToString(), x, y - r, Colors::Black);
	delete session;

	//TODO implement
	/*switch (sound) {
	case 0: break;
	case 1: FG_Frm->sound("kick1.wav", SND_ASYNC); break;
	case 2: FG_Frm->sound("kick2.wav", SND_ASYNC); break;
	case 3: FG_Frm->sound("kick3.wav", SND_ASYNC); break;
	};
	if (sound) {
		FG_Frm->CommentText->Caption = "Team " + IntToStr(teamNo) +
			", No. " + IntToStr(No);
	}*/
	sound = 0;
}

void Player::move()
{
	if (!inGame) {
		moveToBench();
	}
	else {
		int close = 2 * r + 2;
		int xc, yc, xb, yb, xd, yd;
		gameManager->field->getCentre(xc, yc);
		gameManager->ball->getCoord(xb, yb);
		// direction to ball
		xd = xb; yd = yb;
		// player is on his team's side of the field
		bool ownSide = (teamNo == 1 && x < xc) || (teamNo == 2 && x > xc);
		energy = energy > 0 ? --energy : 0;
		//TODO check it and adjust
		speed = 5 + rand() % (energy / 1000);

		dir = direction(x, y, xd, yd);
		dir = disperse(dir, PI / 12);

		//TODO check how it works
		x += speed*cos(dir);
		y -= speed*sin(dir);

		// if in reach of ball kick
		if (distance(x, y, xb, yb) < close)kick();
	}
}

void Player::kick()
{
	int xb, yb, xc, yc, xd, yd, speedb;
	gameManager->ball->getCoord(xb, yb);
	gameManager->field->getCentre(xc, yc);
	yd = yc;
	// depending on team, choose where to kick the ball
	if (teamNo == 1)  xd = gameManager->field->fieldRect->Right;
	else            xd = gameManager->field->fieldRect->Left;

	speedb = disperse(20, 10);
	//TODO refactor to reuse
	bool ownSide = (teamNo == 1 && x < xc) || (teamNo == 2 && x > xc);

	Point p = partner();
	if (p.X >= 0) { // is partner?
		int speedp = sqrt(2 * distance(x, y, p.X, p.Y) + 0.25) - 0.5;

		if ((teamNo == 1 && p.X > x + 10) || (teamNo == 2 && p.X < x - 10)) {
			xd = p.X; yd = p.Y;
			speedb = speedp + disperse(10, 5);
		}

		if (gameManager->gameState == sFirstKick) {
			xd = p.X;
			yd = p.Y;
			speedb = speedp + disperse(10, 3);
			gameManager->gameState = sRunning;
		}
	}

	double ball_direction;
	ball_direction = direction(xb, yb, xd, yd);
	ball_direction = disperse(ball_direction, PI / 24);
	//TODO adjust direction and speed if needed
	gameManager->ball->setDir(ball_direction);
	gameManager->ball->setSpeed(speedb);
	//TODO Kick sound = Kick2.wav, better use Sound enum
	sound = 2;
}

void Player::avoidCollision()
{
	//TODO implement later
}

void Player::moveToBench()
{
	int xc, yc;
	gameManager->field->getCentre(xc, yc);
	int bench_position_y = gameManager->field->fieldRect->Top - gameManager->field->getBorderW() + r;
	if (teamNo == 1) {
		moveTo(xc - 20 - No * 3 * r, bench_position_y);
	}
	else {
		// team 2
		moveTo(xc + 20 + No * 3 * r, bench_position_y);
	}
}

Point & Player::partner()
{
	int distances[7];
	Point p[6];
	int n = 0;

	std::vector<Player*> currentTeam = teamNo == 1 ? gameManager->team1 : gameManager->team2;
	for (Player * player : currentTeam) {
		if (this == player || !player->inGame || player->type == tGoalKeeper) continue;
		p[n].X = player->x;
		p[n].Y = player->y;
		++n;
	}

	if (n == 0) {
		// no partners (everyone's resting at the bench / is a goalkeeper)
		p[0].X = -1;
		return p[0];
	}
	int tmp_distance, min_distance = distance(x, y, p[0].X, p[0].Y);
	// assume player #0 is closest to us
	int player_number = 0;
	for (int i = 0; i < n; i++) {
		tmp_distance = distance(x, y, p[i].X, p[i].Y);
		if (tmp_distance < min_distance) {
			min_distance = tmp_distance;
			player_number = i;
		}
	}

	return p[player_number];
}
