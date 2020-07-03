#include "sarsa.h"
#include <iostream>
#include <chrono>

sarsa::sarsa(int goal, int episodes, double epsilon) {
	goal_state = goal;
	episodesToRun = episodes;
	startingEpsilon = epsilon;
	for (int i = 0; i < STATE_NUM; i++) { // initialize Q matrix to 0
		for (int j = 0; j < STATE_NUM; j++) {
			Q[i][j] = 0;
		}
	}
}

void sarsa::setR(double values[STATE_NUM][STATE_NUM]) { // change R matrix's values
	for (int i = 0; i < STATE_NUM; i++) {
		for (int j = 0; j < STATE_NUM; j++) {
			R[i][j] = values[i][j];
		}
	}
}

void sarsa::get_possible_action(int state) { // get list of possible actions from a given state
	possible_action_num = 0;
	for (int i = 0; i < STATE_NUM; i++) {
		if (R[state][i] >= 0) {
			possible_action[possible_action_num] = i;
			possible_action_num++;
		}
	}
}

int sarsa::run_episode(int state) { // go through each training episode

	int action, action2;
	int state2;
	while (1) {  // get a valid state
		memset(possible_action, 0, MAX_POSSIBLE_ACTIONS * sizeof(int));
		get_possible_action(state);
		if (possible_action_num == 0) { // in case the state is not a valid playing position, such as a wall or box, restart the episode
			state = rand() % STATE_NUM;
			continue;
		}
		double r = ((double)rand() / (RAND_MAX));
		if (epsilon > r)
			action = possible_action[rand() % possible_action_num]; // get next action randomly, explorative
		else {
			action = retrieve_best_action(state); // get best possible action, exploitative
			if (action == 0) // in case the agent hasn't learned enough yet (note we can use 0 because 0 is never a possible state to move to, it's a wall in every level)
				action = possible_action[rand() % possible_action_num]; // get next action randomly, explorative
		}

		state2 = action;
		if (state2 == goal_state) {
			state = rand() % STATE_NUM;
			continue;
		}
		else {
			break;
		}
	}

	while (1) {
		state2 = action;
		memset(possible_action, 0, MAX_POSSIBLE_ACTIONS * sizeof(int));
		get_possible_action(state2);

		double r = ((double)rand() / (RAND_MAX));
		if (epsilon > r)
			action2 = possible_action[rand() % possible_action_num]; // get next action randomly, explorative
		else {
			action2 = retrieve_best_action(state2); // get best possible action, exploitative
			if (action2 == 0) // in case the agent hasn't learned enough yet (note we can use 0 because 0 is never a possible state to move to, it's a wall in every level)
				action2 = possible_action[rand() % possible_action_num]; // get next action randomly, explorative
		}

		Q[state][action] += ALPHA * (R[state][action] + GAMMA * Q[state2][action2] - Q[state][action]); // update Q value for this state

		// if the next state is the goal state, go to the next episode
		// if not, then go back to this loop
		if (action == goal_state) {
			state = rand() % STATE_NUM;
			break;
		}
		else {
			state = state2; // if not the goal state, then second state becomes the initial state
			action = action2; // if not the goal state, then second action becomes the initial action
		}
	}
	return state;
}

int sarsa::retrieve_best_action(int state) { // get the best possible action in the given state
	double temp_max_q = 0;
	int best_action = 0;
	for (int i = 0; i < STATE_NUM; i++) {
		if (Q[state][i] > temp_max_q) {
			temp_max_q = Q[state][i];
			best_action = i;
		}
	}
	return best_action;
}

void sarsa::run_training(int init_state) { // start training
	unsigned int seed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	srand(seed); // start random seed
	int initial_state = init_state;
	for (int i = 0; i < episodesToRun; i++) { // iterate through various episodes
		epsilon = startingEpsilon / (0.05 * ((double)i + 1));
		if (epsilon < 0.1)
			epsilon = 0.1;
		initial_state = run_episode(initial_state);
	}
}
