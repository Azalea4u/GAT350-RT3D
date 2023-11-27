#pragma once

namespace nc
{
	struct ray_t
	{
		ray_t() = default;
		ray_t(const glm::vec3& origin, const glm::vec3& direction) : 
			origin(origin), 
			direction(direction) 
		{}

		glm::vec3 GetPoint(float distance) const { return origin + (direction * distance); }

		glm::vec3 origin{ 0 };
		glm::vec3 direction{ 0 };
	};

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