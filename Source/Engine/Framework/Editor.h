#pragma once

namespace nc
{
	class Editor
	{
	public:
		void ProcesssGui(class Scene* scene);

	private:
		class Object* m_selected{ nullptr };
	};
}