#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

struct Character {
	GLuint     TextureID;  // ID handle of the glyph texture
	glm::ivec2 Size;       // Size of glyph
	glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
	GLuint     Advance;    // Offset to advance to next glyph
};

struct Text {
	std::string text;  
	GLfloat x;     
	GLfloat y;   
	GLfloat scale;
	GLfloat colorR;
	GLfloat colorG;
	GLfloat colorB;

	Text(std::string t, GLfloat x_, GLfloat y_, GLfloat scale_, GLfloat colorR_, GLfloat colorG_, GLfloat colorB_)
	{
		text = t;
		x = x_;
		y = y_;
		scale = scale_;
		colorR = colorR_;
		colorG = colorG_;
		colorB = colorB_;
	}

};

class Writer
{
private:

	GLuint shader;
	GLuint buffer;
	std::map<GLchar, Character> Characters;

	std::vector<Text> textvector;
	

public:
	Writer() {};

	Writer(GLfloat width, GLfloat height)
	{
		glewInit();

		glCreateBuffers(1, &buffer);
		glNamedBufferStorage(buffer, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_STORAGE_BIT);

		shader = CompileShaders(true, true);
		glUseProgram(shader);

		FT_Library ft;
		FT_Init_FreeType(&ft);

		FT_Face face;
		FT_New_Face(ft, "arial.ttf", 0, &face);

		FT_Set_Pixel_Sizes(face, 0, 48);


		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		for (GLubyte c = 0; c < 128; c++) {
			FT_Load_Char(face, c, FT_LOAD_RENDER);

			GLuint texture;
			glCreateTextures(GL_TEXTURE_2D, 1, &texture);
			glTextureStorage2D(texture, 1, GL_R8, face->glyph->bitmap.width, face->glyph->bitmap.rows);
			glTextureSubImage2D(texture, 0, 0, 0, face->glyph->bitmap.width, face->glyph->bitmap.rows, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

			glBindTexture(GL_TEXTURE_2D, texture);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glBindTexture(GL_TEXTURE_2D, 0);

			Character character = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
			};
			Characters.insert(std::pair<GLchar, Character>(c, character));

		}

		FT_Done_Face(face);
		FT_Done_FreeType(ft);


		glm::mat4 projection = glm::ortho(0.0f, width, 0.0f, height);
		glUniformMatrix4fv(1, 1, GL_FALSE, glm::value_ptr(projection));
	}
	~Writer() {};

	GLuint CompileShaders(bool vs_b, bool fs_b) {

		GLuint shader_programme = glCreateProgram();

		GLuint vs, fs;

		if (vs_b) {
			FILE* vs_file;
			long vs_file_len;
			char* vertex_shader;

			vs_file = fopen("vs.glsl", "rb");

			fseek(vs_file, 0, SEEK_END);
			vs_file_len = ftell(vs_file);
			rewind(vs_file);

			vertex_shader = (char*)malloc(vs_file_len + 1);


			fread(vertex_shader, vs_file_len, 1, vs_file);
			vertex_shader[vs_file_len] = '\0';
			fclose(vs_file);

			vs = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vs, 1, &vertex_shader, NULL);
			glCompileShader(vs);

			GLint isCompiled = 0;
			glGetShaderiv(vs, GL_COMPILE_STATUS, &isCompiled);

			if (isCompiled == GL_FALSE) {
				GLint maxLength = 0;
				glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				char* error = (char*)malloc(maxLength);
				glGetShaderInfoLog(vs, maxLength, &maxLength, error);
				printf("Vertex shader error: ");
				printf(error);
				free(error);
			}

			glAttachShader(shader_programme, vs);
			free(vertex_shader);
		}
		if (fs_b) {
			FILE* fs_file;
			long fs_file_len;
			char* fragment_shader;

			fs_file = fopen("fs.glsl", "rb");

			fseek(fs_file, 0, SEEK_END);
			fs_file_len = ftell(fs_file);
			rewind(fs_file);

			fragment_shader = (char*)malloc(fs_file_len + 1);

			fread(fragment_shader, fs_file_len, 1, fs_file);
			fragment_shader[fs_file_len] = '\0';
			fclose(fs_file);

			fs = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fs, 1, &fragment_shader, NULL);
			glCompileShader(fs);

			GLint isCompiled = 0;
			glGetShaderiv(fs, GL_COMPILE_STATUS, &isCompiled);

			if (isCompiled == GL_FALSE) {
				GLint maxLength = 0;
				glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				char* error = (char*)malloc(maxLength);
				glGetShaderInfoLog(fs, maxLength, &maxLength, error);
				printf("Fragment shader error: ");
				printf(error);
				free(error);
			}

			glAttachShader(shader_programme, fs);
			free(fragment_shader);
		}

		glLinkProgram(shader_programme);

		if (vs_b) {
			glDeleteShader(vs);
		}
		if (fs_b) {
			glDeleteShader(fs);
		}

		return shader_programme;
	}

	void addText(Text text)
	{
		textvector.push_back(text);
	}

	void DrawText()

	{
		GLfloat width = 1200;
		GLfloat height = 680;
		//addText(Text("SINGLEPLAYER", width * 0.365, height * 0.58, (float)width / 1300, 1, 1, 1));

		glUseProgram(shader);

		GLuint vao;
		glCreateVertexArrays(1, &vao);
		glBindVertexArray(vao);
		glCreateBuffers(1, &buffer);
		glNamedBufferStorage(buffer, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_STORAGE_BIT);
		glVertexArrayVertexBuffer(vao, 0, buffer, 0, sizeof(GLfloat) * 4);
		glVertexArrayAttribFormat(vao, 0, 4, GL_FLOAT, GL_FALSE, 0);
		glVertexArrayAttribBinding(vao, 0, 0);
		glEnableVertexArrayAttrib(vao, 0);


		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


		std::string::const_iterator c;

		for (auto& element : textvector)
		{
			glUniform3f(6, element.colorR, element.colorG, element.colorB);

			for (c = element.text.begin(); c != element.text.end(); c++)
			{
				Character ch = Characters[*c];
				GLfloat xpos = element.x + ch.Bearing.x * element.scale;
				GLfloat ypos = element.y - (ch.Size.y - ch.Bearing.y) * element.scale;

				GLfloat w = ch.Size.x * element.scale;
				GLfloat h = ch.Size.y * element.scale;
				// Update VBO for each character
				GLfloat vertices[6 * 4] = {
					 xpos,     ypos + h,   0.0f, 0.0f ,
					 xpos,     ypos,       0.0f, 1.0f ,
					 xpos + w, ypos,       1.0f, 1.0f ,

					 xpos,     ypos + h,   0.0f, 0.0f ,
					 xpos + w, ypos,       1.0f, 1.0f ,
					 xpos + w, ypos + h,   1.0f, 0.0f
				};

				glColor3f(0.0f, 1.0f, 0.0f);
				glNamedBufferSubData(buffer, 0, sizeof(GLfloat) * 6 * 4, vertices);
				glBindTexture(GL_TEXTURE_2D, ch.TextureID);
				glDrawArrays(GL_TRIANGLES, 0, 6);
				element.x += (ch.Advance >> 6) * element.scale;

			}

		}

		glUseProgram(0);
		glBindVertexArray(0);

		textvector.clear();

	}


};






