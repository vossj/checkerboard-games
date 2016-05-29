#include <checkerboard.h>

using namespace CheckerBoard;

CheckerBoard::CheckerBoard()
{
    // Create an empty checker board
    Board.reserve( 32 );
    for ( int i = 1 ; i < 32 ; ++i )
        SetPiece( Pieces::NONE, i );
}

CheckerBoard::SetPiece( Piece p, int loc )
{
    Board[loc - 1] = p;
    return p;
}
