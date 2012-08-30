/**
 * @file	InputAccessor.cpp
 * implementation of InputAccessor.hpp	
 * 
 * @author	Chen rishan, Peking University	
 * @date	10/08/2007 
 *
 */

#include <string>
#include<cstdio>
#include<cstring>
#include<sys/termios.h>
#include<iostream>
#include<sys/types.h>
#include<sys/stat.h>
#include<cerrno>
#include<ctime>
#include "app/shell/include/InputAccessor.hpp"
//===================the use of readline library================= 
#if defined (HAVE_CONFIG_H)
#include <config.h>
#endif

#include <stdio.h>
#include <sys/types.h>

#ifdef HAVE_STDLIB_H
#  include <stdlib.h>
#else 
extern void exit();
#endif

#ifdef READLINE_LIBRARY
#  include "readline.h"
#  include "history.h"
#else
#  include <readline/readline.h>
#  include <readline/history.h>
#endif

extern HIST_ENTRY **history_list ();
//==================the use of readline library==================


using namespace std;
using namespace terminal;


static struct termios save_termios;
static enum{ RESET, RAW , CBREAK} ttystate= RESET;

InputAccessor::InputAccessor()
{
}

InputAccessor::~InputAccessor()
{
}

int InputAccessor::setTerminal()
{
	int fd = STDIN_FILENO;
	struct termios	buf;

	if (tcgetattr(fd, &save_termios) < 0)
		return(-1);

	buf = save_termios;	/* structure copy */

	buf.c_lflag &= ~(ECHO | ICANON);
					/* echo off, canonical mode off */

	buf.c_cc[VMIN] = 1;	/* Case B: 1 byte at a time, no timer */
	buf.c_cc[VTIME] = 0;

	if (tcsetattr(fd, TCSAFLUSH, &buf) < 0)
		return(-1);
	ttystate = CBREAK;
	return(0);
}

int InputAccessor::resetTerminal()
{
	int fd = STDIN_FILENO;
	if (ttystate != CBREAK && ttystate != RAW)
		return(0);

	if (tcsetattr(fd, TCSAFLUSH, &save_termios) < 0)
		return(-1);
	ttystate = RESET;
	return(0);
}

string InputAccessor::getCommand()
{
    return m_command;
}

string InputAccessor::getInput(const char* prompt)
{
    char* temp;

    temp = readline(prompt);

    if(*temp){
        add_history(temp);
    }
    string command(temp);
    free(temp);
    return command;
}
