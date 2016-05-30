#include "chessobjs.h"

#include <cassert>
#include <iostream>

using namespace Chess;
using namespace std;
Move::Move()
{
    ShortCastle = false;
    LongCastle = false;
    EnPassant = false;
    StartSquare = "";
    EndSquare = "";
    CapturedPiece = Pieces::NONE;
    Promotion = Pieces::NONE;
}

Position::Position()
{
    // Set up an empty board
    for (int i = 0 ; i < 8 ; ++i )
	for (int j = 0 ; j < 8 ; ++j )
	    Board[i][j] = Pieces::NONE;
}

bool Position::ValidCoordinate( const string & coord )
{
    // Sanity check length first
    if (coord.length() != 2)
	return false;

    // Check actual coordinate is valid
    return ('a' <= coord[0]) && (coord[0] <= 'h') &&
	('1' <= coord[1]) && (coord[1] <= '8');
}

Piece & Position::operator[]( const string & coord )
{
    assert( Position::ValidCoordinate(coord) );

    return Board[coord[0]-'a'][coord[1]-'1'];
}

const Piece Position::operator[]( const string & coord ) const
{
    assert( Position::ValidCoordinate( coord ) );

    return Board[coord[0]-'a'][coord[1]-'1'];
}

void Position::Print( ostream & out ) const
{
    for ( char row = '8' ; row >= '1' ; row-- ) {
	// print row labels
	out << row;

	for ( char col = 'a' ; col <= 'h' ; col++ ) {
	    string coord = "";
	    coord.push_back(col);
	    coord.push_back(row);
	    
	    Piece p = (*this)[coord];
	    
	    out << " ";

	    // Actually print the piece
	    if (p == Pieces::NONE) {
		out << "  ";
		continue;
	    }
	    
	    if (p & PieceFlags::BLACK)
		out << "B";
	    else
		out << "W";

	    if (p & PieceFlags::PAWN)
		out << "P";
	    else if (p & PieceFlags::KNIGHT)
		out << "N";
	    else if (p & PieceFlags::BISHOP)
		out << "B";
	    else if (p & PieceFlags::ROOK)
		out << "R";
	    else if (p & PieceFlags::QUEEN)
		out << "Q";
	    else if (p & PieceFlags::KING)
		out << "K";
	    else
		assert(false);
	}
	out << endl;
    }

    // Print column labels
    out << " ";
    for ( char col = 'a' ; col <= 'h' ; col++ ) {
	out << " " << col << " ";
    }
    out << endl;
}

ostream & operator<<(ostream & out, const Position & p)
{
    p.Print( out );
    
    return out;
}

int main()
{
    Position P;
    P.Print( cout );
    
    return 0;
}
