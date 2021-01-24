#include "pch.h"
#include "Position.h"

Position::Position()
	: m_WhitePawns{ 0xFF00 }
	, m_WhiteKnights{ 0x42 }
	, m_WhiteBishops{ 0x24 }
	, m_WhiteRooks{ 0x81 }
	, m_WhiteKing{ 0x10 }
	, m_WhiteQueen{ 0x8 }
	, m_BlackPawns{ 0xFF000000000000 }
	, m_BlackKnights{ 0x4200000000000000 }
	, m_BlackBishops{ 0x2400000000000000 }
	, m_BlackRooks{ 0x8100000000000000 }
	, m_BlackKing{ 0x1000000000000000 }
	, m_BlackQueen{ 0x800000000000000 }
	, m_AllWhitePieces{ m_WhitePawns | m_WhiteKnights | m_WhiteBishops | m_WhiteRooks | m_WhiteKing | m_WhiteQueen }
	, m_AllBlackPieces{ m_BlackPawns | m_BlackKnights | m_BlackBishops | m_BlackRooks | m_BlackKing | m_BlackQueen }
	, m_NeverMoved{ m_AllBlackPieces | m_AllWhitePieces }
	, m_IsWhitesTurn{ true }
	, m_LastMovedSquare{}
	, m_LastMovedOriginalSquare{}
{
}

Position::Position(const Position& other)
	: m_WhitePawns{ other.m_WhitePawns }
	, m_WhiteKnights{ other.m_WhiteKnights }
	, m_WhiteBishops{ other.m_WhiteBishops }
	, m_WhiteRooks{ other.m_WhiteRooks }
	, m_WhiteKing{ other.m_WhiteKing }
	, m_WhiteQueen{ other.m_WhiteQueen }
	, m_BlackPawns{ other.m_BlackPawns }
	, m_BlackKnights{ other.m_BlackKnights }
	, m_BlackBishops{ other.m_BlackBishops }
	, m_BlackRooks{ other.m_BlackRooks }
	, m_BlackKing{ other.m_BlackKing }
	, m_BlackQueen{ other.m_BlackQueen }
	, m_AllWhitePieces{ m_WhitePawns | m_WhiteKnights | m_WhiteBishops | m_WhiteRooks | m_WhiteKing | m_WhiteQueen }
	, m_AllBlackPieces{ m_BlackPawns | m_BlackKnights | m_BlackBishops | m_BlackRooks | m_BlackKing | m_BlackQueen }
	, m_NeverMoved{ other.m_NeverMoved }
	, m_IsWhitesTurn{ other.m_IsWhitesTurn }
	, m_LastMovedSquare{other.m_LastMovedSquare}
	, m_LastMovedOriginalSquare{other.m_LastMovedOriginalSquare}
{
}

Position::Position(Position&& other) noexcept
	: m_WhitePawns{ other.m_WhitePawns }
	, m_WhiteKnights{ other.m_WhiteKnights }
	, m_WhiteBishops{ other.m_WhiteBishops }
	, m_WhiteRooks{ other.m_WhiteRooks }
	, m_WhiteKing{ other.m_WhiteKing }
	, m_WhiteQueen{ other.m_WhiteQueen }
	, m_BlackPawns{ other.m_BlackPawns }
	, m_BlackKnights{ other.m_BlackKnights }
	, m_BlackBishops{ other.m_BlackBishops }
	, m_BlackRooks{ other.m_BlackRooks }
	, m_BlackKing{ other.m_BlackKing }
	, m_BlackQueen{ other.m_BlackQueen }
	, m_AllWhitePieces{ m_WhitePawns | m_WhiteKnights | m_WhiteBishops | m_WhiteRooks | m_WhiteKing | m_WhiteQueen }
	, m_AllBlackPieces{ m_BlackPawns | m_BlackKnights | m_BlackBishops | m_BlackRooks | m_BlackKing | m_BlackQueen }
	, m_NeverMoved{ other.m_NeverMoved }
	, m_IsWhitesTurn{ other.m_IsWhitesTurn }
	, m_LastMovedSquare{ other.m_LastMovedSquare }
	, m_LastMovedOriginalSquare{ other.m_LastMovedOriginalSquare }
{
}
Position& Position::operator=(const Position& other)
{
	m_WhitePawns = other.m_WhitePawns;
	m_WhiteKnights = other.m_WhiteKnights;
	m_WhiteBishops= other.m_WhiteBishops ;
	m_WhiteRooks= other.m_WhiteRooks ;
	m_WhiteKing= other.m_WhiteKing ;
	m_WhiteQueen= other.m_WhiteQueen ;
	m_BlackPawns= other.m_BlackPawns ;
	m_BlackKnights= other.m_BlackKnights ;
	m_BlackBishops= other.m_BlackBishops ;
	m_BlackRooks= other.m_BlackRooks ;
	m_BlackKing= other.m_BlackKing ;
	m_BlackQueen= other.m_BlackQueen ;
	m_AllWhitePieces= m_WhitePawns | m_WhiteKnights | m_WhiteBishops | m_WhiteRooks | m_WhiteKing | m_WhiteQueen ;
	m_AllBlackPieces= m_BlackPawns | m_BlackKnights | m_BlackBishops | m_BlackRooks | m_BlackKing | m_BlackQueen ;
	m_NeverMoved= other.m_NeverMoved;
	m_IsWhitesTurn= other.m_IsWhitesTurn ;
	m_LastMovedSquare = other.m_LastMovedSquare;
	m_LastMovedOriginalSquare = other.m_LastMovedOriginalSquare;
	return *this;
}
Position& Position::operator=(Position&& other) noexcept
{
	m_WhitePawns = other.m_WhitePawns;
	m_WhiteKnights = other.m_WhiteKnights;
	m_WhiteBishops= other.m_WhiteBishops ;
	m_WhiteRooks= other.m_WhiteRooks ;
	m_WhiteKing= other.m_WhiteKing ;
	m_WhiteQueen= other.m_WhiteQueen ;
	m_BlackPawns= other.m_BlackPawns ;
	m_BlackKnights= other.m_BlackKnights ;
	m_BlackBishops= other.m_BlackBishops ;
	m_BlackRooks= other.m_BlackRooks ;
	m_BlackKing= other.m_BlackKing ;
	m_BlackQueen= other.m_BlackQueen ;
	m_AllWhitePieces= m_WhitePawns | m_WhiteKnights | m_WhiteBishops | m_WhiteRooks | m_WhiteKing | m_WhiteQueen ;
	m_AllBlackPieces= m_BlackPawns | m_BlackKnights | m_BlackBishops | m_BlackRooks | m_BlackKing | m_BlackQueen ;
	m_NeverMoved= other.m_NeverMoved;
	m_IsWhitesTurn= other.m_IsWhitesTurn ;
	m_LastMovedSquare = other.m_LastMovedSquare;
	m_LastMovedOriginalSquare = other.m_LastMovedOriginalSquare;
	return *this;
}

Position::~Position()
{
}

float Position::Evaluate() const
{
	const int pawnWeight{ 95 };
	const int knightWeight{ 320 };
	const int bishopWeight{ 330 };
	const int rookWeight{ 500 };
	const int queenWeight{ 900 };
	const int kingWeight{ 2000 };
	float score{};
	//pieces values
	score += (m_WhitePawns.GetAmount() - m_BlackPawns.GetAmount()) * pawnWeight;
	score += (m_WhiteKnights.GetAmount() - m_BlackKnights.GetAmount()) * knightWeight;
	score += (m_WhiteBishops.GetAmount() - m_BlackBishops.GetAmount()) * bishopWeight;
	score += (m_WhiteRooks.GetAmount() - m_BlackRooks.GetAmount()) * rookWeight;
	score += (m_WhiteQueen.GetAmount() - m_BlackQueen.GetAmount()) * queenWeight;
	score += (m_WhiteKing.GetAmount() - m_BlackKing.GetAmount()) * kingWeight;

	bool isEndGame{ !(m_WhiteQueen.GetData() | m_BlackQueen.GetData()) ||
		(Bitboard{m_AllWhitePieces.GetData() & ~m_WhitePawns.GetData() & ~m_WhiteKing.GetData()}.Count() < 2) &&
	(Bitboard{m_AllBlackPieces.GetData() & ~m_BlackPawns.GetData() & ~m_BlackKing.GetData()}.Count() < 2) };
	//mobility of the pieces
	//https://www.chessprogramming.org/Simplified_Evaluation_Function
	const float pawnMobility[8][8] = {
	 {0,  0,  0,  0,  0,  0,  0,  0},
	{50, 50, 50, 50, 50, 50, 50, 50},
	{10, 10, 20, 30, 30, 20, 10, 10},
	 {5,  5, 10, 25, 25, 10,  5,  5},
	 {0,  0,  0, 20, 20,  0,  0,  0},
	{5, -5,-10,  0,  0,-10, -5,  5},
	{5, 10, 10,-20,-20, 10, 10,  5},
	{0,  0,  0,  0,  0,  0,  0,  0}
	};

	const float knightMobility[8][8] = {
	{-50,-40,-30,-30,-30,-30,-40,-50},
	{-40,-20,  0,  0,  0,  0,-20,-40},
	{-30,  0, 10, 15, 15, 10,  0,-30},
	{-30,  5, 15, 20, 20, 15,  5,-30},
	{-30,  0, 15, 20, 20, 15,  0,-30},
	{-30,  5, 10, 15, 15, 10,  5,-30},
	{-40,-20,  0,  5,  5,  0,-20,-40},
	{-50,-40,-30,-30,-30,-30,-40,-50},
	};
	const float bishopMobility[8][8] = {
		{-20,-10,-10,-10,-10,-10,-10,-20},
		{-10,  0,  0,  0,  0,  0,  0,-10},
		{-10,  0,  5, 10, 10,  5,  0,-10},
		{-10,  5,  5, 10, 10,  5,  5,-10},
		{-10,  0, 10, 10, 10, 10,  0,-10},
		{-10, 10, 10, 10, 10, 10, 10,-10},
		{-10,  5,  0,  0,  0,  0,  5,-10},
		{-20,-10,-10,-10,-10,-10,-10,-20},
	};

	const float rookMobility[8][8] = {
	  {0,  0,  0,  0,  0,  0,  0,  0},
	  {5, 10, 10, 10, 10, 10, 10,  5},
	 {-5,  0,  0,  0,  0,  0,  0, -5},
	 {-5,  0,  0,  0,  0,  0,  0, -5},
	 {-5,  0,  0,  0,  0,  0,  0, -5},
	 {-5,  0,  0,  0,  0,  0,  0, -5},
	 {-5,  0,  0,  0,  0,  0,  0, -5},
	  {0,  0,  0,  5,  5,  0,  0,  0}
	};
	const float queenMobility[8][8] = {
		{-20,-10,-10, -5, -5,-10,-10,-20},
		{-10,  0,  0,  0,  0,  0,  0,-10},
		{-10,  0,  5,  5,  5,  5,  0,-10},
		 {-5,  0,  5,  5,  5,  5,  0, -5},
		  {0,  0,  5,  5,  5,  5,  0, -5},
		{-10,  5,  5,  5,  5,  5,  0,-10},
		{-10,  0,  5,  0,  0,  0,  0,-10},
		{-20,-10,-10, -5, -5,-10,-10,-20}
	};
	// king start and mid game
	const float kingMobility[8][8] = {
		{-30,-40,-40,-50,-50,-40,-40,-30},
		{-30,-40,-40,-50,-50,-40,-40,-30},
		{-30,-40,-40,-50,-50,-40,-40,-30},
		{-30,-40,-40,-50,-50,-40,-40,-30},
		{-20,-30,-30,-40,-40,-30,-30,-20},
		{-10,-20,-20,-20,-20,-20,-20,-10},
		{20, 20,  0,  0,  0,  0, 20, 20},
		{20, 30, 10,  0,  0, 10, 30, 20 },
	};
	// king end game
	const float kingEndMobility[8][8] = { 
		{-50, -40, -30, -20, -20, -30, -40, -50},
		{-30, -20, -10, 0, 0, -10, -20, -30},
		{-30, -10, 20, 30, 30, 20, -10, -30},
		{-30, -10, 30, 40, 40, 30, -10, -30},
		{-30, -10, 30, 40, 40, 30, -10, -30},
		{-30, -10, 20, 30, 30, 20, -10, -30},
		{-30, -30, 0, 0, 0, 0, -30, -30},
		{-50, -30, -30, -30, -30, -30, -30, -50} 
	};
	//white mobility
	for (std::pair<int, int> p : m_WhitePawns.GetPositions())
	{
		score += pawnMobility[p.first][p.second];
	}
	for (std::pair<int, int> p : m_WhiteKnights.GetPositions())
	{
		score += knightMobility[p.first][p.second];
	}
	for (std::pair<int, int> p : m_WhiteBishops.GetPositions())
	{
		score += bishopMobility[p.first][p.second];
	}
	for (std::pair<int, int> p : m_WhiteRooks.GetPositions())
	{
		score += rookMobility[p.first][p.second];
	}
	for (std::pair<int, int> p : m_WhiteQueen.GetPositions())
	{
		score += queenMobility[p.first][p.second];
	}
	for (std::pair<int, int> p : m_WhiteKing.GetPositions())
	{
		if (isEndGame)
		{
			score += kingEndMobility[p.first][p.second];
		}
		else
		{
			score += kingMobility[p.first][p.second];
		}
	}
	//black mobility
	for (std::pair<int, int> p : m_BlackPawns.GetPositions())
	{
		score -= pawnMobility[8-p.first][p.second];
	}
	for (std::pair<int, int> p : m_BlackKnights.GetPositions())
	{
		score -= knightMobility[8-p.first][p.second];
	}
	for (std::pair<int, int> p : m_BlackBishops.GetPositions())
	{
		score -= bishopMobility[8-p.first][p.second];
	}
	for (std::pair<int, int> p : m_BlackRooks.GetPositions())
	{
		score -= rookMobility[8-p.first][p.second];
	}
	for (std::pair<int, int> p : m_BlackQueen.GetPositions())
	{
		score -= queenMobility[8-p.first][p.second];
	}
	for (std::pair<int, int> p : m_BlackKing.GetPositions())
	{
		if (isEndGame)
		{
			score -= kingEndMobility[8 - p.first][p.second];
		}
		else
		{
			score -= kingMobility[8 - p.first][p.second];
		}
	}

	if (m_IsWhitesTurn)
	{
		return score;
	}
	else
	{
		return score * -1;
	}
}

Bitboard Position::GetMoves(Piece p, Square s, bool fromWhite, bool attacksOnly, bool capturesOnly) const
{
	Bitboard result{ 0 };
	uint64_t allpieces = m_AllBlackPieces.GetData() | m_AllWhitePieces.GetData();
	if (fromWhite)
	{
		Bitboard otherRook{ m_WhiteRooks };
		switch (p)
		{
		case NO_PIECE:
			break;
		case W_PAWN:
			if (attacksOnly)
			{
				result = m_WhitePawns.GetPawnsPossibleAttacks(s, m_AllBlackPieces.GetData(), W_PAWN);
			}
			else
			{
				result = m_WhitePawns.GetPawnsPossibleMoves(s, m_AllWhitePieces.GetData() | m_AllBlackPieces.GetData(), W_PAWN, m_LastMovedSquare, m_LastMovedOriginalSquare, m_BlackPawns.GetData())
					& ~allpieces | m_WhitePawns.GetPawnsPossibleAttacks(s, m_AllBlackPieces.GetData(), W_PAWN);
			}
			break;
		case W_KNIGHT:
			result = m_WhiteKnights.GetKnightPossibleMoves(s, m_AllWhitePieces.GetData());
			break;
		case W_BISHOP:
			result = m_WhiteBishops.GetBishopPossibleMoves(s, allpieces & ~m_WhiteBishops.GetData());
			break;
		case W_ROOK:
			otherRook.Reset(s);
			result = m_WhiteRooks.GetRookPossibleMoves(s, allpieces & ~m_WhiteRooks.GetData() | otherRook.GetData());
			break;
		case W_QUEEN:
			result = m_WhiteQueen.GetQueenPossibleMoves(s, allpieces & ~m_WhiteQueen.GetData());
			break;
		case W_KING:
			result = m_WhiteKing.GetKingPossibleMoves(s, m_AllWhitePieces.GetData(), W_KING, m_NeverMoved, m_BlackKing.GetSquarePositions().front(), true);
			result = result & ~GetAllMoves(false, false, true).GetData();
			break;
		case PIECE_NB:
			break;
		default:
			break;
		}
		//can't move to a position where you already have a piece
		result = result & ~m_AllWhitePieces.GetData();
		if (capturesOnly)
		{
			result = result & m_AllBlackPieces;
		}
	}
	else
	{
		Bitboard otherRook{ m_BlackRooks };
		switch (p)
		{
		case NO_PIECE:
			break;
		case B_PAWN:
			if (attacksOnly)
			{
				result = m_BlackPawns.GetPawnsPossibleAttacks(s, m_AllWhitePieces.GetData(), B_PAWN);
			}
			else
			{
				result = m_BlackPawns.GetPawnsPossibleMoves(s, m_AllBlackPieces.GetData() | m_AllWhitePieces.GetData(), B_PAWN, m_LastMovedSquare, m_LastMovedOriginalSquare, m_WhitePawns.GetData())
					& ~m_AllWhitePieces.GetData() | m_BlackPawns.GetPawnsPossibleAttacks(s, m_AllWhitePieces.GetData(), B_PAWN);
			}
			break;
		case B_KNIGHT:
			result = m_BlackKnights.GetKnightPossibleMoves(s, m_AllBlackPieces.GetData());
			break;
		case B_BISHOP:
			result = m_BlackBishops.GetBishopPossibleMoves(s, allpieces & ~m_BlackBishops.GetData());
			break;
		case B_ROOK:
			otherRook.Reset(s);
			result = m_BlackRooks.GetRookPossibleMoves(s, allpieces & ~m_BlackRooks.GetData() | otherRook.GetData());
			break;
		case B_QUEEN:
			result = m_BlackQueen.GetQueenPossibleMoves(s, allpieces & ~m_BlackQueen.GetData());
			break;
		case B_KING:
			result = m_BlackKing.GetKingPossibleMoves(s, m_AllBlackPieces.GetData(), B_KING, m_NeverMoved, m_WhiteKing.GetSquarePositions().front(), true);
			result = result & ~GetAllMoves(true, false, true).GetData();
			break;
		case PIECE_NB:
			break;
		default:
			break;
		}
		//can't move to a position where you already have a piece
		result = result & ~m_AllBlackPieces.GetData();
		if (capturesOnly)
		{
			result = result & m_AllWhitePieces;
		}
	}
	return result;
}
Bitboard Position::GetAllMoves(bool fromWhite, bool withKingMoves, bool attacksOnly) const
{
	Bitboard result{ 0 };
	if (fromWhite)
	{
		for (Square p : m_WhitePawns.GetSquarePositions())
		{
			result = result | GetMoves(W_PAWN, p, fromWhite, attacksOnly, false);
		}
		for (Square p : m_WhiteKnights.GetSquarePositions())
		{
			result = result | GetMoves(W_KNIGHT, p, fromWhite, attacksOnly, false);
		}
		for (Square p : m_WhiteBishops.GetSquarePositions())
		{
			result = result | GetMoves(W_BISHOP, p, fromWhite, attacksOnly, false);
		}
		for (Square p : m_WhiteRooks.GetSquarePositions())
		{
			result = result | GetMoves(W_ROOK, p, fromWhite, attacksOnly, false);
		}
		for (Square p : m_WhiteQueen.GetSquarePositions())
		{
			result = result | GetMoves(W_QUEEN, p, fromWhite, attacksOnly, false);
		}
		if (withKingMoves)
		{
			for (Square p : m_WhiteKing.GetSquarePositions())
			{
				result = result | GetMoves(W_KING, p, fromWhite, attacksOnly, false);
			}
		}
	}
	else
	{
		for (Square p : m_BlackPawns.GetSquarePositions())
		{
			result = result | GetMoves(B_PAWN, p, fromWhite, attacksOnly, false);
		}
		for (Square p : m_BlackKnights.GetSquarePositions())
		{
			result = result | GetMoves(B_KNIGHT, p, fromWhite, attacksOnly, false);
		}
		for (Square p : m_BlackBishops.GetSquarePositions())
		{
			result = result | GetMoves(B_BISHOP, p, fromWhite, attacksOnly, false);
		}
		for (Square p : m_BlackRooks.GetSquarePositions())
		{
			result = result | GetMoves(B_ROOK, p, fromWhite, attacksOnly, false);
		}
		for (Square p : m_BlackQueen.GetSquarePositions())
		{
			result = result | GetMoves(B_QUEEN, p, fromWhite, attacksOnly, false);
		}
		if (withKingMoves)
		{
			for (Square p : m_BlackKing.GetSquarePositions())
			{
				result = result | GetMoves(B_KING, p, fromWhite, attacksOnly, false);
			}
		}
	}
	return result;
}

std::vector<Position> Position::GetNextPositions(bool capturesOnly) const
{
	std::vector<Position> nextPositions{};
	Position nextPossition;
	if (m_IsWhitesTurn)
	{
		for (Square p : m_WhitePawns.GetSquarePositions())
		{
			for (Square np : GetMoves(W_PAWN, p, m_IsWhitesTurn, false, capturesOnly).GetSquarePositions())
			{
				nextPossition = MakeNextPosition(W_PAWN, p, np);
				//en passant
				if (m_LastMovedSquare == np - 8 && m_BlackPawns.GetData() & Bitboard::SquareToBitBoard(Square(np-8)))
				{
					nextPossition.m_BlackPawns.Reset(Square(np - 8));
				}
				if (!nextPossition.isInCheck(true))
				{
					nextPositions.push_back(nextPossition);
				}
			}
		}
		for (Square p : m_WhiteKnights.GetSquarePositions())
		{
			for (Square np : GetMoves(W_KNIGHT, p, m_IsWhitesTurn, false, capturesOnly).GetSquarePositions())
			{
				nextPossition = MakeNextPosition(W_KNIGHT, p, np);
				if (!nextPossition.isInCheck(true))
				{
					nextPositions.push_back(nextPossition);
				}
			}
		}
		for (Square p : m_WhiteBishops.GetSquarePositions())
		{
			for (Square np : GetMoves(W_BISHOP, p, m_IsWhitesTurn, false, capturesOnly).GetSquarePositions())
			{
				nextPossition = MakeNextPosition(W_BISHOP, p, np);
				if (!nextPossition.isInCheck(true))
				{
					nextPositions.push_back(nextPossition);
				}
			}
		}
		for (Square p : m_WhiteRooks.GetSquarePositions())
		{
			for (Square np : GetMoves(W_ROOK, p, m_IsWhitesTurn, false, capturesOnly).GetSquarePositions())
			{
				nextPossition = MakeNextPosition(W_ROOK, p, np);
				if (!nextPossition.isInCheck(true))
				{
					nextPositions.push_back(nextPossition);
				}
			}
		}
		for (Square p : m_WhiteQueen.GetSquarePositions())
		{
			for (Square np : GetMoves(W_QUEEN, p, m_IsWhitesTurn, false, capturesOnly).GetSquarePositions())
			{
				nextPossition = MakeNextPosition(W_QUEEN, p, np);
				if (!nextPossition.isInCheck(true))
				{
					nextPositions.push_back(nextPossition);
				}
			}
		}
		for (Square p : m_WhiteKing.GetSquarePositions())
		{
			for (Square np : GetMoves(W_KING, p, m_IsWhitesTurn, false, capturesOnly).GetSquarePositions())
			{
				nextPossition = MakeNextPosition(W_KING, p, np);
				//long
				if (p == E1 && m_AllWhitePieces.GetState(A1) && np == C1)
				{
					//can't castle out of check
					if (isInCheck(true))
					{
						continue;
					}
					nextPossition.m_WhiteRooks.Reset(A1);
					nextPossition.m_WhiteRooks.Insert(D1);
				}
				//short
				else if (p == E1 && m_AllWhitePieces.GetState(H1) && np == G1)
				{
					//can't castle out of check
					if (isInCheck(true))
					{
						continue;
					}
					nextPossition.m_WhiteRooks.Reset(H1);
					nextPossition.m_WhiteRooks.Insert(F1);
				}
				if (!nextPossition.isInCheck(true))
				{
					nextPositions.push_back(nextPossition);
				}
			}
		}

	}
	else
	{
		for (Square p : m_BlackPawns.GetSquarePositions())
		{
			for (Square np : GetMoves(B_PAWN, p, m_IsWhitesTurn, false, capturesOnly).GetSquarePositions())
			{
				nextPossition = MakeNextPosition(B_PAWN, p, np);
				//en passant
				if (m_LastMovedSquare == np + 8 && m_WhitePawns.GetData() & Bitboard::SquareToBitBoard(Square(np + 8)))
				{
					nextPossition.m_WhitePawns.Reset(Square(np + 8));
				}
				if (!nextPossition.isInCheck(false))
				{
					nextPositions.push_back(nextPossition);
				}
			}
		}
		for (Square p : m_BlackKnights.GetSquarePositions())
		{
			for (Square np : GetMoves(B_KNIGHT, p, m_IsWhitesTurn, false, capturesOnly).GetSquarePositions())
			{
				nextPossition = MakeNextPosition(B_KNIGHT, p, np);
				if (!nextPossition.isInCheck(false))
				{
					nextPositions.push_back(nextPossition);
				}
			}
		}
		for (Square p : m_BlackBishops.GetSquarePositions())
		{
			for (Square np : GetMoves(B_BISHOP, p, m_IsWhitesTurn, false, capturesOnly).GetSquarePositions())
			{
				nextPossition = MakeNextPosition(B_BISHOP, p, np);
				if (!nextPossition.isInCheck(false))
				{
					nextPositions.push_back(nextPossition);
				}
			}
		}
		for (Square p : m_BlackRooks.GetSquarePositions())
		{
			for (Square np : GetMoves(B_ROOK, p, m_IsWhitesTurn, false, capturesOnly).GetSquarePositions())
			{
				nextPossition = MakeNextPosition(B_ROOK, p, np);
				if (!nextPossition.isInCheck(false))
				{
					nextPositions.push_back(nextPossition);
				}
			}
		}
		for (Square p : m_BlackQueen.GetSquarePositions())
		{
			for (Square np : GetMoves(B_QUEEN, p, m_IsWhitesTurn, false, capturesOnly).GetSquarePositions())
			{
				nextPossition = MakeNextPosition(B_QUEEN, p, np);
				if (!nextPossition.isInCheck(false))
				{
					nextPositions.push_back(nextPossition);
				}
			}
		}
		for (Square p : m_BlackKing.GetSquarePositions())
		{
			for (Square np : GetMoves(B_KING, p, m_IsWhitesTurn, false, capturesOnly).GetSquarePositions())
			{
				nextPossition = MakeNextPosition(B_KING, p, np);
				//long
				if (p == E8 && m_AllBlackPieces.GetState(A8) && np == C8)
				{
					//can't castle out of check
					if (isInCheck(true))
					{
						continue;
					}
					nextPossition.m_BlackRooks.Reset(A8);
					nextPossition.m_BlackRooks.Insert(D8);
				}
				//short
				if (p == E8 && m_AllBlackPieces.GetState(H8) && np == G8)
				{
					//can't castle out of check
					if (isInCheck(true))
					{
						continue;
					}
					nextPossition.m_BlackRooks.Reset(H8);
					nextPossition.m_BlackRooks.Insert(F8);
				}
				if (!nextPossition.isInCheck(false))
				{
					nextPositions.push_back(nextPossition);
				}
			}
		}
	}
	return nextPositions;
}

Position Position::MakeNextPosition(Piece p, Square s, Square newSquare) const
{
	Position nextPos{ *this };

	if (nextPos.m_IsWhitesTurn && (SquareBB[newSquare] & nextPos.m_AllBlackPieces.GetData()))
	{
		nextPos.DeletePiece(GetPiece(newSquare), newSquare);
	}
	else if (!nextPos.m_IsWhitesTurn && (SquareBB[newSquare] & nextPos.m_AllWhitePieces.GetData()))
	{
		nextPos.DeletePiece(GetPiece(newSquare), newSquare);
	}
	switch (p)
	{
	case NO_PIECE:
		break;
	case W_PAWN:
		nextPos.m_WhitePawns.Reset(s);
		nextPos.m_WhitePawns.Insert(newSquare);
		break;
	case W_KNIGHT:
		nextPos.m_WhiteKnights.Reset(s);
		nextPos.m_WhiteKnights.Insert(newSquare);
		break;
	case W_BISHOP:
		nextPos.m_WhiteBishops.Reset(s);
		nextPos.m_WhiteBishops.Insert(newSquare);
		break;
	case W_ROOK:
		nextPos.m_WhiteRooks.Reset(s);
		nextPos.m_WhiteRooks.Insert(newSquare);
		break;
	case W_QUEEN:
		nextPos.m_WhiteQueen.Reset(s);
		nextPos.m_WhiteQueen.Insert(newSquare);
		break;
	case W_KING:
		nextPos.m_WhiteKing.Reset(s);
		nextPos.m_WhiteKing.Insert(newSquare);
		break;
	case B_PAWN:
		nextPos.m_BlackPawns.Reset(s);
		nextPos.m_BlackPawns.Insert(newSquare);
		break;
	case B_KNIGHT:
		nextPos.m_BlackKnights.Reset(s);
		nextPos.m_BlackKnights.Insert(newSquare);
		break;
	case B_BISHOP:
		nextPos.m_BlackBishops.Reset(s);
		nextPos.m_BlackBishops.Insert(newSquare);
		break;
	case B_ROOK:
		nextPos.m_BlackRooks.Reset(s);
		nextPos.m_BlackRooks.Insert(newSquare);
		break;
	case B_QUEEN:
		nextPos.m_BlackQueen.Reset(s);
		nextPos.m_BlackQueen.Insert(newSquare);
		break;
	case B_KING:
		nextPos.m_BlackKing.Reset(s);
		nextPos.m_BlackKing.Insert(newSquare);
		break;
	case PIECE_NB:
		break;
	default:
		break;
	}
	nextPos.m_AllWhitePieces = nextPos.m_WhitePawns | nextPos.m_WhiteKnights | nextPos.m_WhiteBishops | nextPos.m_WhiteRooks | nextPos.m_WhiteKing | nextPos.m_WhiteQueen;
	nextPos.m_AllBlackPieces = nextPos.m_BlackPawns | nextPos.m_BlackKnights | nextPos.m_BlackBishops | nextPos.m_BlackRooks | nextPos.m_BlackKing | nextPos.m_BlackQueen;
	nextPos.m_IsWhitesTurn = !nextPos.m_IsWhitesTurn;
	nextPos.m_LastMovedSquare = newSquare;
	nextPos.m_LastMovedOriginalSquare = s;
	nextPos.m_NeverMoved.Reset(s);
	return nextPos;
}

void Position::DeletePiece(Piece p, Square s)
{
	switch (p)
	{
	case NO_PIECE:
		break;
	case W_PAWN:
		m_WhitePawns.Reset(s);
		break;
	case W_KNIGHT:
		m_WhiteKnights.Reset(s);
		break;
	case W_BISHOP:
		m_WhiteBishops.Reset(s);
		break;
	case W_ROOK:
		m_WhiteRooks.Reset(s);
		break;
	case W_QUEEN:
		m_WhiteQueen.Reset(s);
		break;
	case W_KING:
		m_WhiteKing.Reset(s);
		break;
	case B_PAWN:
		m_BlackPawns.Reset(s);
		break;
	case B_KNIGHT:
		m_BlackKnights.Reset(s);
		break;
	case B_BISHOP:
		m_BlackBishops.Reset(s);
		break;
	case B_ROOK:
		m_BlackRooks.Reset(s);
		break;
	case B_QUEEN:
		m_BlackQueen.Reset(s);
		break;
	case B_KING:
		m_BlackKing.Reset(s);
		break;
	case PIECE_NB:
		break;
	default:
		break;
	}
}
Piece Position::GetPiece(Square s) const
{
	if (m_WhitePawns.GetState(s))
	{
		return W_PAWN;
	}
	if (m_WhiteKnights.GetState(s))
	{
		return W_KNIGHT;
	}
	if (m_WhiteBishops.GetState(s))
	{
		return W_BISHOP;
	}
	if (m_WhiteRooks.GetState(s))
	{
		return W_ROOK;
	}
	if (m_WhiteKing.GetState(s))
	{
		return W_KING;
	}
	if (m_WhiteQueen.GetState(s))
	{
		return W_QUEEN;
	}
	if (m_BlackPawns.GetState(s))
	{
		return B_PAWN;
	}
	if (m_BlackKnights.GetState(s))
	{
		return B_KNIGHT;
	}
	if (m_BlackBishops.GetState(s))
	{
		return B_BISHOP;
	}
	if (m_BlackRooks.GetState(s))
	{
		return B_ROOK;
	}
	if (m_BlackKing.GetState(s))
	{
		return B_KING;
	}
	if (m_BlackQueen.GetState(s))
	{
		return B_QUEEN;
	}
	else
	{
		return NO_PIECE;
	}
}
void Position::Print() const
{
	if (!m_IsWhitesTurn)
	{
		std::cout << "black's turn\n";
	}
	std::cout << "+---+---+---+---+---+---+---+---+";
	std::cout << "\t" << Evaluate() << "\n";
	for (int row = 7; row >= 0; --row)
	{
		for (int col = 0; col < 8; ++col)
		{
			Piece p = GetPiece(Bitboard::MakeSquare(row, col));
			
			switch (p)
			{
			case NO_PIECE:
				std::cout << "|   ";
				break;
			case W_PAWN:
				std::cout << "| p ";
				break;
			case W_KNIGHT:
				std::cout << "| k ";
				break;
			case W_BISHOP:
				std::cout << "| b ";
				break;
			case W_ROOK:
				std::cout << "| r ";
				break;
			case W_QUEEN:
				std::cout << "| q ";
				break;
			case W_KING:
				std::cout << "| ki";
				break;
			case B_PAWN:
				std::cout << "|-P ";
				break;
			case B_KNIGHT:
				std::cout << "|-K ";
				break;
			case B_BISHOP:
				std::cout << "|-B ";
				break;
			case B_ROOK:
				std::cout << "|-R ";
				break;
			case B_QUEEN:
				std::cout << "|-Q ";
				break;
			case B_KING:
				std::cout << "|-KI";
				break;
			case PIECE_NB:
				break;
			default:
				break;
			}
		}
		std::cout << "|\n+---+---+---+---+---+---+---+---+\n";
	}
	if (m_IsWhitesTurn)
	{
		std::cout << "white's turn\n";
	}
	std::cout << std::endl;
}
bool Position::isInCheck(bool white) const
{
	Bitboard enemyAttacks = GetAllMoves(!white, false, true);
	if (white && enemyAttacks.GetData() & m_WhiteKing.GetData())
	{
		return true;
	}
	else if(enemyAttacks.GetData() & m_BlackKing.GetData())
	{
		return true;
	}
	return false;
}