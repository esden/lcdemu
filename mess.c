/* lcdemu - emulator of Matrix Orbital(R) lcd displays
   Copyright (C) 1999 Piotr Esden-Tempski

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include <syslog.h>
#include "mess.h"

void mess(int mess_kind, char *txt)
{
  
/*  switch (mess_kind)
  {
    case LCD_ERR:
      fprintf(stderr, "Error: %s", txt);
      exit_prog();
    break;
    case LCD_WRN:
      fprintf(stderr, "Warning: %s", txt);
    break;
    case LCD_DBG:
      fprintf(stderr, "Debug: %s", txt);
    break;
    case LCD_INF:
      fprintf(stderr, "Info: %s", txt);
    break;
  }
*/

  switch (mess_kind)
  {
    case LCD_ERR:
      openlog("lcdemu", LOG_PID|LOG_PERROR, LOG_USER);
      syslog(LOG_USER|LOG_ERR, "%s", txt);
      closelog();
      exit_prog();
    break;
    case LCD_WRN:
      openlog("lcdemu", LOG_PID|LOG_PERROR, LOG_USER);
      syslog(LOG_USER|LOG_WARNING, "%s", txt);
      closelog();
    break;
    case LCD_DBG:
      openlog("lcdemu", LOG_PID|LOG_PERROR, LOG_USER);
      syslog(LOG_USER|LOG_DEBUG, "%s", txt);
      closelog();
    break;
    case LCD_INF:
      openlog("lcdemu", LOG_PID|LOG_PERROR, LOG_USER);
      syslog(LOG_USER|LOG_INFO, "%s", txt);
      closelog();
    break;
  }
}
