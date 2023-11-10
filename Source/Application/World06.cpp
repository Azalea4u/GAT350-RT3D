#include "World06.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"

#include <glm/glm/gtc/type_ptr.hpp>
#include <glm/glm/gtx/color_space.hpp>

namespace nc
{
    bool World06::Initialize()
    {
        m_scene = std::make_unique<Scene>();
        m_scene->Load("Scenes/scene_FrameBuffer.json");
        m_scene->Initialize();

        auto texture = std::make_shared<Texture>();
        texture->CreateTexture(1080, 1080);
        ADD_RESOURCE("fb_texture", texture);
        
        auto framebuffer = std::make_shared<Framebuffer>();
        framebuffer->CreateFramebuffer(texture);
        ADD_RESOURCE("fb", framebuffer);

        auto material = GET_RESOURCE(Material, "Materials/post_process.mtrl");
        if (material)
        {
            material->albedoTexture = texture;
        }

        return true;
    }

    void World06::Shutdown()
    {
    }

    void World06::Update(float dt)
    {
        m_time += dt;

        ENGINE.GetSystem<Gui>()->BeginFrame();

        m_scene->Update(dt);
        m_scene->ProcessGui();

        // set post_process gui
        ImGui::Begin("Post-Process");
        ImGui::SliderFloat("Blend", &m_blend, 0, 1);
        // Invert
        bool effect = m_params& INVERT_MASK;
        if (ImGui::Checkbox("Invert", &effect))
        {
            (effect) ? m_params |= INVERT_MASK : m_params ^= INVERT_MASK;
        }
        // Grayscale
        effect = m_params & GRAYSCALE_MASK;
        if (ImGui::Checkbox("Grayscale", &effect))
        {
            (effect) ? m_params |= GRAYSCALE_MASK : m_params ^= GRAYSCALE_MASK;
        }
        // Color Tint
        effect = m_params & COLORTINT_MASK;
        if (ImGui::Checkbox("Color Tint", &effect))
        {
            (effect) ? m_params |= COLORTINT_MASK : m_params ^= COLORTINT_MASK;
        }
        if (effect) // Show color picker when Color Tint is enabled
        {
            ImGui::ColorEdit3("Tint Color", glm::value_ptr(m_tint));
            ImGui::SliderFloat("Tint Intensity", &m_tintIntensity, 0, 1);
        }
        // Grain
        effect = m_params & GRAIN_MASK;
        if (ImGui::Checkbox("Grain", &effect))
        {
            (effect) ? m_params |= GRAIN_MASK : m_params ^= GRAIN_MASK;
        }
        // Scanline
        effect = m_params & SCANLINE_MASK;
        if (ImGui::Checkbox("Scanline", &effect))
        {
            (effect) ? m_params |= SCANLINE_MASK : m_params ^= SCANLINE_MASK;
        }
        // Kernel
        effect = m_params & RGB_MASK;
        if (ImGui::Checkbox("RGB Shift", &effect))
        {
            (effect) ? m_params |= RGB_MASK : m_params ^= RGB_MASK;
        }
        if (effect)
        {
        ImGui::SliderFloat2("Red Offset", glm::value_ptr(redOffset), -0.01f, 0.01f);
        ImGui::SliderFloat2("Green Offset", glm::value_ptr(greenOffset), -0.01f, 0.01f);
        ImGui::SliderFloat2("Blue Offset", glm::value_ptr(blueOffset), -0.01f, 0.01f);
        }

        ImGui::End();

        // set post_process shader
        auto program = GET_RESOURCE(Program, "Shaders/post_process.prog");
        if (program)
        {
            program->Use();
            program->SetUniform("blend", m_blend);            
            program->SetUniform("params", m_params);
            program->SetUniform("tint", m_tint);
            program->SetUniform("tintIntensity", m_tintIntensity);
            program->SetUniform("redOffset", redOffset);
            program->SetUniform("greenOffset", greenOffset);
            program->SetUniform("blueOffset", blueOffset);
		}

        ENGINE.GetSystem<Gui>()->EndFrame();
    }

    void World06::Draw(Renderer& renderer)
    {
        // *** PASS 1 *** //
        m_scene->GetActorByName("post_process")->active = false;

        auto framebuffer = GET_RESOURCE(Framebuffer, "fb");
        renderer.SetViewport(framebuffer->GetSize().x, framebuffer->GetSize().y);
        framebuffer->Bind();

        renderer.BeginFrame();
        m_scene->Draw(renderer);

        framebuffer->Unbind();

        // *** PASS 2 *** //
        m_scene->GetActorByName("post_process")->active = true;

        renderer.ResetViewport();
        renderer.BeginFrame();
        m_scene->GetActorByName("post_process")->Draw(renderer);

        // post-render
        ENGINE.GetSystem<Gui>()->Draw();
        renderer.EndFrame();
    } 
}
