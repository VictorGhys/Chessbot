#pragma once
#include "Texture.h"
#include "Bitboard.h"
#include <algorithm>

class Game
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	~Game();

	void Update( float elapsedSec );
	void Draw( ) const;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e );
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e );
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e );
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e );
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e );
	
private:
	// DATA MEMBERS
	const Window m_Window;
	Texture* m_Pieces;
	const int m_Rows;
	Rectf m_Board;
	float m_SquareWidth;
	Bitboard m_WhiteSquares;
	Bitboard m_WhitePawns;
	Bitboard m_WhiteKnights;
	Bitboard m_WhiteBishops;
	Bitboard m_WhiteRooks;
	Bitboard m_WhiteKing;
	Bitboard m_WhiteQueen;

	Bitboard m_BlackSquares;
	Bitboard m_BlackPawns;
	Bitboard m_BlackKnights;
	Bitboard m_BlackBishops;
	Bitboard m_BlackRooks;
	Bitboard m_BlackKing;
	Bitboard m_BlackQueen;
	
	Bitboard m_AllWhitePieces;
	Bitboard m_AllBlackPieces;
	bool m_IsHoldingAPiece;
	Piece m_HoldedPiece;
	Square m_HoldedPieceSquare;
	Bitboard m_PossibleMoves;
	bool m_IsWhitesTurn;
	Bitboard m_NeverMoved;
	bool m_IsInCheck;
	// FUNCTIONS
	void Initialize( );
	void Cleanup( );
	void ClearBackground( ) const;

	void DrawChessBoard() const;
	void DrawPieces() const;
	void DrawWhitePawns() const;
	void DrawWhiteKnights() const;
	void DrawWhiteBishops() const;
	void DrawWhiteRooks() const;
	void DrawWhiteKing() const;
	void DrawWhiteQueen() const;

	void DrawBlackPawns() const;
	void DrawBlackKnights() const;
	void DrawBlackBishops() const;
	void DrawBlackRooks() const;
	void DrawBlackKing() const;
	void DrawBlackQueen() const;

	void DrawPossibleMoves() const;
	void DrawSquare(Square s) const;
	void DrawCircleInSquare(std::pair<int, int> p) const;
	void DrawSquare(std::pair<int, int> p) const;
	void DrawInCheck() const;

	Square GetSquare(const Point2f& pos);
	Piece GetPiece(const Square& s) const;
	std::pair<int,int> GetSquarePos(const Square& s) const;
	void PrintAsBitboard(uint64_t bb) const;
	bool CheckValidMove(Square s);
	void UpdateBoard(Square s);
	//void UpdatePossibleMoves();
	void DeletePiece(Piece p, Square s);
	Bitboard GetAttacks(Piece p, Square s, bool fromWhite, bool andMoves);
	Bitboard GetAllAttacks(bool fromWhite);
	bool CheckForCheck();
};

