#include "pch.h"
#include "Player.h"
#include "GameManager.h"
#include "Utils.h"

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
	gameManager->render_target_session->DrawText(No.ToString(), x, y - r, Colors::Black);
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
		energy -= 5;
		energy = energy > 0 ? energy : 0;
		//TODO since energy is not implemented - reuse it
		speed = 5 + rand() % ((energy / 500) + 1);
		speed = 5 + rand() % 5;

		dir = direction(x, y, xd, yd);
		//TODO control precision here
		dir = disperse(dir, PI / 6);

		//TODO check how it works
		x += speed*cos(dir);
		y -= speed*sin(dir);

		avoidCollision();

		// if in reach of ball kick
		if (distance(x, y, xb, yb) < close)kick();
	}
}

void Player::kick()
{
	if (gameManager->ball->immune_counter <= 0) {
		gameManager->ball->immune_counter = 5;

		int xb, yb, xc, yc, xd, yd, speedb;
		gameManager->ball->getCoord(xb, yb);
		gameManager->field->getCentre(xc, yc);
		yd = yc;
		// depending on team, choose where to kick the ball
		if (teamNo == 1)  xd = gameManager->field->fieldRect->Right;
		else            xd = gameManager->field->fieldRect->Left;

		speedb = disperse(30, 10);
		//TODO refactor to reuse
		bool ownSide = (teamNo == 1 && x < xc) || (teamNo == 2 && x > xc);

		Point p = partner();
		if (p.X >= 0) { // is partner?
			int speedp = sqrt(2 * distance(x, y, p.X, p.Y) + 0.25) - 0.5;

			// if partner is closer to the enemy's gates then дать ему пас
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
		gameManager->ball->setSpeed(speedb*2);

		gameManager->sound_queue.push(Kick2);

		// register as last kicked player
		gameManager->last_kick_player = No;
		gameManager->last_kick_team = teamNo;
	}
}

void Player::avoidCollision()
{
	//TODO implement later
	//int limit = r;
	//int pos_count = gameManager->team1.size() + gameManager->team2.size();
	//Point * occupied_positions = new Point[pos_count];

	//int j = 0;
	//for (Player * player : gameManager->team1) {
	//	if (player != this && player->inGame) {
	//		occupied_positions[j].X = player->x;
	//		occupied_positions[j].Y = player->y;
	//	}
	//	// such a difference
	//	j++;
	//}
	//// repeat for team2
	//for (Player * player : gameManager->team2) {
	//	if (player != this && player->inGame) {
	//		occupied_positions[j].X = player->x;
	//		occupied_positions[j].Y = player->y;
	//	}
	//	j++;
	//}
	//occupied_positions[j].X = this->x;
	//occupied_positions[j].Y = this->y;

	//int attempts = 10000;
	//bool is_too_close;
	//int xa = x, ya = y, speeda = speed;
	//double dira = dir;
	//int dist;
	//pos_count = j + 1;
	//do {
	//	for (int i = 0; i < pos_count; i++) {
	//		// current player is too close to other players
	//		is_too_close = distance(xa, ya, occupied_positions[i].X, occupied_positions[i].Y) < limit;
	//		if (is_too_close) {
	//			--attempts;
	//			dist = distance(xa, ya, occupied_positions[i].X, occupied_positions[i].Y);
	//			speeda = speeda + dist - limit;//disperse(speed, lim);
	//			dira = disperse(dir,PI / 12);
	//			xa = x + (double)speeda*cos(dira);
	//			ya = y - (double)speeda*sin(dira);
	//			break;
	//		}
	//	}
	//} while (is_too_close && attempts > 0);
	//x = xa;
	//y = ya;
	//speed = speeda;
	//dir = dira;
	//delete occupied_positions;
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
