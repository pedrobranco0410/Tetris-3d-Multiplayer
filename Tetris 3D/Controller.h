#include<iostream>
#include <string>


class Controller
{
private:


	//screen where the cube will be drawn
    GLFWwindow* window;
	GLfloat height, width;

    Writer *writer;

    /// Game state
    /// 
    /// 0 > MENU
    /// 1 > CREDITS
    /// 2 > SINGLENAME
    /// 3 > SINGLEGAME
    /// 4 > SINGLEPAUSE
    /// 5 > SINGLELOOSE
    /// 6 > MULTINAME
    /// 7 > MULTISEARCH
    /// 8 > MULTIGAME
    /// 9 > MULTIWAIT
    /// 10 > FINALGAME
    /// 20 > EXIT
    /// 
    int state = 0; 

    //variable used only to make the "Tetris" logo spin
    GLfloat roty = 0;

    //Will store the player name
    std::string name;

    //Object that will controll every action that happens when a game begins;
    GameController gamecontroller;
    GameControllerMulti gamecontrollermulti;

    bool dimension = true;

    clock_t tInicio = clock();


public:

	//Constructor and Destructors
	Controller() {}
    Controller(GLFWwindow *window_,GLfloat width_, GLfloat height_, Writer *writer_)
	{

        writer = writer_;
        width = width_;
        height = height_;
        window = window_;

	}
	~Controller() {}

    bool CheckExit() { if (state == 20) return true; return false;}

    void updatewindow(GLfloat width_, GLfloat height_)
    {
        width = width_;
        height = height_;
        if (state == 3) gamecontroller.UpdateWindow(width_, height_);
        if (state == 8) gamecontrollermulti.UpdateWindow(width_, height_);
    }

    //This function drawss the entire Menu
    void DrawMenu()
    {
        //Writing texts
        

        writer->addText(Text("SINGLEPLAYER", width * 0.365, height * 0.58, (float)width / 1300, 1, 1, 1));
        writer->addText(Text("MULTIPLAYER", width * 0.375, height * 0.38, (float)width / 1300, 1, 1, 1));
        writer->addText(Text("CREDITS", width * 0.42, height * 0.18, (float)width / 1300, 1, 1, 1));
        writer->addText(Text("EXIT", width * 0.86, height * 0.1, (float)width / 2000, 1, 1, 1));

    
        //Makes the logo spin
        glPushMatrix();
        glTranslatef(width / 2, height / 2, -500);
        glRotatef(roty, 0, 1, 0);
        glTranslatef(-width / 2, -height / 2, 500);
        roty += 0.04;

        //Drawing Logo
        DrawTetris3dLogo(width * 1.05, height);

        glPopMatrix();

        //Getting mouse position
        double X, Y;
        glfwGetCursorPos(window, &X, &Y);

        //Drawing the "EXIT" button
        if (X < width * 0.9325 && X > width * 0.8425 && Y < height * 0.9325 && Y > height * 0.8425) DrawButton(width * 0.8875, height * 0.1125, 0, width * 0.09, height * 0.09, 1.0f);
        else DrawButton(width * 0.8875, height * 0.1125, 0, width * 0.09, height * 0.09, 0.5f);

        //Drawing the "CREDITS" button
        if (X < width * 0.7 && X > width * 0.3 && Y < height * 0.85 && Y > height * 0.75) DrawButton(width * 0.5, height * 0.2, 0, width * 0.4, height * 0.1, 1.0f);
        else DrawButton(width * 0.5, height * 0.2, 0, width * 0.4, height * 0.1, 0.5f);
        //Drawing the "MULTIPLAYER" button
        if (X < width * 0.7 && X > width * 0.3 && Y < height * 0.65 && Y > height * 0.55)DrawButton(width * 0.5, height * 0.4, 0, width * 0.4, height * 0.1, 1.0f);
        else DrawButton(width * 0.5, height * 0.4, 0, width * 0.4, height * 0.1, 0.5f);

        //Drawing the "SINGLEPLAYER" button
        if (X < width * 0.7 && X > width * 0.3 && Y < height * 0.45 && Y > height * 0.35)DrawButton(width * 0.5, height * 0.6, 0, width * 0.4, height * 0.1, 1.0f);
        else DrawButton(width * 0.5, height * 0.6, 0, width * 0.4, height * 0.1, 0.5f);


        //Text

    }

    //This function draws the entire Credits
    void DrawCredits()
    {
        //Writing texts
       // writer->addText(Text("Escrever um textinho maneiro", width * 0.1, height * 0.58, (float)width / 1700, 1, 1, 1));
        writer->addText(Text("RETURN", width * 0.85, height * 0.1, (float)width / 2800, 1, 1, 1));


        //Makes the logo spin
        glPushMatrix();
        glTranslatef(width / 2, height / 2, -500);
        glRotatef(roty, 0, 1, 0);
        glTranslatef(-width / 2, -height / 2, 500);
        roty += 0.1;

        //Drawing Logo
        DrawTetris3dLogo(width * 1.05, height);
        glPopMatrix();

        //Getting mouse position
        double X, Y;
        glfwGetCursorPos(window, &X, &Y);

        //Drawing the "RETURN" button
        if (X < width * 0.9325 && X > width * 0.8425 && Y < height * 0.9325 && Y > height * 0.8425) DrawButton(width * 0.8875, height * 0.1125, 0, width * 0.09, height * 0.09, 1.0f);
        else DrawButton(width * 0.8875, height * 0.1125, 0, width * 0.09, height * 0.09, 0.5f);


    };

    //This function draws the screen for the user to enter the player's name
    void DrawSingleName()
    {
        //Writing texts
        writer->addText(Text("INSERT YOUR NAME", width * 0.27, height * 0.6, (float)width / 1000, 1, 1, 1));
        writer->addText(Text(name, width * (0.52 - name.size() * 0.012), height * 0.42, (float)width / 1100, 1, 1, 1));
        writer->addText(Text("RETURN", width * 0.077, height * 0.1, (float)width / 2800, 1, 1, 1));
        writer->addText(Text("PLAY 2D", width * 0.855, height * 0.21, (float)width / 3000, 1, 1, 1));
        writer->addText(Text("PLAY 3D", width * 0.855, height * 0.1, (float)width / 3000, 1, 1, 1));


        //Makes the logo spin
        glPushMatrix();
        glTranslatef(width / 2, height / 2, -500);
        glRotatef(roty, 0, 1, 0);
        glTranslatef(-width / 2, -height / 2, 500);
        roty += 0.1;

        //Drawing Logo
        DrawTetris3dLogo(width * 1.05, height);
        glPopMatrix();

        //Getting mouse position
        double X, Y;
        glfwGetCursorPos(window, &X, &Y);

        //Drawing name input
        DrawButton(width * 0.5, height * 0.45, 0, width * 0.7, height * 0.12, 0.5f);

        //Drawing the "RETURN" button
        if (X < width * 0.1575 && X > width * 0.0675 && Y < height * 0.9325 && Y > height * 0.8425) DrawButton(width * 0.1125, height * 0.1125, 0, width * 0.09, height * 0.09, 1.0f);
        else DrawButton(width * 0.1125, height * 0.1125, 0, width * 0.09, height * 0.09, 0.5f);

        //Drawing the "PLAY 3D" button
        if (X < width * 0.9325 && X > width * 0.8425 && Y < height * 0.9325 && Y > height * 0.8425) DrawButton(width * 0.8875, height * 0.1125, 0, width * 0.09, height * 0.09, 1.0f);
        else DrawButton(width * 0.8875, height * 0.1125, 0, width * 0.09, height * 0.09, 0.5f);

        //Drawing the "PLAY 2D" button
        if (X < width * 0.9325 && X > width * 0.8425 && Y < height * 0.825 && Y > height * 0.735) DrawButton(width * 0.8875, height * 0.22, 0, width * 0.09, height * 0.09, 1.0f);
        else DrawButton(width * 0.8875, height * 0.22, 0, width * 0.09, height * 0.09, 0.5f);
    }

    //This function drwas the entire game and the pause button
    void DrawSingleGame()
    {
        gamecontroller.DrawGame(writer);

        //Getting mouse position
        double X, Y;
        glfwGetCursorPos(window, &X, &Y);

        writer->addText(Text("PAUSE", width * 0.855, height * 0.1, (float)width / 2800, 1, 1, 1));

        //Drawing the "PAUSE" button
        if (X < width * 0.9325 && X > width * 0.8425 && Y < height * 0.9325 && Y > height * 0.8425) DrawButton(width * 0.8875, height * 0.1125, 0, width * 0.09, height * 0.09, 1.0f);
        else DrawButton(width * 0.8875, height * 0.1125, 0, width * 0.09, height * 0.09, 0.5f);
    }

    //This function drawss the entire Menu
    void DrawSinglePause()
    {
        //Writing texts
        writer->addText(Text("RETURN GAME", width * 0.365, height * 0.58, (float)width / 1300, 1, 1, 1));
        writer->addText(Text("NEW GAME", width * 0.4, height * 0.38, (float)width / 1300, 1, 1, 1));
        writer->addText(Text("MENU", width * 0.45, height * 0.18, (float)width / 1300, 1, 1, 1));
        writer->addText(Text("EXIT", width * 0.86, height * 0.1, (float)width / 2000, 1, 1, 1));

        DrawGOaniamtion(width, height, roty);

        //Makes the logo spin
        glPushMatrix();
        glTranslatef(width / 2, height / 2, -500);
        glRotatef(roty, 0, 1, 0);
        glTranslatef(-width / 2, -height / 2, 500);
        roty += 0.04;

        //Drawing Logo
        DrawTetris3dLogo(width * 1.05, height);

        glPopMatrix();

        //Getting mouse position
        double X, Y;
        glfwGetCursorPos(window, &X, &Y);

        //Drawing the "EXIT" button
        if (X < width * 0.9325 && X > width * 0.8425 && Y < height * 0.9325 && Y > height * 0.8425) DrawButton(width * 0.8875, height * 0.1125, 0, width * 0.09, height * 0.09, 1.0f);
        else DrawButton(width * 0.8875, height * 0.1125, 0, width * 0.09, height * 0.09, 0.5f);

        //Drawing the "CREDITS" button
        if (X < width * 0.7 && X > width * 0.3 && Y < height * 0.85 && Y > height * 0.75) DrawButton(width * 0.5, height * 0.2, 0, width * 0.4, height * 0.1, 1.0f);
        else DrawButton(width * 0.5, height * 0.2, 0, width * 0.4, height * 0.1, 0.5f);
        //Drawing the "MULTIPLAYER" button
        if (X < width * 0.7 && X > width * 0.3 && Y < height * 0.65 && Y > height * 0.55)DrawButton(width * 0.5, height * 0.4, 0, width * 0.4, height * 0.1, 1.0f);
        else DrawButton(width * 0.5, height * 0.4, 0, width * 0.4, height * 0.1, 0.5f);

        //Drawing the "SINGLEPLAYER" button
        if (X < width * 0.7 && X > width * 0.3 && Y < height * 0.45 && Y > height * 0.35)DrawButton(width * 0.5, height * 0.6, 0, width * 0.4, height * 0.1, 1.0f);
        else DrawButton(width * 0.5, height * 0.6, 0, width * 0.4, height * 0.1, 0.5f);


        //Text

    }

    //This function drawss the entire Menu
    void DrawSingleLoose()
    {
        //Writing texts
        writer->addText(Text("GAME OVER", width * 0.25, height * 0.8, (float)width / 600, 1, 1, 1));
        writer->addText(Text("NEW GAME", width * 0.4, height * 0.38, (float)width / 1300, 1, 1, 1));
        writer->addText(Text("MENU", width * 0.45, height * 0.18, (float)width / 1300, 1, 1, 1));
        writer->addText(Text("EXIT", width * 0.86, height * 0.1, (float)width / 2000, 1, 1, 1));

        gamecontroller.DrawGameOver(writer);
        roty += 0.1;
        DrawGOaniamtion(width, height, roty);
        //Getting mouse position
        double X, Y;
        glfwGetCursorPos(window, &X, &Y);

        //Drawing the "EXIT" button
        if (X < width * 0.9325 && X > width * 0.8425 && Y < height * 0.9325 && Y > height * 0.8425) DrawButton(width * 0.8875, height * 0.1125, 0, width * 0.09, height * 0.09, 1.0f);
        else DrawButton(width * 0.8875, height * 0.1125, 0, width * 0.09, height * 0.09, 0.5f);

        //Drawing the "CREDITS" button
        if (X < width * 0.7 && X > width * 0.3 && Y < height * 0.85 && Y > height * 0.75) DrawButton(width * 0.5, height * 0.2, 0, width * 0.4, height * 0.1, 1.0f);
        else DrawButton(width * 0.5, height * 0.2, 0, width * 0.4, height * 0.1, 0.5f);
        //Drawing the "MULTIPLAYER" button
        if (X < width * 0.7 && X > width * 0.3 && Y < height * 0.65 && Y > height * 0.55)DrawButton(width * 0.5, height * 0.4, 0, width * 0.4, height * 0.1, 1.0f);
        else DrawButton(width * 0.5, height * 0.4, 0, width * 0.4, height * 0.1, 0.5f);



        //Text

    }

    void DrawMultiSearch()
    {
        writer->addText(Text("Searching Player", width * 0.3, height * 0.6, (float)width / 1000, 1, 1, 1));
        writer->addText(Text("RETURN", width * 0.077, height * 0.1, (float)width / 2800, 1, 1, 1));
        writer->addText(Text("  TRY  ", width * 0.855, height * 0.1, (float)width / 3000, 1, 1, 1));

        roty += 0.1;
        DrawSearch(width, height, roty, clock() - tInicio);
        if (clock() - tInicio > 10000)tInicio = clock();

        //Makes the logo spin
        glPushMatrix();
        glTranslatef(width / 2, height / 2, -500);
        glRotatef(roty, 0, 1, 0);
        glTranslatef(-width / 2, -height / 2, 500);
        roty += 0.1;

        //Drawing Logo
        DrawTetris3dLogo(width * 1.05, height);
        glPopMatrix();

        //Getting mouse position
        double X, Y;
        glfwGetCursorPos(window, &X, &Y);

        //Drawing the "RETURN" button
        if (X < width * 0.1575 && X > width * 0.0675 && Y < height * 0.9325 && Y > height * 0.8425) DrawButton(width * 0.1125, height * 0.1125, 0, width * 0.09, height * 0.09, 1.0f);
        else DrawButton(width * 0.1125, height * 0.1125, 0, width * 0.09, height * 0.09, 0.5f);

        //Drawing the "Try" button
        if (X < width * 0.9325 && X > width * 0.8425 && Y < height * 0.9325 && Y > height * 0.8425) DrawButton(width * 0.8875, height * 0.1125, 0, width * 0.09, height * 0.09, 1.0f);
        else DrawButton(width * 0.8875, height * 0.1125, 0, width * 0.09, height * 0.09, 0.5f);


    }

    //This function drwas the entire game and the pause button
    void DrawMultiGame()
    {
        gamecontrollermulti.DrawGameMulti(writer);

        //Getting mouse position
        double X, Y;
        glfwGetCursorPos(window, &X, &Y);

        writer->addText(Text("PAUSE", width * 0.855, height * 0.1, (float)width / 2800, 1, 1, 1));

        //Drawing the "PAUSE" button
        if (X < width * 0.9325 && X > width * 0.8425 && Y < height * 0.9325 && Y > height * 0.8425) DrawButton(width * 0.8875, height * 0.1125, 0, width * 0.09, height * 0.09, 1.0f);
        else DrawButton(width * 0.8875, height * 0.1125, 0, width * 0.09, height * 0.09, 0.5f);
    }

    void ControllerDrawObjects()
    {


        switch (state)
        {
        //Menu
        case 0:
            DrawMenu();
            break;
        
        //Credits
        case 1:
            DrawCredits();
            break;

        //Singlename
        case 2:
            DrawSingleName();
             break;
                
        //Singleplayer Game
        case 3:
            DrawSingleGame();
            if (gamecontroller.CheckEnd()) state = 5;
            break;

        //Singleplayer Game Paused
        case 4:
            DrawSinglePause();
            break;

        case 5:
            DrawSingleLoose();
            break;

        case 6:
            DrawSingleName();
            break;

        case 7:
            DrawMultiSearch();
            break;

        case 8:
            DrawMultiGame();;
            break;

        
        }
    }

    
    //function called when the user clicks anywhere on the screen
    void Mouse(double X, double Y, GLFWwindow* window)
    {
        //Taking the screen size
        int Width, Height;
        glfwGetFramebufferSize(window, &Width, &Height);

        switch (state)
        {
            
        //Menu
        case 0:
        {
            //Button exit pressed
            if (X < Width * 0.9325 && X > Width * 0.8425 && Y < Height * 0.9325 && Y > Height * 0.8425)
                state = 20;

            //Button Singleplayer pressed
            if (X < Width * 0.7 && X > Width * 0.3 && Y < Height * 0.45 && Y > Height * 0.35)
            {
                name = "";
                state = 2;
            }

        //Button MultiPlayer pressed
            if (X < Width * 0.7 && X > Width * 0.3 && Y < Height * 0.65 && Y > Height * 0.55)
            {
                name = "";
                state = 6;
            }

            //Button Credits pressed
            if (X < Width * 0.7 && X > Width * 0.3 && Y < Height * 0.85 && Y > Height * 0.75)
                state = 1;
        }
        break;

        //Credits
        case 1:
        {
            //Button return pressed
            if (X < Width * 0.9325 && X > Width * 0.8425 && Y < Height * 0.9325 && Y > Height * 0.8425)
                state = 0;
        }
        break;

        //SingleName
        case 2:
        {
            //Button Return Pressed
            if (X < width * 0.1575 && X > width * 0.0675 && Y < height * 0.9325 && Y > height * 0.8425)
                state = 0;

            //Button 2d pressed
            if (X < width * 0.9325 && X > width * 0.8425 && Y < height * 0.825 && Y > height * 0.735)
            {
                state = 3;
                dimension = false;
                gamecontroller = GameController(width, height, name, false);
            }

            //Button 3d pressed
            if (X < Width * 0.9325 && X > Width * 0.8425 && Y < Height * 0.9325 && Y > Height * 0.8425)
            {
                state = 3;
                dimension = true;
                gamecontroller = GameController(width, height, name, true);
            }
        }
        break;

        //SingleGame
        case 3:
        {
            //Button Pause pressed
            if (X < Width * 0.9325 && X > Width * 0.8425 && Y < Height * 0.9325 && Y > Height * 0.8425)
                state = 4;

        }
        break;

        //SinglePause
        case 4:
        {
            //Button exit pressed
            if (X < Width * 0.9325 && X > Width * 0.8425 && Y < Height * 0.9325 && Y > Height * 0.8425)
                state = 20;

            //Button Return Game pressed
            if (X < Width * 0.7 && X > Width * 0.3 && Y < Height * 0.45 && Y > Height * 0.35)
                state = 3;

            //Button New Game pressed
            if (X < Width * 0.7 && X > Width * 0.3 && Y < Height * 0.65 && Y > Height * 0.55)
            {
                state = 3;
                gamecontroller = GameController(width, height, name, dimension);
            }

            //Button Menu pressed
            if (X < Width * 0.7 && X > Width * 0.3 && Y < Height * 0.85 && Y > Height * 0.75)
                state = 0;
        }
        break;

        //SingleGameOver
        case 5:
        {
            // Button exit pressed
                if (X < Width * 0.9325 && X > Width * 0.8425 && Y < Height * 0.9325 && Y > Height * 0.8425)
                    state = 20;

            //Button New Game pressed
            if (X < Width * 0.7 && X > Width * 0.3 && Y < Height * 0.65 && Y > Height * 0.55)
            {
                state = 3;
                gamecontroller = GameController(width, height, name, dimension);
            }

            //Button Menu pressed
            if (X < Width * 0.7 && X > Width * 0.3 && Y < Height * 0.85 && Y > Height * 0.75)
                state = 0;
        }
        break;

        //MultiName
        case 6:
        {
            //Button Return Pressed
            if (X < width * 0.1575 && X > width * 0.0675 && Y < height * 0.9325 && Y > height * 0.8425)
                state = 0;

            //Button 2d pressed
            if (X < width * 0.9325 && X > width * 0.8425 && Y < height * 0.825 && Y > height * 0.735)
            {
                state = 7;
                dimension = false;
                gamecontrollermulti = GameControllerMulti(width, height, name, false);
            }

            //Button 3d pressed
            if (X < Width * 0.9325 && X > Width * 0.8425 && Y < Height * 0.9325 && Y > Height * 0.8425)
            {
                state = 7;
                dimension = true;
                gamecontrollermulti = GameControllerMulti(width, height, name, true);
            }
        }
        break;

        //MultiName
        case 7:
        {
            //Button Return Pressed
            if (X < width * 0.1575 && X > width * 0.0675 && Y < height * 0.9325 && Y > height * 0.8425)
                state = 0;


            //Button 3d pressed
            if (X < Width * 0.9325 && X > Width * 0.8425 && Y < Height * 0.9325 && Y > Height * 0.8425)
                state = 8;
        }
        break;
      
        }

    }

    //Function called when the user presses a button on the keyboard
    void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (state == 3) gamecontroller.keyCallback(window, key, scancode, action, mods);
        if (state == 8) gamecontrollermulti.keyCallback(window, key, scancode, action, mods);

        // actions are GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT
        if (action == GLFW_PRESS || action == GLFW_REPEAT)
        {
            if (key == GLFW_KEY_BACKSPACE && (state == 2 || state == 6) && !name.empty())
            {
                name.pop_back();
            }
            
          
        }
    }

    //Function called when the user types a character
    void character_callback(GLFWwindow* window, unsigned int codepoint)
    {
        if ((state == 2 || state == 6) && name.size()< 15)
        {
            name = name + (char)codepoint;
        }
       
    }

};


































	
    


