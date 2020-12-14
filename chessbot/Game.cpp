#include "pch.h"
#include "Game.h"

Game::Game( const Window& window ) 
	:m_Window{ window }
	,m_Pieces{new Texture{"Resources/chess.png"}}
	,m_Rows{8}
	,m_Board{100,100,600,600}
	,m_SquareWidth{ m_Board.width / m_Rows }
	,m_WhiteSquares{0x55AA55AA55AA55AA}
	,m_WhitePawns{ 0xFF00 }
	,m_WhiteKnights{ 0x42 }
	,m_WhiteBishops{ 0x24 }
	,m_WhiteRooks{ 0x81 }
	,m_WhiteKing{ 0x10 }
	,m_WhiteQueen{ 0x8 }
	,m_BlackSquares{ 0xAA55AA55AA55AA55 }
	,m_BlackPawns{ 0xFF000000000000 }
	,m_BlackKnights{ 0x4200000000000000 }
	,m_BlackBishops{ 0x2400000000000000 }
	,m_BlackRooks{ 0x8100000000000000 }
	,m_BlackKing{ 0x1000000000000000 }
	,m_BlackQueen{ 0x800000000000000 }
	, m_IsHoldingAPiece{ false }
	,m_HoldedPiece{NO_PIECE}
	,m_AllWhitePieces{ m_WhitePawns | m_WhiteKnights | m_WhiteBishops | m_WhiteRooks | m_WhiteKing | m_WhiteQueen }
	,m_AllBlackPieces{ m_BlackPawns | m_BlackKnights | m_BlackBishops | m_BlackRooks | m_BlackKing | m_BlackQueen }
	,m_PossibleMoves{0}
	,m_IsWhitesTurn{ true }
	,m_NeverMoved{m_AllBlackPieces | m_AllWhitePieces}
{
	Initialize( );
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	/*std::cout << "white squares:\n";
	m_WhiteSquares.Print();
	std::cout << "white pawns:\n";
	m_WhitePawns.Print();
	std::cout << "white Knights:\n";
	m_WhiteKnights.Print();
	std::cout << "white Bishops:\n";
	m_WhiteBishops.Print();
	std::cout << "white Rooks:\n";
	m_WhiteRooks.Print();
	std::cout << "white King:\n";
	m_WhiteKing.Print();
	std::cout << "white Queen:\n";
	m_WhiteQueen.Print();

	std::cout << "Black squares:\n";
	m_BlackSquares.Print();
	std::cout << "Black pawns:\n";
	m_BlackPawns.Print();
	std::cout << "Black Knights:\n";
	m_BlackKnights.Print();
	std::cout << "Black Bishops:\n";
	m_BlackBishops.Print();
	std::cout << "Black Rooks:\n";
	m_BlackRooks.Print();
	std::cout << "Black King:\n";
	m_BlackKing.Print();
	std::cout << "Black Queen:\n";
	m_BlackQueen.Print();*/
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
	m_WhitePawns.Print();
	m_WhitePawns.Insert(2, 2);
	m_WhitePawns.Print();
	m_WhitePawns.Reset(C3);
	m_WhitePawns.Print();*/
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
}

void Game::Cleanup( )
{
	delete m_Pieces;
}

void Game::Update( float elapsedSec )
{
	// Check keyboard state
	//const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	//if ( pStates[SDL_SCANCODE_RIGHT] )
	//{
	//	std::cout << "Right arrow key is down\n";
	//}
	//if ( pStates[SDL_SCANCODE_LEFT] && pStates[SDL_SCANCODE_UP])
	//{
	//	std::cout << "Left and up arrow keys are down\n";
	//}
}

void Game::Draw( ) const
{
	ClearBackground( );
	DrawChessBoard();
	DrawPieces();
	if (m_IsHoldingAPiece)
	{
		glColor4f(0.f, 0.7, 0.f, 0.5f);
		DrawSquare(m_HoldedPieceSquare);
		DrawPossibleMoves();
	}
	glColor4f(1.f, 1., 1.f, 1.f);
	if (m_IsWhitesTurn)
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
	//glColor4f(0.f, 0.f, 0.f, 1.f);
	glColor4f(181.f/255, 135.f/255, 99.f/255, 1.f);
	utils::FillRect(m_Board);
	//glColor4f(1.f, 1.f, 1.f, 1.f);
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
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	//switch ( e.keysym.sym )
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "`Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
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

	switch (e.button)
	{
	case SDL_BUTTON_LEFT:
		//std::cout << " left button " << std::endl;
		if (m_IsHoldingAPiece)
		{
				
			Square clickedSquare{ GetSquare(Point2f{ float(e.x),m_Window.height - float(e.y) }) };
			//check if valid spot for piece
			if (CheckValidMove(clickedSquare))
			{
				//update the board
				UpdateBoard(clickedSquare);
				m_IsWhitesTurn = !m_IsWhitesTurn;
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
				if (m_IsWhitesTurn && (m_HoldedPiece == W_PAWN
					|| m_HoldedPiece == W_KNIGHT
					|| m_HoldedPiece == W_BISHOP
					|| m_HoldedPiece == W_ROOK
					|| m_HoldedPiece == W_QUEEN
					|| m_HoldedPiece == W_KING))
				{
					m_IsHoldingAPiece = true;
				}
				else if (!m_IsWhitesTurn && (m_HoldedPiece == B_PAWN
					|| m_HoldedPiece == B_KNIGHT
					|| m_HoldedPiece == B_BISHOP
					|| m_HoldedPiece == B_ROOK
					|| m_HoldedPiece == B_QUEEN
					|| m_HoldedPiece == B_KING))
				{
					m_IsHoldingAPiece = true;
				}
			}
			//UpdatePossibleMoves();
			m_PossibleMoves = GetAttacks(m_HoldedPiece, m_HoldedPieceSquare, m_IsWhitesTurn, true);

			//GetAllAttacks(true).Print();
		}
			
		break;
	}
	
}
//void Game::UpdatePossibleMoves()
//{
//	uint64_t allpieces = m_AllBlackPieces.GetData() | m_AllWhitePieces.GetData();
//	if (m_IsWhitesTurn)
//	{
//		switch (m_HoldedPiece)
//		{
//		case NO_PIECE:
//			break;
//		case W_PAWN:
//			m_PossibleMoves = m_WhitePawns.GetPawnsPossibleMoves(m_HoldedPieceSquare, m_AllWhitePieces.GetData(), W_PAWN) 
//				& ~m_BlackPawns.GetData() | m_WhitePawns.GetPawnsPossibleAttacks(m_HoldedPieceSquare, m_AllBlackPieces.GetData(), W_PAWN);
//			break;
//		case W_KNIGHT:
//			m_PossibleMoves = m_WhiteKnights.GetKnightPossibleMoves(m_HoldedPieceSquare, m_AllWhitePieces.GetData());
//			break;
//		case W_BISHOP:
//			//m_PossibleMoves = m_WhiteBishops.GetBishopPossibleMoves(m_HoldedPieceSquare, m_AllWhitePieces.GetData() & ~m_WhiteBishops.GetData() | m_AllBlackPieces.GetData());
//			m_PossibleMoves = m_WhiteBishops.GetBishopPossibleMoves(m_HoldedPieceSquare, allpieces & ~m_WhiteBishops.GetData());
//			break;
//		case W_ROOK:
//			m_PossibleMoves = m_WhiteRooks.GetRookPossibleMoves(m_HoldedPieceSquare, allpieces & ~m_WhiteRooks.GetData());
//			break;
//		case W_QUEEN:
//			m_PossibleMoves = m_WhiteQueen.GetQueenPossibleMoves(m_HoldedPieceSquare, allpieces & ~m_WhiteQueen.GetData());
//			break;
//		case W_KING:
//			m_PossibleMoves = m_WhiteKing.GetKingPossibleMoves(m_HoldedPieceSquare, m_AllWhitePieces.GetData(), W_KING, m_NeverMoved);
//			break;
//		case PIECE_NB:
//			break;
//		default:
//			break;
//		}
//		m_PossibleMoves = m_PossibleMoves & ~m_AllWhitePieces.GetData();
//	}
//	else
//	{
//		switch (m_HoldedPiece)
//		{
//		case NO_PIECE:
//			break;
//		case B_PAWN:
//			m_PossibleMoves = m_BlackPawns.GetPawnsPossibleMoves(m_HoldedPieceSquare, m_AllBlackPieces.GetData(), B_PAWN) 
//				& ~m_WhitePawns.GetData() | m_BlackPawns.GetPawnsPossibleAttacks(m_HoldedPieceSquare, m_AllWhitePieces.GetData(), B_PAWN);
//			break;
//		case B_KNIGHT:
//			m_PossibleMoves = m_BlackKnights.GetKnightPossibleMoves(m_HoldedPieceSquare, m_AllBlackPieces.GetData());
//			break;
//		case B_BISHOP:
//			m_PossibleMoves = m_BlackBishops.GetBishopPossibleMoves(m_HoldedPieceSquare, allpieces & ~m_BlackBishops.GetData());
//			break;
//		case B_ROOK:
//			m_PossibleMoves = m_BlackRooks.GetRookPossibleMoves(m_HoldedPieceSquare, allpieces & ~m_BlackRooks.GetData());
//			break;
//		case B_QUEEN:
//			m_PossibleMoves = m_BlackQueen.GetQueenPossibleMoves(m_HoldedPieceSquare, allpieces & ~m_BlackQueen.GetData());
//			break;
//		case B_KING:
//			m_PossibleMoves = m_BlackKing.GetKingPossibleMoves(m_HoldedPieceSquare, m_AllBlackPieces.GetData(), B_KING, m_NeverMoved);
//			break;
//		case PIECE_NB:
//			break;
//		default:
//			break;
//		}
//		m_PossibleMoves = m_PossibleMoves & ~m_AllBlackPieces.GetData();
//
//	}
//}

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

Piece Game::GetPiece(const Square& s) const
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


void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

void Game::DrawWhitePawns() const
{
	std::vector<std::pair<int, int>> wp = m_WhitePawns.GetPositions();
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
	std::vector<std::pair<int, int>> wk = m_WhiteKnights.GetPositions();
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
	std::vector<std::pair<int, int>> wb = m_WhiteBishops.GetPositions();
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
	std::vector<std::pair<int, int>> wr = m_WhiteRooks.GetPositions();
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
	std::vector<std::pair<int, int>> wking = m_WhiteKing.GetPositions();
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
	std::vector<std::pair<int, int>> wq = m_WhiteQueen.GetPositions();
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
	std::vector<std::pair<int, int>> bp = m_BlackPawns.GetPositions();
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
	std::vector<std::pair<int, int>> bk = m_BlackKnights.GetPositions();
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
	std::vector<std::pair<int, int>> bb = m_BlackBishops.GetPositions();
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
	std::vector<std::pair<int, int>> br = m_BlackRooks.GetPositions();
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
	std::vector<std::pair<int, int>> bking = m_BlackKing.GetPositions();
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
	std::vector<std::pair<int, int>> bq = m_BlackQueen.GetPositions();
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
	utils::FillRect(GetSquarePos(s).first * m_SquareWidth + m_Board.left,
		GetSquarePos(s).second * m_SquareWidth + m_Board.bottom
		, m_SquareWidth, m_SquareWidth);
}

Square MakeSquare(int row, int column)
{
	return Square((row << 3) + column);
}
void Game::DrawCircleInSquare(std::pair<int, int> p) const
{
	Square s = MakeSquare(p.first, p.second);
	utils::FillEllipse(GetSquarePos(s).first * m_SquareWidth + m_SquareWidth / 2.f + m_Board.left,
		GetSquarePos(s).second * m_SquareWidth + m_SquareWidth / 2.f + m_Board.bottom
		, m_SquareWidth / 4.f, m_SquareWidth / 4.f);
}
void Game::DrawSquare(std::pair<int, int> p) const
{
	Square s = MakeSquare(p.first, p.second);
	utils::FillRect(GetSquarePos(s).first * m_SquareWidth + m_Board.left,
		GetSquarePos(s).second * m_SquareWidth + m_Board.bottom
		, m_SquareWidth, m_SquareWidth);
}
void Game::DrawInCheck() const
{
	if (m_IsInCheck)
	{
		if (m_IsWhitesTurn)
		{
			Square s = m_WhiteKing.GetSquarePositions().front();
			glColor4f(1, 0, 0, 0.5f);
			utils::FillRect(GetSquarePos(s).first * m_SquareWidth + m_Board.left,
				GetSquarePos(s).second * m_SquareWidth + m_Board.bottom
				, m_SquareWidth, m_SquareWidth);
		}
		else
		{
			Square s = m_BlackKing.GetSquarePositions().front();
			glColor4f(1, 0, 0, 0.5f);
			utils::FillRect(GetSquarePos(s).first * m_SquareWidth + m_Board.left,
				GetSquarePos(s).second * m_SquareWidth + m_Board.bottom
				, m_SquareWidth, m_SquareWidth);
		}
	}
}
std::pair<int, int> Game::GetSquarePos(const Square& s) const
{
	return std::pair<int, int>{  utils::GetColumn(s, 8), utils::GetRow(s, 8)};
}


uint64_t SquareToBitBoard(const Square& s)
{
	return SquareBB[s];
}

void Game::PrintAsBitboard(uint64_t bb) const
{
	std::cout << bb << std::endl;
	std::cout << "+---+---+---+---+---+---+---+---+\n";
	for (int row = 7; row >= 0; --row)
	{
		for (int col = 0; col < 8; ++col)
		{
			if (bb & SquareToBitBoard(MakeSquare(row, col)))
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
	Bitboard WP = m_WhitePawns;
	Bitboard WK = m_WhiteKnights;
	Bitboard WB = m_WhiteBishops;
	Bitboard WR = m_WhiteRooks;
	Bitboard WKI = m_WhiteKing;
	Bitboard WQ = m_WhiteQueen;

	Bitboard BP = m_BlackPawns;
	Bitboard BK = m_BlackKnights;
	Bitboard BB = m_BlackBishops;
	Bitboard BR = m_BlackRooks;
	Bitboard BKI = m_BlackKing;
	Bitboard BQ = m_BlackQueen;

	Bitboard AW = m_AllWhitePieces;
	Bitboard AB = m_AllBlackPieces;

	//delete the captured piece
	if (m_IsWhitesTurn && (SquareBB[s] & m_AllBlackPieces.GetData()))
	{
		DeletePiece(GetPiece(s), s);
	}
	else if (!m_IsWhitesTurn && (SquareBB[s] & m_AllWhitePieces.GetData()))
	{
		DeletePiece(GetPiece(s), s);
	}
	//set neverMoved to false
	m_NeverMoved.Reset(s);
	//update the moved piece
	switch (m_HoldedPiece)
	{
	case NO_PIECE:
		break;
	case W_PAWN:
		m_WhitePawns.Reset(m_HoldedPieceSquare);
		m_WhitePawns.Insert(s);
		//promotion
		if (s > H7)
		{
			m_WhitePawns.Reset(s);
			m_WhiteQueen.Insert(s);
		}
		break;
	case W_KNIGHT:
		m_WhiteKnights.Reset(m_HoldedPieceSquare);
		m_WhiteKnights.Insert(s);
		break;
	case W_BISHOP:
		m_WhiteBishops.Reset(m_HoldedPieceSquare);
		m_WhiteBishops.Insert(s);
		break;
	case W_ROOK:
		m_WhiteRooks.Reset(m_HoldedPieceSquare);
		m_WhiteRooks.Insert(s);
		break;
	case W_QUEEN:
		m_WhiteQueen.Reset(m_HoldedPieceSquare);
		m_WhiteQueen.Insert(s);
		break;
	case W_KING:
		m_WhiteKing.Reset(m_HoldedPieceSquare);
		m_WhiteKing.Insert(s);
		//castling
		//long
		if (m_HoldedPieceSquare == E1 && m_AllWhitePieces.GetState(A1) && s == B1)
		{
			m_WhiteRooks.Reset(A1);
			m_WhiteRooks.Insert(C1);
		}
		//short
		if (m_HoldedPieceSquare == E1 && m_AllWhitePieces.GetState(H1) && s == G1)
		{
			m_WhiteRooks.Reset(H1);
			m_WhiteRooks.Insert(F1);
		}
		break;
	case B_PAWN:
		m_BlackPawns.Reset(m_HoldedPieceSquare);
		m_BlackPawns.Insert(s);
		//promotion
		if (s < A2)
		{
			m_BlackPawns.Reset(s);
			m_BlackQueen.Insert(s);
		}
		break;
	case B_KNIGHT:
		m_BlackKnights.Reset(m_HoldedPieceSquare);
		m_BlackKnights.Insert(s);
		break;
	case B_BISHOP:
		m_BlackBishops.Reset(m_HoldedPieceSquare);
		m_BlackBishops.Insert(s);
		break;
	case B_ROOK:
		m_BlackRooks.Reset(m_HoldedPieceSquare);
		m_BlackRooks.Insert(s);
		break;
	case B_QUEEN:
		m_BlackQueen.Reset(m_HoldedPieceSquare);
		m_BlackQueen.Insert(s);
		break;
	case B_KING:
		m_BlackKing.Reset(m_HoldedPieceSquare);
		m_BlackKing.Insert(s);
		//castling
		//long
		if (m_HoldedPieceSquare == E8 && m_AllBlackPieces.GetState(A8) && s == B8)
		{
			m_BlackRooks.Reset(A8);
			m_BlackRooks.Insert(C8);
		}
		//short
		if (m_HoldedPieceSquare == E8 && m_AllBlackPieces.GetState(H8) && s == G8)
		{
			m_BlackRooks.Reset(H8);
			m_BlackRooks.Insert(F8);
		}
		break;
	case PIECE_NB:
		break;
	default:
		break;
	}
	m_AllWhitePieces = m_WhitePawns | m_WhiteKnights | m_WhiteBishops | m_WhiteRooks | m_WhiteKing | m_WhiteQueen;
	m_AllBlackPieces = m_BlackPawns | m_BlackKnights | m_BlackBishops | m_BlackRooks | m_BlackKing | m_BlackQueen;

	//if you are in check your move needs to fix it
	if (CheckForCheck())
	{
		//the player didn't fix the check, so revert the move
		m_WhitePawns = WP;
		m_WhiteKnights = WK;
		m_WhiteBishops = WB;
		m_WhiteRooks = WR;
		m_WhiteKing = WKI;
		m_WhiteQueen = WQ;

		m_BlackPawns = BP;
		m_BlackKnights = BK;
		m_BlackBishops = BB;
		m_BlackRooks = BR;
		m_BlackKing = BKI;
		m_BlackQueen = BQ;
		m_IsWhitesTurn = !m_IsWhitesTurn;
		std::cout << "You can't do this move because you are in check\n";
	}
	else
	{
		m_IsInCheck = false;
	}
	
}
void Game::DeletePiece(Piece p, Square s)
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
Bitboard Game::GetAttacks(Piece p, Square s, bool fromWhite, bool andMoves)
{
	Bitboard result{0};
	uint64_t allpieces = m_AllBlackPieces.GetData() | m_AllWhitePieces.GetData();
	if (fromWhite)
	{
		switch (p)
		{
		case NO_PIECE:
			break;
		case W_PAWN:
			if (andMoves)
			{
				result = m_WhitePawns.GetPawnsPossibleMoves(s, m_AllWhitePieces.GetData(), W_PAWN)
					& ~m_BlackPawns.GetData() | m_WhitePawns.GetPawnsPossibleAttacks(s, m_AllBlackPieces.GetData(), W_PAWN);
			}
			else
			{
				result = m_WhitePawns.GetPawnsPossibleAttacks(s, m_AllBlackPieces.GetData(), W_PAWN);
			}
			break;
		case W_KNIGHT:
			result = m_WhiteKnights.GetKnightPossibleMoves(s, m_AllWhitePieces.GetData());
			break;
		case W_BISHOP:
			result = m_WhiteBishops.GetBishopPossibleMoves(s, allpieces & ~m_WhiteBishops.GetData());
			break;
		case W_ROOK:
			result = m_WhiteRooks.GetRookPossibleMoves(s, allpieces & ~m_WhiteRooks.GetData());
			break;
		case W_QUEEN:
			result = m_WhiteQueen.GetQueenPossibleMoves(s, allpieces & ~m_WhiteQueen.GetData());
			break;
		case W_KING:
			result = m_WhiteKing.GetKingPossibleMoves(s, m_AllWhitePieces.GetData(), W_KING, m_NeverMoved);
			result = result & ~GetAllAttacks(false).GetData();
			break;
		case PIECE_NB:
			break;
		default:
			break;
		}
		result = result & ~m_AllWhitePieces.GetData();
	}
	else
	{
		switch (p)
		{
		case NO_PIECE:
			break;
		case B_PAWN:
			if (andMoves)
			{
				result = m_BlackPawns.GetPawnsPossibleMoves(s, m_AllBlackPieces.GetData(), B_PAWN)
					& ~m_WhitePawns.GetData() | m_BlackPawns.GetPawnsPossibleAttacks(s, m_AllWhitePieces.GetData(), B_PAWN);
			}
			else
			{
				result = m_BlackPawns.GetPawnsPossibleAttacks(s, m_AllWhitePieces.GetData(), B_PAWN);
			}
			break;
		case B_KNIGHT:
			result = m_BlackKnights.GetKnightPossibleMoves(s, m_AllBlackPieces.GetData());
			break;
		case B_BISHOP:
			result = m_BlackBishops.GetBishopPossibleMoves(s, allpieces & ~m_BlackBishops.GetData());
			break;
		case B_ROOK:
			result = m_BlackRooks.GetRookPossibleMoves(s, allpieces & ~m_BlackRooks.GetData());
			break;
		case B_QUEEN:
			result = m_BlackQueen.GetQueenPossibleMoves(s, allpieces & ~m_BlackQueen.GetData());
			break;
		case B_KING:
			result = m_BlackKing.GetKingPossibleMoves(s, m_AllBlackPieces.GetData(), B_KING, m_NeverMoved);
			result = result & ~GetAllAttacks(true).GetData();
			break;
		case PIECE_NB:
			break;
		default:
			break;
		}
		result = result & ~m_AllBlackPieces.GetData();

	}
	return result;
}
Bitboard Game::GetAllAttacks(bool fromWhite)
{
	Bitboard result{0};
	Square s;
	if (fromWhite)
	{
		for (std::pair<int, int> p : m_WhitePawns.GetPositions())
		{
			s = MakeSquare(p.first, p.second);
			result = result | GetAttacks(W_PAWN, s, fromWhite, false);
		}
		for (std::pair<int, int> p : m_WhiteKnights.GetPositions())
		{
			s = MakeSquare(p.first, p.second);
			result = result | GetAttacks(W_KNIGHT, s, fromWhite, false);
		}
		for (std::pair<int, int> p : m_WhiteBishops.GetPositions())
		{
			s = MakeSquare(p.first, p.second);
			result = result | GetAttacks(W_BISHOP, s, fromWhite, false);
		}
		for (std::pair<int, int> p : m_WhiteRooks.GetPositions())
		{
			s = MakeSquare(p.first, p.second);
			result = result | GetAttacks(W_ROOK, s, fromWhite, false);
		}
		for (std::pair<int, int> p : m_WhiteQueen.GetPositions())
		{
			s = MakeSquare(p.first, p.second);
			result = result | GetAttacks(W_QUEEN, s, fromWhite, false);
		}
		/*for (std::pair<int, int> p : m_WhiteKing.GetPositions())
		{
			s = MakeSquare(p.first, p.second);
			result = result | GetAttacks(W_KING, s, fromWhite, false);
		}*/

	}
	else
	{
		for (std::pair<int, int> p : m_BlackPawns.GetPositions())
		{
			s = MakeSquare(p.first, p.second);
			result = result | GetAttacks(B_PAWN, s, fromWhite, false);
		}
		for (std::pair<int, int> p : m_BlackKnights.GetPositions())
		{
			s = MakeSquare(p.first, p.second);
			result = result | GetAttacks(B_KNIGHT, s, fromWhite, false);
		}
		for (std::pair<int, int> p : m_BlackBishops.GetPositions())
		{
			s = MakeSquare(p.first, p.second);
			result = result | GetAttacks(B_BISHOP, s, fromWhite, false);
		}
		for (std::pair<int, int> p : m_BlackRooks.GetPositions())
		{
			s = MakeSquare(p.first, p.second);
			result = result | GetAttacks(B_ROOK, s, fromWhite, false);
		}
		for (std::pair<int, int> p : m_BlackQueen.GetPositions())
		{
			s = MakeSquare(p.first, p.second);
			result = result | GetAttacks(B_QUEEN, s, fromWhite, false);
		}
		/*for (std::pair<int, int> p : m_BlackKing.GetPositions())
		{
			s = MakeSquare(p.first, p.second);
			result = result | GetAttacks(B_KING, s, fromWhite, false);
		}*/
	}
	return result;
}
bool Game::CheckForCheck()
{
	if (!m_IsWhitesTurn)
	{
		//check if black is in check
		if (GetAllAttacks(true).GetData() & SquareBB[m_BlackKing.GetSquarePositions().front()])
		{
			GetAllAttacks(true).Print();

			std::cout << "black is in check!\n";
			m_IsInCheck = true;
			return true;
		}
	}
	//check if white is in check
	else if (GetAllAttacks(false).GetData() & SquareBB[m_WhiteKing.GetSquarePositions().front()])
	{
		std::cout << "white is in check!\n";
		m_IsInCheck = true;
		return true;
	}
	return false;
}
