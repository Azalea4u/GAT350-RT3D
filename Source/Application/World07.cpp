#include "World07.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"

#include <glm/glm/gtc/type_ptr.hpp>
#include <glm/glm/gtx/color_space.hpp>

namespace nc
{
    bool World07::Initialize()
    {
        m_scene = std::make_unique<Scene>();
        m_scene->Load("Scenes/scene_Shadow.json");
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

    void World07::Shutdown()
    {
    }

    void World07::Update(float dt)
    {
        m_time += dt;

        ENGINE.GetSystem<Gui>()->BeginFrame();

        m_scene->Update(dt);
        m_scene->ProcessGui();

        // set post_process shader
        auto program = GET_RESOURCE(Program, "Shaders/post_process.prog");
        if (program)
        {
            program->Use();
            program->SetUniform("time", m_time);
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

    void World07::Draw(Renderer& renderer)
    {
        // *** PASS 1 *** //
        /*
        m_scene->GetActorByName("post_process")->active = false;

        auto framebuffer = GET_RESOURCE(Framebuffer, "fb");
        renderer.SetViewport(framebuffer->GetSize().x, framebuffer->GetSize().y);
        framebuffer->Bind();

        renderer.BeginFrame();
        m_scene->Draw(renderer);

        framebuffer->Unbind();
        */

        // *** PASS 2 *** //
        renderer.ResetViewport();
        renderer.BeginFrame();
        m_scene->Draw(renderer);

        // post-render
        ENGINE.GetSystem<Gui>()->Draw();
        renderer.EndFrame();
    } 
}
