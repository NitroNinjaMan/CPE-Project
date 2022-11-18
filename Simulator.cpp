#include <string>
#include <assert.h>
#include <vector>
#include <iostream>
using namespace std;

//Description:
//Pre:
//Post
void Restoring(string* Dividend, string*  Divisor, int Length)
{
  int n_sub, n_add, n_iter;
  n_iter = Length;
  
  return;
}

//Description:
//Pre:
//Post
void NonRestoring(string* Dividend, string* Divisor, int LengthDenom, int LengthNum)
{
  int n_sub, n_add, n_iter;
  n_iter = Length;
  return;
}

//Description: Checks for the presence of Divide Overflow.
//Pre: Dividend, Divisor, and Lengths of numerator and denominator  must be defined.
//Post: Will return if the division will result in overflow or not.
bool DivideOverflow(string* Dividend, string* Divisor, int LengthDenom, int LengthNum)
{
  int index;
  bool Overflow = false;
  if(Dividend[0] == '1') //check if Dividend is negative and 2's complement if so.
 {
    index = 1;
    TwosComp(Dividend, Divisor, LengthNum, index);
  }
  else if(Divisor[0] == '1') //check if Divisor is negative and 2's complement if so.
  {
    index = 0;
    TwosComp(Dividend, Divisor, LengthDenom, index);
  }
  for(int i = 1; i < LengthDenom; i++)
  {
    if((Dividend[i] == 1) && (Divisor[i] == 0)) //if bit of Dividend = 1 and bit of Divisor = 0.
    {
      Overflow = true;
      i = LengthDenom;
    }
    else if((Dividend[i] == 0) && (Divisor[i] == 1)) //if bit of Dividend = 0 and bit of Divisor = 1.
    {
      Overflow = false;
      i = LengthDenom;
    }
  }
  return Overflow;
}

//Description: Performs Two’s complement on either the Dividend or Divisor
//Pre: The Dividend or Divisor is a negative number and the index is used to identify which one to operate on. 1 for Dividend, 0 for Divisor.
//Post: The Dividend and Divisor arrays are replaced with their 2's Complement.
void TwosComp(string* Dividend, string* Divisor, int Length, int index)
{
  if(index == 1) // Dividend
  {
    for(int i = 0; i < Length; i++) // Going across the number from left to right complementing the bits
    {
      if(Dividend[i] == '0')
        Dividend[i] == '1';
      else
       Dividend[i] == '0';
    }
    if(Dividend[Length-1] == '0') // If the LSB is 0 adding 1 just makes it 1.
      Dividend[Length-1] == '1';
    else
    {
      for(int i = Length-1; i > 0; i--) // Going across the number from right to left dealing with the addition of 1.
      {
        if(Dividend[i] == '1')
          Dividend[i] == '0';
        else
          Dividend[i] == '1';
    }
  }
  else // Divisor
  {
    for(int i = 0; i < Length; i++) // Going across the number from left to right complementing the bits
    {
      if(Divisor[i] == '0')
        Divisor[i] == '1';
      else
        Divisor[i] == '0';
    }
    if(Divisor[Length-1] == '0') // If the LSB is 0 adding 1 just makes it 1.
      Divisor[Length-1] == '1';
    else
    {
      for(int i = Length-1; i > 0; i--) // Going across the number from right to left dealing with the addition of 1.
      {
        if(Divisor[i] == '1')
          Divisor[i] == '0';
        else
          Divisor[i] == '1';
    }
  }
  return;
}

int main(){
  bool Finished = false;
  const int MAXNUM = 25;
  const int MAXDENOM = 13;
  string Dividend;
  string Divisor;
  string DividendArray[MAXNUM];
  string DiviorArray[MAXDENOM];
  while(!Finished)
  {
    cin >> Dividend;
    for(int i = 0; i < Dividend.size(); i++)
    {
      DividendArray[i] = Dividend.substr(i);
    }
    cin >> Divisor;
    for(int i = 0; i < Divisor.size(); i++)
    {
      DivisorArray[i] = Divisor.substr(i);
    }
    int LengthDenom = Divisior.size() - 1;
    int LengthNum = Dividend.size() -1;
    if(DivideOverflow(DividendArray, DivisorArray, LengthDenom, LengthNum)
    {
      cout<<"Divide Overflow Occured"<<endl;
    }
    else
    {
      Restoring(DividendArray, DivisorArray, LengthDenom, LengthNum);
      NonRestoring(DividendArray, DivisorArray, LengthDenom, LengthNum);
    }
  }
  return 0;
}

