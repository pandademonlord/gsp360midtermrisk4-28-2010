
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
	if(!(players.get(flags[FLAG_CURRENT_PLAYER])->isAI()))
	{
		switch(flags[FLAG_GAME_STATE])
		{
		case STATE_FORTIFY_TROOPS:
			switch(key)
			{
			case 'w'://increase # of troops to move
				flags[FLAG_PARAM_NUM] = flags[FLAG_PARAM_NUM] + 1;
				if(flags[FLAG_PARAM_NUM] > (board.get(flags[FLAG_PARAM_TER_ONE])->getTroops() - 1))
					flags[FLAG_PARAM_NUM] = (board.get(flags[FLAG_PARAM_TER_ONE])->getTroops() - 1);
				break;
			case 's'://decrease # of troops to move
				flags[FLAG_PARAM_NUM] = flags[FLAG_PARAM_NUM] - 1;
				if(flags[FLAG_PARAM_NUM] < 0)
					flags[FLAG_PARAM_NUM] = 0;
				break;
			case ' '://"enter" your final decision
				flags[FLAG_PARAMS_SET] = true;
				break;
			}
			break;
		}
		glutPostRedisplay();
	}
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
						flags[FLAG_PARAMS_SET] = true;
						break;
					case STATE_ATTACK_TO:
					case STATE_FORTIFY_TO:
						flags[FLAG_PARAM_TER_TWO] = flags[FLAG_CLICKED_TER];
						flags[FLAG_PARAMS_SET] = true;
						break;
					}
				}
				else//go to the next playing state if player doesn't want to attack or fortify
				{
					switch(flags[FLAG_GAME_STATE])
					{
					case STATE_FORTIFY_FROM:
						flags[FLAG_GAME_STATE] = STATE_AFTER_FORTIFY;
						flags[FLAG_UPDATE_GAME_STATE] = true;
						break;
					case STATE_ATTACK_FROM:
						flags[FLAG_GAME_STATE] = STATE_AFTER_ATK_B4_FORTIFY;
						flags[FLAG_UPDATE_GAME_STATE] = true;
						break;
					}
				}
				break;
			}
			//V2DF click = g_screen.convertPixelsToCartesian(V2DF(x,y));
			//printf("clicked at cartiesian coordinate %f, %f\n", click.getX(), click.getY());
			break;
		case GLUT_RIGHT_BUTTON:
			switch(state)
			{
			case STATE_MOUSE_BUTTON_DN:
				switch(flags[FLAG_GAME_STATE])
				{
				case STATE_ATTACK_TO:
					flags[FLAG_GAME_STATE] = STATE_ATTACK_FROM;
				case STATE_ATTACK_FROM:
					flags[FLAG_PARAMS_SET] = false;
					break;
				case STATE_FORTIFY_TO://un-do which territory player is getting troops from
					flags[FLAG_GAME_STATE] = STATE_FORTIFY_FROM;
				case STATE_FORTIFY_FROM:
					flags[STATE_FORTIFY_FROM] = false;
					break;
				}
				break;
			}
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
	//variables to hold card ID's
	short selectC1, selectC2, selectC3;
	//display # of cards player is holding
	printf("You have %d cards.\n", players.get(flags[FLAG_CURRENT_PLAYER])->getNumCards());
	//display all cards held by player, & display stats
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
	//only give troops if 3 cards make a set
	if(players.get(flags[FLAG_CURRENT_PLAYER])->isCardSet(deck.get(selectC1), deck.get(selectC2), deck.get(selectC3)))
	{
		//increase # of sets turned-in by 1
		flags[FLAG_CARD_SET] = flags[FLAG_CARD_SET] + 1;
		//give player troops according to what this set's # is
		switch(flags[FLAG_CARD_SET])
		{
		case CARD_SET_ONE:
			players.get(flags[FLAG_CURRENT_PLAYER])->addBonusTroops(BONUS_SET_ONE);
			break;
		case CARD_SET_TWO:
			players.get(flags[FLAG_CURRENT_PLAYER])->addBonusTroops(BONUS_SET_TWO);
			break;
		case CARD_SET_THREE:
			players.get(flags[FLAG_CURRENT_PLAYER])->addBonusTroops(BONUS_SET_THREE);
			break;
		case CARD_SET_FOUR:
			players.get(flags[FLAG_CURRENT_PLAYER])->addBonusTroops(BONUS_SET_FOUR);
			break;
		case CARD_SET_FIVE:
			players.get(flags[FLAG_CURRENT_PLAYER])->addBonusTroops(BONUS_SET_FIVE);
			break;
		case CARD_SET_SIX:
			players.get(flags[FLAG_CURRENT_PLAYER])->addBonusTroops(BONUS_SET_SIX);
			break;
		default:
			players.get(flags[FLAG_CURRENT_PLAYER])->addBonusTroops(BONUS_SET_SIX + ((flags[FLAG_CARD_SET] - CARD_SET_SIX) * BONUS_SET_AFTER_SIX));
		}
		//if this is the 1st set the player has turned-in this turn,
		//give the player 2 bonus troops if 1 of the card's territory
		//is owned by this player on the board
		if(flags[FLAG_FIRST_SET_IN_TURN])
		{
			if(players.get(flags[FLAG_CURRENT_PLAYER])->terCard(deck.get(selectC1),board))
				flags[FLAG_FIRST_SET_IN_TURN] = false;
			else if(players.get(flags[FLAG_CURRENT_PLAYER])->terCard(deck.get(selectC2),board))
				flags[FLAG_FIRST_SET_IN_TURN] = false;
			else if(players.get(flags[FLAG_CURRENT_PLAYER])->terCard(deck.get(selectC3),board))
				flags[FLAG_FIRST_SET_IN_TURN] = false;
		}
		//now that the cards have been discarded,
		//remove them from the player's hand
		deck.get(selectC1)->setOwnerID(CARD_DISCARDED);
		players.get(flags[FLAG_CURRENT_PLAYER])->removeCard();
		deck.get(selectC2)->setOwnerID(CARD_DISCARDED);
		players.get(flags[FLAG_CURRENT_PLAYER])->removeCard();
		deck.get(selectC3)->setOwnerID(CARD_DISCARDED);
		players.get(flags[FLAG_CURRENT_PLAYER])->removeCard();
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
			if(board.get(flags[FLAG_PARAM_TER_ONE])->getOwner() == OWNER_NONE)
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
			if(board.get(flags[FLAG_PARAM_TER_ONE])->getOwner() == players.get(flags[FLAG_CURRENT_PLAYER])->getID())
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
			//TODO: make AI player turn-in 1st recognized set
			if(players.get(flags[FLAG_CURRENT_PLAYER])->isAI())
			{
			}
			else
			{
				//if the player has 5+ cards, they MUST turn in a set
				if(players.get(flags[FLAG_CURRENT_PLAYER])->getNumCards() >= CARD_MAX_HAND)
				{
					do{
						printf("You have 5+ cards. You MUST turn in a set.\n\n");
						turnInCards();
					}while(players.get(flags[FLAG_CURRENT_PLAYER])->getNumCards() >= CARD_MAX_HAND);
					printf("You now have %d cards. Please go back to the Game Window.\n", players.get(flags[FLAG_CURRENT_PLAYER])->getNumCards());
					flags[FLAG_UPDATE_GAME_STATE] = true;
				}
				else
				{
					//if the player has less than 5 cards, turning-in cards is optional
					char ans;
					do{
						printf("Do you want to turn-in cards for Troops(Y/N)?\n");
						cin >> ans;
					}while(ans != 'y' && ans != 'Y' && ans != 'n' && ans != 'N');
					if(ans == 'y' || ans == 'Y')
						turnInCards();
					printf("You now have %d cards. Please go back to the Game Window.\n", players.get(flags[FLAG_CURRENT_PLAYER])->getNumCards());
					flags[FLAG_UPDATE_GAME_STATE] = true;
				}
			}
		}
		else
			flags[FLAG_UPDATE_GAME_STATE] = true;
		break;
	case STATE_PLACE_BONUS_TROOPS:
		flags[FLAG_UPDATE_GAME_STATE] = true;
		if(players.get(flags[FLAG_CURRENT_PLAYER])->getTroops() > 0)
			flags[FLAG_UPDATE_GAME_STATE] = false;
		if(flags[FLAG_UPDATE_GAME_STATE])
		{
			//save the current # owned territory, to check if playe gains new territory(s) from attacking
			//printf("Storing #Territories Conquered B4 Attacking.\n");
			flags[FLAG_PARAM_NUM] = players.get(flags[FLAG_CURRENT_PLAYER])->getConqueredT();
		}
		if(flags[FLAG_PARAMS_SET])
		{
			if(board.get(flags[FLAG_PARAM_TER_ONE])->getOwner() == players.get(flags[FLAG_CURRENT_PLAYER])->getID())
				players.get(flags[FLAG_CURRENT_PLAYER])->addToTerritory(board.get(flags[FLAG_PARAM_TER_ONE]));
			flags[FLAG_PARAMS_SET] = false;
		}
		break;
	case STATE_ATTACK_FROM:
		if(players.get(flags[FLAG_CURRENT_PLAYER])->canAttack(board))
		{
			if(flags[FLAG_PARAMS_SET])
			{
				if(players.get(flags[FLAG_CURRENT_PLAYER])->ifOwns(board.get(flags[FLAG_PARAM_TER_ONE]))
					&& board.get(flags[FLAG_PARAM_TER_ONE])->haveTroopsToAttackFority()
					&& board.get(flags[FLAG_PARAM_TER_ONE])->isConnectedToEnemy())
				{
					flags[FLAG_UPDATE_GAME_STATE] = true;
				}
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
		if(flags[FLAG_PARAMS_SET])
		{
			if(!(players.get(flags[FLAG_CURRENT_PLAYER])->ifOwns(board.get(flags[FLAG_PARAM_TER_TWO])))
				&& board.get(flags[FLAG_PARAM_TER_TWO])->isConnectedTo(board.get(flags[FLAG_PARAM_TER_ONE])))
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
			printf("You have 6+ cards.\n");
			do{
				printf("You MUST turn cards until you have 4 or fewer.\n\n");
				turnInCards();
			}while(players.get(flags[FLAG_CURRENT_PLAYER])->getNumCards() > CARD_MAX_FR_OPPONENT);
			printf("You now have %d cards. Please go back to the Game Window.\n", players.get(flags[FLAG_CURRENT_PLAYER])->getNumCards());
			flags[FLAG_UPDATE_GAME_STATE] = true;
		}
		else
			flags[FLAG_UPDATE_GAME_STATE] = true;
		break;
	case STATE_PLACE_EXCESS_TROOPS:
		flags[FLAG_UPDATE_GAME_STATE] = true;
		if(players.get(flags[FLAG_CURRENT_PLAYER])->getTroops() > 0)
			flags[FLAG_UPDATE_GAME_STATE] = false;
		if(flags[FLAG_PARAMS_SET])
		{
			if(board.get(flags[FLAG_PARAM_TER_ONE])->getOwner() == players.get(flags[FLAG_CURRENT_PLAYER])->getID())
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
			if(flags[FLAG_PARAMS_SET])
			{
				if(players.get(flags[FLAG_CURRENT_PLAYER])->ifOwns(board.get(flags[FLAG_PARAM_TER_ONE]))
					&& board.get(flags[FLAG_PARAM_TER_ONE])->haveTroopsToAttackFority()
					&& board.get(flags[FLAG_PARAM_TER_ONE])->isConnectedToAlly())
				{
					flags[FLAG_UPDATE_GAME_STATE] = true;
				}
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
		if(flags[FLAG_PARAMS_SET])
		{
			if(players.get(flags[FLAG_CURRENT_PLAYER])->ifOwns(board.get(flags[FLAG_PARAM_TER_TWO]))
				&& board.get(flags[FLAG_PARAM_TER_TWO])->isConnectedTo(board.get(flags[FLAG_PARAM_TER_ONE])))
			{
				flags[FLAG_UPDATE_GAME_STATE] = true;
				flags[FLAG_PARAM_NUM] = 0;
			}
			flags[FLAG_PARAMS_SET] = false;
		}
		break;
	case STATE_FORTIFY_TROOPS:
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

