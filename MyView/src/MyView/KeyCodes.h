#pragma once

/*! @name Key and button actions
 *  @{ */
 /*! @brief The key or mouse button was released.
  *
  *  The key or mouse button was released.
  *
  *  @ingroup input
  */
#define MV_RELEASE                0
  /*! @brief The key or mouse button was pressed.
   *
   *  The key or mouse button was pressed.
   *
   *  @ingroup input
   */
#define MV_PRESS                  1
   /*! @brief The key was held down until it repeated.
	*
	*  The key was held down until it repeated.
	*
	*  @ingroup input
	*/
#define MV_REPEAT                 2


	 /*! @ingroup input
	  */
#define MV_KEY_UNKNOWN            -1

	  /*! @} */

	  /*! @defgroup keys Keyboard key tokens
	   *  @brief Keyboard key tokens.
	   *
	   *  See [key input](@ref input_key) for how these are used.
	   *
	   *  These key codes are inspired by the _USB HID Usage Tables v1.12_ (p. 53-60),
	   *  but re-arranged to map to 7-bit ASCII for printable keys (function keys are
	   *  put in the 256+ range).
	   *
	   *  The naming of the key codes follow these rules:
	   *   - The US keyboard layout is used
	   *   - Names of printable alphanumeric characters are used (e.g. "A", "R",
	   *     "3", etc.)
	   *   - For non-alphanumeric characters, Unicode:ish names are used (e.g.
	   *     "COMMA", "LEFT_SQUARE_BRACKET", etc.). Note that some names do not
	   *     correspond to the Unicode standard (usually for brevity)
	   *   - Keys that lack a clear US mapping are named "WORLD_x"
	   *   - For non-printable keys, custom names are used (e.g. "F4",
	   *     "BACKSPACE", etc.)
	   *
	   *  @ingroup input
	   *  @{
	   */

	   /* Printable keys */
#define MV_KEY_SPACE              32
#define MV_KEY_APOSTROPHE         39  /* ' */
#define MV_KEY_COMMA              44  /* , */
#define MV_KEY_MINUS              45  /* - */
#define MV_KEY_PERIOD             46  /* . */
#define MV_KEY_SLASH              47  /* / */
#define MV_KEY_0                  48
#define MV_KEY_1                  49
#define MV_KEY_2                  50
#define MV_KEY_3                  51
#define MV_KEY_4                  52
#define MV_KEY_5                  53
#define MV_KEY_6                  54
#define MV_KEY_7                  55
#define MV_KEY_8                  56
#define MV_KEY_9                  57
#define MV_KEY_SEMICOLON          59  /* ; */
#define MV_KEY_EQUAL              61  /* = */
#define MV_KEY_A                  65
#define MV_KEY_B                  66
#define MV_KEY_C                  67
#define MV_KEY_D                  68
#define MV_KEY_E                  69
#define MV_KEY_F                  70
#define MV_KEY_G                  71
#define MV_KEY_H                  72
#define MV_KEY_I                  73
#define MV_KEY_J                  74
#define MV_KEY_K                  75
#define MV_KEY_L                  76
#define MV_KEY_M                  77
#define MV_KEY_N                  78
#define MV_KEY_O                  79
#define MV_KEY_P                  80
#define MV_KEY_Q                  81
#define MV_KEY_R                  82
#define MV_KEY_S                  83
#define MV_KEY_T                  84
#define MV_KEY_U                  85
#define MV_KEY_V                  86
#define MV_KEY_W                  87
#define MV_KEY_X                  88
#define MV_KEY_Y                  89
#define MV_KEY_Z                  90
#define MV_KEY_LEFT_BRACKET       91  /* [ */
#define MV_KEY_BACKSLASH          92  /* \ */
#define MV_KEY_RIGHT_BRACKET      93  /* ] */
#define MV_KEY_GRAVE_ACCENT       96  /* ` */
#define MV_KEY_WORLD_1            161 /* non-US #1 */
#define MV_KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define MV_KEY_ESCAPE             256
#define MV_KEY_ENTER              257
#define MV_KEY_TAB                258
#define MV_KEY_BACKSPACE          259
#define MV_KEY_INSERT             260
#define MV_KEY_DELETE             261
#define MV_KEY_RIGHT              262
#define MV_KEY_LEFT               263
#define MV_KEY_DOWN               264
#define MV_KEY_UP                 265
#define MV_KEY_PAGE_UP            266
#define MV_KEY_PAGE_DOWN          267
#define MV_KEY_HOME               268
#define MV_KEY_END                269
#define MV_KEY_CAPS_LOCK          280
#define MV_KEY_SCROLL_LOCK        281
#define MV_KEY_NUM_LOCK           282
#define MV_KEY_PRINT_SCREEN       283
#define MV_KEY_PAUSE              284
#define MV_KEY_F1                 290
#define MV_KEY_F2                 291
#define MV_KEY_F3                 292
#define MV_KEY_F4                 293
#define MV_KEY_F5                 294
#define MV_KEY_F6                 295
#define MV_KEY_F7                 296
#define MV_KEY_F8                 297
#define MV_KEY_F9                 298
#define MV_KEY_F10                299
#define MV_KEY_F11                300
#define MV_KEY_F12                301
#define MV_KEY_F13                302
#define MV_KEY_F14                303
#define MV_KEY_F15                304
#define MV_KEY_F16                305
#define MV_KEY_F17                306
#define MV_KEY_F18                307
#define MV_KEY_F19                308
#define MV_KEY_F20                309
#define MV_KEY_F21                310
#define MV_KEY_F22                311
#define MV_KEY_F23                312
#define MV_KEY_F24                313
#define MV_KEY_F25                314
#define MV_KEY_KP_0               320
#define MV_KEY_KP_1               321
#define MV_KEY_KP_2               322
#define MV_KEY_KP_3               323
#define MV_KEY_KP_4               324
#define MV_KEY_KP_5               325
#define MV_KEY_KP_6               326
#define MV_KEY_KP_7               327
#define MV_KEY_KP_8               328
#define MV_KEY_KP_9               329
#define MV_KEY_KP_DECIMAL         330
#define MV_KEY_KP_DIVIDE          331
#define MV_KEY_KP_MULTIPLY        332
#define MV_KEY_KP_SUBTRACT        333
#define MV_KEY_KP_ADD             334
#define MV_KEY_KP_ENTER           335
#define MV_KEY_KP_EQUAL           336
#define MV_KEY_LEFT_SHIFT         340
#define MV_KEY_LEFT_CONTROL       341
#define MV_KEY_LEFT_ALT           342
#define MV_KEY_LEFT_SUPER         343
#define MV_KEY_RIGHT_SHIFT        344
#define MV_KEY_RIGHT_CONTROL      345
#define MV_KEY_RIGHT_ALT          346
#define MV_KEY_RIGHT_SUPER        347
#define MV_KEY_MENU               348

#define MV_KEY_LAST               MV_KEY_MENU

/*! @} */

/*! @defgroup mods Modifier key flags
 *  @brief Modifier key flags.
 *
 *  See [key input](@ref input_key) for how these are used.
 *
 *  @ingroup input
 *  @{ */

 /*! @brief If this bit is set one or more Shift keys were held down.
  *
  *  If this bit is set one or more Shift keys were held down.
  */
#define MV_MOD_SHIFT           0x0001
  /*! @brief If this bit is set one or more Control keys were held down.
   *
   *  If this bit is set one or more Control keys were held down.
   */
#define MV_MOD_CONTROL         0x0002
   /*! @brief If this bit is set one or more Alt keys were held down.
	*
	*  If this bit is set one or more Alt keys were held down.
	*/
#define MV_MOD_ALT             0x0004
	/*! @brief If this bit is set one or more Super keys were held down.
	 *
	 *  If this bit is set one or more Super keys were held down.
	 */
#define MV_MOD_SUPER           0x0008
	 /*! @brief If this bit is set the Caps Lock key is enabled.
	  *
	  *  If this bit is set the Caps Lock key is enabled and the @ref
	  *  MV_LOCK_KEY_MODS input mode is set.
	  */
#define MV_MOD_CAPS_LOCK       0x0010
	  /*! @brief If this bit is set the Num Lock key is enabled.
	   *
	   *  If this bit is set the Num Lock key is enabled and the @ref
	   *  MV_LOCK_KEY_MODS input mode is set.
	   */
#define MV_MOD_NUM_LOCK        0x0020

	   /*! @} */

	   /*! @defgroup buttons Mouse buttons
		*  @brief Mouse button IDs.
		*
		*  See [mouse button input](@ref input_mouse_button) for how these are used.
		*
		*  @ingroup input
		*  @{ */
#define MV_MOUSE_BUTTON_1         0
#define MV_MOUSE_BUTTON_2         1
#define MV_MOUSE_BUTTON_3         2
#define MV_MOUSE_BUTTON_4         3
#define MV_MOUSE_BUTTON_5         4
#define MV_MOUSE_BUTTON_6         5
#define MV_MOUSE_BUTTON_7         6
#define MV_MOUSE_BUTTON_8         7
#define MV_MOUSE_BUTTON_LAST      MV_MOUSE_BUTTON_8
#define MV_MOUSE_BUTTON_LEFT      MV_MOUSE_BUTTON_1
#define MV_MOUSE_BUTTON_RIGHT     MV_MOUSE_BUTTON_2
#define MV_MOUSE_BUTTON_MIDDLE    MV_MOUSE_BUTTON_3

