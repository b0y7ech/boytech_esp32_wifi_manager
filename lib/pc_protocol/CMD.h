/******************************************************************
 Project     : Esp32 Basic
 Libraries   : Esp32 Basic
 Author      : Tran Ngoc Bach
 Description : PC Communication Protocol
******************************************************************/

/*
 WiFi.h - esp32 Wifi support.
 Based on WiFi.h from Arduino WiFi shield library.
 Copyright (c) 2011-2014 Arduino.  All right reserved.
 Modified by Ivan Grokhotkov, December 2014

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef CMD_H
#define CMD_H

#include <stdint.h>
#include <Arduino.h>
#include <common.h>
#include <WiFi.h>

class CMD
{
    public:
        CMD();
        virtual ~CMD() {};
        void getCommand(char c);

};


#endif //CMD_H
