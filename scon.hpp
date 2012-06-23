//Serial CONnection header file

#include "LogController.hpp"

void open_port(LogController *logger);
/*
 * open_port() opens the serial port and sets the options.
 *
 * Has internal logging for status
 *
 */

void close_port(LogController* logger);
/*
 * close_port() closes the serial port.
 *
 *
 */

void kick_coil(int, int);
/*
 * kick_coil sends a two byte command / coil + duration.
 *
 * To use: first int is coil (0 - 31) you wish to kick. Second int is duration (0-254)
 *
 * Example: kick_coil(3, 120);
 *
 */

void set_servo(int, int);
/*
 * set_servo sends a two byte command / servo + desired value.
 *
 * To use: first int is servo (0 - 31) you wish to set. Second int is position (0 - 128)
 *
 * Example: set_servo(2, 80);
 *
 */

void set_light(int, int, int);
/*
 * set_light sends a two byte command to changes lights. First byte is light number second byte is options and level.
 *
 * To use: First int is light valid values: 0 - 63
 *
 * Second int is option, valid values:
 * * 8  = blink
 * * 16 = Strobe +3
 * * 32 = pulsate
 *
 * Third int is level, valid values: 0 - 8 (expect 0 does nothing)
 *
 * Example: set_light(13, 8, 3);
 *
 * Sets the 13th light to blink at a level of 3.
 *
 */

void set_rgb(int, int, int, int, int, int);
/*
 * set_rgb sets the rbg left and right rgb lights. Sends 8 bytes (1 command , 1 EOL)
 *
 * To use: The first three ints are for the left side and second three ints are for the right. Each value is 0 - 254 RGB
 *
 * Example: set_rgb(0, 0, 200, 200, 0, 0);
 *
 * Sets the left side to blue and the right side to red.
 *
 */

void req_switches(void);
/*
 * Requests the switches from the other board.
 */

void req_cabinet(void);
/*
 * Requets the cabinet switches from the other board.
 */

void read_switches(void);
/*
 * Reads the serial buffer for switch op codes and processes them accordingly. Sets global arrray.
 */





