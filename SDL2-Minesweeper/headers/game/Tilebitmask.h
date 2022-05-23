#pragma once

namespace Minesweeper {
	enum class Tilebitmask {
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