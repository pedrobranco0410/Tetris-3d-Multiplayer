#pragma once

class Board
{


private:

	//table size
	int size = 10;


	//Active piece
	Piece MovingPiece;
	//Array that will store all the pieces that are on the board
	std::vector<Piece> pieces;


	//position where the table is
	GLfloat centerPosX, centerPosY, centerPosZ;
	//edge size
	GLfloat edgeLength;

	//Screen were the table and all pieces and grid will be drawed
	int Width, Height;
	int angle = 0;

	clock_t tInicio = clock();
	bool dimensions = true;

	int type = 0;

public:

	


	//Constructor
	Board() {}
	Board(GLfloat PosX, GLfloat PosY, GLfloat PosZ, GLfloat width, GLfloat height, float ratio, bool dim)
	{
		//setting position
		centerPosX = PosX;
		centerPosY = PosY;
		centerPosZ = PosZ;

		//getting screen
		Width = width;
		Height = height;

		//setting border size proportional to screen size
		edgeLength = Width / ratio;

		//Check if its a 2d or 3d table;
		dimensions = dim;

		//Creating the fist piece;
		srand((unsigned)time(0));
		type = rand() % 7;
		if (dimensions) MovingPiece = Piece(centerPosX, centerPosY, centerPosZ, edgeLength, size/2, 22, size/2, size, type);
		else
		{
			edgeLength = Width / ratio * 1.2;
			//setting position
			centerPosX = PosX*0.9;
			centerPosY = PosY*0.6;
			centerPosZ = PosZ;
			MovingPiece = Piece(centerPosX, centerPosY, centerPosZ, edgeLength, size / 2, 22, 0, size, type);
			
		}
		srand((unsigned)time(0));
		type = rand() % 7;

	}

	//Destructor
	~Board() {}

	//The function put all game(grid and cubes) in a new position
	void UpdateBoard(GLfloat PosX, GLfloat PosY, GLfloat PosZ, GLfloat width, GLfloat height, float ratio)
	{
		//Updating position
		centerPosX = PosX;
		centerPosY = PosY;
		centerPosZ = PosZ;

		//getting screen
		Width = width;
		Height = height;

		//setting border size proportional to screen size
		edgeLength = Width / ratio;

		if (!dimensions)
		{
			edgeLength = Width / ratio * 1.2;
			//setting position
			centerPosX = PosX * 0.9;
			centerPosY = PosY * 0.6;
			centerPosZ = PosZ;
		}

		//Updating every piece position
		MovingPiece.UpdateBoard(centerPosX, centerPosY, centerPosZ, edgeLength);
		for (auto& element : pieces) {
			element.UpdateBoard(centerPosX, centerPosY, centerPosZ,edgeLength);
		}

		
	}

	//Place the current moving piece in the pieces vector and create a new one
	void NewPiece()
	{
		
		pieces.push_back(MovingPiece);
		if (dimensions) MovingPiece = Piece(centerPosX, centerPosY, centerPosZ, edgeLength, size / 2, 22, size / 2, size, type);
		else MovingPiece = Piece(centerPosX, centerPosY, centerPosZ, edgeLength, size / 2, 22, 0, size, type);
		srand((unsigned)time(0));
		type = rand() % 7;
	}

	//send the piece down a square and if it is not possible it means that the piece is no longer moving. Then it create a new piece;
	void FallingDown()
	{
		
		if (MovingPiece.CanBeMoved(0,-1,0,pieces))
		{
			MovingPiece.MovePiece(0, -1, 0);
			return;
		}

		//The piece stop
		NewPiece();

	}

	// Draws the markings on the board to facilitate the user to locate himself in the game
	void DrawGrid()
	{
		GLfloat halfSideLength = edgeLength * 0.5f;

		//base
		for (int i = 0; i < size; i++)
		{
			for (int k = 0; k < size; k++)
			{
				GLfloat vertices[] = { centerPosX + (2 * i - 1) * halfSideLength, centerPosY - halfSideLength, centerPosZ + (2 * k + 1) * halfSideLength, // top left
										centerPosX + (2 * i + 1) * halfSideLength, centerPosY - halfSideLength, centerPosZ + (2 * k + 1) * halfSideLength, // top right
										centerPosX + (2 * i + 1) * halfSideLength, centerPosY - halfSideLength, centerPosZ + (2 * k - 1) * halfSideLength, // bottom right
										centerPosX + (2 * i - 1) * halfSideLength, centerPosY - halfSideLength, centerPosZ + (2 * k - 1) * halfSideLength };

				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
				glEnableClientState(GL_VERTEX_ARRAY);
				glVertexPointer(3, GL_FLOAT, 0, vertices);
				glDrawArrays(GL_QUADS, 0, 4);
				glDisableClientState(GL_VERTEX_ARRAY);
			}
		}

		//wall back 
		if(angle == 0 || angle == 3)
		{
			
			for (int i = 0; i < size; i++)
			{
				for (int k = 0; k < 2 * size; k++)
				{
					GLfloat vertices[] = { centerPosX + (2 * i - 1) * halfSideLength, centerPosY + (2 * k + 1) * halfSideLength, centerPosZ + (2 * size - 1) * halfSideLength , // top left
											centerPosX + (2 * i + 1) * halfSideLength, centerPosY + (2 * k + 1) * halfSideLength, centerPosZ + (2 * size - 1) * halfSideLength , // top right
											centerPosX + (2 * i + 1) * halfSideLength, centerPosY + (2 * k - 1) * halfSideLength, centerPosZ + (2 * size - 1) * halfSideLength , // bottom right
											centerPosX + (2 * i - 1) * halfSideLength, centerPosY + (2 * k - 1) * halfSideLength, centerPosZ + (2 * size - 1) * halfSideLength };

					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
					glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
					glEnableClientState(GL_VERTEX_ARRAY);
					glVertexPointer(3, GL_FLOAT, 0, vertices);
					glDrawArrays(GL_QUADS, 0, 4);
					glDisableClientState(GL_VERTEX_ARRAY);
				}
			}
		}

		//wall front
		if (angle == 1 || angle == 2)
		{
			for (int i = 0; i < size; i++)
			{
				for (int k = 0; k < 2 * size; k++)
				{
					GLfloat vertices[] = { centerPosX + (2 * i - 1) * halfSideLength, centerPosY + (2 * k + 1) * halfSideLength, centerPosZ - halfSideLength , // top left
											centerPosX + (2 * i + 1) * halfSideLength, centerPosY + (2 * k + 1) * halfSideLength, centerPosZ - halfSideLength , // top right
											centerPosX + (2 * i + 1) * halfSideLength, centerPosY + (2 * k - 1) * halfSideLength, centerPosZ - halfSideLength , // bottom right
											centerPosX + (2 * i - 1) * halfSideLength, centerPosY + (2 * k - 1) * halfSideLength, centerPosZ - halfSideLength };

					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
					glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
					glEnableClientState(GL_VERTEX_ARRAY);
					glVertexPointer(3, GL_FLOAT, 0, vertices);
					glDrawArrays(GL_QUADS, 0, 4);
					glDisableClientState(GL_VERTEX_ARRAY);
				}
			}
		}


		//wall left
		if (angle == 0 || angle == 1)
		{
			for (int i = 0; i < size; i++)
			{
				for (int k = 0; k < 2 * size; k++)
				{
					GLfloat vertices[] = { centerPosX - halfSideLength, centerPosY + (2 * k + 1) * halfSideLength, centerPosZ + (2 * i - 1) * halfSideLength , // top left
											centerPosX - halfSideLength, centerPosY + (2 * k + 1) * halfSideLength, centerPosZ + (2 * i + 1) * halfSideLength , // top right
											centerPosX - halfSideLength, centerPosY + (2 * k - 1) * halfSideLength, centerPosZ + (2 * i + 1) * halfSideLength , // bottom right
											centerPosX - halfSideLength, centerPosY + (2 * k - 1) * halfSideLength, centerPosZ + (2 * i - 1) * halfSideLength };

					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
					glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
					glEnableClientState(GL_VERTEX_ARRAY);
					glVertexPointer(3, GL_FLOAT, 0, vertices);
					glDrawArrays(GL_QUADS, 0, 4);
					glDisableClientState(GL_VERTEX_ARRAY);
				}
			}
		}

		//wall right
		if (angle == 2 || angle == 3)
		{
		
			for (int i = 0; i < size; i++)
			{
				for (int k = 0; k < 2 * size; k++)
				{
					GLfloat vertices[] = { centerPosX + (2 * size - 1) * halfSideLength, centerPosY + (2 * k + 1) * halfSideLength, centerPosZ + (2 * i - 1) * halfSideLength , // top left
											centerPosX + (2 * size - 1) * halfSideLength, centerPosY + (2 * k + 1) * halfSideLength, centerPosZ + (2 * i + 1) * halfSideLength , // top right
											centerPosX + (2 * size - 1) * halfSideLength, centerPosY + (2 * k - 1) * halfSideLength, centerPosZ + (2 * i + 1) * halfSideLength , // bottom right
											centerPosX + (2 * size - 1) * halfSideLength, centerPosY + (2 * k - 1) * halfSideLength, centerPosZ + (2 * i - 1) * halfSideLength };

					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
					glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
					glEnableClientState(GL_VERTEX_ARRAY);
					glVertexPointer(3, GL_FLOAT, 0, vertices);
					glDrawArrays(GL_QUADS, 0, 4);
					glDisableClientState(GL_VERTEX_ARRAY);
				}
			}
		}


		return;
	}

	//Draws moving and standing pieces
	void DrawPieces()
	{

		MovingPiece.Updateghosts(pieces);

		if (angle == 0)
		{
			for (int i = 0; i < 3 * size; i++)
			{
				for (int j = size - 1; j >= 0; j--)
				{
					for (int k = 0; k < size; k++)
					{
						MovingPiece.DrawGhosts(k, i, j);
						MovingPiece.DrawPosition(k, i, j);
						for (auto& element : pieces)
						{
							element.DrawPosition(k, i, j);
						}
					}
				}
			}
		}

		if (angle == 1)
		{
			for (int i = 0; i < 3 * size; i++)
			{
				for (int j = 0; j < size ; j++)
				{
					for (int k = 0; k < size; k++)
					{
						MovingPiece.DrawGhosts(k, i, j);
						MovingPiece.DrawPosition(k, i, j);
						for (auto& element : pieces)
						{
							element.DrawPosition(k, i, j);
						}
					}
				}
			}
		}

		if (angle == 2)
		{
			for (int i = 0; i < 3 * size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					for (int k = size - 1; k >= 0; k--)
					{
						MovingPiece.DrawGhosts(k, i, j);
						MovingPiece.DrawPosition(k, i, j);
						for (auto& element : pieces)
						{
							element.DrawPosition(k, i, j);
						}
					}
				}
			}
		}

		if (angle == 3)
		{
			for (int i = 0; i < 3 * size; i++)
			{
				for (int j = size - 1; j >= 0; j--)
				{
					for (int k = size-1; k >= 0; k--)
					{
						MovingPiece.DrawGhosts(k, i, j);
						MovingPiece.DrawPosition(k, i, j);
						for (auto& element : pieces)
						{
							element.DrawPosition(k, i, j);
						}
					}
				}
			}
		}

		

		
	}

	void DrawNext()
	{
		Piece next = Piece(centerPosX , centerPosY, centerPosZ, edgeLength*1.5, -5 , 1 ,  0, size, type);

		next.Draw();

	}

	//Checks if there is a complete line in the gameand then delete it
	void CheckLine(Player* player)
	{
		int count = 0;
		int total = 0;
		std::vector<Piece> temp;
		for (int i = 0; i < size * 2; i++)
		{
			for (auto& element : pieces)
			{
				count += element.CountLine(i);
			}

			if ((dimensions && count == size*size) || (!dimensions && count == size))
			{
				for (auto& element : pieces)
				{
					element.DeleteLine(i);

				}
				i--;
				total += 1;
			}

			
			count = 0; 
		}

		for (auto& element : pieces)if (element.CountBlocks() != 0)temp.push_back(element);
		pieces.clear();
		pieces = temp;

		
		if (total == 1) player->UpdateScore(40);
		else if (total == 2) player->UpdateScore(100);
		else if (total == 3) player->UpdateScore(300);
		else if (total == 4) player->UpdateScore(1200);

	}

	//Check if the player lost the game
	bool CheckEnd()
	{
		int count = 0;
		for (auto& element : pieces)
		{
			count += element.CountLine(2*size);
		}

		if (count > 0) return true;
		return false;
		
	}

	void Play(Player *player)
	{
		CheckLine(player);

		if (clock() - tInicio > 400 / (1 + std::min(player->GetLevel(), 15)))
		{
			FallingDown();
			tInicio = clock();
		}

		//Adjusting the camera's position and angulation
		if (dimensions)
		{
			glPushMatrix();
			glTranslatef((centerPosX + size / 2 * edgeLength), (centerPosY + size * 2 * edgeLength), (centerPosZ + size / 2 * edgeLength));
			glRotatef(-30, 1, 0, 0);
			glRotatef(45 + (90 * angle), 0, 1, 0);
			glTranslatef(-(centerPosX + size / 2 * edgeLength), -(centerPosY + size * 2 * edgeLength), -(centerPosZ + size / 2 * edgeLength));
			glTranslatef(0, -Height * 0.08, 0);
			DrawGrid();
			DrawPieces();
			glPopMatrix();
		}
		else
		{

			DrawGrid();
			DrawPieces();

		}

	}

	void OnlyDraw()
	{
		//Adjusting the camera's position and angulation
		if (dimensions)
		{
			glPushMatrix();
			glTranslatef((centerPosX + size / 2 * edgeLength), (centerPosY + size * 2 * edgeLength), (centerPosZ + size / 2 * edgeLength));
			glRotatef(-30, 1, 0, 0);
			glRotatef(45 + (90 * angle), 0, 1, 0);
			glTranslatef(-(centerPosX + size / 2 * edgeLength), -(centerPosY + size * 2 * edgeLength), -(centerPosZ + size / 2 * edgeLength));
			glTranslatef(0, -Height * 0.08, 0);
			DrawGrid();
			DrawPieces();
			glPopMatrix();
		}
		else
		{

			DrawGrid();
			DrawPieces();

		}
	}

	//This function is called when the user presses any key on the keyboard
	void keyCallback(int key, int scancode, int action, int mods)
	{

		// actions are GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT
		if (action == GLFW_PRESS || action == GLFW_REPEAT)
		{
			switch (key)
			{
			case GLFW_KEY_UP:

				if (MovingPiece.CanBeMoved(0, 0, 1, pieces) && dimensions && angle == 0)MovingPiece.MovePiece(0, 0, 1);
				if (MovingPiece.CanBeMoved(-1, 0, 0, pieces) && dimensions && angle == 1)MovingPiece.MovePiece(-1, 0, 0);
				if (MovingPiece.CanBeMoved(0, 0, -1, pieces) && dimensions && angle == 2)MovingPiece.MovePiece(0, 0, -1);
				if (MovingPiece.CanBeMoved(1, 0, 0, pieces) && dimensions && angle == 3)MovingPiece.MovePiece(1, 0, 0);
				
				break;
			case GLFW_KEY_DOWN:

				if (MovingPiece.CanBeMoved(0, 0, -1, pieces) && dimensions && angle == 0)MovingPiece.MovePiece(0, 0, -1);
				if (MovingPiece.CanBeMoved(1, 0, 0, pieces) && dimensions && angle == 1)MovingPiece.MovePiece(1, 0, 0);
				if (MovingPiece.CanBeMoved(0, 0, 1, pieces) && dimensions && angle == 2)MovingPiece.MovePiece(0, 0, 1);
				if (MovingPiece.CanBeMoved(-1, 0, 0, pieces) && dimensions && angle == 3)MovingPiece.MovePiece(-1, 0, 0);

				//If it is in 2 dimensions it makes the piece fall faster
				if (!dimensions) FallingDown();

				break;
			case GLFW_KEY_RIGHT:
				if (MovingPiece.CanBeMoved(1, 0, 0, pieces) && angle == 0)MovingPiece.MovePiece(1, 0, 0);
				if (MovingPiece.CanBeMoved(0, 0, 1, pieces) && angle == 1)MovingPiece.MovePiece(0, 0, 1);
				if (MovingPiece.CanBeMoved(-1, 0, 0, pieces) && angle == 2)MovingPiece.MovePiece(-1, 0, 0);
				if (MovingPiece.CanBeMoved(0, 0, -1, pieces) && angle == 3)MovingPiece.MovePiece(0, 0, -1);
				
				break;

			case GLFW_KEY_LEFT:
				if (MovingPiece.CanBeMoved(-1, 0, 0, pieces) && angle == 0)MovingPiece.MovePiece(-1, 0, 0);
				if (MovingPiece.CanBeMoved(0, 0, -1, pieces) && angle == 1)MovingPiece.MovePiece(0, 0, -1);
				if (MovingPiece.CanBeMoved(1, 0, 0, pieces) && angle == 2)MovingPiece.MovePiece(1, 0, 0);
				if (MovingPiece.CanBeMoved(0, 0, 1, pieces) && angle == 3)MovingPiece.MovePiece(0, 0, 1);
				break;

			case GLFW_KEY_Q:
				MovingPiece.rotationZ(pieces);
				break;
			case GLFW_KEY_W:
				if (dimensions)MovingPiece.rotationY(pieces);
				break;
			case GLFW_KEY_E:
				if (dimensions)MovingPiece.rotationX(pieces);
				break;
			case GLFW_KEY_S:
				if (dimensions)FallingDown();
				break;


			case GLFW_KEY_SPACE:

				//If it is in 3 dimensions, rotate the board
				if (dimensions)
				{
					angle += 1;
					if (angle > 3) angle = 0;
				}
				break;
			}
		}
	}


};

