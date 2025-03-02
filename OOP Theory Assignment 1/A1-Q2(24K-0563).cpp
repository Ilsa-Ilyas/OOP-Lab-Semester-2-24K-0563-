#include <iostream>
#include <string>
using namespace std;

class Ball {
private:
    int x, y;

public:
    Ball(int X = 0, int Y = 0) {
        x = X;
        y = Y;
    }

    int getX() { return x; }
    int getY() { return y; }

    void setX(int newX) { x = newX; }
    void setY(int newY) { y = newY; } 

    void move(int dx, int dy) {
        x += dx;
        y += dy;
    }

    void getPosition(int &posX, int &posY) {
        posX = x;
        posY = y;
    }
};

class Goal {
private:
    const int X = 3;
    const int Y = 3;

public:
    bool isGoalReached(int ballX, int ballY) {
        return (ballX == X && ballY == Y);
    }

    int getX() { return X; }
    int getY() { return Y; }
};

class Robot {
private:
    string name;
    int hits;

public:
    Robot(string n) {
        name = n;
        hits = 0;
    }

    void hitBall(int &ballX, int &ballY, const string &direction) {
    if (direction == "up" || direction == "down" || direction == "left" || direction == "right") {
        if (direction == "up")
            ballY--;
        else if (direction == "down")
            ballY++;
        else if (direction == "left")
            ballX--;
        else if (direction == "right")
            ballX++;
        hits++; 
    } else {
        cout << "Invalid move! Try again.\n";
    }
}

    int getHits() { return hits; }
    string getName() { return name; }

    void setHits(int h) { hits = h; }
    void setName(string n) { name = n; }
    void resetHits() { hits = 0; }  

};

class Team {
private:
    string teamName;
    Robot *player;

public:
    Team(string n, Robot *y) {
        teamName = n;
        player = y;
    }

    string getTeamName() { return teamName; }
    void setTeamName(string n) { teamName = n; }

    Robot *getRobot() { return player; }
    void setRobot(Robot *r) { player = r; }
};

class Game {
private:
    Team *teamA;
    Team *teamB;
    Ball ball;
    Goal goal;

public:
    Game(Team *t1, Team *t2, int X, int Y) {
        teamA = t1;
        teamB = t2;
        ball = Ball(X, Y);
    }

void play(Team *team) {
    Robot *robot = team->getRobot();
    int ballX, ballY;
    ball.getPosition(ballX, ballY);
    int startX = ballX, startY = ballY;

    cout << "\n========== " << team->getTeamName() << " is now playing ==========" << endl;
    cout << "Move the ball towards the goal (3,3).\n";
    cout << "Enter direction of motion:\n1. Up\n2. Down\n3. Left\n4. Right\n";

    while (!goal.isGoalReached(ballX, ballY)) {
        string dir;
        int c;
        while (true) {
            cout << "Enter choice of move (1-4): ";
            if (cin >> c && (c >= 1 && c <= 4)) break;
            cout << "Invalid input! Please enter a number between 1-4.\n";
            cin.clear();
            cin.ignore(100, '\n');
        }

        if (c == 1) dir = "up";
        else if (c == 2) dir = "down";
        else if (c == 3) dir = "left";
        else dir = "right";

        robot->hitBall(ballX, ballY, dir);
        cout << "Current ball position: (" << ballX << ", " << ballY << ")\n";
    }

    cout << "Goal reached! Total hits: " << robot->getHits() << "\n";
    ball = Ball(startX, startY);
}


    void declareWinner() {
        Robot *r1 = teamA->getRobot();
        Robot *r2 = teamB->getRobot();

        cout << "\n======== GAME RESULTS ========\n";
        cout << teamA->getTeamName() << ": " << r1->getHits() << " hits\n";
        cout << teamB->getTeamName() << ": " << r2->getHits() << " hits\n";

        if (r1->getHits() < r2->getHits()) {
            cout << "" << teamA->getTeamName() << " wins!\n";
        } else if (r2->getHits() < r1->getHits()) {
            cout << "" << teamB->getTeamName() << " wins!\n";
        } else {
            cout << "It's a tie! Well played! \n";
        }
    }

void startGame() {
    cout << "\n====== FOOTBALL GAME STARTING ======\n";
    cout << "Each team will attempt to reach the goal (3,3) in the fewest hits.\n";

    teamA->getRobot()->resetHits();
    teamB->getRobot()->resetHits();

    play(teamA);
    
    if (cin.peek() == '\n') cin.ignore(); 
    play(teamB);

    cout << "\n======= FINAL RESULTS =======\n";
    declareWinner();
}

};

int main() {
    cout << "\n Welcome to the Robot Football Championship! \n";
    cout << "===============================================\n";

    Robot strikerOne("ThunderBot");
    Robot strikerTwo("ShadowBlaze");

    Team teamAlpha("Cyber Strikers", &strikerOne);
    Team teamBeta("Mecha Warriors", &strikerTwo);

    Game footballMatch(&teamAlpha, &teamBeta, 0, 0);

    footballMatch.startGame();

    cout << "\n?? The match has concluded! Thank you for playing! ??\n";

    return 0;
}


