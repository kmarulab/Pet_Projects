#include <iostream>
using std::cout;using std::cin;using std::endl;

void DisplayBoard(){
  //prints the board with positions to user
    char row_one[6]= {'1','|','2','|','3','\0'};
    char row_two[6]= {'4','|','5','|','6','\0'};
    char row_thr[6]= {'7','|','8','|','9','\0'};
    cout<<row_one<<endl;
    cout<<row_two<<endl;
    cout<<row_thr<<endl;
}
void Placement(char row_one[6],char row_two[6],char row_thr[6],int move,char letter){
  //places player choice in correct position on the board
    switch(move){
        case 1:row_one[0]=letter;break;
        case 2:row_one[2]=letter;break;
        case 3:row_one[4]=letter;break;
        case 4:row_two[0]=letter;break;
        case 5:row_two[2]=letter;break;
        case 6:row_two[4]=letter;break;
        case 7:row_thr[0]=letter;break;
        case 8:row_thr[2]=letter;break;
        case 9:row_thr[4]=letter;break;
    }
    cout<<row_one<<endl;
    cout<<row_two<<endl;
    cout<<row_thr<<endl;
}
int playerOneMoves(){
  //takes input from player one on desired position to play
    int player1;
    std::cout<<"Player One Insert position where you'd like to play: "<<endl;
    cin>>player1;
    return player1;
}
int playerTwoMoves(){
  //takes input from player two on desired position to play
    int player2;
    cout<<"Player Two Insert position where you'd like to play: "<<endl;
    cin>>player2;
    return player2;
}
void checkWinner(char row1[6],char row2[6],char row3[6],int x){
  //checks to see which player has won
   //starts with rows, then columns , then diagonals
    int stat;
    if( row1[0]==row1[2] && row1[2]==row1[4]||
        row2[0]==row2[2] && row2[2]==row2[4]||
        row3[0]==row3[2] && row3[2]==row3[4]||
        row1[0]==row2[0] && row2[0]==row3[0]||
        row1[2]==row2[2] && row2[2]==row3[2]||
        row1[4]==row2[4] && row2[4]==row3[4]||
        row1[0]==row2[2] && row2[2]==row3[4]||
        row3[0]==row2[2] && row2[2]==row1[4]
    ){
        if((x%2)==1){
            cout<<"Player 1 Wins"<<endl;
        }
        else{
            cout<<"Player 2 Wins"<<endl;
        }
    }else if(x==9){
            cout<<"Game Ends as a Draw"<<endl;
    }
}
int main(){
    //main board
    char row_one[6]= {'1','|','2','|','3','\0'};
    char row_two[6]= {'4','|','5','|','6','\0'};
    char row_thr[6]= {'7','|','8','|','9','\0'};

    int GameOn;
    cout<<"Player One is X by Default and Player Two is O"<<endl;
    DisplayBoard();
    cout<<"Enter a non negative number to end the game: "<<endl;
    int x=1;
    cin>>GameOn;
    while(GameOn>0 && x<10){
        int status;
        if((x%2)==1){
            Placement(row_one,row_two, row_thr,playerOneMoves(),'X');
            checkWinner(row_one,row_two,row_thr,x);
            
        }
        else {
            Placement(row_one,row_two, row_thr,playerTwoMoves(),'0');
            checkWinner(row_one,row_two,row_thr,x);
        }
        x++;
        }
}

