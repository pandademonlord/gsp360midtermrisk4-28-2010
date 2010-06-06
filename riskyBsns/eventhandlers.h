
/**
 * @param key what keyboard key was pressed (ASCII codes)
 * @param x/y where the mouse was at the time
 * @note: the following may be helpful:<code>
int state=glutGetModifiers();
if (state & GLUT_ACTIVE_SHIFT)	// shift is pressed</code>
 */
void keyboard(unsigned char key, int x, int y)
{
	//only allow input from keyboard to be read if user is NOT AI controlled (human)
	//glutPostRedisplay();
}

/** @param a_width/a_height new dimensions of the resized window */
void reshape(int a_width, int a_height)
{
	// have the graphics context calculate the changes...
	g_screen.reshape(a_width, a_height);
	// now, lets see it!
	glutPostRedisplay();
}

/** @param x/y the coordinate of where the mouse is being dragged */
void draggedMotion(int x, int y)
{
	//printf("mouse dragged (pixel location: %d, %d)\n",x,y);
}

bool isValidMove()
{
	switch(flags[FLAG_GAME_STATE])
	{
	case STATE_INIT_PLACEMENT_CLAIM:
		if(board.get(flags[FLAG_PARAM_TER_ONE])->getOwner() == OWNER_NONE)
			return true;
		break;
	case STATE_INIT_PLACEMENT_PLACE:
	case STATE_PLACE_BONUS_TROOPS:
	case STATE_PLACE_EXCESS_TROOPS:
		if(players.get(flags[FLAG_CURRENT_PLAYER])->ifOwns(board.get(flags[FLAG_PARAM_TER_ONE])))
			return true;
		break;
	case STATE_ATTACK_FROM:
		if(players.get(flags[FLAG_CURRENT_PLAYER])->ifOwns(board.get(flags[FLAG_PARAM_TER_ONE]))
					&& board.get(flags[FLAG_PARAM_TER_ONE])->haveTroopsToAttackFority()
					&& board.get(flags[FLAG_PARAM_TER_ONE])->isConnectedToEnemy())
		{
			return true;
		}
		break;
	case STATE_ATTACK_TO:
		if(!(players.get(flags[FLAG_CURRENT_PLAYER])->ifOwns(board.get(flags[FLAG_PARAM_TER_TWO])))
				&& board.get(flags[FLAG_PARAM_TER_TWO])->isConnectedTo(board.get(flags[FLAG_PARAM_TER_ONE])))
		{
			return true;
		}
		break;
	case STATE_FORTIFY_FROM:
		if(players.get(flags[FLAG_CURRENT_PLAYER])->ifOwns(board.get(flags[FLAG_PARAM_TER_ONE]))
					&& board.get(flags[FLAG_PARAM_TER_ONE])->haveTroopsToAttackFority()
					&& board.get(flags[FLAG_PARAM_TER_ONE])->isConnectedToAlly())
		{
			return true;
		}
		break;
	case STATE_FORTIFY_TO:
		if(players.get(flags[FLAG_CURRENT_PLAYER])->ifOwns(board.get(flags[FLAG_PARAM_TER_TWO]))
				&& board.get(flags[FLAG_PARAM_TER_TWO])->isConnectedTo(board.get(flags[FLAG_PARAM_TER_ONE])))
		{
			return true;
		}
		break;
	}
	return false;
}
bool isValidMoveHover()
{
	switch(flags[FLAG_GAME_STATE])
	{
	case STATE_INIT_PLACEMENT_CLAIM:
		if(board.get(flags[FLAG_CLICKED_TER])->getOwner() == OWNER_NONE)
			return true;
		break;
	case STATE_INIT_PLACEMENT_PLACE:
	case STATE_PLACE_BONUS_TROOPS:
	case STATE_PLACE_EXCESS_TROOPS:
		if(players.get(flags[FLAG_CURRENT_PLAYER])->ifOwns(board.get(flags[FLAG_CLICKED_TER])))
			return true;
		break;
	case STATE_ATTACK_FROM:
		if(players.get(flags[FLAG_CURRENT_PLAYER])->ifOwns(board.get(flags[FLAG_CLICKED_TER]))
					&& board.get(flags[FLAG_CLICKED_TER])->haveTroopsToAttackFority()
					&& board.get(flags[FLAG_CLICKED_TER])->isConnectedToEnemy())
		{
			return true;
		}
		break;
	case STATE_ATTACK_TO:
		if(!(players.get(flags[FLAG_CURRENT_PLAYER])->ifOwns(board.get(flags[FLAG_CLICKED_TER])))
				&& board.get(flags[FLAG_CLICKED_TER])->isConnectedTo(board.get(flags[FLAG_PARAM_TER_ONE])))
		{
			return true;
		}
		break;
	case STATE_FORTIFY_FROM:
		if(players.get(flags[FLAG_CURRENT_PLAYER])->ifOwns(board.get(flags[FLAG_CLICKED_TER]))
					&& board.get(flags[FLAG_CLICKED_TER])->haveTroopsToAttackFority()
					&& board.get(flags[FLAG_CLICKED_TER])->isConnectedToAlly())
		{
			return true;
		}
		break;
	case STATE_FORTIFY_TO:
		if(players.get(flags[FLAG_CURRENT_PLAYER])->ifOwns(board.get(flags[FLAG_CLICKED_TER]))
				&& board.get(flags[FLAG_CLICKED_TER])->isConnectedTo(board.get(flags[FLAG_PARAM_TER_ONE])))
		{
			return true;
		}
		break;
	}
	return false;
}

/** @param x/y the coordinate of where the mouse is */
void passiveMotion(int x, int y)
{
	//printf("mouse moved (pixel location: %d, %d)\n",x,y);
	flags[FLAG_WITHIN_AREA] = false;
	static short prev_state = false;
	V2DF click = g_screen.convertPixelsToCartesian(V2DF(x,y));
	for(int i = 0; i < board.size(); ++i)
	{
		if(board.get(i)->isWithin(click))
		{
			flags[FLAG_WITHIN_AREA] = true;
			flags[FLAG_CLICKED_TER] = i;
			//flags[FLAG_IS_VALID_INPUT] = isValidMove();
			if(isValidMoveHover())
			board.get(flags[FLAG_CLICKED_TER])->setColor(HIGHLIGHT_COLOR);
			break;
		}
		board.get(flags[FLAG_CLICKED_TER])->useContinentColor();
	}
	glutPostRedisplay();
	//printf("flags[FLAG_WITHIN_AREA] == %d, flags[FLAG_CLICKED_TER] == %d\n", flags[FLAG_WITHIN_AREA], flags[FLAG_CLICKED_TER]);
}

void mouse(int button, int state, int x, int y)
{
	//only allow input from mouse to be read if user is NOT AI controlled (human)
	if(!(players.get(flags[FLAG_CURRENT_PLAYER])->isAI()))
	{
		V2DF click = g_screen.convertPixelsToCartesian(V2DF(x,y));
		//printf("button %d, state %d,  x %d, y %d\n", button, state, x, y);
		switch(button)
		{
		case GLUT_LEFT_BUTTON:
			switch(state)
			{
			case STATE_MOUSE_BUTTON_DN:
				if(flags[FLAG_WITHIN_AREA])
				{
					switch(flags[FLAG_GAME_STATE])
					{
					case STATE_INIT_PLACEMENT_CLAIM:
					case STATE_INIT_PLACEMENT_PLACE:
					case STATE_PLACE_BONUS_TROOPS:
					case STATE_ATTACK_FROM:
					case STATE_FORTIFY_FROM:
					case STATE_PLACE_EXCESS_TROOPS:
						flags[FLAG_PARAM_TER_ONE] = flags[FLAG_CLICKED_TER];
						if(isValidMoveHover())
							board.get(flags[FLAG_PARAM_TER_ONE])->setColor(CLICKED_COLOR);
						flags[FLAG_PARAMS_SET] = true;
						break;
					case STATE_ATTACK_TO:
					case STATE_FORTIFY_TO:
						flags[FLAG_PARAM_TER_TWO] = flags[FLAG_CLICKED_TER];
						if(isValidMoveHover())
							board.get(flags[FLAG_PARAM_TER_TWO])->setColor(CLICKED_COLOR);
						flags[FLAG_PARAMS_SET] = true;
						break;
					}
					glutPostRedisplay();
				}
				else if(finishRect.isClickable(click))
				{
					switch(flags[FLAG_GAME_STATE])
					{
					case STATE_ATTACK_FROM:
						flags[FLAG_GAME_STATE] = STATE_AFTER_ATK_B4_FORTIFY;
						flags[FLAG_UPDATE_GAME_STATE] = true;
						break;
					case STATE_ATTACK_TO:
						flags[FLAG_GAME_STATE] = STATE_ATTACK_FROM;
						flags[STATE_FORTIFY_FROM] = false;
						break;
					case STATE_FORTIFY_FROM:
						flags[FLAG_GAME_STATE] = STATE_AFTER_FORTIFY;
						flags[FLAG_UPDATE_GAME_STATE] = true;
						break;
					case STATE_FORTIFY_TO:
						flags[FLAG_GAME_STATE] = STATE_FORTIFY_FROM;
						flags[STATE_FORTIFY_FROM] = false;
						break;
					case STATE_FORTIFY_TROOPS:
						flags[FLAG_PARAMS_SET] = true;
						break;
					}
				}
				else if(fortAdd.isClickable(click))
				{
					flags[FLAG_PARAM_NUM] = flags[FLAG_PARAM_NUM] + 1;
					if(flags[FLAG_PARAM_NUM] > (board.get(flags[FLAG_PARAM_TER_ONE])->getTroops() - 1))
						flags[FLAG_PARAM_NUM] = (board.get(flags[FLAG_PARAM_TER_ONE])->getTroops() - 1);
				}
				else if(fortSub.isClickable(click))
				{
					flags[FLAG_PARAM_NUM] = flags[FLAG_PARAM_NUM] - 1;
					if(flags[FLAG_PARAM_NUM] < 0)
						flags[FLAG_PARAM_NUM] = 0;
				}
				break;
			}
			//V2DF click = g_screen.convertPixelsToCartesian(V2DF(x,y));
			//printf("clicked at cartiesian coordinate %f, %f\n", click.getX(), click.getY());
			break;
		}
	}
}

void goToNextPlayer()
{
	flags[FLAG_CURRENT_PLAYER] = flags[FLAG_CURRENT_PLAYER] + 1;
	flags[FLAG_CURRENT_PLAYER] = flags[FLAG_CURRENT_PLAYER] % flags[FLAG_PLAYERS];
}
void turnInCards()
{
	printf("A SET consists of:\n");
	printf("1. 3 cards with the SAME unit, OR\n");
	printf("2. 1 card of each unit (Soldier, Horseman, Cannon), OR\n");
	printf("3. 1 WILD card & any 2 other cards\n\n");
	printf("You have %d cards.\n", players.get(flags[FLAG_CURRENT_PLAYER])->getNumCards());
	for(int i = 0; i < deck.size(); ++i)
	{
		if(deck.get(i)->getOwnerID() == players.get(flags[FLAG_CURRENT_PLAYER])->getID())
		{
			switch(deck.get(i)->getUnit())
			{
			case CARD_ID_SOLDIER:
				printf("cardID == %d, unitType == Soldier, territoryID == %d\n", deck.get(i)->getCardID(), deck.get(i)->getTerritoryID());
				break;
			case CARD_ID_HORSEMAN:
				printf("cardID == %d, unitType == Horseman, territoryID == %d\n", deck.get(i)->getCardID(), deck.get(i)->getTerritoryID());
				break;
			case CARD_ID_CANNON:
				printf("cardID == %d, unitType == Cannon, territoryID == %d\n", deck.get(i)->getCardID(), deck.get(i)->getTerritoryID());
				break;
			case CARD_ID_WILD:
				printf("cardID == %d, unitType == WILD\n", deck.get(i)->getCardID(), deck.get(i)->getTerritoryID());
				break;
			}
		}
	}
	printf("\n");
	short selectC1, selectC2, selectC3;
	do{
		printf("Enter ID of 1st card to turn-in\n");
		cin >> selectC1;
	}while(deck.get(selectC1)->getOwnerID() != players.get(flags[FLAG_CURRENT_PLAYER])->getID());
	do{
		printf("Enter ID of 2nd card to turn-in\n");
		cin >> selectC2;
	}while(deck.get(selectC1)->getOwnerID() != players.get(flags[FLAG_CURRENT_PLAYER])->getID());
	do{
		printf("Enter ID of 3rd card to turn-in\n");
		cin >> selectC3;
	}while(deck.get(selectC1)->getOwnerID() != players.get(flags[FLAG_CURRENT_PLAYER])->getID());
	printf("\n");
	if(players.get(flags[FLAG_CURRENT_PLAYER])->isCardSet(deck.get(selectC1), deck.get(selectC2), deck.get(selectC3)))
	{
		flags[FLAG_CARD_SET] = flags[FLAG_CARD_SET] + 1;
		players.get(flags[FLAG_CURRENT_PLAYER])->turnCardsTroops(flags[FLAG_CARD_SET]);
		if(flags[FLAG_FIRST_SET_IN_TURN])
		{
			if(players.get(flags[FLAG_CURRENT_PLAYER])->terCard(deck.get(selectC1),board))
				flags[FLAG_FIRST_SET_IN_TURN] = false;
			else if(players.get(flags[FLAG_CURRENT_PLAYER])->terCard(deck.get(selectC2),board))
				flags[FLAG_FIRST_SET_IN_TURN] = false;
			else if(players.get(flags[FLAG_CURRENT_PLAYER])->terCard(deck.get(selectC3),board))
				flags[FLAG_FIRST_SET_IN_TURN] = false;
		}
		deck.get(selectC1)->setOwnerID(CARD_DISCARDED);
		deck.get(selectC2)->setOwnerID(CARD_DISCARDED);
		deck.get(selectC3)->setOwnerID(CARD_DISCARDED);
		players.get(flags[FLAG_CURRENT_PLAYER])->removeCard();
		players.get(flags[FLAG_CURRENT_PLAYER])->removeCard();
		players.get(flags[FLAG_CURRENT_PLAYER])->removeCard();
	}
}
void turnInCardsAI()
{
	short selectC1, selectC2, selectC3;
	bool setFound = false;
	TemplateArray<Card *> cardsAI;
	for(int i = 0; i < deck.size(); ++i)
	{
		if(players.get(flags[FLAG_CURRENT_PLAYER])->getID() == deck.get(i)->getOwnerID())
			cardsAI.add(deck.get(i));
	}
	switch(cardsAI.size())
	{
	case CARD_NUM_IN_SET:
		if(players.get(flags[FLAG_CURRENT_PLAYER])->isCardSet(cardsAI.get(0), cardsAI.get(1), cardsAI.get(2)))
		{
			setFound = true;
			selectC1 = 0;
			selectC2 = 1;
			selectC3 = 2;
		}
		break;
	case CARD_MAX_FR_OPPONENT:
		if(players.get(flags[FLAG_CURRENT_PLAYER])->isCardSet(cardsAI.get(0), cardsAI.get(1), cardsAI.get(2)))
		{
			setFound = true;
			selectC1 = 0;
			selectC2 = 1;
			selectC3 = 2;
		}
		else if(players.get(flags[FLAG_CURRENT_PLAYER])->isCardSet(cardsAI.get(1), cardsAI.get(2), cardsAI.get(3)))
		{
			setFound = true;
			selectC1 = 1;
			selectC2 = 2;
			selectC3 = 3;
		}
		else if(players.get(flags[FLAG_CURRENT_PLAYER])->isCardSet(cardsAI.get(0), cardsAI.get(2), cardsAI.get(3)))
		{
			setFound = true;
			selectC1 = 0;
			selectC2 = 2;
			selectC3 = 3;
		}
		else if(players.get(flags[FLAG_CURRENT_PLAYER])->isCardSet(cardsAI.get(0), cardsAI.get(1), cardsAI.get(3)))
		{
			setFound = true;
			selectC1 = 0;
			selectC2 = 1;
			selectC3 = 3;
		}
		break;
	default:
		if(players.get(flags[FLAG_CURRENT_PLAYER])->isCardSet(cardsAI.get(0), cardsAI.get(1), cardsAI.get(2)))
		{
			setFound = true;
			selectC1 = 0;
			selectC2 = 1;
			selectC3 = 2;
		}
		else if(players.get(flags[FLAG_CURRENT_PLAYER])->isCardSet(cardsAI.get(1), cardsAI.get(2), cardsAI.get(3)))
		{
			setFound = true;
			selectC1 = 1;
			selectC2 = 2;
			selectC3 = 3;
		}
		else if(players.get(flags[FLAG_CURRENT_PLAYER])->isCardSet(cardsAI.get(0), cardsAI.get(2), cardsAI.get(3)))
		{
			setFound = true;
			selectC1 = 0;
			selectC2 = 2;
			selectC3 = 3;
		}
		else if(players.get(flags[FLAG_CURRENT_PLAYER])->isCardSet(cardsAI.get(0), cardsAI.get(1), cardsAI.get(3)))
		{
			setFound = true;
			selectC1 = 0;
			selectC2 = 1;
			selectC3 = 3;
		}
		else if(players.get(flags[FLAG_CURRENT_PLAYER])->isCardSet(cardsAI.get(0), cardsAI.get(1), cardsAI.get(4)))
		{
			setFound = true;
			selectC1 = 0;
			selectC2 = 1;
			selectC3 = 4;
		}
		else if(players.get(flags[FLAG_CURRENT_PLAYER])->isCardSet(cardsAI.get(0), cardsAI.get(2), cardsAI.get(4)))
		{
			setFound = true;
			selectC1 = 0;
			selectC2 = 2;
			selectC3 = 4;
		}
		else if(players.get(flags[FLAG_CURRENT_PLAYER])->isCardSet(cardsAI.get(0), cardsAI.get(3), cardsAI.get(4)))
		{
			setFound = true;
			selectC1 = 0;
			selectC2 = 3;
			selectC3 = 4;
		}
		else if(players.get(flags[FLAG_CURRENT_PLAYER])->isCardSet(cardsAI.get(1), cardsAI.get(2), cardsAI.get(4)))
		{
			setFound = true;
			selectC1 = 1;
			selectC2 = 2;
			selectC3 = 4;
		}
		else if(players.get(flags[FLAG_CURRENT_PLAYER])->isCardSet(cardsAI.get(1), cardsAI.get(3), cardsAI.get(4)))
		{
			setFound = true;
			selectC1 = 1;
			selectC2 = 3;
			selectC3 = 4;
		}
		else if(players.get(flags[FLAG_CURRENT_PLAYER])->isCardSet(cardsAI.get(2), cardsAI.get(3), cardsAI.get(4)))
		{
			setFound = true;
			selectC1 = 2;
			selectC2 = 3;
			selectC3 = 4;
		}
		break;
	}
	
	if(setFound)
	{
		flags[FLAG_CARD_SET] = flags[FLAG_CARD_SET] + 1;
		players.get(flags[FLAG_CURRENT_PLAYER])->turnCardsTroops(flags[FLAG_CARD_SET]);
		if(flags[FLAG_FIRST_SET_IN_TURN])
		{
			if(players.get(flags[FLAG_CURRENT_PLAYER])->terCard(deck.get(cardsAI.get(selectC1)->getCardID()),board))
				flags[FLAG_FIRST_SET_IN_TURN] = false;
			else if(players.get(flags[FLAG_CURRENT_PLAYER])->terCard(deck.get(cardsAI.get(selectC2)->getCardID()),board))
				flags[FLAG_FIRST_SET_IN_TURN] = false;
			else if(players.get(flags[FLAG_CURRENT_PLAYER])->terCard(deck.get(cardsAI.get(selectC3)->getCardID()),board))
				flags[FLAG_FIRST_SET_IN_TURN] = false;
		}
		deck.get(cardsAI.get(selectC1)->getCardID())->setOwnerID(CARD_DISCARDED);
		deck.get(cardsAI.get(selectC2)->getCardID())->setOwnerID(CARD_DISCARDED);
		deck.get(cardsAI.get(selectC3)->getCardID())->setOwnerID(CARD_DISCARDED);
		players.get(flags[FLAG_CURRENT_PLAYER])->removeCard();
		players.get(flags[FLAG_CURRENT_PLAYER])->removeCard();
		players.get(flags[FLAG_CURRENT_PLAYER])->removeCard();
		setFound = false;
	}
}
/** @return true if the game changed state and should redraw */
bool update(int a_ms)
{
	static short enemyPlayer = 0;
	switch(flags[FLAG_GAME_STATE])
	{
	case STATE_INIT_PLACEMENT_CLAIM:
		flags[FLAG_UPDATE_GAME_STATE] = true;
		for(int i = 0; i < board.size(); ++i)
		{
			if(board.get(i)->getOwner() == OWNER_NONE)
				flags[FLAG_UPDATE_GAME_STATE] = false;
		}
		if(players.get(flags[FLAG_CURRENT_PLAYER])->isAI() && !(flags[FLAG_UPDATE_GAME_STATE]))
		{
			flags[FLAG_PARAMS_SET] = true;
			flags[FLAG_PARAM_TER_ONE] = players.get(flags[FLAG_CURRENT_PLAYER])->getClaimID(board);
		}
		if(flags[FLAG_PARAMS_SET])
		{
			if(isValidMove())
			{
				players.get(flags[FLAG_CURRENT_PLAYER])->addLocal(board.get(flags[FLAG_PARAM_TER_ONE]));
				players.get(flags[FLAG_CURRENT_PLAYER])->addToTerritory(board.get(flags[FLAG_PARAM_TER_ONE]));
				flags[FLAG_UPDATE_PLAYER] = true;
			}
			flags[FLAG_PARAMS_SET] = false;
		}
		break;
	case STATE_INIT_PLACEMENT_PLACE:
		flags[FLAG_UPDATE_GAME_STATE] = true;
		for(int i = 0; i < players.size(); ++i)
		{
			if(players.get(flags[FLAG_CURRENT_PLAYER])->getTroops() > 0)
				flags[FLAG_UPDATE_GAME_STATE] = false;
		}
		if(players.get(flags[FLAG_CURRENT_PLAYER])->isAI() && !(flags[FLAG_UPDATE_GAME_STATE]))
		{
			flags[FLAG_PARAMS_SET] = true;
			flags[FLAG_PARAM_TER_ONE] = players.get(flags[FLAG_CURRENT_PLAYER])->getPlaceID(board);
		}
		if(flags[FLAG_PARAMS_SET])
		{
			if(isValidMove())
			{
				players.get(flags[FLAG_CURRENT_PLAYER])->addToTerritory(board.get(flags[FLAG_PARAM_TER_ONE]));
				flags[FLAG_UPDATE_PLAYER] = true;
			}
			flags[FLAG_PARAMS_SET] = false;
		}
		break;
	case STATE_GET_TROOPS_TERRITORY:
		flags[FLAG_UPDATE_PLAYER] = false;
		flags[FLAG_UPDATE_GAME_STATE] = true;
		players.get(flags[FLAG_CURRENT_PLAYER])->Reinforcements(board);
		break;
	case STATE_GET_TROOPS_CARDS:
		flags[FLAG_UPDATE_GAME_STATE] = false;
		if(players.get(flags[FLAG_CURRENT_PLAYER])->ownSet(deck))
		{
			//if(players.get(flags[FLAG_CURRENT_PLAYER])->isAI())
			//{
				do{
					//printf("Player %d has 5+ cards & MUST turn in a set.\n\n", (players.get(flags[FLAG_CURRENT_PLAYER])->getID() + 1));
					turnInCardsAI();
				}while(players.get(flags[FLAG_CURRENT_PLAYER])->getNumCards() >= CARD_MAX_HAND);
				//printf("Player %d now has %d cards. Please go back to the Game Window.\n", (players.get(flags[FLAG_CURRENT_PLAYER])->getID() + 1), players.get(flags[FLAG_CURRENT_PLAYER])->getNumCards());
				flags[FLAG_UPDATE_GAME_STATE] = true;
			/*}
			else
			{
				//if the player has 5+ cards, they MUST turn in a set
				if(players.get(flags[FLAG_CURRENT_PLAYER])->getNumCards() >= CARD_MAX_HAND)
				{
					do{
						printf("Player %d has 5+ cards & MUST turn in a set.\n\n", (players.get(flags[FLAG_CURRENT_PLAYER])->getID() + 1));
						turnInCards();
					}while(players.get(flags[FLAG_CURRENT_PLAYER])->getNumCards() >= CARD_MAX_HAND);
					printf("Player %d now has %d cards. Please go back to the Game Window.\n", (players.get(flags[FLAG_CURRENT_PLAYER])->getID() + 1), players.get(flags[FLAG_CURRENT_PLAYER])->getNumCards());
					flags[FLAG_UPDATE_GAME_STATE] = true;
				}
				else
				{
					//if the player has less than 5 cards, turning-in cards is optional
					char ans;
					do{
						printf("Player %d has a set with %d cards.\n", (players.get(flags[FLAG_CURRENT_PLAYER])->getID() + 1), players.get(flags[FLAG_CURRENT_PLAYER])->getNumCards());
						printf("Do you want to turn-in cards for Troops(Y/N)?\n");
						cin >> ans;
					}while(ans != 'y' && ans != 'Y' && ans != 'n' && ans != 'N');
					if(ans == 'y' || ans == 'Y')
						turnInCards();
					printf("Player %d now has %d cards. Please go back to the Game Window.\n", (players.get(flags[FLAG_CURRENT_PLAYER])->getID() + 1), players.get(flags[FLAG_CURRENT_PLAYER])->getNumCards());
					flags[FLAG_UPDATE_GAME_STATE] = true;
				}
			}*/
		}
		else
			flags[FLAG_UPDATE_GAME_STATE] = true;
		break;
	case STATE_PLACE_BONUS_TROOPS:
		flags[FLAG_UPDATE_GAME_STATE] = true;
		if(players.get(flags[FLAG_CURRENT_PLAYER])->getTroops() > 0)
			flags[FLAG_UPDATE_GAME_STATE] = false;
		if(players.get(flags[FLAG_CURRENT_PLAYER])->isAI() && !(flags[FLAG_UPDATE_GAME_STATE]))
		{
			flags[FLAG_PARAMS_SET] = true;
			flags[FLAG_PARAM_TER_ONE] = players.get(flags[FLAG_CURRENT_PLAYER])->getPlaceID(board);
		}
		if(flags[FLAG_UPDATE_GAME_STATE])
		{
			//save the current # owned territory, to check if playe gains new territory(s) from attacking
			//printf("Storing #Territories Conquered B4 Attacking.\n");
			flags[FLAG_PARAM_NUM] = players.get(flags[FLAG_CURRENT_PLAYER])->getConqueredT();
		}
		if(flags[FLAG_PARAMS_SET])
		{
			if(isValidMove())
				players.get(flags[FLAG_CURRENT_PLAYER])->addToTerritory(board.get(flags[FLAG_PARAM_TER_ONE]));
			flags[FLAG_PARAMS_SET] = false;
		}
		break;
	case STATE_ATTACK_FROM:
		if(players.get(flags[FLAG_CURRENT_PLAYER])->canAttack(board))
		{
			if(players.get(flags[FLAG_CURRENT_PLAYER])->isAI())
			{
				if(players.get(flags[FLAG_CURRENT_PLAYER])->continueAttack())
				{
					if(!(flags[FLAG_UPDATE_GAME_STATE]))
					{
						flags[FLAG_PARAMS_SET] = true;
						flags[FLAG_PARAM_TER_ONE] = players.get(flags[FLAG_CURRENT_PLAYER])->getAtkOriginID(board);
					}
				}
				else
				{
					flags[FLAG_GAME_STATE] = STATE_AFTER_ATK_B4_FORTIFY;
					flags[FLAG_UPDATE_GAME_STATE] = true;
				}
			}
			if(flags[FLAG_PARAMS_SET])
			{
				if(isValidMove())
					flags[FLAG_UPDATE_GAME_STATE] = true;
				flags[FLAG_PARAMS_SET] = false;
			}
		}
		else
		{
			flags[FLAG_GAME_STATE] = STATE_AFTER_ATK_B4_FORTIFY;
			flags[FLAG_UPDATE_GAME_STATE] = true;
		}
		break;
	case STATE_ATTACK_TO:
		if(players.get(flags[FLAG_CURRENT_PLAYER])->isAI() && !(flags[FLAG_UPDATE_GAME_STATE]))
		{
			flags[FLAG_PARAMS_SET] = true;
			flags[FLAG_PARAM_TER_TWO] = players.get(flags[FLAG_CURRENT_PLAYER])->getAtkTargetID(board, flags[FLAG_PARAM_TER_ONE]);
		}
		if(flags[FLAG_PARAMS_SET])
		{
			if(isValidMove())
			{
				enemyPlayer = board.get(flags[FLAG_PARAM_TER_TWO])->getOwner();
				flags[FLAG_UPDATE_GAME_STATE] = true;
			}
			flags[FLAG_PARAMS_SET] = false;
		}
		break;
	case STATE_ATTACK_BATTLE:
		flags[FLAG_UPDATE_GAME_STATE] = true;
		players.get(flags[FLAG_CURRENT_PLAYER])->combat(board.get(flags[FLAG_PARAM_TER_ONE]), board.get(flags[FLAG_PARAM_TER_TWO]), players.get(board.get(flags[FLAG_PARAM_TER_TWO])->getOwner()));
		break;
	case STATE_CAPTURE_TERRITORY:
		flags[FLAG_UPDATE_GAME_STATE] = true;
		//should be given a card?
		//(if #ter after attacking is MORE than #ter b4 attacking)
		if(players.get(flags[FLAG_CURRENT_PLAYER])->getConqueredT() > flags[FLAG_PARAM_NUM])
		{
			//should the player be allowed to draw a card
			if(flags[FLAG_DRAW_CARD])
			{
				players.get(flags[FLAG_CURRENT_PLAYER])->drawCardFromDeck(deck);
				//rules state that only 1 card can be drawn per turn,
				//do if the player captured more than 1 territory,
				//don't let them get cards for extra territories captured
				flags[FLAG_DRAW_CARD] = false;
			}
		}
		break;
	case STATE_ELIMINATE_ENEMY:
		flags[FLAG_UPDATE_GAME_STATE] = true;
		if(players.get(enemyPlayer)->getConqueredT() == 0)
			players.get(flags[FLAG_CURRENT_PLAYER])->exchangeCards(players.get(enemyPlayer), deck);
		break;
	case STATE_CHECK_IF_WON:
		flags[FLAG_UPDATE_GAME_STATE] = true;
		if(players.get(flags[FLAG_CURRENT_PLAYER])->getConqueredT() == TERRITORIES_TOTAL)
			flags[FLAG_GAME_STATE] = STATE_WIN;
		break;
	case STATE_EXCESS_CARDS:
		flags[FLAG_UPDATE_GAME_STATE] = false;
		if(players.get(flags[FLAG_CURRENT_PLAYER])->getNumCards() > CARD_MAX_HAND)
		{
			//printf("Player %d has 6+ cards.\n", (players.get(flags[FLAG_CURRENT_PLAYER])->getID() + 1));
			do{
				//printf("You MUST turn cards until you have 4 or fewer.\n\n");
				//if(players.get(flags[FLAG_CURRENT_PLAYER])->isAI())
				turnInCardsAI();
				//else
				//	turnInCards();
			}while(players.get(flags[FLAG_CURRENT_PLAYER])->getNumCards() > CARD_MAX_FR_OPPONENT);
			//printf("Player %d now has %d cards. Please go back to the Game Window.\n", (players.get(flags[FLAG_CURRENT_PLAYER])->getID() + 1), players.get(flags[FLAG_CURRENT_PLAYER])->getNumCards());
			flags[FLAG_UPDATE_GAME_STATE] = true;
		}
		else
			flags[FLAG_UPDATE_GAME_STATE] = true;
		break;
	case STATE_PLACE_EXCESS_TROOPS:
		flags[FLAG_UPDATE_GAME_STATE] = true;
		if(players.get(flags[FLAG_CURRENT_PLAYER])->getTroops() > 0)
			flags[FLAG_UPDATE_GAME_STATE] = false;
		if(players.get(flags[FLAG_CURRENT_PLAYER])->isAI() && !(flags[FLAG_UPDATE_GAME_STATE]))
		{
			flags[FLAG_PARAMS_SET] = true;
			flags[FLAG_PARAM_TER_ONE] = players.get(flags[FLAG_CURRENT_PLAYER])->getPlaceID(board);
		}
		if(flags[FLAG_PARAMS_SET])
		{
			if(isValidMove())
				players.get(flags[FLAG_CURRENT_PLAYER])->addToTerritory(board.get(flags[FLAG_PARAM_TER_ONE]));
			flags[FLAG_PARAMS_SET] = false;
		}
		break;
	case STATE_AFTER_ATK_B4_FORTIFY:
		flags[FLAG_UPDATE_GAME_STATE] = true;
		break;
	case STATE_FORTIFY_FROM:
		if(players.get(flags[FLAG_CURRENT_PLAYER])->canFortify(board))
		{
			if(players.get(flags[FLAG_CURRENT_PLAYER])->isAI() && !(flags[FLAG_UPDATE_GAME_STATE]))
			{
				flags[FLAG_PARAMS_SET] = true;
				flags[FLAG_PARAM_TER_ONE] = players.get(flags[FLAG_CURRENT_PLAYER])->getFortOriginID(board);
			}
			if(flags[FLAG_PARAMS_SET])
			{
				if(isValidMove())
					flags[FLAG_UPDATE_GAME_STATE] = true;
				flags[FLAG_PARAMS_SET] = false;
			}
		}
		else
		{
			flags[FLAG_GAME_STATE] = STATE_AFTER_FORTIFY;
			flags[FLAG_UPDATE_GAME_STATE] = true;
		}
		break;
	case STATE_FORTIFY_TO:
		if(players.get(flags[FLAG_CURRENT_PLAYER])->isAI() && !(flags[FLAG_UPDATE_GAME_STATE]))
		{
			flags[FLAG_PARAMS_SET] = true;
			flags[FLAG_PARAM_TER_TWO] = players.get(flags[FLAG_CURRENT_PLAYER])->getFortTargetID(board, flags[FLAG_PARAM_TER_ONE]);
		}
		if(flags[FLAG_PARAMS_SET])
		{
			if(isValidMove())
			{
				flags[FLAG_UPDATE_GAME_STATE] = true;
				flags[FLAG_PARAM_NUM] = 0;
			}
			flags[FLAG_PARAMS_SET] = false;
		}
		break;
	case STATE_FORTIFY_TROOPS:
		if(players.get(flags[FLAG_CURRENT_PLAYER])->isAI() && !(flags[FLAG_UPDATE_GAME_STATE]))
		{
			flags[FLAG_PARAMS_SET] = true;
			flags[FLAG_PARAM_NUM] = players.get(flags[FLAG_CURRENT_PLAYER])->getFortTroops(board, flags[FLAG_PARAM_TER_ONE]);
		}
		if(flags[FLAG_PARAMS_SET])
		{
			players.get(flags[FLAG_CURRENT_PLAYER])->fortify(board.get(flags[FLAG_PARAM_TER_ONE]), board.get(flags[FLAG_PARAM_TER_TWO]), flags[FLAG_PARAM_NUM]);
			flags[FLAG_UPDATE_GAME_STATE] = true;
			flags[FLAG_PARAMS_SET] = false;
		}
		break;
	case STATE_AFTER_FORTIFY:
		flags[FLAG_UPDATE_GAME_STATE] = true;
		break;
	case STATE_WIN:
		flags[FLAG_UPDATE_GAME_STATE] = false;
		break;
	}
	if(flags[FLAG_UPDATE_PLAYER])
	{
		goToNextPlayer();
		flags[FLAG_UPDATE_PLAYER] = false;
	}

	if(flags[FLAG_UPDATE_GAME_STATE])
	{
		if(flags[FLAG_GAME_STATE] == STATE_INIT_PLACEMENT_PLACE)
			flags[FLAG_CURRENT_PLAYER] = PLAYER_ONE;

		//handles special cases of how to update
		if(flags[FLAG_GAME_STATE] == STATE_AFTER_FORTIFY)
		{
			flags[FLAG_GAME_STATE] = STATE_GET_TROOPS_TERRITORY;
			flags[FLAG_DRAW_CARD] = true;
			flags[FLAG_FIRST_SET_IN_TURN] = true;
			do{
				goToNextPlayer();
			}while(players.get(flags[FLAG_CURRENT_PLAYER])->getConqueredT() == 0);
		}
		else if(flags[FLAG_GAME_STATE] != STATE_WIN)
		{
			switch(flags[FLAG_GAME_STATE])
			{
			case STATE_CHECK_IF_WON:
				flags[FLAG_GAME_STATE] = STATE_ATTACK_FROM;
				break;
			default:
				flags[FLAG_GAME_STATE] = flags[FLAG_GAME_STATE] + 1;
			}
		}
		flags[FLAG_UPDATE_GAME_STATE] = false;
		//printf("state == %d\n", flags[FLAG_GAME_STATE]);
		return true;
	}
	else
		return false;
}

