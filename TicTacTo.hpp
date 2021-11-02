#include <string>
#include <vector>
using namespace std;
struct out;
struct child{
    out* kid;
};
struct out{
    int n;
    bool comp;
    int win;
    int game[9];
    int move;
    vector<child> children;
    out(int in_n, bool in_comp, int in_win, int in_game[], int in_move){
        n = in_n;
        comp = in_comp;
        win = in_win;
        move = in_move;
        for(int i=0; i<9; i++){
            game[i] = in_game[i];
        }
    }
};
class tic{
    public:
        tic();
        ~tic();
        void player();
        void computer();
        void print();
        int checkResult();
        void ai();
        out* aiBuild(out* n);
        int aiResult(int game[9]);
        out* findNode(out* n, int game[9], int level);
        int bestMove(out* n);

    private:
        out* root;
        int board[9];
};