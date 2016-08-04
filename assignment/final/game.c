/** @file   game.c
    @author K. W. McCall & S. O. Merrick
    @date   9 October
    @brief  Main Game Library
*/
#include "game.h"
#include "../fonts/font3x5_1.h"
#include "stdlib.h"

// Global characters
static Character rock = {"ROCK", ROCK, SCISSORS, LIZARD, ROCK_BITMAP};
static Character scissors = {"SCISSORS", SCISSORS, PAPER, LIZARD, SCISSORS_BITMAP};
static Character paper = {"PAPER", PAPER, ROCK, SPOCK, PAPER_BITMAP};
static Character lizard = {"LIZARD", LIZARD, PAPER, SPOCK, LIZARD_BITMAP};
static Character spock = {"SPOCK", SPOCK, ROCK, SCISSORS, SPOCK_BITMAP};
static Character antispock = {"NULL", 0, 0, 0, 0};

/** Parses a char to it's mapped Character
 *  @param the received char to be parsed
 *  @return returns the corresponding character or antispock
 * */
Character parse_char(char selected)
{
    switch(selected){
    case ROCK:
        return rock;
    case PAPER:
        return paper;
    case SCISSORS:
        return scissors;
    case LIZARD:
        return lizard;
    case SPOCK:
        return spock;
    }
    return antispock;
}

/** Determine end game screen
 * @param players score
 * */
void win_screen(uint16_t player_score){
    // If player was the winner
    if(player_score == 3){
        poll_text("  VICTORY!", PACER_RATE, MESSAGE_RATE);
    } else {
        poll_text("  BETTER LUCK NEXT TIME!", PACER_RATE, MESSAGE_RATE);
    }    
}

/** Send and receive characters,
 * uses a handshake to ensure both
 * parties receive
 * @param players selected character
 * @return opponents selected character
 * */
Character handshake(Character player){
    Character opponent=antispock;
    bool opponent_received = 0;
    char inbound='0';
    char outbound;
    
    // Send and received
    // Acknowledge that both have received with a handshake
    outbound = player.value;
    while (!opponent_received || opponent.value == antispock.value) {
        inbound = poll_ir(outbound);
        
        // Opponent has received our choice, acknowledge this
        if (inbound == '1') {   
            opponent_received = 1;
            outbound = '2'; 
        }
        
        // Opponent acknowledges that his choice has been received,
        // send our choice
        else if (inbound == '2') {
            outbound = player.value;
        }
        
        // Received something that might be a token
        else {
            
            // If we haven't already recveived the opponents token,
            // try to parse this one
            if (opponent.value == antispock.value){
                opponent = parse_char(inbound);
            }
            
            // If this is a token then acknowledge
            if (opponent.value != antispock.value){
                outbound = '1';
            }
        }
    }
    
    return opponent;
}


/** Prompts the user to select a character
 *  @return players chosen character
 * */
Character select_menu(void)
{
    Character options[] = {rock, paper, scissors, lizard, spock};
    int8_t current_selection = 0;
    uint16_t current_column = 0;
    char shake = '1';

    system_init ();
    navswitch_init ();
    ir_uart_init();
    pacer_init (PACER_RATE);
    
    // Wait for opponent
    while (shake != '0'){
        shake = poll_ir('0');
    }
    
    gobble();
    
    
    // Get selection
    while (1) {
        pacer_wait();
        navswitch_update();
        button_update();
        ledmat_display_column(options[current_selection].bitmap[current_column], current_column);
        current_column++;
        
        /*
        if (ir_uart_read_ready_p()){
            opponent = parse_char(ir_uart_getc());
        }
        */
               
        // Bitmap width is 5
        if (current_column > 4){
            current_column = 0;
        }
        
        // Character selection menu navigation     
        if (navswitch_push_event_p(NAVSWITCH_EAST) || navswitch_push_event_p(NAVSWITCH_NORTH))
        {
            current_selection++;
        }
        else if (navswitch_push_event_p(NAVSWITCH_WEST) || navswitch_push_event_p(NAVSWITCH_SOUTH))
        {
            current_selection--;
        }
        else if ((navswitch_push_event_p(NAVSWITCH_PUSH))){
            return options[current_selection];
        }
        current_selection = WRAP5(current_selection);
    }
}

/** Displays the main menu screen
 * */
void play_menu(void) {
    
    uint16_t player_score = 0;
    uint16_t opponent_score = 0;
    int8_t result = 0;
    Character player;
    Character opponent;
    char message[22];
    
    //Main game loop: First to 3
    while(player_score < 3 && opponent_score < 3){
        player = select_menu();
        tinygl_clear();
        opponent = handshake(player);
        memset(message, '\0', 22);
        // Compare choices; deduce winner
        switch(CMP(player, opponent))
        {
        case -1:
            // Loss
            opponent_score++;
            sprintf(message, "  %s BEATS %s", opponent.name, player.name);
            poll_text(message, PACER_RATE, 35);
            break;
        case 0:
            // Draw
            poll_text("  DRAW ", PACER_RATE, 25);
            break;
        case 1:
            // Win
            player_score++;
            sprintf(message, "  %s BEATS %s", player.name, opponent.name);
            poll_text(message, PACER_RATE, 35);
            break;
        }
    }
    win_screen(player_score);
}

/** Initializes and infinitely runs the program
 * 
 * */
int main (void)
{
    // Initializations
    system_init ();
    navswitch_init();
    button_init();
    ir_uart_init();
    pacer_init (PACER_RATE);
    poll_init();
    poll_set_event(BUTTON1, 0);
    led_set(LED1, 1);
    
    //Main Loop (OUTER)
    while (1)
    {
        pacer_wait();
        poll_text("  PRESS TO BEGIN RPSLS...", PACER_RATE, MESSAGE_RATE);
        play_menu();
    }
    return 0;
}
