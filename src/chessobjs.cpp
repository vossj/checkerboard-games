#include "chessobjs.h"

#include <cassert>
#include <iostream>
#include <vector>

using namespace Chess;
using namespace std;

/////////////////////////////////////////////////////////////////////////////
// Piece class definitions --------------------------------------------------
/////////////////////////////////////////////////////////////////////////////
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

/////////////////////////////////////////////////////////////////////////////
// Move class definitions ---------------------------------------------------
/////////////////////////////////////////////////////////////////////////////
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

/////////////////////////////////////////////////////////////////////////////
// Position class definitions -----------------------------------------------
/////////////////////////////////////////////////////////////////////////////
void Position::ExecuteMove( const Move & m )
{
    // STUB FUNCTION
}

void Position::GenLegalMoves( vector<Move> & Moves )
{
    vector<Move>().swap( Moves);  // Destroys / clears the Moves vector.
    //
    // STUB FUNCTION
    //
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

ostream & Chess::operator<<(ostream & out, const Position & p)
{
    p.Print( out );
    
    return out;
}

Position::Position()
{
    SetToEmptyPosition();
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

	    // Print the piece color
	    ProtoPiece Color = p & PieceFlags::COLOR_MASK;
	    if (Color == PieceFlags::BLACK)
		out << "B";
	    else if ( Color == PieceFlags::WHITE )
		out << "W";
	    else
		assert(false); // All non-empty pieces should have a color of either BLACK or WHITE.

	    // Print the piece type
	    ProtoPiece Type = p & PieceFlags::TYPE_MASK;
	    if (Type == PieceFlags::PAWN)
		out << "P";
	    else if (Type == PieceFlags::KNIGHT)
		out << "N";
	    else if (Type == PieceFlags::BISHOP)
		out << "B";
	    else if (Type == PieceFlags::ROOK)
		out << "R";
	    else if (Type == PieceFlags::QUEEN)
		out << "Q";
	    else if (Type == PieceFlags::KING)
		out << "K";
	    else
		assert(false); // Piece does not have a valid description.
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

void Position::RetractMove( const Move & m )
{
    // STUB FUNCTION
}

void Position::SetToEmptyPosition()
{
    // Set up an empty board
    for (int i = 0 ; i < 8 ; ++i )
	for (int j = 0 ; j < 8 ; ++j )
	    Board[i][j] = Pieces::NONE;

    // Set default flags (nothing moved out of place, white to move)
    WKMoved = false;
    BKMoved = false;
    a1RMoved = false;
    h1RMoved = false;
    a8RMoved = false;
    h8RMoved = false;
    EPPLocale = "";
    WhiteToMove = true;
}

void Position::SetToInitialPosition()
{
    this->SetToEmptyPosition();

    // Manually place all pieces except pawns
    (*this)["a1"] = Chess::Pieces::WHITE_ROOK;
    (*this)["b1"] = Chess::Pieces::WHITE_KNIGHT;
    (*this)["c1"] = Chess::Pieces::WHITE_BISHOP;
    (*this)["d1"] = Chess::Pieces::WHITE_QUEEN;
    (*this)["e1"] = Chess::Pieces::WHITE_KING;
    (*this)["f1"] = Chess::Pieces::WHITE_BISHOP;
    (*this)["g1"] = Chess::Pieces::WHITE_KNIGHT;
    (*this)["h1"] = Chess::Pieces::WHITE_ROOK;
    (*this)["a8"] = Chess::Pieces::BLACK_ROOK;
    (*this)["b8"] = Chess::Pieces::BLACK_KNIGHT;
    (*this)["c8"] = Chess::Pieces::BLACK_BISHOP;
    (*this)["d8"] = Chess::Pieces::BLACK_QUEEN;
    (*this)["e8"] = Chess::Pieces::BLACK_KING;
    (*this)["f8"] = Chess::Pieces::BLACK_BISHOP;
    (*this)["g8"] = Chess::Pieces::BLACK_KNIGHT;
    (*this)["h8"] = Chess::Pieces::BLACK_ROOK;    
    
    // Add pawns
    for (char File = 'a' ; File <= 'h' ; ++File) {
	string s;
	s.push_back(File);
	s.push_back('2');
	(*this)[ s ] = Pieces::WHITE_PAWN;

	s[1] = '7';
	(*this)[ s ] = Pieces::BLACK_PAWN;
    }
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
