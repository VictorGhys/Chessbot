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
	Bitboard GetAllMoves(bool fromWhite, bool withKingMoves) const;
	Bitboard GetMoves(Piece p, Square s, bool fromWhite) const;
	std::vector<Position> GetNextPositions();
	Position MakeNextPosition(Piece p, Square s, Square newSquare);
	void DeletePiece(Position& nextPos, Piece p, Square s);
	Piece GetPiece(const Square& s) const;
	void Print();
	bool isInCheck();

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
