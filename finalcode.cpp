
#include <iostream>
#include <graphics.h>
#include <ctime>
using namespace std;
string player1, player2;
enum Piece
{
    King,
    Queen,
    Bishop,
    Knight,
    Rook,
    Pawn,
    Empty
};
enum Color
{
    Black,
    White,
    None
};
Color whowins = None;
class box
{
    int x;
    int y;
    Piece piece;        
    Color color;

public:
    box()
    {
        x = 0;
        y = 0;
        piece = Empty;
        color = None;
    }

    Piece getpiece()
    {
        return this->piece;
    }
    Color getcolor()
    {
        return this->color;
    }
    int getx()
    {
        return x;
    }
    int gety()
    {
        return y;
    }
    void setSpace(box *space)
    {
        color = space->getcolor();
        piece = space->getpiece();
    }
    void set_piece_and_color(Piece p, Color c)
    {
        this->color = c;
        this->piece = p;
    }
    void set_x_y(int a, int b)
    {
        this->x = a;
        this->y = b;
    }
    void setempty()
    {
        color = None;
        piece = Empty;
    }
};
class game
{
    box board[8][8];
    Color turn; //to tell which players turn is it.
public:
    void display_board(); //the function which we gave in flowchart 1

    bool moveBishop(box *currBishop, box *destSpace);
    //takes two argument of box type , "currBishop" is current position of bishop and "destSpace" is position where we want to insert bishop
    bool moveQueen(box *curQueen, box *finalQueen);
    void setboard();
    bool moveKing(box *, box *);
    bool moveRook(box *, box *);
    bool moveKnight(box *, box *);
    bool movePawn(box *currPawn, box *destSpace);
    bool makemove(int x1, int y1, int x2, int y2, Color);
    void clear(int x1, int y1, int x2, int y2);
};
void game::setboard()
{
    board[7][0].set_piece_and_color(Rook, White);
    board[7][1].set_piece_and_color(Knight, White);
    board[7][2].set_piece_and_color(Bishop, White);
    board[7][3].set_piece_and_color(Queen, White);
    board[7][4].set_piece_and_color(King, White);
    board[7][5].set_piece_and_color(Bishop, White);
    board[7][7].set_piece_and_color(Rook, White);
    board[7][6].set_piece_and_color(Knight, White);
    for (int i = 0; i <= 7; i++)
        board[6][i].set_piece_and_color(Pawn, White);
    board[0][0].set_piece_and_color(Rook, Black);
    board[0][1].set_piece_and_color(Knight, Black);
    board[0][2].set_piece_and_color(Bishop, Black);
    board[0][3].set_piece_and_color(Queen, Black);
    board[0][4].set_piece_and_color(King, Black);
    board[0][5].set_piece_and_color(Bishop, Black);
    board[0][7].set_piece_and_color(Rook, Black);
    board[0][6].set_piece_and_color(Knight, Black);
    for (int i = 0; i <= 7; i++)
        board[1][i].set_piece_and_color(Pawn, Black);

    for (int i = 2; i <= 5; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            board[i][j].set_piece_and_color(Empty, None);
        }
    }
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            board[i][j].set_x_y(i, j);
        }
    }
    whowins = None;
}
bool game::moveKing(box *thisKing, box *destSpace)
{
    int currKingX = thisKing->getx();   //take x coordinate of current king position
    int currKingY = thisKing->gety();   //take y coordinate of current king position
    int destSpaceX = destSpace->getx(); //take x coordinate of destination king position
    int destSpaceY = destSpace->gety(); //take y coordinate of destination king position
    bool valid = true;
    if (currKingX == destSpaceX && currKingY == destSpaceY)
    {
        return false;
    }
    if (abs(destSpace->getx() - thisKing->getx()) == 1)
    {
        if (abs(destSpace->gety() - thisKing->gety()) == 1)
        {
            destSpace->setSpace(thisKing);
            thisKing->setempty();
            return true;
        }
        else if (abs(destSpace->gety() - thisKing->gety()) == 0)
        {
            destSpace->setSpace(thisKing);
            thisKing->setempty();
            return true;
        }
        else
            return false;
    }
    else if (abs(destSpace->gety() - thisKing->gety()) == 1)
    {
        destSpace->setSpace(thisKing);
        thisKing->setempty();
        return true;
    }

    else
        return false;
}

bool game::moveBishop(box *currBishop, box *destSpace)
{
    int currBishopX = currBishop->getx(); //take x coordinate of current bishop position
    int currBishopY = currBishop->gety(); //take y coordinate of current bishop position
    int destSpaceX = destSpace->getx();   //take x coordinate of destination bishop position
    int destSpaceY = destSpace->gety();   //take y coordinate of destination bishop position
    bool valid = true;

    if (abs(currBishopX - destSpaceX) == abs(currBishopY - destSpaceY)) //condition for diagnol movement of bishop
    {
        int IncreaseX = (destSpaceX - currBishopX) / (abs(destSpaceX - currBishopX)); //increment x coordinte of cuurent bishop position
        int IncreaseY = (destSpaceY - currBishopY) / (abs(destSpaceY - currBishopY)); //increment y coordinte of cuurent bishop position

        for (int i = 1; i < abs(currBishopX - destSpaceX); i++) //loop to check every block between current to destination
        {

            if (board[currBishopX + IncreaseX * i][currBishopY + IncreaseY * i].getcolor() != None) // condition to check every block between current to destination is empty or not
                return false;
        }
    }
    else
        return false;

    if (valid == true) //if bishop can move to destination
    {
        destSpace->setSpace(currBishop); //set bishop to destination
        currBishop->setempty();          // and set empty to the current position
        return true;
    }
    else
    {
        return false;
    }
}
bool game::moveQueen(box *curQueen, box *finalQueen)
{
    int curQueenX = curQueen->getx();     //intial position x
    int curQueenY = curQueen->gety();     //initial position y
    int finalQueenX = finalQueen->getx(); // final position x
    int finalQueenY = finalQueen->gety(); //final position y
    if ((curQueenX == finalQueenX) && (curQueenY == finalQueenY))
    {

        return false; // for same position input
    }
    if (curQueenX == finalQueenX)
    {
        if (finalQueenY > curQueenY)
        {

            for (int i = curQueenY + 1; i != finalQueenY; i++)
            {
                if (board[curQueenX][i].getcolor() != None)
                {
                    //for checking the path is clear
                    return false;
                }
            }
        }
        else
        {

            for (int i = curQueenY - 1; i != finalQueenY; i--)
            {
                cout << board[curQueenX][i].getcolor();
                cout << endl;
                if (board[curQueenX][i].getcolor() != None)
                {
                    //for checking the path is clear
                    return false;
                }
            }
        }
        //else return false;
    }
    else if (curQueenY == finalQueenY)
    {
        if (finalQueenX > curQueenX)
        {

            for (int i = curQueenX + 1; i != finalQueenX; i++)
            {
                if (board[i][curQueenY].getcolor() != None)
                { //for checking the path is clear
                    return false;
                }
            }
        }
        else
        {

            for (int i = curQueenX - 1; i != finalQueenX; i--)
            {
                if (board[i][curQueenY].getcolor() != None)
                { //for checking the path is clear
                    return false;
                }
            }
        }
        //else return false;
    }
    else if (abs(curQueenX - finalQueenX) == abs(curQueenY - finalQueenY))
    {
        int xIncrement = (finalQueenX - curQueenX) / (abs(curQueenX - finalQueenX));
        int yIncrement = (finalQueenY - curQueenY) / (abs(curQueenY - finalQueenY));
        for (int i = 1; i < abs(curQueenX - finalQueenX); i++)
        {

            if (board[curQueenX + xIncrement * i][curQueenY + yIncrement * i].getcolor() != None)
                return false;
        }
    }

    finalQueen->setSpace(curQueen);
    curQueen->setempty();
    return true;
}
bool game::movePawn(box *currPawn, box *destSpace)
{
    int currPawnX = currPawn->getx();   // take x coordinate of current pawn position
    int currPawnY = currPawn->gety();   // take y coordinate of current pawn position
    int destSpaceX = destSpace->getx(); // take x coordinate of destination pawn position
    int destSpaceY = destSpace->gety(); // take y coordinate of destination of pawn position
    bool invalid = false;

    // condition for pawn move  code
    if (currPawn->getcolor() == White) // considering the board color case( white )
    {

        if (currPawnX == destSpaceX + 1 && destSpaceY == currPawnY && destSpace->getcolor() == None)
        {
            destSpace->setSpace(currPawn);

            currPawn->setempty();
            return true;
        }
        else
        {
            if ((currPawnY - 1 == destSpaceY || currPawnY + 1 == destSpaceY) && currPawnX - 1 == destSpaceX && destSpace->getcolor() == Black)
            {
                destSpace->setSpace(currPawn);
                currPawn->setempty();
                return true;
            }
            else
                return false;
        }
    }
    else
    {
        if (currPawn->getcolor() == Black) // handling case in case pawn is at another color side(BLACK)
        {
            if (currPawnX + 1 == destSpaceX && destSpaceY == currPawnY && destSpace->getcolor() == None) //change
            {
                destSpace->setSpace(currPawn);
                currPawn->setempty();
                return true;
            }
            else
            {
                if ((currPawnY + 1 == destSpaceY || currPawnY - 1 == destSpaceY) && currPawnX + 1 == destSpaceX && destSpace->getcolor() == White)
                {
                    destSpace->setSpace(currPawn);
                    currPawn->setempty();
                    return true;
                }
                else
                    return false;
            }
        }
        else
            return false;
    }
}
bool game::moveRook(box *currook, box *finalrook)
{
    int currookX = currook->getx();     //intial position x
    int currookY = currook->gety();     //initial position y
    int finalrookX = finalrook->getx(); // final position x
    int finalrookY = finalrook->gety(); //final position y
    int yIncrement;
    int xIncrement;
    bool valid = true;
    if (abs(currookX == finalrookX) && abs(currookY == finalrookY))
    {
        return false;
    } // for same position input
    if (currookX != finalrookX || currookY != finalrookY)
    {
        if (currookX == finalrookX)
        {
            yIncrement = (finalrookY - currookY) / (abs(finalrookY - currookY));  //increment y coordinte of cuurent Rook
            for (int i = currookY + yIncrement; i != finalrookY; i += yIncrement) //loop to check  between current to destination
            {
                if (board[finalrookX][i].getcolor() != None) //for checking the path is clear
                    return false;
            }
        }
        else if (currookY == finalrookY)
        {
            xIncrement = (finalrookX - currookX) / (abs(finalrookX - currookX));  //increment x coordinte of cuurent Rook
            for (int i = currookX + xIncrement; i != finalrookX; i += xIncrement) //loop to check  between current to destination
            {
                if (board[i][finalrookY].getcolor() != None) //for checking the path is clear
                    return false;
            }
        }
        else
            return false;
    }
    if (valid == true) //if rook can move to destination
    {
        finalrook->setSpace(currook); //set rook to destination
        currook->setempty();          // and set empty to the current position
        return true;
    }
    else
    {
        return false;
    }
}
bool game::moveKnight(box *src, box *dest)
{

    int srcX = src->getx();
    int srcY = src->gety();
    int destX = dest->getx();
    int destY = dest->gety();

    if ((abs(srcX - destX) == 2 && abs(srcY - destY) == 1) || (abs(srcX - destX) == 1 && abs(srcY - destY) == 2))
    {
        dest->setSpace(src);
        src->setempty();
        return true;
    }
    else
    {
        return false;
    }
}
bool game::makemove(int x1, int y1, int x2, int y2, Color turn)
{

    if (x1 < 0 || y1 < 0 || y2 < 0 || x2 < 0 || x1 >= 8 || y1 >= 8 || x2 >= 8 || y2 >= 8)
        return false;

    box *src = &board[x1][y1];
    box *dest = &board[x2][y2];

    Piece destpiece = dest->getpiece();
    if (src->getpiece() == Empty)
        return false;

    if (src->getcolor() == dest->getcolor())
        return false;
    if (src->getcolor() != turn)
        return false;
    bool movee = false;
    switch (src->getpiece())
    {
    case King:
    {
        movee = moveKing(src, dest);
        break;
    }
    case Queen:
    {
        movee = moveQueen(src, dest);

        break;
    }

    case Bishop:
    {
        movee = moveBishop(src, dest);
        break;
    }

    case Knight:
    {
        movee = moveKnight(src, dest);

        break;
    }

    case Rook:
    {
        movee = moveRook(src, dest);
        break;
    }

    case Pawn:
    {
        movee = movePawn(src, dest);

        break;
    }
    }
    if (movee && (destpiece == King))
    {
        whowins = turn;
    }
    return movee;
}
void game::display_board()
{
    int gd = 0, gm;
    int i = 0, j, k = 0, l, n = 49;
    char c;
    system("cls");
    initgraph(&gd, &gm, (char *)" ");
    setcolor(WHITE);
    line(450, 0, 450, 450);
    line(400, 0, 400, 400);
    line(0, 0, 400, 0);
    line(0, 400, 400, 400);
    line(0, 450, 450, 450);
    line(0, 0, 0, 400);

    for (l = 10; l < 400; l = l + 50)
    {
        c = (char)n;
        settextstyle(8, 0, 4);
        outtextxy(405, l, &c);
        n++;
    }
    n = 49;
    for (l = 10; l < 400; l = l + 50)
    {
        c = (char)n;
        settextstyle(8, 0, 4);
        outtextxy(l, 405, &c);
        n++;
    }
    for (j = 0; j < 400; j = j + 50)
    {
        for (; i < 400; i = i + 100)
        {
            bar(i, k, 50 + i, 50 + j);
        }
        k = k + 50;
        i = k - i - j;
    }
    for (int i = 0; i < 8; i++)
    {
        settextstyle(8, 0, 4);
        if (i < 3)
            setcolor(3);
        else
            setcolor(4);
        for (int j = 0; j < 8; j++)
        {
            switch (board[i][j].getpiece())
            {
            case King:
            {
                if (i == 0)
                    outtextxy(5 + 50 * j, 5, (char *)"BK");
                else if (i == 7)
                    outtextxy(5 + 50 * j, 355, (char *)"WK");
                break;
            }
            case Queen:
            {
                if (i == 0)
                    outtextxy(5 + 50 * j, 5, (char *)"BQ");
                else if (i == 7)
                    outtextxy(5 + 50 * j, 355, (char *)"WQ");
                break;
            }
            case Bishop:
            {
                if (i == 0)
                    outtextxy(5 + 50 * j, 5, (char *)"BB");
                else if (i == 7)
                    outtextxy(5 + 50 * j, 355, (char *)"WB");
                break;
            }
            case Knight:
            {
                if (i == 0)
                    outtextxy(5 + 50 * j, 5, (char *)"BH");
                else if (i == 7)
                    outtextxy(5 + 50 * j, 355, (char *)"WH");
                break;
            }
            case Rook:
            {
                if (i == 0)
                    outtextxy(5 + 50 * j, 5, (char *)"BR");
                else if (i == 7)
                    outtextxy(5 + 50 * j, 355, (char *)"WR");
                break;
            }
            case Pawn:
            {
                if (i == 1)
                    outtextxy(5 + 50 * j, 55, (char *)"BP");
                else if (i == 6)
                    outtextxy(5 + 50 * j, 305, (char *)"WP");
                break;
            }
            }
        }
    }
    delay(3000);
    getch();
}

void game::clear(int x1, int y1, int x2, int y2)
{
    box *src, *dest;
    src = &board[x1][y1];
    dest = &board[x2][y2];
    Piece p = dest->getpiece();
    if ((x1 % 2 == 0 && y1 % 2 == 0) || (x1 % 2 != 0 && y1 % 2 != 0))
        setcolor(WHITE);
    else
        setcolor(BLACK);
    int x = y1 * 50;
    for (int i = x; i < x + 50; i++)
    {
        line(i, x1 * 50, i, x1 * 50 + 50);
    }
    if ((x2 % 2 == 0 && y2 % 2 == 0) || (x2 % 2 != 0 && y2 % 2 != 0))
        setcolor(WHITE);
    else
        setcolor(BLACK);
    int y = y2 * 50;
    for (int i = y; i < y + 50; i++)
    {
        line(i, x2 * 50, i, x2 * 50 + 50);
    }

    if (dest->getcolor() == White)
        setcolor(4);
    else if (dest->getcolor() == Black)
        setcolor(3);
    switch (p)
    {
    case King:

        if (dest->getcolor() == White)
            outtextxy(y + 5, x2 * 50 + 5, (char *)"WK");
        else
            outtextxy(y + 5, x2 * 50 + 5, (char *)"BK");
        break;
    case Queen:

        if (dest->getcolor() == White)
            outtextxy(y + 5, x2 * 50 + 5, (char *)"WQ");
        else
            outtextxy(y + 5, x2 * 50 + 5, (char *)"BQ");
        break;

    case Bishop:
        if (dest->getcolor() == White)
            outtextxy(y + 5, x2 * 50 + 5, (char *)"WB");
        else
            outtextxy(y + 5, x2 * 50 + 5, (char *)"BB");
        break;

    case Knight:
        if (dest->getcolor() == White)
        {

            outtextxy(y + 5, x2 * 50 + 5, (char *)"WH");
        }
        else
            outtextxy(y + 5, x2 * 50 + 5, (char *)"BH");
        break;

    case Rook:
        if (dest->getcolor() == White)
            outtextxy(y + 5, x2 * 50 + 5, (char *)"WR");
        else
            outtextxy(y + 5, x2 * 50 + 5, (char *)"BR");
        break;
    case Pawn:

        if (dest->getcolor() == White)
        {

            outtextxy(y + 5, x2 * 50 + 5, (char *)"WP");
        }
        else
            outtextxy(y + 5, x2 * 50 + 5, (char *)"BP");
        break;
    }
}

void fornt_screen()
{
    system("cls");
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char *)" ");
    setcolor(3);
    settextstyle(5, 0, 5);
    outtextxy(10, 0, (char *)"Welcome To Chess Game\n");
    delay(2000);
    char l[2];
    outtextxy(10, 260, (char *)"Enter length of name Player1: ");
    l[0] = getch();
    l[1] = '\0';

    outtextxy(650, 260, l);
    int n = (int)l[0];
    char p1[(int)l[0] + 1] = {'\0'}, k[2];
    outtextxy(10, 360, (char *)"Enter name Player1: ");
    for (int i = 0; i < (int)l[0] - 48; i++)
    {
        k[0] = getch();
        k[1] = '\0';
        outtextxy(440 + i * 35, 360, k);
    }
    outtextxy(10, 460, (char *)"Enter length of name Player2: ");
    l[0] = getch();
    l[1] = '\0';
    outtextxy(630, 460, l);
    outtextxy(10, 560, (char *)"Enter name Player2: ");
    for (int i = 0; i < (int)l[0] - 48; i++)
    {
        k[0] = getch();
        k[1] = '\0';
        outtextxy(440 + i * 35, 560, k);
    }
    delay(5000);
}

int main()
{
    char y1[2], x2[2], y2[2];
    char x1[2];
    int i = 0;
    fornt_screen();
    cleardevice();
    setcolor(BLACK);
    game g;
    g.setboard();
    g.display_board();
    setviewport(0, 0, 600, 600, 1);

    settextstyle(8, 0, 4);
    setcolor(3);
    x1[1] = '\0';
    y1[1] = '\0';
    x2[1] = '\0';
    y2[1] = '\0';
    Color turn = White;
    while (whowins == None)
    {
        if (i % 2 == 0)
        {
            setcolor(BLACK);
            outtextxy(0, 460, (char *)"Player1 move from ::");
            outtextxy(400, 460, x1);
            outtextxy(430, 460, y1);
            outtextxy(500, 460, x2);
            outtextxy(530, 460, y2);
        }
        if (i % 2 == 1)
        {

            setcolor(BLACK);
            outtextxy(0, 560, (char *)"Player2 move from ::");
            outtextxy(400, 560, x1);
            outtextxy(430, 560, y1);
            outtextxy(500, 560, x2);
            outtextxy(530, 560, y2);
        }
        x1[0] = '\0', y1[0] = x2[0] = y2[0] = '\0';
        if (i % 2 == 0)
        {
            setcolor(RED);
            outtextxy(0, 460, (char *)"Player1 move from ::");
            x1[0] = getch();
            outtextxy(400, 460, x1);
            y1[0] = getch();
            outtextxy(430, 460, y1);

            x2[0] = getch();
            outtextxy(500, 460, x2);
            y2[0] = getch();
            outtextxy(530, 460, y2);
            if (g.makemove((int)x1[0] - 49, (int)y1[0] - 49, (int)x2[0] - 49, (int)y2[0] - 49, turn))
            {

                g.clear((int)x1[0] - 49, (int)y1[0] - 49, (int)x2[0] - 49, (int)y2[0] - 49);
                turn = Black;
                i++;
            }
        }
        else
        {
            setcolor(3);
            outtextxy(0, 560, (char *)"Player2 move from ::");
            x1[0] = getch();
            outtextxy(400, 560, x1);
            y1[0] = getch();
            outtextxy(430, 560, y1);
            x2[0] = getch();
            outtextxy(500, 560, x2);
            y2[0] = getch();
            outtextxy(530, 560, y2);
            if (g.makemove((int)x1[0] - 49, (int)y1[0] - 49, (int)x2[0] - 49, (int)y2[0] - 49, turn))
            {
                g.clear((int)x1[0] - 49, (int)y1[0] - 49, (int)x2[0] - 49, (int)y2[0] - 49);
                turn = White;
                i++;
            }
        }
    }
    if (whowins == White)
        cout << "Player 1 win";
    else
        cout << "Player2 win";

    delay(1000);
}
