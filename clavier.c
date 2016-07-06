#include "main.h"
#include "systeme.h"

void intputtexteup(struct DIVERSsysteme *systeme, struct CONSOLE *console)
{

	char typeclavier = '1';

	switch (systeme->evenement.key.keysym.scancode)
	{
    case SDL_SCANCODE_TAB:
        console->active = false;
        SDL_FlushEvent(SDL_KEYDOWN);
        SDL_FlushEvent(SDL_KEYUP);
        break;
	case SDL_SCANCODE_ESCAPE:
		break;
	case SDL_SCANCODE_DOWN:
		break;
	case SDL_SCANCODE_UP:
		break;
	case SDL_SCANCODE_LEFT:
		break;
	case SDL_SCANCODE_RIGHT:
		break;
	case SDL_SCANCODE_A:
			if (typeclavier == '1')
			{
				addletter('q', console);
			}
			else if (typeclavier == '2')
			{
				addletter( 'a', console);
			}
			else if (typeclavier == '3')
			{
				addletter( 'a', console);
			}
		break;
	case SDL_SCANCODE_B:
			addletter( 'b', console);

		break;
	case SDL_SCANCODE_C:
			addletter( 'c', console);

		break;
	case SDL_SCANCODE_D:
			addletter( 'd', console);
		break;
	case SDL_SCANCODE_E:
			addletter( 'e', console);

		break;
	case SDL_SCANCODE_F:
			addletter( 'f', console);

		break;
	case SDL_SCANCODE_G:
			addletter( 'g', console);

		break;
	case SDL_SCANCODE_H:
			addletter( 'h', console);

		break;
	case SDL_SCANCODE_I:
			addletter( 'i', console);

		break;
	case SDL_SCANCODE_J:
			addletter( 'j', console);

		break;
	case SDL_SCANCODE_K:
			addletter( 'k', console);

		break;
	case SDL_SCANCODE_L:
			addletter( 'l', console);

		break;
	case SDL_SCANCODE_M:
			if (typeclavier == '1' && systeme->shiftactif == true)
			{
				addletter( '?', console);
			}
			else if (typeclavier == '1' && systeme->altactif == true)
			{
				addletter( '\0', console);
			}
			else if (typeclavier == '1')
			{
				addletter( ',', console);

		break;
	case SDL_SCANCODE_SEMICOLON:
			addletter( 'm', console);

		break;
	case SDL_SCANCODE_N:
			addletter( 'n', console);

		break;
	case SDL_SCANCODE_O:
			addletter( 'o', console);

		break;
	case SDL_SCANCODE_P:
			addletter( 'p', console);

		break;
	case SDL_SCANCODE_Q:
			if (typeclavier == '1')
			{
				addletter( 'a', console);
			}
			else if (typeclavier == '2')
			{
				addletter( 'q', console);
			}
			else if (typeclavier == '3')
			{
				addletter( 'q', console);
			}

		break;
	case SDL_SCANCODE_R:
			addletter( 'r', console);

		break;
	case SDL_SCANCODE_S:
			addletter( 's', console);

		break;
	case SDL_SCANCODE_T:
			addletter( 't', console);

		break;
	case SDL_SCANCODE_U:
			addletter( 'u', console);

		break;
	case SDL_SCANCODE_V:
			addletter( 'v', console);

		break;
	case SDL_SCANCODE_W:
			if (typeclavier == '1')
			{
				addletter( 'z', console);
			}
			else if (typeclavier == '2')
			{
				addletter( 'w', console);
			}
			else if (typeclavier == '3')
			{
				addletter( 'w', console);
			}
		break;
	case SDL_SCANCODE_X:
			addletter( 'x', console);

		break;
	case SDL_SCANCODE_Y:
			if (typeclavier == '1')
			{
				addletter( 'y', console);
			}
			else if (typeclavier == '2')
			{
				addletter( 'y', console);
			}
			else if (typeclavier == '3')
			{
				addletter( 'z', console);
            }
		break;
	case SDL_SCANCODE_Z:
			if (typeclavier == '1')
			{
				addletter( 'w', console);
			}
			else if (typeclavier == '2')
			{
				addletter( 'z', console);
			}
			else if (typeclavier == '3')
			{
				addletter( 'y', console);
			}

		break;
	case SDL_SCANCODE_0:
			if (typeclavier == '1' && systeme->shiftactif == true)
			{
				addletter( '0', console);
			}
			else if (typeclavier == '1' && systeme->altactif == true)
			{
				addletter( '@', console);
			}
			else if (typeclavier == '1')
			{
				addletter( 'à', console);
			}

		break;
	case SDL_SCANCODE_1:
			if (typeclavier == '1' && systeme->shiftactif == true)
			{
				addletter( '1', console);
			}
			else if (typeclavier == '1' && systeme->altactif == true)
			{
				addletter( '\0', console);
			}
			else if (typeclavier == '1')
			{
				addletter( '&', console);
			}

		break;
	case SDL_SCANCODE_2:
			if (typeclavier == '1' && systeme->shiftactif == true)
			{
				addletter( '2', console);
			}
			else if (typeclavier == '1' && systeme->altactif == true)
			{
				addletter( '~', console);
			}
			else if (typeclavier == '1')
			{
				addletter( 'é', console);
			}

		break;
	case SDL_SCANCODE_3:
				if (typeclavier == '1' && systeme->shiftactif == true)
				{
					addletter( '3', console);
				}
				else if (typeclavier == '1' && systeme->altactif == true)
				{
					addletter( '#', console);
				}
				else if (typeclavier == '1')
				{
					addletter( '"', console);
				}

		break;
	case SDL_SCANCODE_4:
			if (typeclavier == '1' && systeme->shiftactif == true)
			{
				addletter( '4', console);
			}
			else if (typeclavier == '1' && systeme->altactif == true)
			{
				addletter( '{', console);
			}
			else if (typeclavier == '1')
			{
				addletter( '\\', console);
			}

		break;
	case SDL_SCANCODE_5:
			if (typeclavier == '1' && systeme->shiftactif == true)
			{
				addletter( '5', console);
			}
			else if (typeclavier == '1' && systeme->altactif == true)
			{
				addletter( '[', console);
			}
			else if (typeclavier == '1')
			{
				addletter( '(', console);
			}

		break;
	case SDL_SCANCODE_6:
			if (typeclavier == '1' && systeme->shiftactif == true)
			{
				addletter( '6', console);
			}
			else if (typeclavier == '1' && systeme->altactif == true)
			{
				addletter( '|', console);
			}
			else if (typeclavier == '1')
			{
				addletter( '-', console);
			}

		break;
	case SDL_SCANCODE_7:
			if (typeclavier == '1' && systeme->shiftactif == true)
			{
				addletter( '7', console);
			}
			else if (typeclavier == '1' && systeme->altactif == true)
			{
				addletter( '`', console);
			}
			else if (typeclavier == '1')
			{
				addletter( 'è', console);
			}

		break;
	case SDL_SCANCODE_8:
			if (typeclavier == '1' && systeme->shiftactif == true)
			{
				addletter( '8', console);
			}
			else if (typeclavier == '1' && systeme->altactif == true)
			{
				addletter( '\\', console);
			}
			else if (typeclavier == '1')
			{
				addletter( '_', console);
			}

		break;
	case SDL_SCANCODE_9:
			if (typeclavier == '1' && systeme->shiftactif == true)
			{
				addletter( '9', console);
			}
			else if (typeclavier == '1' && systeme->altactif == true)
			{
				addletter( '^', console);
			}
			else if (typeclavier == '1')
			{
				addletter( 'ç', console);
			}

		break;
	case SDL_SCANCODE_MINUS:
			if (typeclavier == '1' && systeme->shiftactif == true)
			{
				addletter( '°', console);
			}
			else if (typeclavier == '1' && systeme->altactif == true)
			{
				addletter( ']', console);
			}
			else if (typeclavier == '1')
			{
				addletter( ')', console);
			}

		break;
	case SDL_SCANCODE_EQUALS:
			if (typeclavier == '1' && systeme->shiftactif == true)
			{
				addletter( '+', console);
			}
			else if (typeclavier == '1' && systeme->altactif == true)
			{
				addletter( '}', console);
			}
			else if (typeclavier == '1')
			{
				addletter( '=', console);
			}
			break;
		case SDL_SCANCODE_LEFTBRACKET:
				if (typeclavier == '1' && systeme->shiftactif == true)
				{
					addletter( '¨', console);
				}
				else if (typeclavier == '1' && systeme->altactif == true)
				{
					addletter( '\0', console);
				}
				else if (typeclavier == '1')
				{
					addletter( '^', console);
				}
			break;
		case SDL_SCANCODE_RIGHTBRACKET:
				if (typeclavier == '1' && systeme->shiftactif == true)
				{
					addletter( '£', console);
				}
				else if (typeclavier == '1' && systeme->altactif == true)
				{
					addletter( '¤', console);
				}
				else if (typeclavier == '1')
				{
					addletter( '$', console);
				}
			break;
		case SDL_SCANCODE_APOSTROPHE:
				if (typeclavier == '1' && systeme->shiftactif == true)
				{
					addletter( '%', console);
				}
				else if (typeclavier == '1' && systeme->altactif == true)
				{
					addletter( '\0', console);
				}
				else if (typeclavier == '1')
				{
					addletter( 'ù', console);
				}
			break;
		case SDL_SCANCODE_COMMA:
				if (typeclavier == '1' && systeme->shiftactif == true)
				{
					addletter( '.', console);
				}
				else if (typeclavier == '1' && systeme->altactif == true)
				{
					addletter( '\0', console);
				}
				else if (typeclavier == '1')
				{
					addletter( ';', console);
				}
			break;
		case SDL_SCANCODE_PERIOD:
				if (typeclavier == '1' && systeme->shiftactif == true)
				{
					addletter( '/', console);
				}
				else if (typeclavier == '1' && systeme->altactif == true)
				{
					addletter( '\0', console);
				}
				else if (typeclavier == '1')
				{
					addletter( ':', console);
				}
			break;
		case SDL_SCANCODE_SLASH:
				if (typeclavier == '1' && systeme->shiftactif == true)
				{
					addletter( '§', console);
				}
				else if (typeclavier == '1' && systeme->altactif == true)
				{
					addletter( '\0', console);
				}
				else if (typeclavier == '1')
				{
					addletter( '!', console);
				}
			break;
		case SDL_SCANCODE_KP_0:
				addletter( '0', console);

			break;
		case SDL_SCANCODE_KP_1:
				addletter( '1', console);

			break;
		case SDL_SCANCODE_KP_2:
				addletter( '2', console);

			break;
		case SDL_SCANCODE_KP_3:
				addletter( '3', console);

			break;
		case SDL_SCANCODE_KP_4:
				addletter( '4', console);

			break;
		case SDL_SCANCODE_KP_5:
				addletter( '5', console);

			break;
		case SDL_SCANCODE_KP_6:
				addletter( '6', console);

			break;
		case SDL_SCANCODE_KP_7:
				addletter( '7', console);

			break;
		case SDL_SCANCODE_KP_8:
				addletter( '8', console);

			break;
		case SDL_SCANCODE_KP_9:
				addletter( '9', console);

			break;
		case SDL_SCANCODE_SPACE:
				addletter( ' ', console);

			break;
		case SDL_SCANCODE_BACKSPACE:
				removeletter(console);

			break;
		case SDL_SCANCODE_LSHIFT:
			systeme->shiftactif = false;
			break;
		case SDL_SCANCODE_RSHIFT:
			systeme->shiftactif = false;
			break;
		case SDL_SCANCODE_LALT:
			systeme->altactif = false;
			break;
		case SDL_SCANCODE_RALT:
			systeme->altactif = false;
			break;
        case SDL_SCANCODE_RETURN:
            say(console->tampon, console, systeme);
            sprintf(console->lastanswer, console->tampon);
            flushbuffer(console);
            console->answered = true;
            break;
		default:
			break;
		}
	}
}

void intputtextedown(struct DIVERSsysteme *systeme, struct CONSOLE *console)
{
	switch (systeme->evenement.key.keysym.scancode)
	{
	case SDL_SCANCODE_ESCAPE:
		break;
	case SDL_SCANCODE_DOWN:
		break;
	case SDL_SCANCODE_UP:
		break;
	case SDL_SCANCODE_LEFT:
		break;
	case SDL_SCANCODE_RIGHT:
		break;
    case SDL_SCANCODE_BACKSPACE:
        removeletter(console);
        break;
    case SDL_SCANCODE_LSHIFT:
        systeme->shiftactif = true;
        break;
    case SDL_SCANCODE_RSHIFT:
        systeme->shiftactif = true;
        break;
    case SDL_SCANCODE_LALT:
        systeme->altactif = true;
        break;
    case SDL_SCANCODE_RALT:
        systeme->altactif = true;
        break;
    case SDL_SCANCODE_RETURN:
        break;
    default:
        break;
    }
}


void pressdown(struct DIVERSsysteme *systeme)
{
    char typeclavier = '1';

	switch (systeme->evenement.key.keysym.scancode)
	{
    case SDL_SCANCODE_W:
        if (typeclavier == '1')
        {
            systeme->origine.y -= 10;
        }
    break;
    case SDL_SCANCODE_S:
        if (typeclavier == '1')
        {
            systeme->origine.y += 10;
        }
    break;
    case SDL_SCANCODE_A:
        if (typeclavier == '1')
        {
            systeme->origine.x += 10;
        }
    break;
    case SDL_SCANCODE_D:
        if (typeclavier == '1')
        {
            systeme->origine.x -= 10;
        }
    break;
    default:
        break;
    }
}

