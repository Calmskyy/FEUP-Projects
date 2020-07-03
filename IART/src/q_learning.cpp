#include "q_learning.h"
#include <chrono>
#include <ios>

q_learning::q_learning(int goal, int episodes, double epsilon) {
	goal_state = goal;
	episodesToRun = episodes;
	startingEpsilon = epsilon;
	for (int i = 0; i < STATE_NUM; i++) { // initialize Q matrix to 0
		for (int j = 0; j < STATE_NUM; j++) {
			Q[i][j] = 0;
		}
	}
}

void q_learning::setR(double values[STATE_NUM][STATE_NUM]) { // change R matrix's values
	for (int i = 0; i < STATE_NUM; i++) {
		for (int j = 0; j < STATE_NUM; j++) {
			R[i][j] = values[i][j];
		}
	}
}

void q_learning::get_possible_action(int state) { // get list of possible actions from a given state
	possible_action_num = 0;
	for (int i = 0; i < STATE_NUM; i++) {
		if (R[state][i] >= 0) {
			possible_action[possible_action_num] = i;
			possible_action_num++;
		}
	}
}

double q_learning::get_max_q(int state) { // get the Q max from a given state
	double temp_max = 0;
	for (int i = 0; i < STATE_NUM; i++) {
		if ((R[state][i] >= 0) && (Q[state][i] > temp_max)) {
			temp_max = Q[state][i];
		}
	}
	return temp_max;
}

int q_learning::run_episode(int state) { // go through each training episode

	int action;
	double max_q;
	int count = 0;
	while (1) {
		count++;
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
		max_q = get_max_q(action); // treat next action as state, and we can get max{Q(s, a)}

		Q[state][action] += ALPHA * (R[state][action] + GAMMA * max_q - Q[state][action]); // update Q value for this state

		// if the next state is the goal state, go to the next episode
		// if not, then go back to this loop
		if (action == goal_state) {
			state = rand() % STATE_NUM;
			break;
		}
		else {
			state = action; // if not the goal state, then next state becomes the initial state
		}
	}
	return state;
}

int q_learning::retrieve_best_action(int state) { // get the best possible action in the given state
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

void q_learning::run_training(int init_state) { // start training
	int initial_state = init_state;
	unsigned int seed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	srand(seed); // start random seed
	for (int i = 0; i < episodesToRun; i++) { // iterate through various episodes
		epsilon = startingEpsilon / (0.05 * ((double)i + 1));
		if (epsilon < 0.1)
			epsilon = 0.1;
		initial_state = run_episode(initial_state);
	}
}
