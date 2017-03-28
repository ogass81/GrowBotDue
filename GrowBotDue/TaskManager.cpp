// 
// 
// 

#include "TaskManager.h"

void TaskManager::next()
{
	if (task_ptr < (TASKBUFFER - 1)) {
		task_ptr++;
	}
	else task_ptr = 0;
}

void TaskManager::prev()
{
	if (task_ptr > 0) {
		task_ptr--;
	}
	else task_ptr = (TASKBUFFER - 1);
}

uint8_t TaskManager::getNextPosition(uint8_t delay)
{
	if (task_ptr + delay < TASKBUFFER) {
		return uint8_t(task_ptr + delay);
	}
	else {
		return (delay - (TASKBUFFER - task_ptr - 1));
	}
}

uint8_t TaskManager::getNextPositionFrom(uint8_t current_pos, uint8_t delay)
{
	if (current_pos + delay < TASKBUFFER) {
		return uint8_t(current_pos + delay);
	}
	else {
		return (delay - (TASKBUFFER - current_pos - 1));
	}
}

uint8_t TaskManager::getOffSet(ActionChain *actionchain)
{
	uint8_t current_ptr = task_ptr;
	bool empty_spot = false;
	uint8_t offset = 0;

	while (offset < TASKBUFFER) {
		current_ptr += offset;
		for (uint8_t i = 0; i < TASKSINCHAIN; i++) { //Iterate all Tasks in Chain
			if (actionchain->assignedAction[i] != NULL) {
				if (actionchain->actionParameter[i] == 0) {  //Simple Action - only Start, no End
					 //Empty Spot for Start of Action
					for (uint8_t j = 0; j < PARALLELTASKS; j++) {
						if (queue[current_ptr][j] == NULL) {
							empty_spot = true;
							Serial.println("OK: Found a sport for simple action" + String(current_ptr));
							current_ptr = getNextPositionFrom(current_ptr, 0); //Allow Parallel Tasks -> 0
							break;
						}
						else empty_spot = false;
					}
				}
				else {  //Complex Action - need two spots for Start and End
						//Find Empty Spot for
						//Start
					for (uint8_t j = 0; j < PARALLELTASKS; j++) {
						if (queue[current_ptr][j] == NULL) {
							current_ptr = getNextPositionFrom(current_ptr, actionchain->actionParameter[i]);
							//End
							for (uint8_t k = 0; k < PARALLELTASKS; k++) {
								if (queue[current_ptr][k] == NULL) {
									empty_spot = true;
									Serial.println("OK: Found a sport for complex action start and end" + String(current_ptr));
									current_ptr = getNextPositionFrom(current_ptr, 0); //Allow Parallel Tasks -> 0
									break;
								}
								else empty_spot = false;
							}
						}
						else empty_spot = false;
					}
				}
			}
			else break; //No Action No Effort -> Break

			if (empty_spot == false) { //Last Task didnt find spot - bad -> start over with different offset
				Serial.println("Info: No place for Task " + String(i));
				offset++;
				Serial.println("Info: Raising Offset " + String(offset));
				break;
			}
		}
		if (empty_spot == true) {
			Serial.println("Ok: Last Task found its place at Offset " + String(offset));
			break; //Last Task found spot - good -> break loop
		}
	}

	return offset;
}

TaskManager::TaskManager()
{
	for (uint8_t i = 0; i < TASKBUFFER; i++) {
		for (uint8_t j = 0; j < PARALLELTASKS; j++) {
			queue[i][j] = NULL;
		}
	}
}

void TaskManager::addActions(ActionChain *actionchain)
{
	uint8_t current_ptr = task_ptr;

	uint8_t offset = 0;
	if ((offset = getOffSet(actionchain)) < TASKBUFFER) {
		current_ptr = getNextPositionFrom(task_ptr, offset);

		for (uint8_t i = 0; i < TASKSINCHAIN; i++) { //Iterate all Tasks in Chain
			if (actionchain->assignedAction[i] != NULL) {
				if (actionchain->actionParameter[i] == 0) {  //Simple Action - only Start, no End
															 //Empty Spot for Start of Action
					for (uint8_t j = 0; j < PARALLELTASKS; j++) {
						if (queue[current_ptr][j] == NULL) {
							Serial.println("OK: Found a spot assigning simple action" + String(current_ptr));
							queue[current_ptr][j] = actionchain->assignedAction[i];
							current_ptr = getNextPositionFrom(current_ptr, 0); //Allow Parallel Tasks -> 0
							break;
						}
					}
				}
				else {  //Complex Action - need two spots for Start and End
						//Find Empty Spot for
						//Start
					for (uint8_t j = 0; j < PARALLELTASKS; j++) {
						if (queue[current_ptr][j] == NULL) {
							Serial.println("OK: Found a spot assigning complex action Start" + String(current_ptr));
							queue[current_ptr][j] = actionchain->assignedAction[i];
							current_ptr = getNextPositionFrom(current_ptr, actionchain->actionParameter[i]);
							//End
							for (uint8_t k = 0; k < PARALLELTASKS; k++) {
								if (queue[current_ptr][k] == NULL) {
									Serial.println("OK: Found a spot assigning complex action End" + String(current_ptr));
									if(actionchain->assignedAction[i]->antaObject != NULL) queue[current_ptr][k] = actionchain->assignedAction[i]->antaObject;
									else Serial.println("Error: No Antagonist Defined");
									current_ptr = getNextPositionFrom(current_ptr, 0); //Allow Parallel Tasks -> 0
									break;
								}
							}
						}
					}
				}
			}
			else break; //No Action No Effort -> Break
		}
	}
	else {
		Serial.println("Error: No room for Action Chain in Task Queue");
	}
}

void TaskManager::execute()
{
	for (uint8_t i = 0; i < PARALLELTASKS; i++) {
		if (queue[task_ptr][i] != NULL) {
			queue[task_ptr][i]->execute();
			queue[task_ptr][i] = NULL;
		}
	}
	//Move Pointer forward
	next();
}
