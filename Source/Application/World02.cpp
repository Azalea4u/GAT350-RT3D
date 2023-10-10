#include "World02.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"

//#define INTERLEAVE
#define INDEX

namespace nc
{
    bool World02::Initialize()
    {
        // shaders
        const char* vertexShader =
            "#version 430\n"
            "layout (location=0) in vec3 position;"
            "layout (location=1) in vec3 color;"
            "layout (location=0) out vec3 ocolor;"
            "void main() {"
            "  ocolor = color;"
            "  gl_Position = vec4(position, 1.0);"
            "}";

        const char* fragmentShader =
            "#version 430\n"
            "layout (location=0) in vec3 color;"
            "out vec4 ocolor;"
            "void main() {"
            "  ocolor = vec4(color, 1);"
            "}";

        GLuint vs = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vs, 1, &vertexShader, NULL);
        glCompileShader(vs);

        GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fs, 1, &fragmentShader, NULL);
        glCompileShader(fs);

        GLuint program = glCreateProgram();
        glAttachShader(program, vs);
        glAttachShader(program, fs);
        glLinkProgram(program);
        glUseProgram(program);

#ifdef INTERLEAVE

        // vertex data
        float vertexData[] = { // position for 3, color for 3
            -0.8f, -0.8f, 0.0f, 1.0f, 0.0f, 0.0f,
            -0.8f,  0.8f, 0.0f, 0.0f, 1.0f, 0.0f, 
             0.8f, -0.8f, 0.0f, 0.0f, 0.0f, 1.0f,
             0.8f,  0.8f, 0.0f, 1.0f, 1.0f, 1.0f,
        };

        GLuint vbo;
        glGenBuffers(1, &vbo); // Create a Vertex Buffer Object
        glBindBuffer(GL_ARRAY_BUFFER, vbo); // Set Vertex Buffer Object as current/active buffer
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW); // Set Vertex Data in VBO

        glGenVertexArrays(1, &m_vao); // Create a Vertex Array Object
        glBindVertexArray(m_vao); // Set Vertex Array Object as current/active object

        glBindVertexBuffer(0, vbo, 0, 6 * sizeof(GLfloat));

        // position
        glEnableVertexAttribArray(0);
        glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0);
        glVertexAttribBinding(0, 0);

        // color
        glEnableVertexAttribArray(1);
        glVertexAttribFormat(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat));
        glVertexAttribBinding(1, 0);

#elif defined(INDEX)
        // vertex data
        const float vertexData[] = {
             -1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f, // top-left
              1.0f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top-right
              1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-right
             -1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f  // bottom-left
        };

        GLuint indices[] =
        {
			0, 1, 2,
			2, 3, 0
		};

        // Vertex Buffer Object
        GLuint vbo;
        glGenBuffers(1, &vbo); // Create a Vertex Buffer Object
        glBindBuffer(GL_ARRAY_BUFFER, vbo); // Set Vertex Buffer Object as current/active buffer
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW); // Set Vertex Data in VBO

        // Index Buffer Object
        GLuint ibo;
        glGenBuffers(1, &ibo); // Create a Index Buffer Object
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo); // Set Index Buffer Object as current/active buffer
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); // Set Index Data in IBO

        // Vertex Array Object
        glGenVertexArrays(1, &m_vao); // Create a Vertex Array Object
        glBindVertexArray(m_vao); // Set Vertex Array Object as current/active object

        glBindVertexBuffer(0, vbo, 0, 6 * sizeof(GLfloat));
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

        // position
        glEnableVertexAttribArray(0);
        glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0);
        glVertexAttribBinding(0, 0);

        // color
        glEnableVertexAttribArray(1);
        glVertexAttribFormat(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat));
        glVertexAttribBinding(1, 0);

#else
        // vertex data
        float position_data[] = {
            -0.8f, -0.8f, 0.0f,
            -0.8f,  0.8f, 0.0f,
             0.8f, -0.8f, 0.0f,
             0.0f,  0.8f, 0.0f,
        };

#endif
        return true;
    }

    void World02::Shutdown()
    {
    }

    void World02::Update(float dt)
    {
        m_angle += 90 * dt;
        m_position.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_A) ? -dt : 0;
        m_position.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_D) ? +dt : 0;

        m_time += dt;
    }

    void World02::Draw(Renderer& renderer)
    {
        // pre-render
        renderer.BeginFrame();

        // render
        glBindVertexArray(m_vao);

#ifdef INDEX
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
#else
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
#endif

        // post-render
        renderer.EndFrame();
    }

}