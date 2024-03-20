#pragma once

#include "MyView/Layer.h"

#include "MyView/Events/MouseEvent.h"
#include "MyView/Events/ApplicationEvent.h"
#include "MyView/Events/KeyEvent.h"

namespace MyView {

	class MYVIEW_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
		
	private:
		float m_Time = 0.f;
	};
}