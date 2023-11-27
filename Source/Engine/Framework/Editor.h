#pragma once

namespace nc
{
	enum class ResourceType {
		TEXTURE,
		MODEL,
		MATERIAL,
		SHADER
	};

	class Editor
	{
	public:
		void Update();
		void ProcesssGui(class Scene* scene);
		void RenderResourceFilter();

	private:
		bool m_active{ false };
		class Object* m_selected{ nullptr };

		ResourceType m_currentResourceType{ ResourceType::TEXTURE };
	};
}