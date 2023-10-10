#include "World01.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"

namespace nc
{
    bool World01::Initialize()
    {
        for (int i = 0; i < 10; i++)
        {
            m_positions.push_back({ randomf(-1, 1), randomf(-1, 1) });
        }

        return true;
    }

    void World01::Shutdown()
    {
    }

    void World01::Update(float dt)
    {
        m_angle += 90 * dt;
        m_position.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_A) ? -dt : 0;
        m_position.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_D) ? +dt : 0;

        m_time += dt;
    }

    void World01::Draw(Renderer& renderer)
    {
        // pre-render
        renderer.BeginFrame();

        for (int i = 0; i < 10; i++)
        {
            // render
            glPushMatrix();
            glTranslatef(m_positions[i].x/5, m_positions[i].y/5, 0);
            glRotatef(m_angle + i * 20, 0, 0, 1); // Rotate each triangle differently

            glBegin(GL_POLYGON); // Use GL_POLYGON for a filled shape

            // Generate a random color for each triangle
            glColor3f(static_cast<float>(rand()) / RAND_MAX,
                static_cast<float>(rand()) / RAND_MAX,
                static_cast<float>(rand()) / RAND_MAX);

            for (float angle = 0; angle < 2 * M_PI; angle += M_PI / 3)
            {
                // Create a hexagon by drawing 6 vertices
                float x = 0.3f * cos(angle);
                float y = 0.3f * sin(angle);
                glVertex2f(x, y);
            }

            glEnd();

            glPopMatrix();
        }

        // post-render
        renderer.EndFrame();
    }

    /*
    void World01::Draw(Renderer& renderer)
    {
        // pre-render
        renderer.BeginFrame();

        for (int i = 0; i < 50; i++)
        {
            // render
            glPushMatrix();
            glTranslatef(m_positions[i].x, m_positions[i].y, 0);
            //glRotatef(m_angle, 0, 0, 1);
            //glScalef(sin(m_time * 5) * 0.5f, 1, 1);

            glBegin(GL_TRIANGLES);

            glColor3f(0, 1, 0.5);
            glVertex2f(0.5f, 0.5f);

            glColor3f(0.5, 1, 0);
            glVertex2f(randomf(0.1f), randomf(0.1f));

            glColor3f(1, 0.4, 0.5);
            glVertex2f(randomf(0.1f), randomf(0.1f));

            glEnd();

            glPopMatrix();
        }

        // post-render
        renderer.EndFrame();
    }*/
    


}
