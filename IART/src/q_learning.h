#pragma once

using namespace std;

#define STATE_NUM 64 // all possible combinations of x,y
#define MAX_POSSIBLE_ACTIONS 4 // left, right, up, down
#define GAMMA 0.7 // gamma value for Q calculation
#define ALPHA 0.8 // alpha value for Q calculation

class q_learning
{
public:
	q_learning(int goal, int episodes, double epsilon);
	double R[STATE_NUM][STATE_NUM];
	double Q[STATE_NUM][STATE_NUM];
	int goal_state;
	int episodesToRun;
	int possible_action[MAX_POSSIBLE_ACTIONS];
	int possible_action_num;
	double startingEpsilon;
	double epsilon;
	void setR(double values[STATE_NUM][STATE_NUM]); // change R matrix's values
	void get_possible_action(int state); // get list of possible actions from a given state
	double get_max_q(int state); // get the Q max from a given state
	int run_episode(int state); // go through each training episode
	int retrieve_best_action(int state); // get the best possible action in the given state
	void run_training(int init_state); // start training
};
