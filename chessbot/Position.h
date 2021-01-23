#pragma once
#include "Bitboard.h"
class Position
{
public:
	Position();
	~Position();
	Position(const Position& other);
	Position(Position&& other) noexcept;
	Position& operator=(const Position& other);
	Position& operator=(Position&& other) noexcept;

	float Evaluate() const;
	Bitboard GetAllMoves(bool fromWhite, bool withKingMoves, bool attacksOnly) const;
	Bitboard GetMoves(Piece p, Square s, bool fromWhite, bool attacksOnly, bool capturesOnly) const;
	std::vector<Position> GetNextPositions(bool capturesOnly) const;
	Position MakeNextPosition(Piece p, Square s, Square newSquare) const;
	void DeletePiece(Piece p, Square s);
	Piece GetPiece(Square s) const;
	void Print();
	bool isInCheck(bool white) const;

	Bitboard m_WhitePawns;
	Bitboard m_WhiteKnights;
	Bitboard m_WhiteBishops;
	Bitboard m_WhiteRooks;
	Bitboard m_WhiteKing;
	Bitboard m_WhiteQueen;

	Bitboard m_BlackPawns;
	Bitboard m_BlackKnights;
	Bitboard m_BlackBishops;
	Bitboard m_BlackRooks;
	Bitboard m_BlackKing;
	Bitboard m_BlackQueen;

	Bitboard m_AllWhitePieces;
	Bitboard m_AllBlackPieces;

	bool m_IsWhitesTurn;
	Bitboard m_NeverMoved;

	Square m_LastMovedSquare;
	Square m_LastMovedOriginalSquare;
};
