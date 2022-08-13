#define PLAYER1 'x'
#define PLAYER2 'o'
#include <iostream>
#include <windows.h>
#include <map>
#include <cmath>
#include <vector>
#include <limits>
#include <ctime>
using namespace std;

inline auto available_squares(char board[])
{
  vector <int> positions;
  for(int i = 0; i < 9; i++)
  {
    if(board[i] == '-')
    {
      positions.push_back(i);
    }
    else
    {

    }
  }
  return (positions);
}

bool check_win(char board[], char player)
{
  if(board[0] == board[1] && board[1] == board[2] && board[0] == player)
  {
    return true;
  }
  else if(board[3] == board[4] && board[4] == board[5] && board[3] == player)
  {
    return true;
  }
  else if(board[6] == board[7] && board[7] == board[8] && board[6] == player)
  {
    return true;
  }
  else if(board[0] == board[3] && board[3] == board[6] && board[0] == player)
  {
    return true;
  }
  else if(board[1] == board[4] && board[4] == board[7] && board[1] == player)
  {
    return true;
  }
  else if(board[2] == board[5] && board[5] == board[8] && board[2] == player)
  {
    return true;
  }
  else if(board[0] == board[4] && board[4] == board[8] && board[0] == player)
  {
    return true;
  }
  else if(board[2] == board[4] && board[4] == board[6] && board[2] == player)
  {
    return true;
  }
  else
  {
    return false;
  }
}

int minimax(char board[], char player)
{
  if(check_win(board,PLAYER1) == true)
  {
    return 1;
  }
  if(check_win(board,PLAYER2) == true)
  {
    return -1;
  }
  if(available_squares(board).empty() == true)
  {
    return 0;
  }

  map <int,double> Alltestplaysinfo;
  int result = 0;
  for(const int& i : available_squares(board))
  {
    int currentTestplayinfo = board[i];
    board[i] = player;

    if(player == PLAYER1)
    {
      result = minimax(board,PLAYER2);
    }
    else if(player == PLAYER2)
    {
      result = minimax(board,PLAYER1);
    }
    board[i] = currentTestplayinfo;
    Alltestplaysinfo.insert(make_pair(i,result));

  }

  double best_play = 0;
  if(player == PLAYER2)
  {
    double best_score = -numeric_limits<double>::infinity();
    map<int,double>::iterator itr;
    for(const int& i : available_squares(board))
    {
      for(itr = Alltestplaysinfo.begin(); itr != Alltestplaysinfo.end(); ++itr)
      {
        if(itr->second > best_score)
        {
          best_score = itr->second;
          best_play = itr->first;
        }
      }
    }
  }
  if(player == PLAYER1)
  {
    double best_score = numeric_limits<double>::infinity();
    map<int,double>::iterator itr;
    for(const int& i : available_squares(board))
    {
      for(itr = Alltestplaysinfo.begin(); itr != Alltestplaysinfo.end(); ++itr)
      {
        if(itr->second < best_score)
        {
          best_score = itr->second;
          best_play = itr->first;
        }
      }
    }
  }

  return best_play;
}

int rand(char player, char board[])
{
  int a = rand() % 9;
  board[a] = player;
  return a;
}

int Ai(char board[])
{
  cout << "AI is thinking!..." << endl;
  Sleep(1000);
  for(const int& i : available_squares(board))
  {
    char current = board[i];
    board[i] = PLAYER1;
    if(check_win(board,PLAYER1) == true)
    {
      board[i] = PLAYER1;
      return 0;
    }
    else
    {
      board[i] = current;
    }
  }
  for(const int& j : available_squares(board))
  {
    char current = board[j];
    board[j] = PLAYER2;
    if(check_win(board,PLAYER2) == true)
    {
      board[j] = PLAYER1;
      break;
    }
    else
    {
      board[j] = current;
    }
    int n = available_squares(board).size();

    if(j == available_squares(board)[n-1])
    {
      board[minimax(board,PLAYER1)] = PLAYER1;
    }
  }
  return 0;
}

int play_human(char board[])
{
    int b;
    cout << "Enter a number between 0 and 8: " << endl;
    cin >> b;
    for(const int& i : available_squares(board))
    {
      if(i == b)
      {
        board[i] = PLAYER2;
        break;
      }
      int n = available_squares(board).size();
      if(i == available_squares(board)[n-1] && i != b)
      {
        if(b > 8)
        {
          cerr << "Enter a valid integer!" << endl;
        }
        else
        {
          cerr << "Position has been occupied!" << endl;
        }
        play_human(board);
      }
    }
  return 0;
}

int outcome(char board[])
{
  if(check_win(board,PLAYER1) == true)
  {
    return 1;
  }
  if(check_win(board,PLAYER2) == true)
  {
    return -1;
  }
  if(available_squares(board).empty() == true)
  {
    return 0;
  }
  return 2;
}

int Play(char board[])
{
  for(int i = 0; i < 9; i++)
  {
    string line = "-------------------------------------";
    if(i == 0)
    {
      Ai(board);
    }
    if(i == 1)
    {
      play_human(board);
    }
    if(i == 2)
    {
      Ai(board);
    }
    if(i == 3)
    {
      play_human(board);
    }
    if(i == 4)
    {
      Ai(board);
    }
    if(i == 5)
    {
      play_human(board);
    }
    if(i == 6)
    {
      Ai(board);
    }
    if(i == 7)
    {
      play_human(board);
    }
    if(i == 8)
    {
      Ai(board);
    }
    cout << line << endl;
    cout << board[0] << "|" << board[1] << "|" << board[2]  << "|" << endl;
    cout << board[3] << "|" << board[4] << "|" << board[5]  << "|" << endl;
    cout << board[6] << "|" << board[7] << "|" << board[8]  << "|" << endl;
    cout << line << endl;
    if(outcome(board) == 1)
    {
       printf("AI wins!");
       break;
    }
    else if(outcome(board) == -1)
    {
      printf("Human wins!");
      break;
    }
    else if(outcome(board) == 0)
    {
      printf("Tie!");
      break;
    }
    else{}
  }
  return 0;
}

int main()
{
  srand(time(NULL));
  char board[9] = {'-','-','-',
                   '-','-','-',
                   '-','-','-'};
  cout << board[0] << "|" << board[1] << "|" << board[2]  << "|" << endl;
  cout << board[3] << "|" << board[4] << "|" << board[5]  << "|" << endl;
  cout << board[6] << "|" << board[7] << "|" << board[8]  << "|" << endl;
  cout << "-------------------------------------" << endl;
  Play(board);
}
