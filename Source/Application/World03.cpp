#include "World03.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"

#include <glm/glm/gtc/type_ptr.hpp>

namespace nc
{
    bool World03::Initialize()
    {
        m_material = GET_RESOURCE(Material, "Materials/quad.mtrl");

        //m_program = GET_RESOURCE(Program, "Shaders/unlit_texture.prog");
        //m_program->Use();

        //m_texture = GET_RESOURCE(Texture, "Textures/llama.png");
        //m_texture->Bind();
        //m_texture->SetActive(GL_TEXTURE0);

        // vertex data
        float vertexData[] = {
          -0.8f, -0.8f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
          -0.8f,  0.8f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
           0.8f, -0.8f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
           0.8f,  0.8f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f
        };

        //m_vertexBuffer = GET_RESOURCE(VertexBuffer, "vb");
        m_vertexBuffer = std::make_shared<VertexBuffer>();
        m_vertexBuffer->CreateVertexBuffer(sizeof(vertexData), 4, vertexData);
        m_vertexBuffer->SetAttribute(0, 3, 8 * sizeof(float), 0);                  // position
        m_vertexBuffer->SetAttribute(1, 3, 8 * sizeof(float), 3 * sizeof(float));  // color
        m_vertexBuffer->SetAttribute(2, 2, 8 * sizeof(float), 6 * sizeof(float));  // texcoord

        m_transform.rotation.z = 0;

        return true;
    }

    void World03::Shutdown()
    {
    }

    void World03::Update(float dt)
    {
        ENGINE.GetSystem<Gui>()->BeginFrame();

        ImGui::Begin("Transform");
        ImGui::DragFloat3("Position", &m_transform.position[0]);
        ImGui::DragFloat3("Scale", &m_transform.scale[0]);
        ImGui::End();

        //m_transform.rotation.z += 180 * dt;

        /*
        if (ENGINE.GetSystem<InputSystem>()->GetMouseButtonDown(0))
        {
			auto position = ENGINE.GetSystem<InputSystem>()->GetMousePosition();
            position += 2;
            position -= 1;
            position.y += -1;

            m_positions.push_back(position);
        }
        */

        m_transform.rotation.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_UP) ? 180 * dt : 0;
        m_transform.rotation.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_D) ? m_speed * +dt : 0;
        m_transform.rotation.z += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_W) ? m_speed * -dt : 0;
        m_transform.rotation.z += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_S) ? m_speed * +dt : 0;
        
        m_time += dt;

        m_material->ProcessGui();
        m_material->Bind();

        // model matrix
        m_material->GetProgram()->SetUniform("model", m_transform.GetMatrix());

        // view matrix
        glm::mat4 view = glm::lookAt(glm::vec3{ 0, 0, 3 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 });
        m_material->GetProgram()->SetUniform("view", view);

        // projection
        glm::mat4 projection = glm::perspective(glm::radians(70.0f), 800.0f / 600.0f, 0.01f, 100.0f);
        m_material->GetProgram()->SetUniform("projection", projection);

        ENGINE.GetSystem<Gui>()->EndFrame();

    }

    void World03::Draw(Renderer& renderer)
    {
        // pre-render
        renderer.BeginFrame();

        // render
        m_vertexBuffer->Draw(GL_TRIANGLE_STRIP);
        ENGINE.GetSystem<Gui>()->Draw();

        // post-render
        renderer.EndFrame();
    }
      
}
