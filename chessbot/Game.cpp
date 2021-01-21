#include "pch.h"
#include "Game.h"
#include <chrono>

Game::Game( const Window& window ) 
	:m_Window{ window }
	,m_Pieces{new Texture{"Resources/chess.png"}}
	,m_Rows{8}
	,m_Board{100,100,600,600}
	,m_SquareWidth{ m_Board.width / m_Rows }
	, m_IsHoldingAPiece{ false }
	,m_HoldedPiece{NO_PIECE}
	,m_PossibleMoves{0}
	, m_CurrentPos{}
	,m_ChessBotDepth{ 4 }
{
	Initialize( );
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	Bitboard::Initialize();
#pragma region BitboardTests
	/*std::cout << "white pawns:\n";
	m_CurrentPos.m_WhitePawns.Print();
	std::cout << "white Knights:\n";
	m_CurrentPos.m_WhiteKnights.Print();
	std::cout << "white Bishops:\n";
	m_CurrentPos.m_WhiteBishops.Print();
	std::cout << "white Rooks:\n";
	m_CurrentPos.m_WhiteRooks.Print();
	std::cout << "white King:\n";
	m_CurrentPos.m_WhiteKing.Print();
	std::cout << "white Queen:\n";
	m_CurrentPos.m_WhiteQueen.Print();

	std::cout << "Black pawns:\n";
	m_CurrentPos.m_BlackPawns.Print();
	std::cout << "Black Knights:\n";
	m_CurrentPos.m_BlackKnights.Print();
	std::cout << "Black Bishops:\n";
	m_CurrentPos.m_BlackBishops.Print();
	std::cout << "Black Rooks:\n";
	m_CurrentPos.m_BlackRooks.Print();
	std::cout << "Black King:\n";
	m_CurrentPos.m_BlackKing.Print();
	std::cout << "Black Queen:\n";
	m_CurrentPos.m_BlackQueen.Print();*/
	//Diagonals
	/*std::cout << "North east bit boards\n";
	for (int i = 0; i < 64; i++)
	{
		PrintAsBitboard( RAYS[0][i]);
	}
	std::cout << "---------North west bit boards-----------------\n";
	for (int i = 0; i < 64; i++)
	{
		PrintAsBitboard( RAYS[3][i]);
	}
	std::cout << "---------South East bit boards-----------------\n";
	for (int i = 0; i < 64; i++)
	{
		PrintAsBitboard( RAYS[1][i]);
	}
	std::cout << "---------South West bit boards-----------------\n";
	for (int i = 0; i < 64; i++)
	{
		PrintAsBitboard( RAYS[2][i]);
	}*/
	//Rows
	/*std::cout << "---------North bit boards-----------------\n";
	for (int i = 0; i < 64; i++)
	{
		PrintAsBitboard( RAYS[4][i]);
	}
	std::cout << "---------East bit boards-----------------\n";
	for (int i = 0; i < 64; i++)
	{
		PrintAsBitboard( RAYS[5][i]);
	}
	std::cout << "---------South bit boards-----------------\n";
	for (int i = 0; i < 64; i++)
	{
		PrintAsBitboard( RAYS[6][i]);
	}
	std::cout << "---------West bit boards-----------------\n";
	for (int i = 0; i < 64; i++)
	{
		PrintAsBitboard( RAYS[7][i]);
	}*/
	
	/*std::cout << "white pawns:\n";
	m_CurrentPos.m_WhitePawns.Print();
	m_CurrentPos.m_WhitePawns.Insert(2, 2);
	m_CurrentPos.m_WhitePawns.Print();
	m_CurrentPos.m_WhitePawns.Reset(C3);
	m_CurrentPos.m_WhitePawns.Print();*/

	/*std::cout << "---------KingMoves bit boards-----------------\n";
	for (int i = 0; i < 64; i++)
	{
		PrintAsBitboard(KingMoves[i]);
	}*/
	/*std::cout << "---------KnightMoves bit boards-----------------\n";
	for (int i = 0; i < 64; i++)
	{
		PrintAsBitboard(KnightMoves[i]);
	}*/
#pragma endregion

}

void Game::Cleanup( )
{
	delete m_Pieces;

}

void Game::Update( float elapsedSec )
{
	if (m_CurrentPos.m_IsWhitesTurn || m_HasMatchFinished)
	{
		return;
	}
	std::cout << "Calculating...\n";
	//do the engine
	float score{};
	float elapsedTime{};
	std::chrono::steady_clock::time_point startTime{};
	startTime = std::chrono::high_resolution_clock::now();
	//Position engineMove = RootNegaMax(m_ChessBotDepth, m_CurrentPos, score);
	Position engineMove = RootNegaMaxAlphaBeta(m_ChessBotDepth, m_CurrentPos, score);
	elapsedTime += std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - startTime).count();
	m_CurrentPos = engineMove;
	m_CurrentPos.m_IsWhitesTurn = true;
	std::cout << "Calculation took " << elapsedTime << " ms, current evaluation: " << score * -1 << std::endl;
	std::cout << "Your turn\n";
	if (CheckForCheck() && m_CurrentPos.GetNextPositions().size() == 0)
	{
		std::cout << "-------------------------------------------------\n";
		std::cout << "You Lost!\n";
		std::cout << "r to restart\n";
		std::cout << "-------------------------------------------------\n";
	}
}

void Game::Draw( ) const
{
	ClearBackground( );
	DrawChessBoard();
	DrawLastMove();
	DrawPieces();
	if (m_IsHoldingAPiece)
	{
		glColor4f(0.f, 0.7f, 0.f, 0.5f);
		DrawSquare(m_HoldedPieceSquare);
		DrawPossibleMoves();
	}
	glColor4f(1.f, 1., 1.f, 1.f);
	if (m_CurrentPos.m_IsWhitesTurn)
	{
		utils::FillRect(700, 100, 30, 30);
	}
	else
	{
		utils::FillRect(700, 670, 30, 30);
	}
	DrawInCheck();
}
void Game::DrawChessBoard() const
{
	glColor4f(181.f/255, 135.f/255, 99.f/255, 1.f);
	utils::FillRect(m_Board);
	glColor4f(240.f/255, 218.f/255, 181.f/255, 1.f);
	
	bool draw{ false };
	for (int i = 0; i < m_Rows; i++)
	{
		for (int k = 0; k < m_Rows; k++)
		{
			if (draw)
			{
				utils::FillRect(Rectf{ m_Board.left + k * m_SquareWidth,
					m_Board.bottom + i * m_SquareWidth, m_SquareWidth, m_SquareWidth });
				if (k != m_Rows - 1)
				{
					draw = !draw;
				}
			}
			else
			{
				if (k != m_Rows -1)
				{
					draw = !draw;
				}
			}
		}
	}

}

void Game::DrawPieces() const
{
	DrawWhitePawns();
	DrawWhiteKnights();
	DrawWhiteBishops();
	DrawWhiteRooks();
	DrawWhiteKing();
	DrawWhiteQueen();
	DrawBlackPawns();
	DrawBlackKnights();
	DrawBlackBishops();
	DrawBlackRooks();
	DrawBlackKing();
	DrawBlackQueen();
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	switch ( e.keysym.sym )
	{
	case SDLK_r:
		m_CurrentPos = Position{};
		m_HasMatchFinished = false;
		m_IsInCheck = false;
		break;
	case SDLK_UP:
		m_ChessBotDepth++;
		break;
	case SDLK_DOWN:
		m_ChessBotDepth--;
		break;
	}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
	switch (e.button)
	{
	case SDL_BUTTON_LEFT:
		//std::cout << " left button " << std::endl;
		if (!m_HasMatchFinished)
		{
			if (m_IsHoldingAPiece)
			{
				Square clickedSquare{ GetSquare(Point2f{ float(e.x),m_Window.height - float(e.y) }) };
				//check if valid spot for piece
				if (CheckValidMove(clickedSquare))
				{
					//update the board
					UpdateBoard(clickedSquare);
				}
				m_IsHoldingAPiece = false;
				m_HoldedPiece = NO_PIECE;
			}
			else
			{
				//hold the piece that is clicked and show it's posible moves
				m_HoldedPieceSquare = GetSquare(Point2f{ float(e.x),m_Window.height - float(e.y) });
				m_HoldedPiece = GetPiece(m_HoldedPieceSquare);
				if (m_HoldedPiece != NO_PIECE)
				{
					if (m_CurrentPos.m_IsWhitesTurn && (m_HoldedPiece == W_PAWN
						|| m_HoldedPiece == W_KNIGHT
						|| m_HoldedPiece == W_BISHOP
						|| m_HoldedPiece == W_ROOK
						|| m_HoldedPiece == W_QUEEN
						|| m_HoldedPiece == W_KING))
					{
						m_IsHoldingAPiece = true;
					}
					else if (!m_CurrentPos.m_IsWhitesTurn && (m_HoldedPiece == B_PAWN
						|| m_HoldedPiece == B_KNIGHT
						|| m_HoldedPiece == B_BISHOP
						|| m_HoldedPiece == B_ROOK
						|| m_HoldedPiece == B_QUEEN
						|| m_HoldedPiece == B_KING))
					{
						m_IsHoldingAPiece = true;
					}
				}
				m_PossibleMoves = m_CurrentPos.GetMoves(m_HoldedPiece, m_HoldedPieceSquare, m_CurrentPos.m_IsWhitesTurn, false);
				//GetAllAttacks(true).Print();
			}
		}
		break;
	}
}

bool Game::CheckValidMove(Square s)
{
	return m_PossibleMoves.GetState(s);
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

Square Game::GetSquare(const Point2f& pos)
{
	int col = int((pos.x - m_Board.left) / m_SquareWidth);
	int row = int((pos.y - m_Board.bottom) / m_SquareWidth);
	return Square((row << 3) + col);
}

Piece Game::GetPiece(Square s) const
{
	if (m_CurrentPos.m_WhitePawns.GetState(s))
	{
		return W_PAWN;
	}
	if (m_CurrentPos.m_WhiteKnights.GetState(s))
	{
		return W_KNIGHT;
	}
	if (m_CurrentPos.m_WhiteBishops.GetState(s))
	{
		return W_BISHOP;
	}
	if (m_CurrentPos.m_WhiteRooks.GetState(s))
	{
		return W_ROOK;
	}
	if (m_CurrentPos.m_WhiteKing.GetState(s))
	{
		return W_KING;
	}
	if (m_CurrentPos.m_WhiteQueen.GetState(s))
	{
		return W_QUEEN;
	}
	if (m_CurrentPos.m_BlackPawns.GetState(s))
	{
		return B_PAWN;
	}
	if (m_CurrentPos.m_BlackKnights.GetState(s))
	{
		return B_KNIGHT;
	}
	if (m_CurrentPos.m_BlackBishops.GetState(s))
	{
		return B_BISHOP;
	}
	if (m_CurrentPos.m_BlackRooks.GetState(s))
	{
		return B_ROOK;
	}
	if (m_CurrentPos.m_BlackKing.GetState(s))
	{
		return B_KING;
	}
	if (m_CurrentPos.m_BlackQueen.GetState(s))
	{
		return B_QUEEN;
	}
	else
	{
		return NO_PIECE;
	}
}


void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

void Game::DrawWhitePawns() const
{
	std::vector<std::pair<int, int>> wp = m_CurrentPos.m_WhitePawns.GetPositions();
	Rectf src;
	src.width = m_Pieces->GetWidth() / 6;
	src.height = m_Pieces->GetHeight() / 2;
	src.left = 5 * src.width;
	src.bottom = src.height;

	std::for_each(wp.begin(), wp.end(), [&](std::pair<int, int> p)
		{
			Rectf dest;
			dest.width = m_SquareWidth;
			dest.height = m_SquareWidth;
			dest.left = p.second * dest.width + m_Board.left;
			dest.bottom = p.first * dest.height + m_Board.bottom;
			m_Pieces->Draw(dest, src);
		});
}
void Game::DrawWhiteKnights() const
{
	std::vector<std::pair<int, int>> wk = m_CurrentPos.m_WhiteKnights.GetPositions();
	Rectf src;
	src.width = m_Pieces->GetWidth() / 6;
	src.height = m_Pieces->GetHeight() / 2;
	src.left = 3 * src.width;
	src.bottom = src.height;

	std::for_each(wk.begin(), wk.end(), [&](std::pair<int, int> p)
		{
			Rectf dest;
			dest.width = m_SquareWidth;
			dest.height = m_SquareWidth;
			dest.left = p.second * dest.width + m_Board.left;
			dest.bottom = p.first * dest.height + m_Board.bottom;
			m_Pieces->Draw(dest, src);
		});
}
void Game::DrawWhiteBishops() const
{
	std::vector<std::pair<int, int>> wb = m_CurrentPos.m_WhiteBishops.GetPositions();
	Rectf src;
	src.width = m_Pieces->GetWidth() / 6;
	src.height = m_Pieces->GetHeight() / 2;
	src.left = 2 * src.width;
	src.bottom = src.height;

	std::for_each(wb.begin(), wb.end(), [&](std::pair<int, int> p)
		{
			Rectf dest;
			dest.width = m_SquareWidth;
			dest.height = m_SquareWidth;
			dest.left = p.second * dest.width + m_Board.left;
			dest.bottom = p.first * dest.height + m_Board.bottom;
			m_Pieces->Draw(dest, src);
		});
}
void Game::DrawWhiteRooks() const
{
	std::vector<std::pair<int, int>> wr = m_CurrentPos.m_WhiteRooks.GetPositions();
	Rectf src;
	src.width = m_Pieces->GetWidth() / 6;
	src.height = m_Pieces->GetHeight() / 2;
	src.left = 4 * src.width;
	src.bottom = src.height;

	std::for_each(wr.begin(), wr.end(), [&](std::pair<int, int> p)
		{
			Rectf dest;
			dest.width = m_SquareWidth;
			dest.height = m_SquareWidth;
			dest.left = p.second * dest.width + m_Board.left;
			dest.bottom = p.first * dest.height + m_Board.bottom;
			m_Pieces->Draw(dest, src);
		});
}
void Game::DrawWhiteKing() const
{
	std::vector<std::pair<int, int>> wking = m_CurrentPos.m_WhiteKing.GetPositions();
	Rectf src;
	src.width = m_Pieces->GetWidth() / 6;
	src.height = m_Pieces->GetHeight() / 2;
	src.left = 0;
	src.bottom = src.height;

	std::for_each(wking.begin(), wking.end(), [&](std::pair<int, int> p)
		{
			Rectf dest;
			dest.width = m_SquareWidth;
			dest.height = m_SquareWidth;
			dest.left = p.second * dest.width + m_Board.left;
			dest.bottom = p.first * dest.height + m_Board.bottom;
			m_Pieces->Draw(dest, src);
		});
}
void Game::DrawWhiteQueen() const
{
	std::vector<std::pair<int, int>> wq = m_CurrentPos.m_WhiteQueen.GetPositions();
	Rectf src;
	src.width = m_Pieces->GetWidth() / 6;
	src.height = m_Pieces->GetHeight() / 2;
	src.left = 1 * src.width;
	src.bottom = src.height;

	std::for_each(wq.begin(), wq.end(), [&](std::pair<int, int> p)
		{
			Rectf dest;
			dest.width = m_SquareWidth;
			dest.height = m_SquareWidth;
			dest.left = p.second * dest.width + m_Board.left;
			dest.bottom = p.first * dest.height + m_Board.bottom;
			m_Pieces->Draw(dest, src);
		});
}
void Game::DrawBlackPawns() const
{
	std::vector<std::pair<int, int>> bp = m_CurrentPos.m_BlackPawns.GetPositions();
	Rectf src;
	src.width = m_Pieces->GetWidth() / 6;
	src.height = m_Pieces->GetHeight() / 2;
	src.left = 5 * src.width;
	src.bottom = 0;

	std::for_each(bp.begin(), bp.end(), [&](std::pair<int, int> p)
		{
			Rectf dest;
			dest.width = m_SquareWidth;
			dest.height = m_SquareWidth;
			dest.left = p.second * dest.width + m_Board.left;
			dest.bottom = p.first * dest.height + m_Board.bottom;
			m_Pieces->Draw(dest, src);
		});
}
void Game::DrawBlackKnights() const
{
	std::vector<std::pair<int, int>> bk = m_CurrentPos.m_BlackKnights.GetPositions();
	Rectf src;
	src.width = m_Pieces->GetWidth() / 6;
	src.height = m_Pieces->GetHeight() / 2;
	src.left = 3 * src.width;
	src.bottom = 0;

	std::for_each(bk.begin(), bk.end(), [&](std::pair<int, int> p)
		{
			Rectf dest;
			dest.width = m_SquareWidth;
			dest.height = m_SquareWidth;
			dest.left = p.second * dest.width + m_Board.left;
			dest.bottom = p.first * dest.height + m_Board.bottom;
			m_Pieces->Draw(dest, src);
		});
}
void Game::DrawBlackBishops() const
{
	std::vector<std::pair<int, int>> bb = m_CurrentPos.m_BlackBishops.GetPositions();
	Rectf src;
	src.width = m_Pieces->GetWidth() / 6;
	src.height = m_Pieces->GetHeight() / 2;
	src.left = 2 * src.width;
	src.bottom = 0;

	std::for_each(bb.begin(), bb.end(), [&](std::pair<int, int> p)
		{
			Rectf dest;
			dest.width = m_SquareWidth;
			dest.height = m_SquareWidth;
			dest.left = p.second * dest.width + m_Board.left;
			dest.bottom = p.first * dest.height + m_Board.bottom;
			m_Pieces->Draw(dest, src);
		});
}
void Game::DrawBlackRooks() const
{
	std::vector<std::pair<int, int>> br = m_CurrentPos.m_BlackRooks.GetPositions();
	Rectf src;
	src.width = m_Pieces->GetWidth() / 6;
	src.height = m_Pieces->GetHeight() / 2;
	src.left = 4 * src.width;
	src.bottom = 0;

	std::for_each(br.begin(), br.end(), [&](std::pair<int, int> p)
		{
			Rectf dest;
			dest.width = m_SquareWidth;
			dest.height = m_SquareWidth;
			dest.left = p.second * dest.width + m_Board.left;
			dest.bottom = p.first * dest.height + m_Board.bottom;
			m_Pieces->Draw(dest, src);
		});
}
void Game::DrawBlackKing() const
{
	std::vector<std::pair<int, int>> bking = m_CurrentPos.m_BlackKing.GetPositions();
	Rectf src;
	src.width = m_Pieces->GetWidth() / 6;
	src.height = m_Pieces->GetHeight() / 2;
	src.left = 0;
	src.bottom = 0;

	std::for_each(bking.begin(), bking.end(), [&](std::pair<int, int> p)
		{
			Rectf dest;
			dest.width = m_SquareWidth;
			dest.height = m_SquareWidth;
			dest.left = p.second * dest.width + m_Board.left;
			dest.bottom = p.first * dest.height + m_Board.bottom;
			m_Pieces->Draw(dest, src);
		});
}
void Game::DrawBlackQueen() const
{
	std::vector<std::pair<int, int>> bq = m_CurrentPos.m_BlackQueen.GetPositions();
	Rectf src;
	src.width = m_Pieces->GetWidth() / 6;
	src.height = m_Pieces->GetHeight() / 2;
	src.left = 1 * src.width;
	src.bottom = 0;

	std::for_each(bq.begin(), bq.end(), [&](std::pair<int, int> p)
		{
			Rectf dest;
			dest.width = m_SquareWidth;
			dest.height = m_SquareWidth;
			dest.left = p.second * dest.width + m_Board.left;
			dest.bottom = p.first * dest.height + m_Board.bottom;
			m_Pieces->Draw(dest, src);
		});
}

void Game::DrawPossibleMoves() const
{
	std::vector<std::pair<int, int>> vec{ m_PossibleMoves.GetPositions()};
	for (std::vector<std::pair<int, int>>::iterator It{ vec.begin() };
		It != vec.end(); ++It)
	{
		DrawCircleInSquare(*It);
	}
}

void Game::DrawSquare(Square s) const
{
	utils::FillRect(Bitboard::GetSquarePos(s).first * m_SquareWidth + m_Board.left,
		Bitboard::GetSquarePos(s).second * m_SquareWidth + m_Board.bottom
		, m_SquareWidth, m_SquareWidth);
}

Square Game::MakeSquare(int row, int column)
{
	return Square((row << 3) + column);
}
void Game::DrawCircleInSquare(std::pair<int, int> p) const
{
	Square s = MakeSquare(p.first, p.second);
	utils::FillEllipse(Bitboard::GetSquarePos(s).first * m_SquareWidth + m_SquareWidth / 2.f + m_Board.left,
		Bitboard::GetSquarePos(s).second * m_SquareWidth + m_SquareWidth / 2.f + m_Board.bottom
		, m_SquareWidth / 4.f, m_SquareWidth / 4.f);
}
void Game::DrawSquare(std::pair<int, int> p) const
{
	Square s = MakeSquare(p.first, p.second);
	utils::FillRect(Bitboard::GetSquarePos(s).first * m_SquareWidth + m_Board.left,
		Bitboard::GetSquarePos(s).second * m_SquareWidth + m_Board.bottom
		, m_SquareWidth, m_SquareWidth);
}
void Game::DrawInCheck() const
{
	if (m_IsInCheck)
	{
		if (m_CurrentPos.m_IsWhitesTurn && m_CurrentPos.m_WhiteKing.GetData())
		{
			Square s = m_CurrentPos.m_WhiteKing.GetSquarePositions().front();
			glColor4f(1, 0, 0, 0.5f);
			utils::FillRect(Bitboard::GetSquarePos(s).first * m_SquareWidth + m_Board.left,
				Bitboard::GetSquarePos(s).second * m_SquareWidth + m_Board.bottom
				, m_SquareWidth, m_SquareWidth);
		}
		else if(m_CurrentPos.m_BlackKing.GetData())
		{
			Square s = m_CurrentPos.m_BlackKing.GetSquarePositions().front();
			glColor4f(1, 0, 0, 0.5f);
			utils::FillRect(Bitboard::GetSquarePos(s).first * m_SquareWidth + m_Board.left,
				Bitboard::GetSquarePos(s).second * m_SquareWidth + m_Board.bottom
				, m_SquareWidth, m_SquareWidth);
		}
	}
}
void Game::DrawLastMove() const
{
	if (m_CurrentPos.m_AllWhitePieces.GetData() != Position{}.m_AllWhitePieces.GetData())
	{
		glColor4f(1, 1, 0, 0.3f);
		utils::FillRect(Bitboard::GetSquarePos(m_CurrentPos.m_LastMovedSquare).first * m_SquareWidth + m_Board.left,
			Bitboard::GetSquarePos(m_CurrentPos.m_LastMovedSquare).second * m_SquareWidth + m_Board.bottom
			, m_SquareWidth, m_SquareWidth);
		glColor4f(1, 1, 0, 0.3f);
		utils::FillRect(Bitboard::GetSquarePos(m_CurrentPos.m_LastMovedOriginalSquare).first * m_SquareWidth + m_Board.left,
			Bitboard::GetSquarePos(m_CurrentPos.m_LastMovedOriginalSquare).second * m_SquareWidth + m_Board.bottom
			, m_SquareWidth, m_SquareWidth);
	}
}

void Game::PrintAsBitboard(uint64_t bb) const
{
	std::cout << bb << std::endl;
	std::cout << "+---+---+---+---+---+---+---+---+\n";
	for (int row = 7; row >= 0; --row)
	{
		for (int col = 0; col < 8; ++col)
		{
			if (bb & Bitboard::SquareToBitBoard(MakeSquare(row, col)))
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
void Game::UpdateBoard(Square s)
{
	//make a copy from the bitboards
	Position currentPosCopy{ m_CurrentPos };
	//delete the captured piece
	if (m_CurrentPos.m_IsWhitesTurn && (SquareBB[s] & m_CurrentPos.m_AllBlackPieces.GetData()))
	{
		DeletePiece(GetPiece(s), s);
	}
	else if (!m_CurrentPos.m_IsWhitesTurn && (SquareBB[s] & m_CurrentPos.m_AllWhitePieces.GetData()))
	{
		DeletePiece(GetPiece(s), s);
	}
	//set neverMoved to false
	m_CurrentPos.m_NeverMoved.Reset(s);
	//update the moved piece
	UpdateMovedPiece(s);
	//if you are in check your move needs to fix it
	if (CheckForCheck())
	{
		//the player didn't fix the check, so revert the move
		m_CurrentPos = currentPosCopy;
		std::cout << "You can't do this move because you are in check\n";
		return;
	}
	else
	{
		m_IsInCheck = false;
	}
	m_CurrentPos.m_LastMovedSquare = s;
	m_CurrentPos.m_LastMovedOriginalSquare = m_HoldedPieceSquare;
	m_CurrentPos.m_IsWhitesTurn = false;
}
void Game::UpdateMovedPiece(Square s)
{
	switch (m_HoldedPiece)
	{
	case NO_PIECE:
		break;
	case W_PAWN:
		m_CurrentPos.m_WhitePawns.Reset(m_HoldedPieceSquare);
		m_CurrentPos.m_WhitePawns.Insert(s);
		//promotion
		if (s > H7)
		{
			m_CurrentPos.m_WhitePawns.Reset(s);
			m_CurrentPos.m_WhiteQueen.Insert(s);
		}
		break;
	case W_KNIGHT:
		m_CurrentPos.m_WhiteKnights.Reset(m_HoldedPieceSquare);
		m_CurrentPos.m_WhiteKnights.Insert(s);
		break;
	case W_BISHOP:
		m_CurrentPos.m_WhiteBishops.Reset(m_HoldedPieceSquare);
		m_CurrentPos.m_WhiteBishops.Insert(s);
		break;
	case W_ROOK:
		m_CurrentPos.m_WhiteRooks.Reset(m_HoldedPieceSquare);
		m_CurrentPos.m_WhiteRooks.Insert(s);
		break;
	case W_QUEEN:
		m_CurrentPos.m_WhiteQueen.Reset(m_HoldedPieceSquare);
		m_CurrentPos.m_WhiteQueen.Insert(s);
		break;
	case W_KING:
		//castling
		//long
		if (m_HoldedPieceSquare == E1 && m_CurrentPos.m_AllWhitePieces.GetState(A1) && s == C1)
		{
			//can't castle out of check
			if (m_CurrentPos.isInCheck(true))
				return;
			m_CurrentPos.m_WhiteRooks.Reset(A1);
			m_CurrentPos.m_WhiteRooks.Insert(D1);
		}
		//short
		if (m_HoldedPieceSquare == E1 && m_CurrentPos.m_AllWhitePieces.GetState(H1) && s == G1)
		{
			//can't castle out of check
			if (m_CurrentPos.isInCheck(true))
				return;
			m_CurrentPos.m_WhiteRooks.Reset(H1);
			m_CurrentPos.m_WhiteRooks.Insert(F1);
		}
		m_CurrentPos.m_WhiteKing.Reset(m_HoldedPieceSquare);
		m_CurrentPos.m_WhiteKing.Insert(s);
		break;
	case B_PAWN:
		m_CurrentPos.m_BlackPawns.Reset(m_HoldedPieceSquare);
		m_CurrentPos.m_BlackPawns.Insert(s);
		//promotion
		if (s < A2)
		{
			m_CurrentPos.m_BlackPawns.Reset(s);
			m_CurrentPos.m_BlackQueen.Insert(s);
		}
		break;
	case B_KNIGHT:
		m_CurrentPos.m_BlackKnights.Reset(m_HoldedPieceSquare);
		m_CurrentPos.m_BlackKnights.Insert(s);
		break;
	case B_BISHOP:
		m_CurrentPos.m_BlackBishops.Reset(m_HoldedPieceSquare);
		m_CurrentPos.m_BlackBishops.Insert(s);
		break;
	case B_ROOK:
		m_CurrentPos.m_BlackRooks.Reset(m_HoldedPieceSquare);
		m_CurrentPos.m_BlackRooks.Insert(s);
		break;
	case B_QUEEN:
		m_CurrentPos.m_BlackQueen.Reset(m_HoldedPieceSquare);
		m_CurrentPos.m_BlackQueen.Insert(s);
		break;
	case B_KING:
		//castling
		//long
		if (m_HoldedPieceSquare == E8 && m_CurrentPos.m_AllBlackPieces.GetState(A8) && s == C8)
		{
			//can't castle out of check
			if (m_CurrentPos.isInCheck(true))
				return;
			m_CurrentPos.m_BlackRooks.Reset(A8);
			m_CurrentPos.m_BlackRooks.Insert(D8);
		}
		//short
		if (m_HoldedPieceSquare == E8 && m_CurrentPos.m_AllBlackPieces.GetState(H8) && s == G8)
		{
			//can't castle out of check
			if (m_CurrentPos.isInCheck(true))
				return;
			m_CurrentPos.m_BlackRooks.Reset(H8);
			m_CurrentPos.m_BlackRooks.Insert(F8);
		}
		m_CurrentPos.m_BlackKing.Reset(m_HoldedPieceSquare);
		m_CurrentPos.m_BlackKing.Insert(s);
		break;
	case PIECE_NB:
		break;
	default:
		break;
	}
	m_CurrentPos.m_AllWhitePieces = m_CurrentPos.m_WhitePawns | m_CurrentPos.m_WhiteKnights | m_CurrentPos.m_WhiteBishops | m_CurrentPos.m_WhiteRooks | m_CurrentPos.m_WhiteKing | m_CurrentPos.m_WhiteQueen;
	m_CurrentPos.m_AllBlackPieces = m_CurrentPos.m_BlackPawns | m_CurrentPos.m_BlackKnights | m_CurrentPos.m_BlackBishops | m_CurrentPos.m_BlackRooks | m_CurrentPos.m_BlackKing | m_CurrentPos.m_BlackQueen;

}

void Game::DeletePiece(Piece p, Square s)
{
	switch (p)
	{
	case NO_PIECE:
		break;
	case W_PAWN:
		m_CurrentPos.m_WhitePawns.Reset(s);
		break;
	case W_KNIGHT:
		m_CurrentPos.m_WhiteKnights.Reset(s);
		break;
	case W_BISHOP:
		m_CurrentPos.m_WhiteBishops.Reset(s);
		break;
	case W_ROOK:
		m_CurrentPos.m_WhiteRooks.Reset(s);
		break;
	case W_QUEEN:
		m_CurrentPos.m_WhiteQueen.Reset(s);
		break;
	case W_KING:
		m_CurrentPos.m_WhiteKing.Reset(s);
		break;
	case B_PAWN:
		m_CurrentPos.m_BlackPawns.Reset(s);
		break;
	case B_KNIGHT:
		m_CurrentPos.m_BlackKnights.Reset(s);
		break;
	case B_BISHOP:
		m_CurrentPos.m_BlackBishops.Reset(s);
		break;
	case B_ROOK:
		m_CurrentPos.m_BlackRooks.Reset(s);
		break;
	case B_QUEEN:
		m_CurrentPos.m_BlackQueen.Reset(s);
		break;
	case B_KING:
		m_CurrentPos.m_BlackKing.Reset(s);
		break;
	case PIECE_NB:
		break;
	default:
		break;
	}
}

bool Game::CheckForCheck()
{
	if (!m_CurrentPos.m_IsWhitesTurn)
	{
		//check if black is in check
		if (m_CurrentPos.GetAllMoves(true, true, true).GetData() & SquareBB[m_CurrentPos.m_BlackKing.GetSquarePositions().front()])
		{
			//m_CurrentPos.GetAllMoves(true, true).Print();

			std::cout << "black is in check!\n";
			m_IsInCheck = true;
			return true;
		}
	}
	//check if white is in check
	else if (m_CurrentPos.GetAllMoves(false, true, true).GetData() & SquareBB[m_CurrentPos.m_WhiteKing.GetSquarePositions().front()])
	{
		//m_CurrentPos.GetAllMoves(false, true).Print();
		std::cout << "white is in check!\n";
		m_IsInCheck = true;
		return true;
	}
	return false;
}
float Game::NegaMax(int depth, const Position& pos)
{
	if (depth == 0) 
		return pos.Evaluate();
	float max = std::numeric_limits<float>::lowest();
	for (Position np : pos.GetNextPositions()) 
	{
		//np.Print();
		float score = -NegaMax(depth - 1, np);
		if (score > max)
			max = score;
	}
	return max;
}
Position Game::RootNegaMax(int depth, const Position& pos, float& outScore)
{
	float max = std::numeric_limits<float>::lowest();
	Position bestContinuation{};
	std::vector<Position> nextPositions{ pos.GetNextPositions() };
	if (nextPositions.size() == 0)
	{
		if (m_CurrentPos.isInCheck(false))
		{
			std::cout << "-------------------------------------------------\n";
			std::cout << "Congratulations! You won!\n";
			std::cout << "Press r to restart\n";
			std::cout << "-------------------------------------------------\n";
		}
		else
		{
			std::cout << "-------------------------------------------------\n";
			std::cout << "Stalemate! Nobody won!\n";
			std::cout << "Press r to restart\n";
			std::cout << "-------------------------------------------------\n";
		}
		m_HasMatchFinished = true;
		return m_CurrentPos;
	}
	for (const Position& np : nextPositions) 
	{
		//np.Print();
		float score = -NegaMax(depth - 1, np);
		if (score > max)
		{
			max = score;
			bestContinuation = np;
			outScore = score;
		}
	}
	//std::cout << "-------------------------------------------------\n";
	return bestContinuation;
}
float Game::NegaMaxAlphaBeta(int depth, const Position& pos, float alpha, float beta)
{
	if (depth == 0)
	{
		//return quiesce(alpha, beta);
		return pos.Evaluate();
	}
		
	for (const Position& np : pos.GetNextPositions()) 
	{
		float score = -NegaMaxAlphaBeta(depth - 1, np, -beta, -alpha);
		if (score >= beta)
			return beta;   //  fail hard beta-cutoff
		if (score > alpha)
			alpha = score; // alpha acts like max in MiniMax
	}
	return alpha;
}
Position Game::RootNegaMaxAlphaBeta(int depth, const Position& pos, float& outScore)
{
	float max = std::numeric_limits<float>::lowest();
	Position bestContinuation{};
	std::vector<Position> nextPositions{ pos.GetNextPositions() };
	if (nextPositions.size() == 0)
	{
		if (m_CurrentPos.isInCheck(false))
		{
			std::cout << "-------------------------------------------------\n";
			std::cout << "Congratulations! You won!\n";
			std::cout << "Press r to restart\n";
			std::cout << "-------------------------------------------------\n";
		}
		else
		{
			std::cout << "-------------------------------------------------\n";
			std::cout << "Stalemate! Nobody won!\n";
			std::cout << "Press r to restart\n";
			std::cout << "-------------------------------------------------\n";
		}
		m_HasMatchFinished = true;
		return m_CurrentPos;
	}
	for (const Position& np : nextPositions)
	{
		//np.Print();
		float score = -NegaMaxAlphaBeta(depth - 1, np, std::numeric_limits<float>::lowest(), FLT_MAX);
		if (score >= max)
		{
			max = score;
			bestContinuation = np;
			outScore = score;
		}
	}
	//std::cout << "-------------------------------------------------\n";
	return bestContinuation;
}