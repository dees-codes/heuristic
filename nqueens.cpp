/**
 * nqueens: A program to place n queens in n*n chessboard without
 *          checking each other.
 * @author Deepson Shrestha
 * @version 5 December 2019
 */

#include <cassert>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <vector>
#include <bits/stdc++.h>
#include <stdio.h>
#include <algorithm>
using namespace std;

void hr(unsigned cols);
vector<unsigned> heuristic(vector<unsigned> permutation, unsigned n);
unsigned collisions(vector<unsigned> vec, unsigned size);
void printBoard(const vector<unsigned> vec, unsigned n);

/**
 * set up the board and start the heuristic algorithm
 */
int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    cout << "Usage: " << argv[0] << " n" << endl;
    cout << "       where n is the number of queens to place" << endl;
    cout << "       on an n x n chessboard, with 4 <= n < 26" << endl;
    exit(2);
  }

  unsigned n = static_cast<unsigned>(stoul(argv[1]));
  assert(n > 3 && n < 26);

  // Declare a vector to hold the nqueens permutation
  vector<unsigned> myvector;

  // set the values 1 to n in the vector
  for (unsigned i = 1; i <= n; ++i)
  {
    myvector.push_back(i);
  }

  // run the heuristic algorithm and assign the returned vector to
  // printable
  vector<unsigned> printable = heuristic(myvector, n);

  // print the board in the terminal
  printBoard(printable, n);
  return 0;
}

/* Function to heuristically determine the nqueens permutation and print the
 * number of swaps, comparisons and resets.
 * @param permutation the ordered vector of size n that is to be solved
 * @param vsize the size of the vector i.e. n
 * return the solved vector i.e vector of size n with consecutive elements 
 *        describing the position of n queens along the consecutive vertical
 *        axes of chess board
 */
vector<unsigned> heuristic(const vector<unsigned> permutation, unsigned vsize)
{
  // seeding the random built in generator
  srand(static_cast<unsigned>(time(nullptr)));

  // shallow copying the input vector
  vector<unsigned> p = permutation;

  unsigned print_swaps = 0;
  unsigned print_comparisons = 0;
  unsigned sets = 0;
  
  do
  {
    //using the random built in generator
    random_shuffle (p.begin(), p.end()); 
    sets++;                       //the number of times the vector is shuffled
    unsigned swaps = 0;
    do
    {
      swaps = 0;
      for(unsigned i = 0; i < vsize; i++)
      {
        for(unsigned j = 0; j < vsize; j++)
        {
          //Swapping and comparing the collisions before and after swapping
          vector<unsigned> dummyvector = p;
          swap(dummyvector[i], dummyvector[j]);
          if (collisions(dummyvector, vsize) < collisions(p, vsize))
          {
            // For each call of collision function, n*(n-1)/2 comparisons is
            // done.

            // Comparisions during collision(dummyvector, size)
            print_comparisons += (vsize * (vsize - 1) / 2);

            // Comparisions during collision(p, size)
            print_comparisons += (vsize * (vsize - 1) / 2);
            
            p = dummyvector;
            swaps++;
            print_swaps++;
          }
        }
      }
    } while (swaps > 0);
  } while (collisions(p, vsize) > 0);

  // The number of resets is one less than the total number of shuffling
  unsigned resets = sets - 1;
  
  cout << "Performed " << resets << " resets, " << print_swaps
       << " swaps, and " << print_comparisons << " comparisons" << endl;

  return p; //The final permutation without any queens checking the any other
}

/* The function to check the total number of collisions in nqueens permutation.
 * This collision counter is based on the fact that sum of the x co-ordinate and
 * y co-ordinate in the diagonal with negative slope in the board is same and the
 * difference between x co-ordinate and y co-ordinate in the diagonal with positive
 * slope in the board is same.
 * @param v the vector that is to be checked
 * @vecSize the size of the vector
 * return the number of collisions: collisions occur when queens are in the
 *        same diagonal
 */
unsigned collisions(vector<unsigned> v, unsigned vecSize)
{
  unsigned collisions = 0;
  unsigned n = vecSize;

  // Create hash tables for storing information for diagonals with negative
  // slope and positive slope
  unordered_map<unsigned, unsigned> mpNegDiagonal;
  unordered_map<unsigned, unsigned> mpPosDiagonal;

  // loop through the vector and add the vector values to their position as
  // well as subtract the vector values from their positions. Then assign
  // the vector values with the same sum to the same position in positive diagonal
  // hash table whereas the vector values with the same difference to the same
  // position in the negative diagonal hash table. It is actually the count of
  // total number of vector values with same sum or same difference assigned to
  // respective keys in the hash table where the value of the key is the value
  // of the sum or the difference. Hash table has been used for better algorithmic
  // efficiency.
  for(unsigned i = 0; i < n; i++)
  {
    mpNegDiagonal[v.at(i) + i]++;
    mpPosDiagonal[v.at(i) - i]++;
  }

  // Loop through the diagonal hash tables  to count total number of collisions
  
  for (auto x : mpNegDiagonal)
  {
    collisions += (x.second * (x.second - 1) / 2);
  }

  for (auto x : mpPosDiagonal)
  {
    collisions += (x.second * (x.second - 1) / 2);
  }
  
  return collisions;
}  
 
/**
 * a simple procedure to output an ASCII art horizontal line with plus
 * signs where columns will intersect
 */
void hr(unsigned cols)
{
  cout << "    +";
  for (unsigned col = 0; col < cols; col++)
  {
    cout << "---+";
  }
  cout << endl;
}

/**
 * a simple procedure to print the board in the terminal
 * @param vec the final permutation vector to be printed
 * @param n the size of the vector to be printed
 */
void printBoard(const vector<unsigned> vec, unsigned n)
{
  hr(static_cast<unsigned>(n));
  for (unsigned row = 0; row < n; row++)
  {
    cout << ' ' << setw(2) << row << " |";
    for (unsigned col = 0; col < n; col++)
    {
      if (vec.at(col) == n - row)
      {
        cout << " X |";
      }
      else
      {
        cout << "   |";
      }
    }
    cout << endl;
    hr(static_cast<unsigned>(n));
  }

  cout << "     ";
  for (unsigned col = 0; col < n; col++)
  {
    cout << ' ' << static_cast<char>('a' + col) << "  ";
  }
  cout << endl;
}




