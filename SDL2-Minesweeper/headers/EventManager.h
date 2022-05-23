#pragma once
#include "EventHandler.h"
#include <string>
#include <unordered_map>

using namespace std;
namespace Toolset {
	class EventManager {
	private:
		static string event_pool[5];
	public:
		static unordered_map<string, EventHandler*> events;
		static void create();
		static void destroy();
		static EventHandler* get(string key);
	};
}