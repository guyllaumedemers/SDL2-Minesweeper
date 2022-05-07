#pragma once

namespace Minesweeper {
	enum class Tilebitmask {
		None = 0,
		Empty = 1,
		Flag = 2,
		Bomb = 4,
		Covered = 8,
		Uncovered = 16,
		Numbered = 32
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