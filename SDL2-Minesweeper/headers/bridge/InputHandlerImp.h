#pragma once

namespace Toolset {
	template<class GraphicAPIsEvent>
	class InputHandlerImp {
	private:
		InputHandlerImp(const InputHandlerImp&) = delete;
		InputHandlerImp(InputHandlerImp&&) = delete;
	protected:
		InputHandlerImp() = default;
	public:
		virtual ~InputHandlerImp() = 0 {};
		virtual void pollEvents(GraphicAPIsEvent&) = 0;
		virtual void getMouseState(int&, int&) = 0;
	};
}