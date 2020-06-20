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

class RapiSW : public INDI::Focuser
  public:
    RapiSW() = default;
    bool ISNewSwitch(const char *dev, const char *name, ISState *states, char *names[], int n);
    bool ISNewText(const char *dev, const char *name, char *texts[], char *names[], int n);
    virtual void ISGetProperties(const char *dev);

  protected:
    // General device functions
    bool Connect();
    bool Disconnect();
    const char *getDefaultName();
    bool initProperties();
    bool updateProperties();
    virtual bool saveConfigItems(FILE *fp);

  private:
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
