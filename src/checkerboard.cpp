#include <checkerboard.h>

using namespace CheckerBoard;

CheckerBoard::CheckerBoard()
{
    // Create an empty checker board
    Board.reserve( 32 );
    for ( int i = 1 ; i < 32 ; ++i )
        SetPiece( Pieces::NONE, i );
}

void CheckerBoard::SetInitialPos()
{
    this->SetInitialPos( "English Draughts" );
}

void CheckerBoard::SetInitialPos( const char * GameName )
{
    for (int i = 1 ; i <= 12 ; ++i )
	this->SetPiece( Pieces::DARK_STANDARD, i );

    for (int i = 21 ; i <= 32 ; ++i )
	this->SetPiece( Pieces::LIGHT_STANDARD, i );
}

Piece CheckerBoard::SetPiece( Piece p, int loc )
{
    Board[loc - 1] = p;
    return p;
}
