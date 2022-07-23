
#ifndef INCLUDED_TILEBITMASK
#define INCLUDED_TILEBITMASK

#include <cstdint>

namespace Minesweeper {
	enum Tilebitmask : uint8_t {
		None = 0,
		Flag = 1,
		Bomb = 2,
		Covered = 4,
		Uncovered = 8,
		Numbered = 16,
		Hit = 32
	};

	inline Tilebitmask operator|(const Tilebitmask& lhs, const Tilebitmask& rhs) {
		return (Tilebitmask)((int)lhs | (int)rhs);
	}

	inline Tilebitmask operator&(const Tilebitmask& lhs, const Tilebitmask& rhs) {
		return (Tilebitmask)((int)lhs & (int)rhs);
	}

	inline Tilebitmask operator~(Tilebitmask rhs) {
		return (Tilebitmask)(~(int)rhs);
	}

	inline Tilebitmask& operator&=(Tilebitmask& lhs, const Tilebitmask& rhs) {
		return (Tilebitmask&)((int&)lhs &= (int)rhs);
	}

	inline Tilebitmask& operator|=(Tilebitmask& lhs, const Tilebitmask& rhs) {
		return (Tilebitmask&)((int&)lhs |= (int)rhs);
	}
}
#endif