#include "pch.h"
#include "Bitboard.h"
#include "utils.h"
uint64_t SquareBB[64];
uint64_t RAYS[8][64];
uint64_t KingMoves[64];
uint64_t KnightMoves[64];

Bitboard::Bitboard(uint64_t data)
	:m_Data {data}
{
	
}
Bitboard::Bitboard(const Bitboard& other)
	:m_Data{other.m_Data}
{
}
Bitboard& Bitboard::operator=(const Bitboard& other)
{
	if (this != &other)
	{
		m_Data = other.m_Data;
	}
	return *this;
}
Bitboard::Bitboard(Bitboard&& other) noexcept
	:m_Data{ other.m_Data }
{

}
Bitboard& Bitboard::operator=(Bitboard&& other) noexcept
{
	if (this != &other)
	{
		m_Data = other.m_Data;
	}
	return *this;
}

Bitboard::~Bitboard()
{
}
void Bitboard::Initialize()
{
	//initialize squares
	for (int i = 0; i < 64; ++i)
	{
		SquareBB[i] = (1ULL << i);
	}
	//initialize rays
	int offset{ 0 };
	int rows{ 0 };
	for (int i = 0; i < 8; i++)
	{
		for (int k = 0; k < 64; k++)
		{
			RAYS[i][k] = (1ULL << k);
			offset = k % 8;
			rows = k / 8;
			int count{ 0 };
			switch (i)
			{
			case NORTH_EAST:
				while (offset + count < 7)
				{
					RAYS[i][k] <<= 9;
					RAYS[i][k] += (1ULL << offset + rows * 8);
					count++;
				}
				break;
			case SOUTH_EAST:
				while (offset + count < 7)
				{
					RAYS[i][k] >>= 7;
					RAYS[i][k] += (1ULL << offset + rows * 8);
					count++;
				}
				break;
			case SOUTH_WEST:
				while (offset - count > 0)
				{
					RAYS[i][k] >>= 9;
					RAYS[i][k] += (1ULL << offset + rows * 8);
					count++;
				}
				break;
			case NORTH_WEST:
				while (offset - count > 0)
				{
					RAYS[i][k] <<= 7;
					RAYS[i][k] += (1ULL << offset + rows * 8);
					count++;
				}
				break;
			case NORTH:
				while (rows + count < 7)
				{
					RAYS[i][k] <<= 8;
					RAYS[i][k] += (1ULL << offset + rows * 8);
					count++;
				}
				break;
			case EAST:
				while (offset + count < 7)
				{
					RAYS[i][k] <<= 1;
					RAYS[i][k] += (1ULL << offset + rows * 8);
					count++;
				}
				break;
			case SOUTH:
				while (rows - count > 0)
				{
					RAYS[i][k] >>= 8;
					RAYS[i][k] += (1ULL << offset + rows * 8);
					count++;
				}
				break;
			case WEST:
				while (offset - count > 0)
				{
					RAYS[i][k] >>= 1;
					RAYS[i][k] += (1ULL << offset + rows * 8);
					count++;
				}
				break;

			}
		}
	}
	//intialize king moves
	int collumn{ 0 };
	int row{ 0 };
	for (int k = 0; k < 64; k++)
	{
		KingMoves[k] = 0;
		collumn = k % 8;
		row = k / 8;
		//west
		if (collumn != 0)
		{
			KingMoves[k] += (1ULL << collumn - 1 + row * 8);
			//south west
			if (row != 0)
			{
				KingMoves[k] += (1ULL << collumn - 1 + (row - 1) * 8);
			}
			//north west
			if (row != 7)
			{
				KingMoves[k] += (1ULL << collumn - 1 + (row + 1) * 8);
			}
		}
		//east
		if (collumn != 7)
		{
			KingMoves[k] += (1ULL << collumn + 1 + row * 8);
			//south east
			if (row != 0)
			{
				KingMoves[k] += (1ULL << collumn + 1 + (row - 1) * 8);
			}
			//north east
			if (row != 7)
			{
				KingMoves[k] += (1ULL << collumn + 1 + (row + 1) * 8);
			}
		}
		//south
		if (row != 0)
		{
			KingMoves[k] += (1ULL << collumn + (row - 1) * 8);
		}
		//north
		if (row != 7)
		{
			KingMoves[k] += (1ULL << collumn + (row + 1) * 8);
		}
	}
	//initialize knight moves
	collumn = 0;
	row = 0;
	for (int k = 0; k < 64; k++)
	{
		KnightMoves[k] = 0;
		collumn = k % 8;
		row = k / 8;
		//west
		if (collumn >= 2)
		{
			//south west
			if (row != 0)
			{
				KnightMoves[k] += (1ULL << collumn - 2 + (row - 1) * 8);
			}
			//north west
			if (row != 7)
			{
				KnightMoves[k] += (1ULL << collumn - 2 + (row + 1) * 8);
			}
		}
		//east
		if (collumn <= 5)
		{
			//south east
			if (row != 0)
			{
				KnightMoves[k] += (1ULL << collumn + 2 + (row - 1) * 8);
			}
			//north east
			if (row != 7)
			{
				KnightMoves[k] += (1ULL << collumn + 2 + (row + 1) * 8);
			}
		}
		//south
		if (row >= 2)
		{
			//south west
			if (collumn >= 1)
			{
				KnightMoves[k] += (1ULL << collumn - 1 + (row - 2) * 8);
			}
			//south east
			if (collumn <= 6)
			{
				KnightMoves[k] += (1ULL << collumn + 1 + (row - 2) * 8);
			}
		}
		//north
		if (row <= 5)
		{
			//north west
			if (collumn >= 1)
			{
				KnightMoves[k] += (1ULL << collumn - 1 + (row + 2) * 8);
			}
			//north east
			if (collumn <= 6)
			{
				KnightMoves[k] += (1ULL << collumn + 1 + (row + 2) * 8);
			}
		}
	}
}
void Bitboard::Insert(int row, int column)
{
	uint64_t mask = SquareToBitBoard(MakeSquare(row, column));
	m_Data |= mask;
}
void Bitboard::Insert(Square s)
{
	uint64_t mask = SquareToBitBoard(s);
	m_Data |= mask;
}

bool Bitboard::GetState(int row, int column) const
{
	uint64_t mask = SquareToBitBoard(MakeSquare(row,column));
	return ((m_Data & mask) != 0);
}
bool Bitboard::GetState(Square s) const
{
	uint64_t mask = SquareToBitBoard(s);
	return ((m_Data & mask) != 0);
}
void Bitboard::Reset(Square s)
{
	uint64_t mask = SquareToBitBoard(s);
	m_Data &= ~mask;
}

void Bitboard::Print() const
{
	std::cout << m_Data << std::endl;
	std::cout << "+---+---+---+---+---+---+---+---+\n";
	for (int row = 7; row >= 0; --row)
	{
		for (int col = 0; col < 8; ++col)
		{
			if (m_Data & SquareToBitBoard( MakeSquare(row,col)))
			{
				std::cout << "| X ";
			}
			else
			{
				std::cout << "|   ";
			}
		}
		std::cout << "|\n+---+---+---+---+---+---+---+---+\n";
	}
	std::cout << std::endl;
}

Square Bitboard::MakeSquare(int row, int column)
{
	return Square((row << 3) + column);
}

uint64_t Bitboard::SquareToBitBoard(const Square& s)
{
	return SquareBB[s];
}

int Bitboard::Count() const
{
	uint64_t copy = m_Data;
	int count{};
	while (copy != 0)
	{
		copy &= copy - 1;
		count++;
	}
	return count;
}

std::vector<std::pair<int, int>> Bitboard::GetPositions() const
{
	std::vector<std::pair<int, int>> vec;
	for (int row = 0; row < 8; ++row)
	{
		for (int col = 0; col < 8; ++col)
		{
			if (GetState(row, col))
			{
				vec.push_back(std::pair<int, int>(row, col));
			}
		}
	}
	return vec;
}
int Bitboard::GetAmount() const
{
	int count{};
	for (int row = 0; row < 8; ++row)
	{
		for (int col = 0; col < 8; ++col)
		{
			if (GetState(row, col))
			{
				++count;
			}
		}
	}
	return count;
}

std::vector<Square> Bitboard::GetSquarePositions() const
{
	std::vector<Square> vec;
	for (int row = 0; row < 8; ++row)
	{
		for (int col = 0; col < 8; ++col)
		{
			if (GetState(row, col))
			{
				vec.push_back(MakeSquare(row, col));
			}
		}
	}
	return vec;
}

//from https://rhysre.net/fast-chess-move-generation-with-magic-bitboards.html
uint64_t Bitboard::GetBishopPossibleMoves(Square bishopPos, uint64_t board)
{
	uint64_t attacks = 0ULL;
	
	// North West
	attacks |= RAYS[NORTH_WEST][bishopPos];
	if (RAYS[NORTH_WEST][bishopPos] & board) {
		int blockerIndex = bitscanForward(RAYS[NORTH_WEST][bishopPos] & board);
		attacks &= ~RAYS[NORTH_WEST][blockerIndex];
		attacks |= SquareBB[blockerIndex];
	}

	// North East
	attacks |= RAYS[NORTH_EAST][bishopPos];
	if (RAYS[NORTH_EAST][bishopPos] & board) {
		int blockerIndex = bitscanForward(RAYS[NORTH_EAST][bishopPos] & board);
		attacks &= ~RAYS[NORTH_EAST][blockerIndex];
		attacks |= SquareBB[blockerIndex];
	}

	// South East
	attacks |= RAYS[SOUTH_EAST][bishopPos];
	if (RAYS[SOUTH_EAST][bishopPos] & board) {
		int blockerIndex = bitscanReverse(RAYS[SOUTH_EAST][bishopPos] & board);
		attacks &= ~RAYS[SOUTH_EAST][blockerIndex];
		attacks |= SquareBB[blockerIndex];
	}

	// South West
	attacks |= RAYS[SOUTH_WEST][bishopPos];
	if (RAYS[SOUTH_WEST][bishopPos] & board) {
		int blockerIndex = bitscanReverse(RAYS[SOUTH_WEST][bishopPos] & board);
		attacks &= ~RAYS[SOUTH_WEST][blockerIndex];
		attacks |= SquareBB[blockerIndex];
	}

	return attacks & ~SquareBB[bishopPos];
}
uint64_t Bitboard::GetPawnsPossibleMoves(Square pawnPos, uint64_t board, Piece piece, Square lastMoved, Square lastMovedOrigin, uint64_t enemyPawns)
{
	uint64_t pos = SquareToBitBoard(pawnPos);
	if (piece == W_PAWN && pawnPos < 64 - 8)
	{
		//make double move possible if on start pos
		if (pawnPos >= 8 && pawnPos <= 15 && !(board & pos << 8))
		{
			pos += pos << 8;
		}
		return pos << 8;
	}
	else if (piece == B_PAWN && pawnPos > 7)
	{
		//make double move possible if on start pos
		if (pawnPos >= 48 && pawnPos <= 55 && !(board & pos >> 8))
		{
			pos += pos >> 8;
		}
		return pos >> 8;
	}
	
	//en passant
	if (piece == W_PAWN && enemyPawns & SquareToBitBoard(lastMoved) 
		&& pawnPos < 40 && pawnPos > 31 && lastMoved < 40 && lastMoved > 31
		&& lastMovedOrigin < 56 && lastMovedOrigin > 47)
	{
		if (lastMoved == pawnPos - 1)
		{
			pos += pos << 7;
		}
		else if (lastMoved == pawnPos + 1)
		{
			pos += pos << 9;
		}
	}
	else if (piece == B_PAWN && enemyPawns & SquareToBitBoard(lastMoved) 
		&& pawnPos < 32 && pawnPos > 23 && lastMoved < 32 && lastMoved > 23
		&& lastMovedOrigin < 16 && lastMovedOrigin > 7)
	{
		if (lastMoved == pawnPos - 1)
		{
			pos += pos >> 7;
		}
		else if (lastMoved == pawnPos + 1)
		{
			pos += pos >> 9;
		}
	}
	return pos;
}
uint64_t Bitboard::GetPawnsPossibleAttacks(Square pawnPos, uint64_t enemyBoard, Piece piece)
{
	uint64_t pos = SquareToBitBoard(pawnPos);
	uint64_t leftAttack{};
	uint64_t rightAttack{};
	if (piece == W_PAWN)
	{
		const int row{ GetSquarePos(pawnPos).first };
		if ( row != 0)
		{
			leftAttack = pos << 7;
		}
		if ( row != 7)
		{
			rightAttack = pos << 9;
		}
	}
	else if(piece == B_PAWN)
	{
		const int row{ GetSquarePos(pawnPos).first };
		if ( row != 0)
		{
			leftAttack = pos >> 9;
		}
		if ( row != 7)
		{
			rightAttack = pos >> 7;
		}
	}
	return enemyBoard & (leftAttack | rightAttack);
}
uint64_t Bitboard::GetRookPossibleMoves(Square rookPos, uint64_t board)
{
	uint64_t attacks = 0ULL;

	// North
	attacks |= RAYS[NORTH][rookPos];
	if (RAYS[NORTH][rookPos] & board) {
		int blockerIndex = bitscanForward(RAYS[NORTH][rookPos] & board);
		attacks &= ~RAYS[NORTH][blockerIndex];
		attacks |= SquareBB[blockerIndex];
	}

	// East
	attacks |= RAYS[EAST][rookPos];
	if (RAYS[EAST][rookPos] & board) {
		int blockerIndex = bitscanForward(RAYS[EAST][rookPos] & board);
		attacks &= ~RAYS[EAST][blockerIndex];
		attacks |= SquareBB[blockerIndex];
	}

	// South
	attacks |= RAYS[SOUTH][rookPos];
	if (RAYS[SOUTH][rookPos] & board) {
		int blockerIndex = bitscanReverse(RAYS[SOUTH][rookPos] & board);
		attacks &= ~RAYS[SOUTH][blockerIndex];
		attacks |= SquareBB[blockerIndex];
	}

	// West
	attacks |= RAYS[WEST][rookPos];
	if (RAYS[WEST][rookPos] & board) {
		int blockerIndex = bitscanReverse(RAYS[WEST][rookPos] & board);
		attacks &= ~RAYS[WEST][blockerIndex];
		attacks |= SquareBB[blockerIndex];
	}

	return attacks & ~SquareBB[rookPos];
}
uint64_t Bitboard::GetQueenPossibleMoves(Square queenPos, uint64_t board)
{
	return GetBishopPossibleMoves(queenPos, board) | GetRookPossibleMoves(queenPos, board);
}
uint64_t Bitboard::GetKnightPossibleMoves(Square knightPos, uint64_t board)
{
	return KnightMoves[knightPos] & ~board;
}
uint64_t Bitboard::GetKingPossibleMoves(Square kingPos, uint64_t board, Piece piece, const Bitboard& neverMoved, Square enemyKingPos, bool withEnemy)
{
	uint64_t castleMoves{};
	//check for casteling
	if (piece == Piece::W_KING && kingPos == E1)
	{
		//long
		if (neverMoved.GetState(E1) && neverMoved.GetState(A1) && !Bitboard(board).GetState(B1) && !Bitboard(board).GetState(C1) && !Bitboard(board).GetState(D1))
		{
			castleMoves |= SquareBB[C1];
		}
		//short
		if (neverMoved.GetState(E1) && neverMoved.GetState(H1) && !Bitboard(board).GetState(F1))
		{
			castleMoves |= SquareBB[G1];
		}
	}
	else if(kingPos == E8)
	{
		//long
		if (neverMoved.GetState(E8) && neverMoved.GetState(A8) && !Bitboard(board).GetState(B8) && !Bitboard(board).GetState(C8)&& !Bitboard(board).GetState(D8))
		{
			castleMoves |= SquareBB[C8];
		}
		//short
		if (neverMoved.GetState(E8) && neverMoved.GetState(H8) && !Bitboard(board).GetState(F8))
		{
			castleMoves |= SquareBB[G8];
		}
	}
	if (withEnemy)
	{
		if (piece == W_KING)
		{
			return (castleMoves | KingMoves[kingPos] & ~board) & ~GetKingPossibleMoves(enemyKingPos, board, B_KING, neverMoved, kingPos, false);
		}
		else
		{
			return (castleMoves | KingMoves[kingPos] & ~board) & ~GetKingPossibleMoves(enemyKingPos, board, W_KING, neverMoved, kingPos, false);
		}
	}
	else
	{
		return castleMoves | KingMoves[kingPos] & ~board;
	}
}

Square Bitboard::bitscanForward(uint64_t board)
{
	DWORD* index{ new DWORD{} };
	BitScanForward64(index, board);
	return Square(*index);
}
Square Bitboard::bitscanReverse(uint64_t board)
{
	DWORD* index{ new DWORD{} };
	BitScanReverse64(index, board);
	return Square(*index);
}
uint64_t Bitboard::GetData() const
{
	return m_Data;
}
std::pair<int, int> Bitboard::GetSquarePos(const Square& s)
{
	return std::pair<int, int>{  utils::GetColumn(s, 8), utils::GetRow(s, 8)};
}