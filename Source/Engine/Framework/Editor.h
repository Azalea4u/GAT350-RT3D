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
		bool m_active{ true };
		class Object* m_selected{ nullptr };
		class Object* m_rename { nullptr };

		ResourceType m_currentResourceType{ ResourceType::TEXTURE };
	};
}