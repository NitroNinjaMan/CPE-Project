#include <string>
#include <assert.h>
#include <vector>
#include <iostream>
using namespace std;

void Restoring(char Dividend[], char Divisor[], int LengthDenom, int LengthNum, bool CompNum);
void NonRestoring(char Dividend[], char Divisor[], int LengthDenom, int LengthNum, bool CompNum);
bool DivideOverflow(char Dividend[], char Divisor[], int LengthDenom, int LengthNum);
void TwosComp(char Dividend[], char Divisor[], int Length, int index);
char Sub(char Dividend[], char Divisor[], int LengthNum, int LengthDenom, int Ebit);
char Add(char Dividend[], char Divisor[], int LengthNum, int LengthDenom, int Ebit);

int main()
{
  bool CompNum;
  const int MAXNUM = 25;
  const int MAXDENOM = 13;
  string Dividend;
  string Divisor;
  char DividendArray[MAXNUM];
  char DivisorArray[MAXDENOM];
  for(int i = 0; i < 20; i++)
  {
    cin >> Dividend;
    DividendArray[0] = Dividend[0];
    for(int i = 0; i < Dividend.size(); i++)
    {
      DividendArray[i+1] = Dividend[i];
    }
    cin >> Divisor;
    for(int i = 0; i < Divisor.size(); i++)
    {
      DivisorArray[i] = Divisor[i];
    }
    int LengthDenom = Divisor.size();
    int LengthNum = Dividend.size();
    CompNum = false;
    if(Dividend[0] == '1') //twos complement Dividend if negative
    {
      CompNum = true;
      TwosComp(DividendArray, DivisorArray, LengthNum, 1);
    }
    if(Divisor[0] == '1') //twos complement Divisor if negative
    {
      TwosComp(DividendArray, DivisorArray, LengthDenom, 0);
    }
    if(DivideOverflow(DividendArray, DivisorArray, LengthDenom, LengthNum)) //check for divide overflow
    {
      cout<<"Divide Overflow Occured"<<endl;
    }
    else //perform division
    {
      Restoring(DividendArray, DivisorArray, LengthDenom, LengthNum, CompNum);
      NonRestoring(DividendArray, DivisorArray, LengthDenom, LengthNum, CompNum);
    }
  }
  return 0;
}


//Description: Performs the restoring division method
//Pre: Dividend, Divisor, and their lengths have been defined.
//Post: Prints out the Quotient, Remainder, and the number of additions, subtractions, and iterations.
void Restoring(char Dividend[], char Divisor[], int LengthDenom, int LengthNum, bool CompNum)
{
  int n_sub = 0;
  int n_add = 0;
  int n_iter;
  char ExtraBit;
  n_iter = LengthDenom;
  for(int i = 0; i < n_iter; i++)
  {
    ExtraBit = Dividend[0]; //extra bit = first bit of dividend
    for(int j = 0; j < LengthNum; j++) //shift left
    {
      if(j != LengthNum-1)
        Dividend[j] = Dividend[j+1]; //position in dividend equals the next position
      else
        Dividend[j] = 'E'; //empty bit to be decided
    }
    ExtraBit = Sub(Dividend, Divisor, LengthNum, LengthDenom, ExtraBit); //subtract
    n_sub ++;
    if(ExtraBit == '1') //if the E bit is 1
    {
      ExtraBit = Add(Dividend, Divisor, LengthNum, LengthDenom, ExtraBit); //restore
      n_add +=1;
    }
  }
  if(CompNum) //twos complement Dividend
    TwosComp(Dividend, Divisor, LengthNum, 1);
  cout<<"Restoring: "<<endl;
  cout<<"Remainder: ";
  for(int i = 0; i < LengthDenom; i++) //print Remainder (the first half of the result)
  {
    cout<<Dividend[i];
  }
  cout<<endl;
  cout<<"Quotient: ";
  for(int i = 0; i < LengthDenom; i++) //print Quotient (the second half of the result)
  {
    cout<<Dividend[i+LengthDenom];
  }
  cout<<endl;
  cout<<"Num Additions: "<<n_add<<endl;
  cout<<"Num Subtractions: "<<n_sub<<endl;
  cout<<"Num Iterations: "<<n_iter<<endl;
  return;
}

//Description: Performs the nonrestoring division method
//Pre: Dividend, Divisor, and their lengths have been defined.
//Post: Prints out the Quotient, Remainder, and the number of additions, subtractions, and iterations.
void NonRestoring(char Dividend[], char Divisor[], int LengthDenom, int LengthNum, bool CompNum)
{
  int n_sub = 0;
  int n_add = 0;
  int n_iter;
  char ExtraBit;
  n_iter = LengthDenom;
  for(int i = 0; i < n_iter; i++)
  {
    ExtraBit = Dividend[0]; //the extra bit = the frist dividend bit
    for(int j = 0; j < LengthNum; j++) //shift left
    {
      if(j != LengthNum-1)
        Dividend[j] = Dividend[j+1]; //each position of the dividend = the next position
      else
        Dividend[j] = 'E'; //empty bit to be decided
    }
    if((i == 0)  || (ExtraBit == '0')) //if the first time through or the E bit is 0
    {
      ExtraBit = Sub(Dividend, Divisor, LengthNum, LengthDenom, ExtraBit);
      n_sub++;
    }
    else if(ExtraBit == '1') //if the E bit is 1
    {
      ExtraBit = Add(Dividend, Divisor, LengthNum, LengthDenom, ExtraBit);
      n_add++;
    }
  }
  if(CompNum) //twos complement dividend
    TwosComp(Dividend, Divisor, LengthNum, 1);
  cout<<"NonRestoring: "<<endl;
  cout<<"Remainder: ";
  for(int i = 0; i < LengthDenom; i++) //print out remainder
  {
    cout<<Dividend[i];
  }
  cout<<endl;
  cout<<"Quotient: ";
  for(int i = 0; i < LengthDenom; i++) //print out quotient
  {
    cout<<Dividend[i+LengthDenom];
  }
  cout<<endl;
  cout<<"Num Additions: "<<n_add<<endl;
  cout<<"Num Subtractions: "<<n_sub<<endl;
  cout<<"Num Iterations: "<<n_iter<<endl;
  return;
}

//Description: Checks for the presence of Divide Overflow.
//Pre: Dividend, Divisor, and Lengths of numerator and denominator  must be defined.
//Post: Will return if the division will result in overflow or not.
bool DivideOverflow(char Dividend[], char Divisor[], int LengthDenom, int LengthNum)
{
  bool Overflow = false;
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
void TwosComp(char Dividend[], char Divisor[], int Length, int index)
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
  }
  return;
}

//Description: Performs Subtraction on the Dividend and Divisor
//Pre: Dividend. Divisor. and their lengths must be defined
//Post: returns the extra bit adn updates the dividend
char Sub(char Dividend[], char Divisor[], int LengthNum, int LengthDenom, int Ebit)
{
  bool carry = false;
  char extra;
  TwosComp(Dividend, Divisor, LengthDenom, 0); //twos complement divisor
  for(int i = LengthDenom-1; i >= 0; i--)
  {
    if((Divisor[i] == '1') && (Dividend[i] == '1')) //if 1+1
    {
      if(carry) //if 1+1+1
        Dividend[i] = '1';
      else
        Dividend[i] = '0';
      carry = true;
    }
    else if((Divisor[i] == '1') && (Dividend[i] == '0')) //if 0+1
    {
      if(carry) //if 0+1+1
        carry = true;
      else
        Dividend[i] = '1';
    }
    else if((Divisor[i] == '0') && (Dividend[i] == '1')) //if 1+0
    {
      if(carry) //if 1+0+1
      {
        carry = true;
        Dividend[i] = '0';
      }
    }
    else if((Divisor[i]  == '0') && (Dividend[i] == '0')) //if 0+0
    {
      if(carry) //if 0+0+1
      {
        carry = false;
        Dividend[i] = '1';
      }
    }
  }
  if(carry) //if carry bit is 1
  {
    if(Ebit == 1) //if E bit was 1 before carry
    {
      Dividend[LengthNum-1] = '1';
      extra = '0';
    }
    else //if E bit was 0 before carry
    {
      Dividend[LengthNum-1] = '0';
      extra = '1';
    }
  }
  else //if carry bit is 0
  {
    if(Ebit == 1) //if E bit was 1 before
    {
      Dividend[LengthNum-1] = '0';
      extra = '1';
    }
    else //if E bit was 0 before
    {
      Dividend[LengthNum-1] = '1';
      extra = '0';
    }
  }
  TwosComp(Dividend, Divisor, LengthDenom, 0); //twos complement divisor, bring it back to original
  return extra;
}

//Description: Performs Addition on the Dividend and Divisor
//Pre: Dividend, Divisor, and their lengths must be defined
//Post: return updated dividend and extra bit
char Add(char Dividend[], char Divisor[], int LengthNum, int LengthDenom, int Ebit)
{
  bool carry = false;
  char extra;
  for(int i = LengthDenom-1; i >= 0; i--)
  {
    if((Divisor[i] == '1') && (Dividend[i] == '1')) //if 1+1
    {
      if(carry) //if 1+1+1
        Dividend[i] = '1';
      else
        Dividend[i] = '0';
      carry = true;
    }
    else if((Divisor[i] == '1') && (Dividend[i] == '0')) //if 0+1
    {
      if(carry) //if 0+1+1
        carry = true;
      else
        Dividend[i] = '1';
    }
    else if((Divisor[i] == '0') && (Dividend[i] == '1')) //if 1+0
    {
      if(carry) //if 1+0+1
      {
        carry = true;
        Dividend[i] = '0';
      }
    }
    else if((Divisor[i]  == '0') && (Dividend[i] == '0')) //if 0+0
    {
      if(carry) //if 0+0+1
      {
        carry = false;
        Dividend[i] = '1';
      }
    }
  }
  if(carry) //if carry bit is 1
  {
    if(Ebit == 1) //if E bit was 1 before carry
    {
      Dividend[LengthNum-1] = '1';
      extra = '0';
    }
    else //if E bit was 0 before carry
    {
      Dividend[LengthNum-1] = '0';
      extra = '1';
    }
  }
  else //if carry bit is 0
  {
    if(Ebit == 1) //if E bit was 1 before
    {
      Dividend[LengthNum-1] = '0';
      extra = '1';
    }
    else //if E bit was 0 before
    {
      Dividend[LengthNum-1] = '1';
      extra = '0';
    }
  }
  return extra;
}

