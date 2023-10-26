
#include "state.h"
#include <string>

state::state(std::initializer_list< unsigned int > init)
    :sticks(init)
{
}

state::state( unsigned int i1, unsigned int i2 )
{
    for (unsigned int i = i1; i <= i2; i++) {
        sticks.push_back(i);
    }
}

unsigned int state::sum( ) const 
{
    unsigned int sum=0;
    for (unsigned int i = 0; i < sticks.size(); i++) {
        sum += sticks[i];
    }
    return sum;
}

std::optional< move > state::randommove( ) const 
{
    if (this->sum() == 0) {
        return std::optional< move >();
    }
    else {
        int row=rand()%sticks.size();
        while (sticks[row] == 0) {
            row = rand() % sticks.size();
        }
        int remain = rand() % sticks[row];
        return move(row, remain);
    }
}


std::optional< move >
state::usermove( std::ostream& out, std::istream& in ) const
{
   // It seems to me that usermove( ) is the same as randommove( ),
   // with the only difference that rand( ) should be replaced by
   // user( ). We could make it into a template. 

   if( sum( ))
   {
      while( true )
      {
         std::string inp;
         try
         {
            out << "row? "; out. flush( );
            in >> inp; 

            unsigned int row = std::stoul( inp ); inp. clear( );

            if( row > 0 && row <= sticks. size( )) 
            {
               unsigned int row1 = row - 1;  // This is a type conversion! 
               if( sticks[ row1 ] )
               {
                  out << "how many remaining? "; out. flush( );
                  in >> inp; 
                  unsigned int remain = std::stoul( inp ); inp. clear( ); 

                  if( remain < sticks[ row1 ] )
                     return move( row1, remain );
                  else
                  {
                     out << "having " << remain 
                         << " remaining is not possible, "
                         << "you have to remove at least one stick\n";
                  }
               }
               else 
               {
                  out << "row " << row << " is already empty\n";
               }
            }
            else
            {
               out << "row " << row << " is not a valid row, ";
               out << "rows are between 1 and " << sticks. size( ) << "\n";
            }
            
         }
         catch( std::invalid_argument& inv )
         {
            out << inp << " is not a number\n";
         }
         catch( std::out_of_range& r )
         {
            out << inp << " is too big\n";
         }
      }
   }
   else
      return std::optional< move > ( );
}

std::optional<move> state::removelastmorethantwo() const {
    int TwoOrMore=0;
    unsigned int index=-1;
    int OneStickRow=0;
    for (unsigned int i = 0; i < sticks.size(); i++) {
        if (sticks[i] >=2) {
            TwoOrMore++;
            index = i;
        }
        if (sticks[i] == 1) {
            OneStickRow++;
        }
    }
    if (TwoOrMore != 1) {
        return std::optional< move >();
    }
    int remainder;
    (OneStickRow % 2 == 0) ? remainder = 1 : remainder = 0;
    return move(index, remainder);
}

unsigned int state::nimber() const{
    unsigned int sum=0;
    for (unsigned int i = 0; i < sticks.size(); i++) {
        sum = sum ^ sticks[i];
    }
    return sum;
}

void state::make( move m )
{ 
    sticks[m.row] = m.remaining;
}

std::optional<move> state::makenimberzero() const {
    if (nimber() == 0) {
        return std::optional< move >();
    }
    int  row = rand() % sticks.size();
    while (nimber() ^ (sticks[row]) >= (sticks[row])) {
        row = rand() % sticks.size();
    }
    return move(row, nimber() ^ (sticks[row]));
}

void state::print( std::ostream& out ) const
{ 
    unsigned int numberOfOnes;
    for (unsigned int i = 1; i <=sticks.size(); i++) {
        out << i <<":" << '\t';
            numberOfOnes = sticks[i - 1];
        while (numberOfOnes != 0) {
            out << "1 ";
            numberOfOnes--;
            }
        out << '\n';
    }
 }


