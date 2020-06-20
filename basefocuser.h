/*
 * RapiSW project.
 *
 * The startingpoint of this project was the INDI Developers Manual Tutorial #5, author Jasem Mutlaq.
 * 
 * This file is part of the RapiSW project.
 * Copyright (c) 2020 Othmar Ehrhardt
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.


*/

#pragma once

#include "indifocuser.h"

class BaseFocuser : public INDI::Focuser
{
  public:
    BaseFocuser(char *thisName);
    ~BaseFocuser() override = default;
    bool ISNewSwitch(const char *dev, const char *name, ISState *states, char *names[], int n) override;
    bool ISNewText(const char *dev, const char *name, char *texts[], char *names[], int n) override;
    void ISGetProperties(const char *dev) override;
    bool ISNewNumber(const char *dev, const char *name, double values[], char *names[], int n) override;
    bool ISNewBLOB(const char *dev, const char *name, int sizes[], int blobsizes[], char *blobs[], char *formats[], char *names[], int n) override;
    const char *getDefaultName() override;

  protected:
    // General device functions
    bool Connect();
    bool Disconnect();
    
    bool initProperties();
    bool updateProperties();
    virtual bool saveConfigItems(FILE *fp);
    
    virtual IPState MoveFocuser(FocusDirection dir, int speed, uint16_t duration) override;
    virtual IPState MoveAbsFocuser(uint32_t targetTicks) override;
    virtual IPState MoveRelFocuser(FocusDirection dir, uint32_t ticks) override;
    virtual bool SetFocuserSpeed(int speed) override;

    virtual bool SetFocuserBacklash(int32_t steps) override;
    virtual bool SetFocuserBacklashEnabled(bool enabled) override;

  private:
    char deviceName[32];
  
    ISwitch Outlet1S[2];
    ISwitchVectorProperty Outlet1SP;
    
    ISwitch Outlet2S[2];
    ISwitchVectorProperty Outlet2SP;
    
    ITextVectorProperty Outlet1NameTP;
    IText Outlet1NameT[1] {};
    
    ITextVectorProperty Outlet2NameTP;
    IText Outlet2NameT[1] {};
    
    INumberVectorProperty Outlet3NP;
    INumber Outlet3N[1];
        
};
