#include <simplecpp>
#include "shooter.h"
#include "bubble.h"

/* Simulation Vars */
const double STEP_TIME = 0.02;

/* Game Vars */
const int PLAY_Y_HEIGHT = 450;
const int LEFT_MARGIN = 70;
const int TOP_MARGIN = 20;
const int BOTTOM_MARGIN = (PLAY_Y_HEIGHT+TOP_MARGIN);
int Shooter_Health = 51; // Shooter_Health is initilized with 51 because asciiof(51) is 3
int level_number = 49;   // Level_number is initilized with 49 because asciiof(49) is 1 i.e. first level
char score_unit = char(48); // score_unit (units place of score) is initilized with asciiof(48) i.e. zero
char score_tens = char(48); // score_tens (tens place of score) is initilized with asciiof(48) i.e. zero
char Tim = char(48);        // Time (units place of score) is initilized with asciiof(48) i.e. zero
char p = char(48);          // Time (tens place of score) is initilized with asciiof(48) i.e. zero
int i = 0;

void move_bullets(vector<Bullet> &bullets){
    // move all bullets
    for(unsigned int i=0; i<bullets.size(); i++){
        if(!bullets[i].nextStep(STEP_TIME)){
            bullets.erase(bullets.begin()+i);
        }
    }
}

void move_bubbles(vector<Bubble> &bubbles){
    // move all bubbles
    for (unsigned int i=0; i < bubbles.size(); i++)
    {
        bubbles[i].nextStep(STEP_TIME);

}
}
void erase_bullet_bubble(vector<Bullet> &bullets, vector<Bubble> &bubbles){
    for(int i = 0; i < bullets.size(); i++){
        for(int j = 0; j < bubbles.size(); j++){
            // This condition is to check are the bullets and bubbles colliding
            // if yes then erase both of them
            if (((bullets[i].get_center_x() <= bubbles[j].get_center_x() +bubbles[j]. get_radius())
                &&
                (bullets[i].get_center_x() >= bubbles[j].get_center_x() - bubbles[j].get_radius()))
                &&
                ((bullets[i].get_center_y() <= bubbles[j].get_center_y() + bubbles[j].get_radius())
                &&
                (bullets[i].get_center_y() >= bubbles[j].get_center_y() - bubbles[j].get_radius()))){
                bullets.erase(bullets.begin() + i); // erasing bullets
                bubbles.erase(bubbles.begin() + j); // erasing bubbles
                // ++score_unit;
                // ++score_tens;
                }
        }
    }
}

int colo = 30;
void bubble_macker(vector<Bubble> &bubbles, vector<Bullet> &bullets)
{   // This condition is to check are the bullets and bubbles colliding
    // if yes then erase both of them
    for (int i = 0; i < bullets.size(); i++)
    {
        for (int j = 0; j < bubbles.size(); j++)
        {
            if ((abs(bullets[i].get_center_x() - bubbles[j].get_center_x()) <= (bullets[i].get_width() / 2.0 + bubbles[j].get_radius()))
            &&
            (abs(bullets[i].get_center_y() - bubbles[j].get_center_y()) <= (bullets[i].get_height() / 2.0 + bubbles[j].get_radius())))
            {
                if (bubbles[j].get_radius() > 10){ // checking the threshold radius
                    colo = colo + 100;         // i have dissabled the color changing functionality of bubble on split
                    bubbles.push_back(Bubble(bubbles[j].get_center_x(), bubbles[j].get_center_y(), bubbles[j].get_radius() / 2.0, -bubbles[j].get_vx()*1.2, bubbles[j].get_vy()*1.02, COLOR(150, 93, 195)));
                    bubbles.push_back(Bubble(bubbles[j].get_center_x(), bubbles[j].get_center_y(), bubbles[j].get_radius() / 2.0, bubbles[j].get_vx()*1.2, -bubbles[j].get_vy()*1.02, COLOR(150, 93, 195)));
                    bullets.erase(bullets.begin() + i); // erasing bullets
                    bubbles.erase(bubbles.begin() + j); // erasing bubbles
                }
                else{
                    bullets.erase(bullets.begin() + i); // erasing bullets
                    bubbles.erase(bubbles.begin() + j); // erasing bubbles
                }
                // It keeps the track of the collusion of bullet with the bubble and updates the score
                if (score_unit < 58)
                {   // It works still 1 to 9 in units place
                    ++(score_unit);
                }
                else
                {   // It works when score_unit hits the 9
                    score_unit = 48;
                    ++score_tens;
                }
            }
            }
        }
}

    int dead_shooter(vector<Bubble> &bubbles, Shooter shoot){
    for(int i = 0; i < bubbles.size(); i++){
            // This checks the collusion between the shooter and the bubble
        if (// This part of if condition checks wether the bubblel has hitted the rectangle part or not
            (abs(shoot.get_body_center_x() - bubbles[i].get_center_x()) <= (shoot.get_body_width() / 2.0 + bubbles[i].get_radius()))
            &&
            (abs(shoot.get_body_center_y() - bubbles[i].get_center_y()) <= (shoot.get_body_height() / 2.0 + bubbles[i].get_radius()))
            ||
            // This part of if condition checks wether the bubble has hitted the head (circular part) or not
            (sqrt((shoot.get_head_center_x() - bubbles[i].get_center_x())*(shoot.get_head_center_x() - bubbles[i].get_center_x())
                +
                (shoot.get_head_center_y() - bubbles[i].get_center_y())*(shoot.get_head_center_y() - bubbles[i].get_center_y())) <= bubbles[i].get_radius() + shoot.get_head_radius())
        )
        {
            // Text Game_Oveqr(250,250,"Game Over.."); // this line was for the basic required condition
            // *If there is a collusion in between bubble and the shooter the the Shooter_Health decreases by one
            --Shooter_Health;
            bubbles.push_back(Bubble(bubbles[i].get_center_x(), bubbles[i].get_center_y(), bubbles[i].get_radius(), -bubbles[i].get_vx()*1.2, -bubbles[i].get_vy()*1.2, COLOR(colo, 93, 195)));
            bubbles.erase(bubbles.begin() + i);
            return 0;
        }
    }
}
void level1(vector<Bubble> &bubbles, vector<Bullet> &bullets)
{   // This is level one (1)
    // This level is complex in terms of the number of bubbles, size  and speed and also i can make it more complex
    // by reducing time.
    if(bubbles.size() == 0){
        // again i, set all the score (00), timmer(00) and Health(3) to orignal value
        ++level_number;
        Shooter_Health = 51;
        score_unit = char(48);
        score_tens = char(48);
        Tim = char(48);
        p = char(48);
            // this prints the second level start at the center of the initCanvas
        Text cong1(250, 230, "(●'◡'●) CONGRATULATION !! Level 1 compleated (❁´◡`❁)");
        Text cong2(250, 250, "Now the 2 nd level starts");
        cong1.setColor(COLOR(0, 0, 255));
        cong2.setColor(COLOR(0,0,255));
        wait(2);

        for (int i = 0; i < bullets.size(); i++){
            bullets.erase(bullets.begin() + i);
        }
        bubbles.push_back(Bubble(WINDOW_X / 2.0, BUBBLE_START_Y, BUBBLE_DEFAULT_RADIUS, -BUBBLE_DEFAULT_VX, 400, COLOR(255, 105, 180)));
        bubbles.push_back(Bubble(WINDOW_X / 4.0, BUBBLE_START_Y, BUBBLE_DEFAULT_RADIUS, BUBBLE_DEFAULT_VX, 400, COLOR(255, 105, 180)));
        bubbles.push_back(Bubble(WINDOW_X / 6.0, BUBBLE_START_Y, BUBBLE_DEFAULT_RADIUS, BUBBLE_DEFAULT_VX, 400, COLOR(255, 105, 180)));
    }
}

void level2(vector<Bubble> &bubbles, vector<Bullet> &bullets)
{   // This is level two (2)
    // This level is complex in terms of the number of bubbles, size  and speed and also i can make it more complex
    // by reducing time.
    if(bubbles.size() == 0){
        Shooter_Health = 51;
        ++level_number;
        score_unit = char(48);
        score_tens = char(48);
        Tim = char(48);
        p = char(48);
        // this prints the third level start at the center of the initCanvas
        Text cong1(250, 230, "(●'◡'●) CONGRATULATION !! Level 2 compleated (❁´◡`❁)");
        Text cong2(250, 250, "Now the 3 rd level starts");
        cong1.setColor(COLOR(0, 0, 255));
        cong2.setColor(COLOR(0, 0, 255));
        wait(2);

        for (int i = 0; i < bullets.size(); i++){
            bullets.erase(bullets.begin() + i);
        }
        // here i have made the color of bubble change as per the coordinate
        bubbles.push_back(Bubble(WINDOW_X / 2.0, BUBBLE_START_Y, BUBBLE_DEFAULT_RADIUS, -BUBBLE_DEFAULT_VX, 500, COLOR(255, 182, 180)));
        bubbles.push_back(Bubble(WINDOW_X / 4.0, BUBBLE_START_Y, BUBBLE_DEFAULT_RADIUS, BUBBLE_DEFAULT_VX, 500, COLOR(255,182, 180)));
        bubbles.push_back(Bubble(WINDOW_X / 6.0, BUBBLE_START_Y, BUBBLE_DEFAULT_RADIUS, BUBBLE_DEFAULT_VX, 500, COLOR(255,182, 180)));
        bubbles.push_back(Bubble(WINDOW_X / 8.0, BUBBLE_START_Y, BUBBLE_DEFAULT_RADIUS * 2, BUBBLE_DEFAULT_VX, 600, COLOR(255,182, 180)));
    }
}
    vector<Bubble> create_bubbles()
{
    // create initial bubbles in the game
    vector<Bubble> bubbles;
    bubbles.push_back(Bubble(WINDOW_X/2.0, BUBBLE_START_Y, BUBBLE_DEFAULT_RADIUS, -BUBBLE_DEFAULT_VX, 200, COLOR(255,105,180)));
    bubbles.push_back(Bubble(WINDOW_X/4.0, BUBBLE_START_Y, BUBBLE_DEFAULT_RADIUS, BUBBLE_DEFAULT_VX, 200, COLOR(255,105,180)));
    return bubbles;
}


int main()
{
    initCanvas("Bubble Trouble", WINDOW_X, WINDOW_Y);
    Text T1( 250, 250, "Level 1");
    T1.setColor(COLOR(0, 0, 255));
    wait(4);
    Text t1(250,250,"                      ");
    Line b1(0, PLAY_Y_HEIGHT, WINDOW_X, PLAY_Y_HEIGHT);
    b1.setColor(COLOR(0, 0, 255));

    string msg_cmd("Cmd: _");
    Text charPressed(LEFT_MARGIN, BOTTOM_MARGIN, msg_cmd);

    string Health("Health : _ / 3");
    Text ShooterHealth(400, TOP_MARGIN,Health);

    string Timmer("Time : __ / 60");
    Text Time(50, TOP_MARGIN,Timmer);

    string level("Level : _ / 3");
    Text lev(250, BOTTOM_MARGIN, level);

    string score("score : __ ");
    Text soc(400, BOTTOM_MARGIN, level);

    // string Timmer("Time : _ / 60");
    // Text Time(50, TOP_MARGIN,Timmer);

    // Intialize the shooter
    Shooter shooter(SHOOTER_START_X, SHOOTER_START_Y, SHOOTER_VX);

    // Initialize the bubbles
    vector<Bubble> bubbles = create_bubbles();

    // Initialize the bullets (empty)
    vector<Bullet> bullets;

    XEvent event;
    int n = 0;
    // Main game loop
    while (true)
    {  ++n; // Measures the number of iteration
        if(n%15 == 0 ){
            if(n%150 == 0){
                Tim = 48;
                ++p;
            }else{
            Tim = Tim + 1;
            }
        }

        bool pendingEvent = checkEvent(event);
        if (pendingEvent)
        {
            // Get the key pressed
            char c = charFromEvent(event);
            msg_cmd[msg_cmd.length() - 1] = c;
            charPressed.setMessage(msg_cmd);


            // Update the shooter
            if (c == 'a')
                shooter.move(STEP_TIME, true);
            else if (c == 'd')
                shooter.move(STEP_TIME, false);
            else if (c == 'w')
                bullets.push_back(shooter.shoot());
            else if (c == 'q')
                return 0;

        }

        // Update the bubbles
        move_bubbles(bubbles);

        // Update the bullets
        move_bullets(bullets);

        bubble_macker(bubbles, bullets);

        (level)[(level).length() - 5] = ((level_number)); // This chances the level number agfter completion
        lev.setMessage(level);

        (Timmer)[(Timmer).length() - 6] = (int(Tim)); // This updates the timmer
        (Timmer)[(Timmer).length() - 7] = (int(p));
        Time.setMessage(Timmer);

        (Health)[(Health).length() - 5] = int(char(Shooter_Health)); //This updates the Shooter_Health on collusin
        ShooterHealth.setMessage(Health);                            // of bubble with shooter

        if (Shooter_Health - 48 <= 0 ||(Tim == 48 && p == 54))
        {   // Game is over if time is over or Shooters_Health becomes zero
            Text Game_Over(250, 250, "Game Over :-)");
            wait(8);
            break;
        }
            if (dead_shooter(bubbles, shooter) == 0 && bubbles.size() == 0)
            {
                // Text Game_Over(250, 250, "Game Over.."); *
                // wait(10);                                * This is as per the basic condition
                // break;                                   *

                // Once all the bubbles are over the  next level starts
                if (i == 0)
                {
                    ++i;
                    level1(bubbles, bullets);
                }
                else if (i == 1)
                {
                    ++i;
                    level2(bubbles, bullets);
                }
                else{
                    Text  Game_Over1( 250,250," You have compleated all the levels ");
                    Text  Game_Over2( 250,280," Successfully !!! :-) ");
                    wait(5);
                    break;
                }
        }
            (score)[(score).length() - 2] = (int(score_unit)); // This updates the score_unit
            (score)[(score).length() - 3] = (int(score_tens)); // This updates the score_tens
            soc.setMessage(score);
        wait(STEP_TIME);
            }
}
