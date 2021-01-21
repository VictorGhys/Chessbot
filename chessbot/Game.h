#pragma once
#include "Texture.h"
#include "Bitboard.h"
#include <algorithm>
#include "Position.h"

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
	bool m_IsHoldingAPiece;
	Piece m_HoldedPiece;
	Square m_HoldedPieceSquare;
	Bitboard m_PossibleMoves;
	bool m_IsInCheck;
	Position m_CurrentPos;
	int m_ChessBotDepth;
	bool m_HasMatchFinished;
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
	void DrawLastMove() const;

	Square GetSquare(const Point2f& pos);
	Piece GetPiece(Square s) const;
	void PrintAsBitboard(uint64_t bb) const;
	bool CheckValidMove(Square s);
	void UpdateBoard(Square s);
	void UpdateMovedPiece(Square s);
	void DeletePiece(Piece p, Square s);
	bool CheckForCheck();
	static Square MakeSquare(int row, int column);

	float NegaMax(int depth, const Position& pos);
	Position RootNegaMax(int depth, const Position& pos, float& outScore);
	float NegaMaxAlphaBeta(int depth, const Position& pos, float alpha, float beta);
	Position RootNegaMaxAlphaBeta(int depth, const Position& pos, float& outScore);

};

