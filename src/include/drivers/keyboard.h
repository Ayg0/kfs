# pragma once

# include "klibc/types.h"
# include "arch/i386/cpu/descriptorTables.h"

# define MAX_KEYBOARD_BUFFER 200
# define MAX_HISTORY_SIZE 128
# define MAX_SHORTCUTS 50

# define KEYBOARD_DATA_PORT 0x60
# define KEYBOARD_STATUS_PORT 0x64

typedef enum kbdFlags {
	KBD_FLAG_SHIFT = 0,
	KBD_FLAG_CAPS,
	KBD_FLAG_CTRL,
	KBD_FLAG_ALT,
	KBD_FLAG_NUM,
	KBD_FLAG_NEWLINE
} e_kbdFlags;

typedef void (*onShortcutHandler)(void);
typedef void (*onKeyPressHanlder)(uint8_t);
typedef void (*onKeyReleaseHandler)(uint8_t);

typedef struct shortcut {
	char				key;
	uint8_t				flagedModifiers;
	onShortcutHandler	handler;
} _shortcut;

typedef struct kbdBuffer {
    uint8_t     buffer[MAX_KEYBOARD_BUFFER];
    uint32_t    index;
	uint32_t    size;
} _kbdBuffer;

typedef struct keyboardViews {
	uint8_t	*keys;
	uint8_t	*shiftedKeys;
} _keyboardViews;

typedef union kbdLayout {
	struct keyboardViews kbdV;
	uint8_t *views[2];
} _kbdLayout;

typedef struct keyboardData {
    _kbdLayout	        layout;
    uint8_t             kbdFlags;
	_kbdBuffer			*buffer;
    onKeyPressHanlder   keyPressHandler;
    onKeyReleaseHandler keyReleaseHandler;
} _keyboardData;

void	keyboardInit(void);
void	keyboardSetLayout(_kbdLayout layout);
void	keyboardSetBuffer(_kbdBuffer *currentTTYBuffer, bool clearBuffer);

// prompt functions
void	interruptPrompting(void);
char	*prompt(char *promtMessage, char *buffer);
void	keyboardClearBuffer(void);

// key press/release handlers
void	keyboardResetKeyPressHandler(void);
void	keyboardResetKeyReleaseHandler(void);
void	keyboardSetKeyPressHandler(onKeyPressHanlder handler);
void	keyboardSetKeyReleaseHandler(onKeyReleaseHandler handler);

// getters
uint8_t	keyboardGetScancode(uint8_t letter);
uint8_t	keyboardGetLetter(uint8_t scancode);

// shortcuts handling
void	shortcutsReset(void);
void	setShortcut(char *shortcutFormula, onShortcutHandler func);