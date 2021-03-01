


//This class represents a game piece formed by 4 cubes;
class Piece
{

private:
	//Position where the board is and his size
	GLfloat centerPosX, centerPosY, centerPosZ;
	//edge size
	GLfloat edgeLength;
	int size;

	// base cube position (bottom and left cube) for the construction of the piece;
	int X, Y, Z;

	/// Chossing type
	///
	///    #
	///    #	  #       #         #            #        #
	///    #	  #       # #     # #     # #    # #      #
	/// 0  #   1  # #   2 #     3 #     4 # #  5   #  6 # #
	/// 
	int type = 0;

	//vector that will store all the blocks that make up the piece;
	std::vector<Block> blocks;

	std::vector<Block> ghosts;



public:

	//Constructor
	Piece() {}

	Piece (GLfloat PosX, GLfloat PosY, GLfloat PosZ, GLfloat edge, int X_, int Y_, int Z_, int size_, int type_)
	{
		//setting board position
		centerPosX = PosX;
		centerPosY = PosY;
		centerPosZ = PosZ;
		size = size_;

		//setting cube position
		X = X_;
		Y = Y_;
		Z = Z_;
		edgeLength = edge;

		type = type_;

		MakePiece();
		
	}
	~Piece() {}

	void MakePiece()
	{
		//Choosing a random color
		srand((unsigned)time(0));
		int color = rand() % 6;

		if (type == 0)
		{
			blocks.push_back(Block(centerPosX, centerPosY, centerPosZ, edgeLength, X, Y, Z, size, color));
			blocks.push_back(Block(centerPosX, centerPosY, centerPosZ, edgeLength, X, Y+1, Z, size, color));
			blocks.push_back(Block(centerPosX, centerPosY, centerPosZ, edgeLength, X, Y+2, Z, size, color));
			blocks.push_back(Block(centerPosX, centerPosY, centerPosZ, edgeLength, X, Y+3, Z, size, color));
		}
		if (type == 1)
		{
			blocks.push_back(Block(centerPosX, centerPosY, centerPosZ, edgeLength, X, Y, Z, size, color));
			blocks.push_back(Block(centerPosX, centerPosY, centerPosZ, edgeLength, X, Y + 1, Z, size, color));
			blocks.push_back(Block(centerPosX, centerPosY, centerPosZ, edgeLength, X+1, Y, Z, size, color));
			blocks.push_back(Block(centerPosX, centerPosY, centerPosZ, edgeLength, X, Y + 2, Z, size, color));
		}
		if (type == 2)
		{
			blocks.push_back(Block(centerPosX, centerPosY, centerPosZ, edgeLength, X, Y, Z, size, color));
			blocks.push_back(Block(centerPosX, centerPosY, centerPosZ, edgeLength, X, Y + 1, Z, size, color));
			blocks.push_back(Block(centerPosX, centerPosY, centerPosZ, edgeLength, X+1, Y + 1, Z, size, color));
			blocks.push_back(Block(centerPosX, centerPosY, centerPosZ, edgeLength, X, Y + 2, Z, size, color));
		}
		if (type == 3)
		{
			blocks.push_back(Block(centerPosX, centerPosY, centerPosZ, edgeLength, X, Y, Z, size, color));
			blocks.push_back(Block(centerPosX, centerPosY, centerPosZ, edgeLength, X, Y + 1, Z, size, color));
			blocks.push_back(Block(centerPosX, centerPosY, centerPosZ, edgeLength, X+1, Y + 1, Z, size, color));
			blocks.push_back(Block(centerPosX, centerPosY, centerPosZ, edgeLength, X+1, Y + 2, Z, size, color));
		}
		if (type == 4)
		{
			blocks.push_back(Block(centerPosX, centerPosY, centerPosZ, edgeLength, X, Y, Z, size, color));
			blocks.push_back(Block(centerPosX, centerPosY, centerPosZ, edgeLength, X+1, Y , Z, size, color));
			blocks.push_back(Block(centerPosX, centerPosY, centerPosZ, edgeLength, X, Y + 1, Z, size, color));
			blocks.push_back(Block(centerPosX, centerPosY, centerPosZ, edgeLength, X+1, Y + 1, Z, size, color));
		}
		if (type == 5)
		{
			blocks.push_back(Block(centerPosX, centerPosY, centerPosZ, edgeLength, X, Y, Z, size, color));
			blocks.push_back(Block(centerPosX, centerPosY, centerPosZ, edgeLength, X, Y + 1, Z, size, color));
			blocks.push_back(Block(centerPosX, centerPosY, centerPosZ, edgeLength, X - 1, Y + 1, Z, size, color));
			blocks.push_back(Block(centerPosX, centerPosY, centerPosZ, edgeLength, X - 1, Y + 2, Z, size, color));
		}

		if (type == 6)
		{
			blocks.push_back(Block(centerPosX, centerPosY, centerPosZ, edgeLength, X, Y, Z, size, color));
			blocks.push_back(Block(centerPosX, centerPosY, centerPosZ, edgeLength, X + 1, Y + 1, Z, size, color));
			blocks.push_back(Block(centerPosX, centerPosY, centerPosZ, edgeLength, X + 1, Y, Z, size, color));
			blocks.push_back(Block(centerPosX, centerPosY, centerPosZ, edgeLength, X + 1, Y + 2, Z, size, color));
		}

	}

	//Changing board parameters
	void UpdateBoard(GLfloat PosX, GLfloat PosY, GLfloat PosZ, GLfloat edge)
	{
		//setting board new position and edge
		centerPosX = PosX;
		centerPosY = PosY;
		centerPosZ = PosZ;
		edgeLength = edge;

		for (auto& element : blocks) element.UpdateBoard(centerPosX, centerPosY, centerPosZ, edge);
	}

	//Moves the cube to a new position
	void Updateposition(int X_, int Y_, int Z_)
	{
		//setting cube position
		X = X_;
		Y = Y_;
		Z = Z_;

		blocks.clear();
		MakePiece();
	}

	//Checks whether the piece can be moved according to the passed parameters
	bool CanBeMoved(int X_, int Y_, int Z_ , std::vector<Piece> pieces)
	{
		for (auto& element : blocks)
		{
			if (!element.CanBeMoved(X_, Y_, Z_)) return false;

			for (auto& part : pieces)
			{
				if (part.CheckColision(element.positionX() + X_, element.positionY() + Y_, element.positionZ() + Z_)) return false;
			}
		}

		return true;
	}

	//Moves the cube to a new position
	void MovePiece(int X_, int Y_, int Z_)
	{
		X += X_;
		Y += Y_;
		Z += Z_;

		for (auto& element : blocks)
		{
			element.MoveCube(X_, Y_, Z_);
		}
	}

	//checks if a given position is equal to the position of any cube that makes up the piece
	bool CheckColision(int X_, int Y_, int Z_)
	{
		for (auto& element : blocks)
		{
			if (element.CheckColision(X_, Y_, Z_)) return true;;
		}

		return false;
	}


	//Rotate the pieces in X axis
	void rotationX(std::vector<Piece> pieces)
	{


		int distanceZ;
		int distanceY;

		for (auto& element : blocks)
		{
			distanceZ = element.positionZ() - Z;
			distanceY = element.positionY() - Y;

			if (!element.CanBeMoved(0, Y - distanceZ - element.positionY(), Z + distanceY - element.positionZ())) return;

			for (auto& part : pieces)
			{
				if (part.CheckColision(element.positionX(), Y - distanceZ, Z + distanceY)) return;
			}
		}

		for (auto& element : blocks)
		{
			distanceZ = element.positionZ() - Z;
			distanceY = element.positionY() - Y;

			element.Updateposition(element.positionX(), Y - distanceZ, Z + distanceY);
		}


	}

	//Rotate the pieces in Y axis
	void rotationY(std::vector<Piece> pieces)
	{


		int distanceX;
		int distanceZ;

		for (auto& element : blocks)
		{
			distanceX = element.positionX() - X;
			distanceZ = element.positionZ() - Z;

			if (!element.CanBeMoved(X + distanceZ - element.positionX(),0, Z - distanceX - element.positionZ())) return;

			for (auto& part : pieces)
			{
				if (part.CheckColision(X + distanceZ,element.positionY(), Z - distanceX)) return;
			}
		}

		for (auto& element : blocks)
		{
			distanceX = element.positionX() - X;
			distanceZ = element.positionZ() - Z;

			element.Updateposition(X + distanceZ, element.positionY(), Z - distanceX);
		}


	}

	//Rotate the pieces in Z axis
	void rotationZ(std::vector<Piece> pieces)
	{


		int distanceX;
		int distanceY;

		for (auto& element : blocks)
		{
			distanceX = element.positionX() - X;
			distanceY = element.positionY() - Y;

			if (!element.CanBeMoved(X + distanceY - element.positionX(), Y - distanceX - element.positionY(), 0)) return;

			for (auto& part : pieces)
			{
				if (part.CheckColision(X + distanceY, Y - distanceX, element.positionZ())) return;
			}
		}

		for (auto& element : blocks)
		{
			distanceX = element.positionX() - X;
			distanceY = element.positionY() - Y;

			element.Updateposition(X + distanceY ,Y - distanceX, element.positionZ());
		}

		
	}

	
	//delete cubes that are at a specific level and make the cubes aboves fall
	void DeleteLine(int Y_)
	{
		std::vector<Block> temp; 

		for (auto& element : blocks)
		{
			if (element.positionY() < Y_) temp.push_back(element);
			if (element.positionY() > Y_)
			{
				element.MoveCube(0, - 1, 0);
				temp.push_back(element);
			}
		}

		blocks.clear();
		blocks = temp;
	}

	//Counts how many blocks of the piece are in a given row
	int CountLine(int Y_)
	{
		int counter = 0;

		for (auto& element : blocks)
		{
			if (element.positionY() == Y_) counter += 1;
		}

		return counter;
	}

	int CountBlocks()
	{
		return blocks.size();
	}

	//Updates ghost blocks
	void Updateghosts(std::vector<Piece> pieces)
	{
		ghosts.clear();

		int i = 0;
		while (CanBeMoved(0, -i, 0, pieces))i++;
		i--;
		if (i > 0)
		{
			for (auto& element : blocks) ghosts.push_back(Block(centerPosX, centerPosY, centerPosZ, edgeLength, element.positionX(), element.positionY()-i,element.positionZ(), size, 6));
		}

		

	}

	void DrawGhosts(int X_, int Y_, int Z_)
	{
		for (auto& element : ghosts)
		{
			if (element.positionX() == X_ && element.positionY() == Y_ && element.positionZ() == Z_)element.DrawCube();
		}
	}


	//Function responsible for drawing the Piece on the board
	void DrawPosition(int X_, int Y_, int Z_)
	{
	
		for (auto& element : blocks)
		{
			if(element.positionX() == X_ && element.positionY() == Y_ && element.positionZ() == Z_)element.DrawCube();
		}
	}

	void Draw()
	{

		for (auto& element : blocks)
		{
			element.DrawCube();
		}
	}

};