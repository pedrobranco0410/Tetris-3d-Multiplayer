


//This function draw a button in a specified position and with an specified size
void DrawButton(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLengthX, GLfloat edgeLengthY, GLfloat color)
{
    GLfloat halfSideLengthX = edgeLengthX * 0.5f;
    GLfloat halfSideLengthY = edgeLengthY * 0.5f;

    GLfloat vertices[] =
    {
        // front face
        centerPosX - halfSideLengthX, centerPosY + halfSideLengthY, centerPosZ, // top left
        centerPosX + halfSideLengthX, centerPosY + halfSideLengthY, centerPosZ, // top right
        centerPosX + halfSideLengthX, centerPosY - halfSideLengthY, centerPosZ, // bottom right
        centerPosX - halfSideLengthX, centerPosY - halfSideLengthY, centerPosZ, // bottom left


    };

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    if (color != 1) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);

    glDrawArrays(GL_QUADS, 0, 24);

    glDisableClientState(GL_VERTEX_ARRAY);
}

//This function draws a filled cube in position X, Y
void DrawCube(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength, int color)
{
    GLfloat halfSideLength = edgeLength * 0.5f;

    GLfloat vertices[] =
    {
        // front face
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top left
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top right
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom right
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom left

        // back face
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top left
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top right
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom right
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom left

        // left face
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top left
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top right
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom right
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom left

        // right face
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top left
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top right
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom right
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom left

        // top face
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top left
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top right
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // bottom right
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // bottom left

        // top face
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // top left
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // top right
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom right
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength  // bottom left
    };

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    if (color == 0)glColor4f(1.0f, 0.0f, 0.0f, 0.5f);
    if (color == 1)glColor4f(0.0f, 1.0f, 0.0f, 0.5f);
    if (color == 2)glColor4f(0.0f, 0.0f, 1.0f, 0.5f);
    if (color == 3)glColor4f(0.980, 0.396, 0.039, 0.5f);
    if (color == 4)glColor4f(0.980, 0.835, 0.039, 0.5f);
    if (color == 5)glColor4f(0.521, 0.043, 0.878, 0.5f);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);

    glDrawArrays(GL_QUADS, 0, 24);

    glDisableClientState(GL_VERTEX_ARRAY);
}

//This function draws a filled cube in position X, Y
void DrawCubeEdges(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength)
{
    GLfloat halfSideLength = edgeLength * 0.5f;

    GLfloat vertices[] =
    {
        // front face
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top left
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top right
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom right
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom left

        // back face
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top left
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top right
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom right
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom left

        // left face
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top left
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top right
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom right
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom left

        // right face
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top left
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top right
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom right
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom left

        // top face
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top left
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top right
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // bottom right
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // bottom left

        // top face
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // top left
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // top right
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom right
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength  // bottom left
    };




    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3f(1.0f, 1.0f, 1.0f);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);

    glDrawArrays(GL_QUADS, 0, 24);

    glDisableClientState(GL_VERTEX_ARRAY);
}

//This function draws th logo "TETRIS"
void DrawTetris3dLogo(GLfloat width, GLfloat height)
{
    GLfloat size = width / 60;

    /// T
    {
        DrawCube(width / 2 - size * 15, height - size, -500, size - 1, 0);
        DrawCubeEdges(width / 2 - size * 15, height - size, -500, size);
        DrawCube(width / 2 - size * 14, height - size, -500, size - 1, 0);
        DrawCubeEdges(width / 2 - size * 14, height - size, -500, size);
        DrawCube(width / 2 - size * 13, height - size, -500, size - 1, 0);
        DrawCubeEdges(width / 2 - size * 13, height - size, -500, size);
        DrawCube(width / 2 - size * 13, height - size * 2, -500, size - 1, 0);
        DrawCubeEdges(width / 2 - size * 13, height - size * 2, -500, size);
        DrawCube(width / 2 - size * 13, height - size * 3, -500, size - 1, 0);
        DrawCubeEdges(width / 2 - size * 13, height - size * 3, -500, size);
        DrawCube(width / 2 - size * 13, height - size * 4, -500, size - 1, 0);
        DrawCubeEdges(width / 2 - size * 13, height - size * 4, -500, size);
        DrawCube(width / 2 - size * 13, height - size * 5, -500, size - 1, 0);
        DrawCubeEdges(width / 2 - size * 13, height - size * 5, -500, size);
        DrawCube(width / 2 - size * 13, height - size * 6, -500, size - 1, 0);
        DrawCubeEdges(width / 2 - size * 13, height - size * 6, -500, size);
        DrawCube(width / 2 - size * 12, height - size, -500, size - 1, 0);
        DrawCubeEdges(width / 2 - size * 12, height - size, -500, size);
        DrawCube(width / 2 - size * 11, height - size, -500, size - 1, 0);
        DrawCubeEdges(width / 2 - size * 11, height - size, -500, size);
    }

    //E
    {
        DrawCube(width / 2 - size * 9, height - size, -500, size - 1, 1);
        DrawCubeEdges(width / 2 - size * 9, height - size, -500, size);
        DrawCube(width / 2 - size * 9, height - size * 2, -500, size - 1, 1);
        DrawCubeEdges(width / 2 - size * 9, height - size * 2, -500, size);
        DrawCube(width / 2 - size * 9, height - size * 3, -500, size - 1, 1);
        DrawCubeEdges(width / 2 - size * 9, height - size * 3, -500, size);
        DrawCube(width / 2 - size * 9, height - size * 4, -500, size - 1, 1);
        DrawCubeEdges(width / 2 - size * 9, height - size * 4, -500, size);
        DrawCube(width / 2 - size * 9, height - size * 5, -500, size - 1, 1);
        DrawCubeEdges(width / 2 - size * 9, height - size * 5, -500, size);
        DrawCube(width / 2 - size * 8, height - size, -500, size - 1, 1);
        DrawCubeEdges(width / 2 - size * 8, height - size, -500, size);
        DrawCube(width / 2 - size * 8, height - size * 3, -500, size - 1, 1);
        DrawCubeEdges(width / 2 - size * 8, height - size * 3, -500, size);
        DrawCube(width / 2 - size * 8, height - size * 5, -500, size - 1, 1);
        DrawCubeEdges(width / 2 - size * 8, height - size * 5, -500, size);
        DrawCube(width / 2 - size * 7, height - size, -500, size - 1, 1);
        DrawCubeEdges(width / 2 - size * 7, height - size, -500, size);
        DrawCube(width / 2 - size * 7, height - size * 3, -500, size - 1, 1);
        DrawCubeEdges(width / 2 - size * 7, height - size * 3, -500, size);
        DrawCube(width / 2 - size * 7, height - size * 5, -500, size - 1, 1);
        DrawCubeEdges(width / 2 - size * 7, height - size * 5, -500, size);
        DrawCube(width / 2 - size * 6, height - size, -500, size - 1, 1);
        DrawCubeEdges(width / 2 - size * 6, height - size, -500, size);
        DrawCube(width / 2 - size * 6, height - size * 5, -500, size - 1, 1);
        DrawCubeEdges(width / 2 - size * 6, height - size * 5, -500, size);
    }

    /// T
    {
        DrawCube(width / 2 - size * 4, height - size, -500, size - 1, 4);
        DrawCubeEdges(width / 2 - size * 4, height - size, -500, size);
        DrawCube(width / 2 - size * 3, height - size, -500, size - 1, 4);
        DrawCubeEdges(width / 2 - size * 3, height - size, -500, size);
        DrawCube(width / 2 - size * 2, height - size, -500, size - 1, 4);
        DrawCubeEdges(width / 2 - size * 2, height - size, -500, size);
        DrawCube(width / 2 - size * 2, height - size * 2, -500, size - 1, 4);
        DrawCubeEdges(width / 2 - size * 2, height - size * 2, -500, size);
        DrawCube(width / 2 - size * 2, height - size * 3, -500, size - 1, 4);
        DrawCubeEdges(width / 2 - size * 2, height - size * 3, -500, size);
        DrawCube(width / 2 - size * 2, height - size * 4, -500, size - 1, 4);
        DrawCubeEdges(width / 2 - size * 2, height - size * 4, -500, size);
        DrawCube(width / 2 - size * 2, height - size * 5, -500, size - 1, 4);
        DrawCubeEdges(width / 2 - size * 2, height - size * 5, -500, size);
        DrawCube(width / 2 - size * 1, height - size, -500, size - 1, 4);
        DrawCubeEdges(width / 2 - size * 1, height - size, -500, size);
        DrawCube(width / 2 - size * 0, height - size, -500, size - 1, 4);
        DrawCubeEdges(width / 2 - size * 0, height - size, -500, size);
    }

    ///R
    {
        DrawCube(width / 2 + size * 2, height - size, -500, size - 1, 3);
        DrawCubeEdges(width / 2 + size * 2, height - size, -500, size);
        DrawCube(width / 2 + size * 3, height - size, -500, size - 1, 3);
        DrawCubeEdges(width / 2 + size * 3, height - size, -500, size);
        DrawCube(width / 2 + size * 4, height - size, -500, size - 1, 3);
        DrawCubeEdges(width / 2 + size * 4, height - size, -500, size);
        DrawCube(width / 2 + size * 5, height - size, -500, size - 1, 3);
        DrawCubeEdges(width / 2 + size * 5, height - size, -500, size);
        DrawCube(width / 2 + size * 2, height - size * 2, -500, size - 1, 3);
        DrawCubeEdges(width / 2 + size * 2, height - size * 2, -500, size);
        DrawCube(width / 2 + size * 5, height - size * 2, -500, size - 1, 3);
        DrawCubeEdges(width / 2 + size * 5, height - size * 2, -500, size);
        DrawCube(width / 2 + size * 2, height - size * 3, -500, size - 1, 3);
        DrawCubeEdges(width / 2 + size * 2, height - size * 3, -500, size);
        DrawCube(width / 2 + size * 3, height - size * 3, -500, size - 1, 3);
        DrawCubeEdges(width / 2 + size * 3, height - size * 3, -500, size);
        DrawCube(width / 2 + size * 4, height - size * 3, -500, size - 1, 3);
        DrawCubeEdges(width / 2 + size * 4, height - size * 3, -500, size);
        DrawCube(width / 2 + size * 5, height - size * 3, -500, size - 1, 3);
        DrawCubeEdges(width / 2 + size * 5, height - size * 3, -500, size);

        DrawCube(width / 2 + size * 2, height - size * 4, -500, size - 1, 3);
        DrawCubeEdges(width / 2 + size * 2, height - size * 4, -500, size);
        DrawCube(width / 2 + size * 4, height - size * 4, -500, size - 1, 3);
        DrawCubeEdges(width / 2 + size * 4, height - size * 4, -500, size);


        DrawCube(width / 2 + size * 2, height - size * 5, -500, size - 1, 3);
        DrawCubeEdges(width / 2 + size * 2, height - size * 5, -500, size);
        DrawCube(width / 2 + size * 5, height - size * 5, -500, size - 1, 3);
        DrawCubeEdges(width / 2 + size * 5, height - size * 5, -500, size);

    }

    ///I
    {
        DrawCube(width / 2 + size * 7, height - size, -500, size - 1, 2);
        DrawCubeEdges(width / 2 + size * 7, height - size, -500, size);
        DrawCube(width / 2 + size * 7, height - size * 2, -500, size - 1, 2);
        DrawCubeEdges(width / 2 + size * 7, height - size * 2, -500, size);
        DrawCube(width / 2 + size * 7, height - size * 3, -500, size - 1, 2);
        DrawCubeEdges(width / 2 + size * 7, height - size * 3, -500, size);
        DrawCube(width / 2 + size * 7, height - size * 4, -500, size - 1, 2);
        DrawCubeEdges(width / 2 + size * 7, height - size * 4, -500, size);
        DrawCube(width / 2 + size * 7, height - size * 5, -500, size - 1, 2);
        DrawCubeEdges(width / 2 + size * 7, height - size * 5, -500, size);
    }

    ///S
    {

        DrawCube(width / 2 + size * 9, height - size * 2, -500, size - 1, 5);
        DrawCubeEdges(width / 2 + size * 9, height - size * 2, -500, size);
        DrawCube(width / 2 + size * 10, height - size, -500, size - 1, 5);
        DrawCubeEdges(width / 2 + size * 10, height - size, -500, size);
        DrawCube(width / 2 + size * 10, height - size * 3, -500, size - 1, 5);
        DrawCubeEdges(width / 2 + size * 10, height - size * 3, -500, size);
        DrawCube(width / 2 + size * 11, height - size, -500, size - 1, 5);
        DrawCubeEdges(width / 2 + size * 11, height - size, -500, size);
        DrawCube(width / 2 + size * 11, height - size * 4, -500, size - 1, 5);
        DrawCubeEdges(width / 2 + size * 11, height - size * 4, -500, size);
        DrawCube(width / 2 + size * 12, height - size, -500, size - 1, 5);
        DrawCubeEdges(width / 2 + size * 12, height - size, -500, size);
        DrawCube(width / 2 + size * 12, height - size * 5, -500, size - 1, 5);
        DrawCubeEdges(width / 2 + size * 12, height - size * 5, -500, size);
        DrawCube(width / 2 + size * 9, height - size * 6, -500, size - 1, 5);
        DrawCubeEdges(width / 2 + size * 9, height - size * 6, -500, size);
        DrawCube(width / 2 + size * 10, height - size * 6, -500, size - 1, 5);
        DrawCubeEdges(width / 2 + size * 10, height - size * 6, -500, size);
        DrawCube(width / 2 + size * 11, height - size * 6, -500, size - 1, 5);
        DrawCubeEdges(width / 2 + size * 11, height - size * 6, -500, size);



    }
}

void DrawGOaniamtion(GLfloat width, GLfloat height, float rot)
{

    //Makes the logo spin
    glPushMatrix();
    glTranslatef(width * 0.13, height * 0.8, -500);
    glRotatef(rot, 0.5, 1, 0.7);
    glTranslatef(-width * 0.1, -height * 0.8, 500);
    //Drawing blocks
    DrawCube(width * 0.13, height * 0.8, -500, (float)width / 22, 1);
    DrawCubeEdges(width * 0.13, height * 0.8, -500, (float)width / 22);
    glPopMatrix();

    //Makes the logo spin
    glPushMatrix();
    glTranslatef(width * 0.25, height * 0.6, -500);
    glRotatef(rot, 0.2, 1.3, 0.9);
    glTranslatef(-width * 0.25, -height * 0.6, 500);
    //Drawing blocks
    DrawCube(width * 0.25, height * 0.6, -500, (float)width / 25, 3);
    DrawCubeEdges(width * 0.25, height * 0.6, -500, (float)width / 25);
    glPopMatrix();

    //Makes the logo spin
    glPushMatrix();
    glTranslatef(width * 0.08, height * 0.3, -500);
    glRotatef(rot, 1.5, 0.3, 0.9);
    glTranslatef(-width * 0.08, -height * 0.3, 500);
    //Drawing blocks
    DrawCube(width * 0.08, height * 0.3, -500, (float)width / 18, 2);
    DrawCubeEdges(width * 0.08, height * 0.3, -500, (float)width / 18);
    glPopMatrix();


    //Makes the logo spin
    glPushMatrix();
    glTranslatef(width * 0.8, height * 0.8, -500);
    glRotatef(rot, 1, 0.3, 0.6);
    glTranslatef(-width * 0.8, -height * 0.8, 500);
    //Drawing blocks
    DrawCube(width * 0.8, height * 0.8, -500, (float)width / 23, 0);
    DrawCubeEdges(width * 0.8, height * 0.8, -500, (float)width / 23);
    glPopMatrix();

    //Makes the logo spin
    glPushMatrix();
    glTranslatef(width * 0.92, height * 0.4, -500);
    glRotatef(rot, 0.36, 0.98, 1.4);
    glTranslatef(-width * 0.92, -height * 0.4, 500);
    //Drawing blocks
    DrawCube(width * 0.92, height * 0.4, -500, (float)width / 20, 4);
    DrawCubeEdges(width * 0.92, height * 0.4, -500, (float)width / 20);
    glPopMatrix();



}

void DrawSearch(GLfloat width, GLfloat height, float rot, int time)
{

    if (time > 2000)
    {
        //Makes the logo spin
        glPushMatrix();
        glTranslatef(width * 0.2, height * 0.4, -500);
        glRotatef(rot, 0.5, 1, 0.7);
        glTranslatef(-width * 0.2, -height * 0.4, 500);
        //Drawing blocks
        DrawCube(width * 0.2, height * 0.4, -500, (float)width / 20, 0);
        DrawCubeEdges(width * 0.2, height * 0.4, -500, (float)width / 20);
        glPopMatrix();
    }

    if (time > 4000)
    {
        //Makes the logo spin
        glPushMatrix();
        glTranslatef(width * 0.4, height * 0.4, -500);
        glRotatef(rot, 0.5, 1, 0.7);
        glTranslatef(-width * 0.4, -height * 0.4, 500);
        //Drawing blocks
        DrawCube(width * 0.4, height * 0.4, -500, (float)width / 20, 1);
        DrawCubeEdges(width * 0.4, height * 0.4, -500, (float)width / 20);
        glPopMatrix();
    }

    if (time > 6000)
    {
        //Makes the logo spin
        glPushMatrix();
        glTranslatef(width * 0.6, height * 0.4, -500);
        glRotatef(rot, 0.5, 1, 0.7);
        glTranslatef(-width * 0.6, -height * 0.4, 500);
        //Drawing blocks
        DrawCube(width * 0.6, height * 0.4, -500, (float)width / 20, 2);
        DrawCubeEdges(width * 0.6, height * 0.4, -500, (float)width / 20);
        glPopMatrix();
    }

    if (time  > 8000)
    {
        //Makes the logo spin
        glPushMatrix();
        glTranslatef(width * 0.8, height * 0.4, -500);
        glRotatef(rot, 0.5, 1, 0.7);
        glTranslatef(-width * 0.8, -height * 0.4, 500);
        //Drawing blocks
        DrawCube(width * 0.8, height * 0.4, -500, (float)width / 20, 3);
        DrawCubeEdges(width * 0.8, height * 0.4, -500, (float)width / 20);
        glPopMatrix();
    }



}