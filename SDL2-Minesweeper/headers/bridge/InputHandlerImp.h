
#ifndef INCLUDED_INPUTHANDLERIMP
#define INCLUDED_INPUTHANDLERIMP

namespace Toolset {
	template<class GraphicAPIsEvent>
	class InputHandlerImp {
	protected:
		InputHandlerImp() = default;
	public:
		InputHandlerImp(const InputHandlerImp&) = delete;
		InputHandlerImp(InputHandlerImp&&) = delete;
		virtual ~InputHandlerImp() = 0;
		InputHandlerImp& operator=(const InputHandlerImp&) = delete;
		InputHandlerImp& operator=(InputHandlerImp&&) = delete;
		virtual void pollEvents(GraphicAPIsEvent&) = 0;
		virtual void getMouseState(int&, int&) = 0;
	};

	template<class GraphicAPIsEvent>
	inline InputHandlerImp<GraphicAPIsEvent>::~InputHandlerImp()
	{}
}
#endif