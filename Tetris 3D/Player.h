#pragma once

class Player
{

private:

	//Player information

	int level = 0;
	int score = 0;
	std::string name = "basicplayer";


public:

	
	bool paused = false;
	bool loser = false;

	Player() {}
	~Player() {}

	void SetName(std::string n)
	{
		name = n;
	}
	std::string GetName()
	{
		return name;
	}

	//Function that updates the player's score when he eliminates a complete block level
	void UpdateScore(int total)
	{
		score += total*(level+1);
		level = score / 1000;
	}

	//Return level and score values
	int GetLevel() { return level; }
	int GetScore() { return score; }

};