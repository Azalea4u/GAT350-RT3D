#include "World04.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"

#include <glm/glm/gtc/type_ptr.hpp>

namespace nc
{
    bool World04::Initialize()
    {
        auto material = GET_RESOURCE(Material, "Materials/grid.mtrl"); 
        m_model = std::make_shared<Model>();
        m_model->SetMaterial(material);
        m_model->Load("Models/sphere.obj", glm::vec3{ 0 }, glm::vec3{ 90, 0, 0 });

        return true;
    }

    void World04::Shutdown()
    {
    }

    void World04::Update(float dt)
    {
        ENGINE.GetSystem<Gui>()->BeginFrame();

        ImGui::Begin("Transform");
        ImGui::DragFloat3("Position", &m_transform.position[0], 0.1f);
        ImGui::DragFloat3("Rotation", &m_transform.rotation[0]);
        ImGui::DragFloat3("Scale", &m_transform.scale[0]);
        ImGui::End();

        ImGui::Begin("Light");
        ImGui::DragFloat3("Position", glm::value_ptr(m_lightPosition), 0.1f);
        ImGui::ColorEdit3("Color", glm::value_ptr(m_lightColor));
        ImGui::ColorEdit3("Ambient Color", glm::value_ptr(m_ambientLight));
        ImGui::End();

        //m_transform.rotation.z += 180 * dt;

        m_transform.rotation.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_UP) ? 180 * dt : 0;
        m_transform.rotation.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_D) ? m_speed * +dt : 0;
        m_transform.rotation.z += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_W) ? m_speed * -dt : 0;
        m_transform.rotation.z += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_S) ? m_speed * +dt : 0;
        
        m_time += dt;

        auto material = m_model->GetMaterial();

        material->ProcessGui();
        material->Bind();

        material->GetProgram()->SetUniform("light.position", m_lightPosition);
        material->GetProgram()->SetUniform("light.color", m_lightColor);
        material->GetProgram()->SetUniform("ambientLight", m_ambientLight);

        // model matrix
        material->GetProgram()->SetUniform("model", m_transform.GetMatrix());

        // view matrix
        glm::mat4 view = glm::lookAt(glm::vec3{ 0, 0, 3 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 });
        material->GetProgram()->SetUniform("view", view);

        // projection
        glm::mat4 projection = glm::perspective(glm::radians(70.0f), ENGINE.GetSystem<Renderer>()->GetWidth() / (float)ENGINE.GetSystem<Renderer>()->GetHeight(), 0.01f, 100.0f);
        material->GetProgram()->SetUniform("projection", projection);

        ENGINE.GetSystem<Gui>()->EndFrame();
    }

    void World04::Draw(Renderer& renderer)
    {
        // pre-render
        renderer.BeginFrame();

        // render
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        m_model->Draw();

        ENGINE.GetSystem<Gui>()->Draw();

        // post-render
        renderer.EndFrame();
    }
      
}
