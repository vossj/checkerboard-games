#include "chessobjs.h"

#include <cassert>
#include <iostream>

using namespace Chess;
using namespace std;

Chess::Piece::Piece()
{
    Value = Pieces::NONE;
}

Chess::Piece::Piece( ProtoPiece p )
{
    Value = p;
}

bool Piece::IsValid()
{
    if ((*this) == Pieces::NONE)
	return true;

    // A piece should consist of exactly one color and a single piece
    // type among the valid ranges, and no other bits.

    // Check that the piece has exactly one color set.
    if (IsWhite() == IsBlack())
	return false;

    // Check that the piece type is valid
    ProtoPiece PieceType = (*this) & PieceFlags::TYPE_MASK;
    if (PieceType > PieceFlags::TYPE_MAX)
	return false;
    
    // Check no extra bits of information
    return ((*this) & ( PieceFlags::COLOR_MASK |
			PieceFlags::TYPE_MASK )) == (*this);
}

Piece::operator ProtoPiece() const
{
    return Value;
}

Piece & Piece::operator=(const ProtoPiece & p)
{
    Value = ProtoPiece(p);
    return (*this);
}

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
    char File = GetFile(coord);
    char Rank = GetRank(coord);
    return ('a' <= File) && (File <= 'h') &&
	('1' <= Rank) && (Rank <= '8');
}

Piece & Position::operator[]( const string & coord )
{
    assert( Position::ValidCoordinate(coord) );

    char Rank = GetRank(coord);
    char File = GetFile(coord);
    return Board[File-'a'][Rank-'1'];
}

const Piece Position::operator[]( const string & coord ) const
{
    assert( Position::ValidCoordinate( coord ) );

    char Rank = GetRank( coord );
    char File = GetFile( coord );
    return Board[File-'a'][Rank-'1'];
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

ostream & Chess::operator<<(ostream & out, const Position & p)
{
    p.Print( out );
    
    return out;
}
