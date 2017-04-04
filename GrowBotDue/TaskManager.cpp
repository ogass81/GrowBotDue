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
		LOGDEBUG(F("[TaskManager]"), F("getOffSet()"), F("OK: Searching spot for Actionchain"), String(actionchain->getTitle()), String(current_ptr), String(offset));
	
		for (uint8_t i = 0; i < TASKSINCHAIN; i++) { //Iterate all Tasks in Chain
			if (actionchain->assignedAction[i] != NULL) {
				if (actionchain->actionParameter[i] == 0) {  //Simple Action - only Start, no End
					 //Empty Spot for Start of Action
					for (uint8_t j = 0; j < PARALLELTASKS; j++) {
						if (queue[current_ptr][j] == NULL) {
							empty_spot = true;
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
									current_ptr = getNextPositionFrom(current_ptr, 0); //Allow Parallel Tasks -> 0
									break;
								}
								else empty_spot = false;
							}
							break;
						}
						else empty_spot = false;
					}
				}
			}
			else break; //No Action No Effort -> Break

			if (empty_spot == false) { //Last Task didnt find spot - bad -> start over with different offset
				offset++;
				current_ptr = getNextPositionFrom(task_ptr, offset);
				LOGDEBUG(F("[TaskManager]"), F("getOffSet()"), F("INFO: No spot found for Action"), String(i), String("Raising Pointer and Offset"), String(offset));
				break;
			}
		}
		if (empty_spot == true) {
			LOGDEBUG(F("[TaskManager]"), F("getOffSet()"), F("Ok: Spot found for Actionchain"), String(actionchain->getTitle()), String(current_ptr), String(offset));
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
	task_ptr = 0;
}

void TaskManager::addActions(ActionChain *actionchain)
{
	uint8_t current_ptr = task_ptr;
	uint8_t offset = 0;

	offset = getOffSet(actionchain);

	if (offset < TASKBUFFER) {
		current_ptr = getNextPositionFrom(task_ptr, offset);

		for (uint8_t i = 0; i < TASKSINCHAIN; i++) { //Iterate all Tasks in Chain
			if (actionchain->assignedAction[i] != NULL) {
				if (actionchain->actionParameter[i] == 0) {  //Simple Action - only Start, no End
															 //Empty Spot for Start of Action
					for (uint8_t j = 0; j < PARALLELTASKS; j++) {
						if (queue[current_ptr][j] == NULL) {
							LOGMSG(F("[TaskManager]"), F("OK: Added action to queue @"), String(current_ptr), String(actionchain->assignedAction[i]->getTitle()), "");
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
							uint8_t start_ptr, start_task;
							queue[current_ptr][j] = actionchain->assignedAction[i];
							LOGMSG(F("[TaskManager]"), F("OK: Added action to queue @"), String(current_ptr), String(actionchain->assignedAction[i]->getTitle()), "");
							
							//If adding of antagonist task fails -> needed to remove previously added action
							start_ptr = current_ptr;
							start_task = j;
							
							current_ptr = getNextPositionFrom(current_ptr, actionchain->actionParameter[i]);
							//End
							for (uint8_t k = 0; k < PARALLELTASKS; k++) {
								if (queue[current_ptr][k] == NULL) {
									if (actionchain->assignedAction[i]->antaObject != NULL) {
										queue[current_ptr][k] = actionchain->assignedAction[i]->antaObject;
										LOGMSG(F("[TaskManager]"), F("OK: Added action to queue @"), String(current_ptr), String(actionchain->assignedAction[i]->antaObject->getTitle()), "");
									}
									else {
										queue[start_ptr][start_task] = NULL;
										LOGMSG(F("[TaskManager]"), F("ERROR: Antagonist Object missing."), F("Removed Start Action from"), start_ptr, start_task);
									}
									current_ptr = getNextPositionFrom(current_ptr, 0); //Allow Parallel Tasks -> 0
									break;
								}
							}
							break;
						}
					}
				}
			}
			else break; //No Action No Effort -> Break
		}
	}
	else {
		LOGMSG(F("[TaskManager]"), F("ERROR: Could not find spot for all tasks of Actionchain."), String(actionchain->getTitle()), F("Current # of parallel tasks"), String(PARALLELTASKS));
	}
}

void TaskManager::execute()
{
	//LOGDEBUG(F("[TaskManager]"), F("execute()"), F("OK: Taskpointer @"), String(task_ptr), F("of"), String(TASKBUFFER));
	for (uint8_t i = 0; i < PARALLELTASKS; i++) {
		if (queue[task_ptr][i] != NULL) {
			LOGMSG(F("[TaskManager]"), F("OK: Executing task @"), String(task_ptr), String(queue[task_ptr][i]->getTitle()), "");
		
			queue[task_ptr][i]->execute();
			queue[task_ptr][i] = NULL;
		}
	}
	//Move Pointer forward
	next();
}