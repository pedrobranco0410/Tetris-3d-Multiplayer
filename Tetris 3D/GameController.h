//OpenGL Libs
#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include <time.h>




class GameController
{
	protected: 
	
		//Creating the player;
		Player player = Player();
		
		//screen where the cube will be drawn
		GLfloat width, height;

		//Board where the game pieces are and will be drawn
		Board board;

		bool dimension = true;

	public:

		//Constructor and Destructors
		GameController() {}
		GameController(GLfloat width_, GLfloat height_, std::string name, bool dimension3) 
		{
			
			player.SetName(name);
			width = width_;
			height = height_;
			dimension = dimension3;		
			board = Board(width / 2.7, height * 0.2, -650, width, height, 50, dimension);
			
		}
		~GameController() {}

		void UpdateWindow(GLfloat width_, GLfloat height_)
		{
			width = width_;
			height = height_;
			board.UpdateBoard(width / 2.7, height * 0.2, -650, width, height, 50);
		}

		bool CheckEnd()
		{
			
			return board.CheckEnd();
		}

		void DrawGameOver(Writer* writer)
		{
			writer->addText(Text("Final Level : " + std::to_string(player.GetLevel()), width * 0.4, height * 0.6, (float)width / 1500, 1, 1, 1));
			writer->addText(Text("Final Score : " + std::to_string(player.GetScore()), width * 0.4, height * 0.5, (float)width / 1500, 1, 1, 1));
		}

		void DrawGame(Writer *writer)
		{
					
			board.DrawNext();
			board.Play(&player);
			DrawInstructions(writer);

			writer->addText(Text(player.GetName(), width * 0.03, height * 0.9, (float)width / 1300, 1, 1, 1));
			writer->addText(Text("Level : " + std::to_string(player.GetLevel()), width * 0.03, height * 0.8, (float)width / 1500, 1, 1, 1));
			writer->addText(Text("Score: " + std::to_string(player.GetScore()), width * 0.03, height * 0.7, (float)width / 1500, 1, 1, 1));
			writer->addText(Text("NEXT", width * 0.1, height * 0.5, (float)width / 1000, 1, 1, 1));
				
		}

		void DrawInstructions(Writer* writer)
		{
			writer->addText(Text("INSTRUCTIONS: ", width * 0.63, height * 0.9, (float)width / 2000, 1, 1, 1));
			writer->addText(Text("Movements:                 UP    ", width * 0.63, height * 0.8, (float)width / 2800, 1, 1, 1));
			writer->addText(Text("LEFT          RIGHT", width * 0.75, height * 0.75, (float)width / 2800, 1, 1, 1));
			writer->addText(Text("DOWN    ", width * 0.79, height * 0.7, (float)width / 2800, 1, 1, 1));

			if(!dimension) writer->addText(Text("Rotation:       Q    ", width * 0.63, height * 0.5, (float)width / 2800, 1, 1, 1));
			else writer->addText(Text("Rotation:  Q   W   E   SPACE    ", width * 0.63, height * 0.5, (float)width / 2800, 1, 1, 1));

		}
		

		//This function is called when the user presses any key on the keyboard
		void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			board.keyCallback(key, scancode, action, mods);
		}

};




class GameControllerMulti : public GameController
{
	private:

	Player rival = Player();
	Board  rivalboard = Board();

	public:

		//Constructor and Destructors
		GameControllerMulti() {}
		GameControllerMulti(GLfloat width_, GLfloat height_, std::string name, bool dimension3)
		{

			player.SetName(name);
			width = width_;
			height = height_;
			dimension = dimension3;
			board = Board(width / 2.7, height * 0.2, -650, width, height, 50, dimension);

		}
		~GameControllerMulti() {}

		//
		bool SearchPlayer()
		{
			return false;
		}

		void Comunication()
		{
			rivalboard = board;
			rival = player;

			if(dimension) rivalboard.UpdateBoard(width / 1.4, height * 0.5, -650, width, height, 75);
			else rivalboard.UpdateBoard(width / 1.2, height * 0.7, -650, width, height, 75);
			
			return;
		}

		

		void DrawGameMulti(Writer* writer)
		{
			Comunication();
			
			board.Play(&player);
			rivalboard.OnlyDraw();
		
			writer->addText(Text(player.GetName(), width * 0.03, height * 0.9, (float)width / 1300, 1, 1, 1));
			writer->addText(Text("Level : " + std::to_string(player.GetLevel()), width * 0.03, height * 0.8, (float)width / 1500, 1, 1, 1));
			writer->addText(Text("Score: " + std::to_string(player.GetScore()), width * 0.03, height * 0.7, (float)width / 1500, 1, 1, 1));
			writer->addText(Text("NEXT", width * 0.1, height * 0.5, (float)width / 1000, 1, 1, 1));
			
			writer->addText(Text(rival.GetName(), width * 0.75, height * 0.35, (float)width / 2500, 1, 1, 1));
			writer->addText(Text("Level : " + std::to_string(rival.GetLevel()), width * 0.75, height * 0.30, (float)width / 2500, 1, 1, 1));
			writer->addText(Text("Score: " + std::to_string(rival.GetScore()), width * 0.75, height * 0.25, (float)width / 2500, 1, 1, 1));


			
			board.DrawNext();
			
		}
};