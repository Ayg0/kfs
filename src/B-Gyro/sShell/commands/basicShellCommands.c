# include "klibc/print.h"
# include "klibc/memory.h"
# include "terminal/tty.h"
# include "sshell/sshell.h"
# include "klibc/strings.h"

extern _command g_sshelCommands[MAX_COMMANDS];

void	clear(char *args) {
	char *arg;

	arg = strtok(args, " ");
	if (!strncmp(arg, "-h", 2) || !strncmp(arg, "--help", 6)) {
		VGA_PRINT("Clears the terminal screen.\n");
		return;
	}
	clearTTY(SCREEN_SIZE);
}

void	history(char *args) {
	char *arg;

	arg = strtok(args, " ");
	if (!strncmp(arg, "-h", 2) || !strncmp(arg, "--help", 6)) {
		VGA_PRINT("Displays the last %d history of commands for the current session.\n", MAX_HISTORY);
		return;
	}
	printHistory();
}


void	help(char *args) {
	char	*arg;

	arg = strtok(args, " ");
	if (arg) {
		if (!strncmp(arg, "-h", 2) || !strncmp(arg, "--help", 6)) {
			VGA_PRINT("Are you serious right now !!\n");
			return ;
		}
	}
	for (size_t i = 0; i < (AVAILABLE_COMMANDS - 1); i++) {
		VGA_PRINT("%s%s: \033[0m\n ", COLOR_CYAN, g_sshelCommands[i].name);
		// g_sshelCommands[i].func("-h");
	}
	
}

void	whoami(char *args) {
	if (args && *args) {
		VGA_PRINT("%sInvalid options `%s`\n%s", COLOR_RED, args, COLOR_RESET);
		return;
	}
	VGA_PRINT("%s\n", CURRENT_USER->username);
}