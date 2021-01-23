#pragma once
#include <stdint.h>
#include <vector>

enum Square : int {
	A1, B1, C1, D1, E1, F1, G1, H1,
	A2, B2, C2, D2, E2, F2, G2, H2,
	A3, B3, C3, D3, E3, F3, G3, H3,
	A4, B4, C4, D4, E4, F4, G4, H4,
	A5, B5, C5, D5, E5, F5, G5, H5,
	A6, B6, C6, D6, E6, F6, G6, H6,
	A7, B7, C7, D7, E7, F7, G7, H7,
	A8, B8, C8, D8, E8, F8, G8, H8
};
enum Piece {
	NO_PIECE,
	W_PAWN = 1, W_KNIGHT, W_BISHOP, W_ROOK, W_QUEEN, W_KING,
	B_PAWN = 9, B_KNIGHT, B_BISHOP, B_ROOK, B_QUEEN, B_KING,
	PIECE_NB = 16
};
extern uint64_t SquareBB[64];
extern uint64_t RAYS[8][64];
extern uint64_t KingMoves[64];
extern uint64_t KnightMoves[64];
enum Direction : int {
	NORTH_EAST,
	SOUTH_EAST,
	SOUTH_WEST,
	NORTH_WEST,
	NORTH,
	EAST,
	SOUTH,
	WEST
};
class Bitboard
{
public:
	Bitboard(uint64_t data);
	Bitboard(const Bitboard& other);
	Bitboard& operator=(const Bitboard& other);
	Bitboard(Bitboard&& other) noexcept;
	Bitboard& operator=(Bitboard&& other) noexcept;
	~Bitboard();
	static void Initialize();
	void Insert(int row, int column);
	void Insert(Square s);
	bool GetState(int row, int column) const;
	bool GetState(Square s) const;
	void Reset(Square s);
	uint64_t GetData() const;
	void Print() const;
	std::vector<std::pair<int, int>> GetPositions() const;
	std::vector<Square> GetSquarePositions() const;
	int GetAmount() const;
	static uint64_t GetBishopPossibleMoves(Square bishopPos, uint64_t board);
	static uint64_t GetRookPossibleMoves(Square rookPos, uint64_t board);
	static uint64_t GetQueenPossibleMoves(Square queenPos, uint64_t board);
	static uint64_t GetKnightPossibleMoves(Square knightPos, uint64_t board);
	static uint64_t GetKingPossibleMoves(Square kingPos, uint64_t board, Piece piece, const Bitboard& neverMoved, Square enemyKingPos, bool withEnemy);
	static uint64_t GetPawnsPossibleMoves(Square pawnPos, uint64_t board, Piece piece, Square lastMoved, Square lastMovedOrigin, uint64_t enemyPawns);
	static uint64_t GetPawnsPossibleAttacks(Square pawnPos, uint64_t enemyBoard, Piece piece);

	inline Bitboard  operator&(Square s) { return m_Data & SquareToBitBoard(s); }
	inline Bitboard  operator|(Square s) { return  m_Data | SquareToBitBoard(s); }
	inline Bitboard  operator^(Square s) { return m_Data ^ SquareToBitBoard(s); }
	
	inline Bitboard  operator&(const Bitboard& b) { return m_Data & b.m_Data; }
	inline Bitboard  operator|(const Bitboard& b) { return  m_Data | b.m_Data; }
	inline Bitboard  operator^(const Bitboard& b) { return m_Data ^ b.m_Data; }
	static uint64_t SquareToBitBoard(const Square& s);
	static std::pair<int, int> GetSquarePos(const Square& s);
	static Square MakeSquare(int row, int column);
	int Count() const;

private:
	uint64_t m_Data;
	
	static Square bitscanForward(uint64_t board);
	static Square bitscanReverse(uint64_t board);
};

