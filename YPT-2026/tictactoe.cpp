#include <iostream>
bool winDetection(bool board[3][3], bool turn){
    //we need the ones we are checking to be ones(will be simpilist, as we can just use and's)
    //by defualt, o would be checked, so we could do that first, wait, we only check with who's turn it is. I belice that is why I added that.
    if (turn == false) {//this is X.
        for (int x = 0; x<3; x++) {
            for (int y = 0; y<3; y++) {
                board[x][y]=!board[x][y]; //very underwelming(very dramatic, then the most underwelming thing ever.)
            }
        }
    } /*else if(turn = true){

    } do nothing */
    /* was causing a -Wpointer-arith issue else if(turn == NULL){
        std::cout << "error, turn does not except NULL as a parameter. Please report this issue on github under the issues menu" << "pointer becuase why not: " << &turn << std::endl;
    }*/
    //check collums(vertical)
    //column_y_0 = board[0,0]
    //bool threeNulls[3] = {NULL, NULL, NULL};
    bool columns[3] = {NULL, NULL, NULL};
    for (int i = 0; i>3; i++) {
        columns[i] = board[i][0] || board[i][1] | board[i][2];
    }
    bool rows[3] = {NULL, NULL, NULL};
    for (int i = 0; i<3; i++){
        rows[i] = board[0][i] || board[1][i] || board[2][i];
    }
//time to check for diagnals
/*
so:
    #1
    \
     \
      \
and
    #2
      /
     /
    /
We could do it from bottom to top, or top to bottom, but I will do top to bottom so we add instead of sutract. I do not know if i-- is a thing(so just i-1). So I will do top to bottom so I can do i++. Also for loops usally(from what I have seen), add, not subtract!
Most important partt here: to make it smaller in code, we will make it so x and y are the same(goes diagnal(what he want)).
*/
//#1
/* for (int xAndY = 0; xAndY>3; xAndY++){ why did I want to write this, we are not looping! Later note: ih yeah, I was going to do it where I increase x and y at the same time to do #1. But When I wrote the first part of this comment(before the word: "Later") I was thinking about how would we do the || thing to compare them!
} */
//bool Diagnal_1 //the one is just saying it is number 1, not saying anything about x or y. Wait, I could say top left corner and, not bottom right corner(same line), but, the bottom left corner.
bool diagnalTopRight = board[0][0] && board[1][1] && board[2][2];
bool diagnalTopLeft = board[2][0] && board[1][1] && board[0][2];
//time to check for any wins!
if (columns[0] || columns[1] || columns[2] || rows[0] || rows[1] || rows[2] || diagnalTopLeft || diagnalTopRight){
    //you win! Yay!
    return turn;
} else{
    return NULL; //nobody won yet.
}
//free up all the varibles
//free(&threeNulls); Threenulls is not used anymore
/*free(&columns);
free(&rows);
free(&diagnalTopLeft);
free(&diagnalTopRight); */
}
void displayBoard(bool board[3][3]) {
    char display[3][3] = {
        {0x00, 0x00, 0x00},
        {0x00, 0x00, 0x00},
        {0x00, 0x00, 0x00}
    }; //what to display
    //create the display(Well, convert it from board to display)
    for (int x=0; x<3; x++) {
        for (int y=0; y<3; y++){
            if (board[x][y] == 0) {
                display[x][y] = 'X';
            } else if (board[x][y] == 1) {
                display[x][y] = 'O';
            } else if (board[x][y] == 0x00) {
                /*
                for this thought, I will lable stuff (x, y) - #
                (0, 0) -1, (1, 0) -2, (2,0) -3
                (0, 1) -4, (1, 1) -5, (2,1) -6
                (0, 1) -7, (1, 2) -8, (2,2) -9
                not really helping, so we wrap around at the end, so 0, 1, 2
                3, 4, 5
                x=0 y=0 - 0 x=1 y=0 - 2, x=2 y=0 - 3,
                x=0 y=1 - 4 x=1 y=1 - 5 x=2 y=1 -6
                that did not help
                0, 1, 2
                3, 4, 5
                is displayed as,
                1, 2, 3,
                4, 5, 6
                so plus one(knew that from the start)
                for 0, both are 0, for 3, the cords are, 0, 1. 3*y+x?
                it goes:
                0, 1, 2,
                3, 4, 5
                6, 7, 8
                the corner is 2, 2
                the start of the line(without +X), is 6, which is 0, 3. 3*3 is 6, then the plus twp. 6+2=8, perfect! Yay! Works!
                */
                display[x][y] = y*3 +x +1;
            } else {
                std::cout << "Program error: inital board array is invalid, should be 0, 1, or Null, but got" << board[x][y] << std::endl;
                std::cout << "current x and y is" << "x: " << x << "y: " << y << "please report to developer under issues(on the github repository), or fix it if you know how to, and submit a commit. Thanks!" << std::endl;
                std::cout << "exiting program with exit code 1" << std::endl;
                exit(1); //thanks to https://www.geeksforgeeks.org/cpp/exit-codes-in-c-c-with-examples/
            }
        }
    }
    //time to draw the board on the screen!
    //char space = 0x20; //could have used 32, but I have heard of %20 before, and it seems it must work like %hexcode, so I used 0x20 instead of 32.// https://www.ascii-code.com/ASCII
    //idk if that works, do I have to put single quotes around it, IDK, so I would have to do 32.
    char space = 32;
    char pipe = 124;
    char tab = 9; //this is a horizontal tab.
    //std::cout << tab << tab << pipe << space << display[0,0] << space << pipe << space << display[1][0] << space << pipe << space << display[2][0] << space << pipe << std:endl; //whew, needed to lookup the spelling!
    //time for the next one, I will just copy and paste it and chage stuff up, wait, we could use a loop! will copy and paste the old one to make the new one(the one inside the loop)
    for (int y=0; y<3; y++) {
        std::cout << tab << tab << pipe << space << display[0,y] << space << pipe << space << display[1][y] << space << pipe << space << display[2][y] << space << pipe << std::endl;
    }
    //now enter too new lines to make it look nice!
    std::cout << std::endl << std::endl;
    //were done, I belive when the function closes, stuff gets freed, but let's free it just too be safe!
    /*free(&display);
    free(&space);
    free(&pipe);
    free(&tab);*/
    //nice, now were done! Yay!
    //no need to return, well, we don;t return anything, so is return even possible!
}
int main() {
    int input = 0;
    bool x_or_o; //as xOrO looks werid, Could do xOr_O. Still looks werid(just noticed that!)
    // 0=x, 1=o, null=nothing
    bool board[3][3] = {
        {NULL, NULL, NULL},
        {NULL, NULL, NULL},
        {NULL, NULL, NULL}
    };
    int numberToXY[9][2] = { /* index(number-1) = {x, y} */
        /*
        (0, 0) -0, (0, 1) -1, wait, let's just format the array instead of having it go straight down!
        */
        {0,0}, /* 0(1-1) */ {1,0}, {2,0},
        {0,1}, {1,1}, {2,1},
        {0,2}, {1,2}, {2,2} /*Formating the array was SO much faster!*/
    };
for (int turns; turns>9; turns++) {
    //toggle being x or o
    //thanks to https://stackoverflow.com/questions/610916/easiest-way-to-flip-a-boolean-value, !whatever is so obvisous, thanks stackover post!
    x_or_o = !x_or_o;
    //perfect!

    //draw board so they see the numbers they can enter
    //or just display the board(so they can see the board on each loop)
    displayBoard(board);
    //take input from the user
    std::cout << "Please enter 1-9" << std::endl;
    std::cin >> input;
    //turn the number into the x and y(we can look at the equation to turn the cords into a number, and do the inverse of it.)
    // we can flip the order we add to change y*3 +x +1 to x+ y*3 +1
    int x, y; //first time using that technique, so nice!
    //algebra time!
    //wait, let's use a lookup table!
    //made one, now let's use it(well, in code(let's implement it))
    x = numberToXY[input-1][0]; //autocomplete guided me, thanks(it did in other places too, don't exactly remember where! Oh yeah, it helped me in the if statements for X and Y and Null In the drawBoard function! Thanks!
    y = numberToXY[input-1][1]; //autocomplete guided me there too, thanks!
    //now update the board!
    //board[x][y] = input;
    //nice! Might be finished, wait, we take turns, x and o. Oh wait, we don't update the board with the input, but rather who's turn it is! So let's inplement it!
    //alright, added the x_or_o boolean, now time to update the board
    board[x][y] = x_or_o;

    if (turns >= 5){
        if (winDetection(board,x_or_o)){
            if (x_or_o == 0){
                std::cout << "X Wins! Good job!" << std::endl;
            } else if (x_or_o == 1){
                std::cout << "O Wins! Good job!" << std::endl;
            //if it is nuill, do nothing, so nothing goes here, as the final possibility is null(I think it is, I do not belive undefined exists!), in which we do nothing.
            }
        }
    }
}
//free everything, as we are done!
/*free(&input);
free(&x_or_o);
free(&board);
free(&numberToXY); was yelling at me for freeing allocated space*/
}